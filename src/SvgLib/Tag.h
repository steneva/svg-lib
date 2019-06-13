#pragma once

#include <string>
#include <vector>
#include <regex>
#include "TagAttributeCollection.h"

namespace xml
{
	class Tag
	{
	public:
		typedef std::vector<Tag>::iterator iterator;
		typedef std::vector<Tag>::const_iterator const_iterator;

	private:
		std::string _name;
		std::vector<Tag> _children;
		TagAttributeCollection _attributes;

	public:
		Tag(const std::string& name)
		{
			this->_name = name;
			this->_attributes = TagAttributeCollection();
		}

		Tag(const std::string& name, const std::vector<Attribute>& attributes)
		{
			this->_name = name;
			this->_attributes = TagAttributeCollection(attributes);
		}

		Tag(const std::string& name, const TagAttributeCollection& attributes)
		{
			this->_name = name;
			this->_attributes = attributes;
		}

		Tag(const Tag& other)
		{
			this->_children = other._children;
			this->_attributes = other._attributes;
			this->_name = other._name;
		}

		Tag& operator=(const Tag& other)
		{
			if (this == &other)
				return *this;
			this->_name = other._name;
			this->_attributes = other._attributes;
			this->_children = other._children;
			return *this;
		}

		bool has_children() const
		{
			return !_children.empty();
		}

		void set_name(const std::string& name)
		{
			this->_name = name;
		}

		void add_child(const Tag& child_tag)
		{
			this->_children.emplace_back(child_tag);
		}

		const std::vector<Attribute>& get_attributes() const
		{
			return this->_attributes.all();
		}

		TagAttributeCollection& attributes()
		{
			return this->_attributes;
		}

		std::string name() const
		{
			return _name;
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

		void to_xml(std::ostream& out)
		{
			to_xml_impl(out, *this);
		}

	private:
		void to_xml_impl(std::ostream& out, const Tag& root, int level = 0)
		{
			for (auto i = root.children_begin(); i != root.children_end(); ++i)
			{
				const xml::Tag& current_child = *i;
				const std::string tag_name = current_child.name();
				const std::string indent = std::string(level * 2, ' ');
				out << indent << "<" << tag_name << " ";

				for (auto attribute = current_child.get_attributes().begin();
				     attribute != current_child.get_attributes().end();
				     ++attribute)
				{
					out << attribute->name << "=\"" << attribute->value << "\"";
					if (attribute != current_child.get_attributes().end() - 1)
						out << " ";
				}

				if (current_child.has_children())
				{
					out << ">" << std::endl;
					to_xml_impl(out, current_child, level + 1);
					out << indent << "</" << tag_name << ">" << std::endl;
				}
				else
				{
					out << "/>" << std::endl;
				}
			}
		}
	};
}
