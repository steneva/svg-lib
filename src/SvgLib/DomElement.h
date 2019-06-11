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
	xml::Tag* _x_tag = nullptr;
protected:

	xml::Tag* tag() const
	{
		return this->_x_tag;
	}

	template <typename T>
	T get(const std::string& name) const
	{
		static_assert(std::is_base_of<PropertyValue, T>::value, "T must derive from PropertyValue.");

		std::string attribute_value = tag()->attributes().get(name);
		T property_value;
		if (attribute_value != "")
		{
			property_value.parse(attribute_value);
		}
		return property_value;
	}

	template <typename T>
	void set(std::string name, const T& value)
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

public:
	DomElement(xml::Tag& tag)
	{
		this->_x_tag = &tag;
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
};
