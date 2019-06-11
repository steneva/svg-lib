#pragma once

#include <string>
#include <map>
#include <vector>
#include <regex>
#include <functional>
#include "TagAttributeCollection.h"

using namespace std;

namespace xml {

	class Tag
	{
	public:
		typedef vector<Tag>::iterator iterator;
		typedef vector<Tag>::const_iterator const_iterator;

	private:
		string name;
		vector<Tag> children;
		TagAttributeCollection attribute_collection;

	public:
		Tag(const string& name)
		{
			this->name = name;
			this->attribute_collection = TagAttributeCollection();
		}

		Tag(const string& name, const map<string, string>& attributes)
		{
			this->name = name;
			this->attribute_collection = TagAttributeCollection(attributes);
		}

		Tag(const Tag& other)
		{
			this->children = other.children;
			this->attribute_collection = other.attribute_collection;
			this->name = other.name;
		}

		Tag& operator=(const Tag& other)
		{
			if (this == &other)
				return *this;
			this->name = other.name;
			this->attribute_collection = other.attribute_collection;
			this->children = other.children;
			return *this;
		}

		static vector<Tag*> copy_children(const vector<Tag*> & children)
		{
			vector<Tag*> new_children;
			new_children.reserve(children.size());
			for (auto child : children)
			{
				new_children.push_back(new Tag(*child));
			}
			return new_children;
		}

		bool has_children() const
		{
			return !children.empty();
		}

		void set_name(const string & name)
		{
			this->name = name;
		}

		void add_child(const Tag & child_tag)
		{
			this->children.emplace_back(child_tag);
		}

		const map<string, string>& get_attributes() const
		{
			return this->attribute_collection.get_values();
		}

		TagAttributeCollection& attributes()
		{
			return this->attribute_collection;
		}

		string get_name() const
		{
			return name;
		}

		const_iterator children_begin() const
		{
			return children.begin();
		}

		iterator children_begin()
		{
			return children.begin();
		}

		const_iterator children_end() const
		{
			return children.end();
		}

		iterator children_end()
		{
			return children.end();
		}
	};
}