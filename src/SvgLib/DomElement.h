#pragma once

#include<functional>
#include "PropertyValue.h"
#include "Tag.h"
#include "DomElementCollection.h"
#include <string>

class DomElement
{
private:

	DomElementCollection _children;
	xml::Tag* _tag;
protected:

	xml::Tag* tag() const
	{
		return this->_tag;
	}

	template <typename T>
	T get(const std::string& name) const
	{
		static_assert(std::is_base_of<PropertyValue, T>::value, "T must derive from PropertyValue.");

		std::string attribute_value = tag()->attributes().get(name);
		T property_value;
		if (!attribute_value.empty())
		{
			property_value.parse(attribute_value);
		}
		return property_value;
	}

	template <typename T>
	void set(std::string name, const T value)
	{
		tag()->attributes().set(name, value.to_string());
	}

	template <typename T>
	void traverse_tree(std::function<void(T* element, DomElement* parent)> action)
	{
		static_assert(std::is_base_of<DomElement, T>::value, "T must derive from DomElement.");

		for (DomElement* current : this->children())
		{
			T* element = dynamic_cast<T*>(current);
			if (element != nullptr)
			{
				action(element, this);
			}

			current->traverse_tree(action);
		}
	}

	template <typename T>
	void traverse_tree(std::function<void(T* element)> action)
	{
		static_assert(std::is_base_of<DomElement, T>::value, "T must derive from DomElement.");

		traverse_tree<T>(
			[&action](T* element, DomElement* parent)
			{
				action(element);
			});
	}

	bool has_children() const
	{
		return !_children.empty();
	}

	static void to_xml_impl(std::ostream& out, DomElement* root, int level = 0)
	{
		const xml::Tag* tag = root->tag();
		const std::string tag_name = tag->name();
		const std::string indent = std::string(level * 4, ' ');
		out << indent << "<" << tag_name << " ";

		const std::vector<Attribute>& attributes = tag->get_attributes();

		for (auto attribute = attributes.begin();
			attribute != attributes.end();
			++attribute)
		{
			out << attribute->name << "=\"" << attribute->value << "\"";
			if (attribute != attributes.end() - 1)
				out << " ";
		}

		if (root->has_children())
		{
			out << ">" << std::endl;
			for (DomElement* child : root->children())
			{
				to_xml_impl(out, child, level + 1);
			}
			out << indent << "</" << tag_name << ">" << std::endl;
		}
		else
		{
			out << "/>" << std::endl;
		}
	}

public:
	DomElement(xml::Tag* tag)
		: _tag(tag)
	{
	}

	DomElement(const DomElement& other)
		: _tag(other._tag)
	{
		this->_children = other._children;
	}

	virtual ~DomElement() = default;

	virtual DomElement* clone() const
	{
		return new DomElement(*this);
	}

	DomElementCollection& children()
	{
		return this->_children;
	}

	std:: string to_xml()
	{
		std::stringstream content;
		to_xml_impl(content, this);
		return content.str();
	}
};
