#pragma once

#include "Tag.h"
#include <stack>
#include "TagToken.h"

namespace xml {

	class Parser
	{
	private:

		static void visit_matches(string text, const regex& regex, const std::function<void(smatch match)>& visitor)
		{
			auto tag_begin = sregex_iterator(text.begin(), text.end(), regex);
			auto tag_end = std::sregex_iterator();

			for (sregex_iterator i = tag_begin; i != tag_end; ++i) {
				visitor(*i);
			}
		}

		static map<string, string> parse_attributes(string attributes_str)
		{
			map<string, string> attributes;

			const auto on_match = [&attributes](smatch match) {
				const string name = match.str(1);
				const string value = match.str(2);

				attributes[name] = value;
			};

			const regex attribute_regex(R"(([\w\-_]+)(?:=\"([^\"]*)\")?)");

			visit_matches(attributes_str, attribute_regex, on_match);
			return attributes;
		}

		static vector<detail::TagToken> tokenize(string xml)
		{
			vector<detail::TagToken> tags;
			const regex tag_regex(R"((?:<(\w+)(.*?)(\/)?>)|(?:<\/(\w+)>))");

			auto tag_begin = sregex_iterator(xml.begin(), xml.end(), tag_regex);
			auto tag_end = std::sregex_iterator();

			for (sregex_iterator i = tag_begin; i != tag_end; ++i) {
				detail::TagToken::Type type = detail::TagToken::Type::OPENING;
				string identifier = i->str(1);
				if (!i->str(3).empty())
				{
					type = detail::TagToken::Type::SELF_CLOSING;
				}
				else if (!i->str(4).empty())
				{
					type = detail::TagToken::CLOSING;
					identifier = i->str(4);
				}

				detail::TagToken token = {
					identifier,
					type,
					i->str(2),
				};

				tags.push_back(token);
			}

			return tags;
		}

		static Tag construct_tree(const vector<detail::TagToken>& tokens)
		{
			stack<Tag> tree_stack;
			tree_stack.emplace("root");

			for (detail::TagToken token : tokens)
			{
				if (token.type == detail::TagToken::CLOSING)
				{
					if (token.identifier != tree_stack.top().get_name()) {
						throw std::runtime_error("Unmatching opening tag.");
					}

					if (tree_stack.size() == 1){
						return tree_stack.top();
					}

					Tag child = tree_stack.top();
					tree_stack.pop();
					tree_stack.top().add_child(child);
				}
				else
				{
					map<string, string> attributes_map = parse_attributes(token.attributes);
					Tag child(token.identifier, attributes_map);
					child.set_name(token.identifier);

					if (token.type == detail::TagToken::OPENING) {
						tree_stack.push(child);
					}
					else if (token.type == detail::TagToken::SELF_CLOSING)
					{
						tree_stack.top().add_child(child);
					}
				}
			}

			if (tree_stack.size() != 1)
			{
				throw std::runtime_error("Invalid xml.");
			}

			Tag& root = tree_stack.top();
			return root;
		}

	public:
		static Tag parse(string xml)
		{
			const vector<detail::TagToken> tokens = tokenize(xml);
			return construct_tree(tokens);
		}
	};

}