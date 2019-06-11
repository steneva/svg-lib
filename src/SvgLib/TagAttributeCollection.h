#pragma once
#include <string>
#include <map>

namespace xml {

	class TagAttributeCollection
	{
	private:
		std::map<std::string, std::string> values;
	public:

		TagAttributeCollection() = default;

		TagAttributeCollection(std::map<std::string, std::string> attributes)
		{
			this->values = attributes;
		}

		TagAttributeCollection(const TagAttributeCollection& other)
		{
			this->values = other.values;
		}

		TagAttributeCollection& operator =(const TagAttributeCollection& other)
		{
			if (&other != this)
			{
				this->values = other.values;
			}

			return *this;
		}

		void set(std::string name, std::string value = "")
		{
			this->values[name] = value;
		}

		std::string get(std::string name)
		{
			return values[name];
		}

		const std::map<std::string, std::string>& get_values() const
		{
			return this->values;
		}

		void remove_attribute(std::string name)
		{
			values.erase(name);
		}

		std::map<std::string, std::string>::const_iterator begin() const
		{
			return values.begin();
		}

		std::map<std::string, std::string>::const_iterator end() const
		{
			return values.end();
		}
	};

}