#pragma once
#include <string>
#include "Attribute.h"
#include <vector>
#include <stdexcept>

namespace xml
{
	class TagAttributeCollection
	{
	private:
		std::vector<Attribute> attributes;
	public:

		TagAttributeCollection() = default;

		TagAttributeCollection(std::vector<Attribute> attributes)
		{
			this->attributes = attributes;
		}

		TagAttributeCollection(const TagAttributeCollection& other)
		{
			this->attributes = other.attributes;
		}

		TagAttributeCollection& operator =(const TagAttributeCollection& other)
		{
			if (&other != this)
			{
				this->attributes = other.attributes;
			}

			return *this;
		}

		void set(std::string name, std::string value = "")
		{
			for (Attribute& current : attributes)
			{
				if (current.name == name)
				{
					current.value = value;
					return;
				}
			}

			const Attribute attribute(name, value);
			this->attributes.push_back(attribute);
		}

		std::string get(std::string name)
		{
			for (const Attribute& current : attributes)
			{
				if (current.name == name)
				{
					return current.value;
				}
			}

			return "";
		}

		const std::vector<Attribute>& all() const
		{
			return this->attributes;
		}

		void remove(std::string name)
		{
			std::vector<Attribute>::iterator attribute_to_remove;
			for (auto current = attributes.begin(); current != attributes.end(); ++current)
			{
				Attribute attribute = (*current);
				if (attribute.name == name)
				{
					attribute_to_remove = current;
				}
			}

			this->attributes.erase(attribute_to_remove);
		}

		std::vector<Attribute>::const_iterator begin() const
		{
			return attributes.begin();
		}

		std::vector<Attribute>::const_iterator end() const
		{
			return attributes.end();
		}
	};
}
