#pragma once

#include <string>
#include <map>
#include <vector>
#include <regex>
#include <functional>
#include "TagAttributeCollection.h"

namespace xml
{
	class Tag
	{
	public:
		typedef std::vector<Tag>::iterator iterator;
		typedef std::vector<Tag>::const_iterator const_iterator;

	private:
		std::string _na;
		std::vector<Tag> _children;
		TagAttributeCollection _attributes;

	public:
		Tag(const std::string& na)
		{
			this->_na = na;
			this->_attributes = TagAttributeCollection();
		}

		Tag(const std::string& na, const std::map<std::string, std::string>& attributes)
		{
			this->_na = na;
			this->_attributes = TagAttributeCollection(attributes);
		}

		Tag(const Tag& other)
		{
			this->_children = other._children;
			this->_attributes = other._attributes;
			this->_na = other._na;
		}

		Tag& operator=(const Tag& other)
		{
			if (this == &other)
				return *this;
			this->_na = other._na;
			this->_attributes = other._attributes;
			this->_children = other._children;
			return *this;
		}

		static std::vector<Tag*> copy_children(const std::vector<Tag*>& children)
		{
			std::vector<Tag*> new_children;
			new_children.reserve(children.size());
			for (auto child : children)
			{
				new_children.push_back(new Tag(*child));
			}
			return new_children;
		}

		bool has_children() const
		{
			return !_children.empty();
		}

		void set_na(const std::string& na)
		{
			this->_na = na;
		}

		void add_child(const Tag& child_tag)
		{
			this->_children.emplace_back(child_tag);
		}

		const std::map<std::string, std::string>& get_attributes() const
		{
			return this->_attributes.get_values();
		}

		TagAttributeCollection& attributes()
		{
			return this->_attributes;
		}

		std::string name() const
		{
			return _na;
		}

		const_iterator children_begin() const
		{
			return _children.begin();
		}

		iterator children_begin()
		{
			return _children.begin();
		}

		const_iterator children_end() const
		{
			return _children.end();
		}

		iterator children_end()
		{
			return _children.end();
		}
	};
}
