#include "DomElement.h"

xml::Tag* DomElement::tag() const
{
	return this->_tag;
}

bool DomElement::has_children() const
{
	return !_children.empty();
}

void DomElement::to_xml_impl(std::ostream& out, DomElement* root, int level)
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

DomElement::DomElement(xml::Tag* tag): _tag(tag)
{
}

DomElement::DomElement(const DomElement& other): _tag(other._tag)
{
	this->_children = other._children;
}

DomElement::~DomElement() = default;

DomElement* DomElement::clone() const
{
	return new DomElement(*this);
}

DomElementCollection& DomElement::children()
{
	return this->_children;
}

std::string DomElement::to_xml()
{
	std::stringstream content;
	to_xml_impl(content, this);
	return content.str();
}
