#pragma once

#include "Tag.h"
#include <stack>
#include<regex>
#include "TagToken.h"
#include <functional>

namespace xml
{
	class Parser
	{
	private:

		static void visit_matches(std::string text, const std::regex& regex,
		                          const std::function<void(std::smatch match)>& visitor)
		{
			auto tag_begin = std::sregex_iterator(text.begin(), text.end(), regex);
			auto tag_end = std::sregex_iterator();

			for (std::sregex_iterator i = tag_begin; i != tag_end; ++i)
			{
				visitor(*i);
			}
		}

		static TagAttributeCollection parse_attributes(std::string attributes_str)
		{
			TagAttributeCollection attributes;

			const auto on_match = [&attributes](std::smatch match)
			{
				const std::string name = match.str(1);
				const std::string value = match.str(2);

				attributes.set(name, value);
			};

			const std::regex attribute_regex(R"(([\w\-_]+)(?:=\"([^\"]*)\")?)");

			visit_matches(attributes_str, attribute_regex, on_match);
			return attributes;
		}

		static std::vector<detail::TagToken> tokenize(std::string x)
		{
			std::vector<detail::TagToken> tags;
			const std::regex tag_regex(R"((?:<(\w+)(.*?)(\/)?>)|(?:<\/(\w+)>))");

			auto tag_begin = std::sregex_iterator(x.begin(), x.end(), tag_regex);
			auto tag_end = std::sregex_iterator();

			for (std::sregex_iterator i = tag_begin; i != tag_end; ++i)
			{
				detail::TagToken::Type type = detail::TagToken::Type::OPENING;
				std::string identifier = i->str(1);
				if (!i->str(3).empty())
				{
					type = detail::TagToken::Type::SELF_CLOSING;
				}
				else if (!i->str(4).empty())
				{
					type = detail::TagToken::Type::CLOSING;
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

		static Tag construct_tree(const std::vector<detail::TagToken>& tokens)
		{
			std::stack<Tag> tree_stack;
			tree_stack.emplace("root");

			for (detail::TagToken token : tokens)
			{
				if (token.type == detail::TagToken::Type::CLOSING)
				{
					if (token.identifier != tree_stack.top().name())
					{
						throw std::runtime_error("Unmatching opening tag.");
					}

					if (tree_stack.size() == 1)
					{
						return tree_stack.top();
					}

					Tag child = tree_stack.top();
					tree_stack.pop();
					tree_stack.top().add_child(child);
				}
				else
				{
					TagAttributeCollection attributes = parse_attributes(token.attributes);
					Tag child(token.identifier, attributes);
					child.set_name(token.identifier);

					if (token.type == detail::TagToken::Type::OPENING)
					{
						tree_stack.push(child);
					}
					else if (token.type == detail::TagToken::Type::SELF_CLOSING)
					{
						tree_stack.top().add_child(child);
					}
				}
			}

			if (tree_stack.size() != 1)
			{
				throw std::runtime_error("Invalid x.");
			}

			Tag& root = tree_stack.top();
			return root;
		}

	public:
		static Tag parse(std::string x)
		{
			const std::vector<detail::TagToken> tokens = tokenize(x);
			return construct_tree(tokens);
		}
	};
}
