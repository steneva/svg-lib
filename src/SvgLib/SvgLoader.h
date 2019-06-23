#pragma once
#include "DomElement.h"
#include "ScalableVectorGraphic.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class SvgLoader
{
private:
	static xml::Tag* find_svg_tag(xml::Tag& tag)
	{
		if (tag.name() == "svg")
		{
			return &tag;
		}

		for (xml::Tag::iterator current = tag.children_begin(); current != tag.children_end(); ++current)
		{
			return find_svg_tag(*current);
		}

		return nullptr;
	}

	static void visit_tag(xml::Tag& tag, DomElement& parent_dom_element)
	{
		DomElement* element = nullptr;
		const std::string tag_name = tag.name();

		if (tag_name == "rect")
		{
			element = new Rectangle(&tag);
		}
		else if (tag_name == "circle")
		{
			element = new Circle(&tag);
		}
		else if (tag_name == "line")
		{
			element = new Line(&tag);
		}
		else
		{
			element = new DomElement(&tag);
		}

		for (xml::Tag::iterator child_tag = tag.children_begin(); child_tag != tag.children_end(); ++child_tag)
		{
			visit_tag(*child_tag, *element);
		}

		parent_dom_element.children().add(*element);

		delete element;
	}

public:
	static ScalableVectorGraphic load(xml::Tag& root)
	{
		xml::Tag* svg_tag = find_svg_tag(root);
		if (svg_tag == nullptr)
			throw std::runtime_error("Could not find a valid svg tag.");

		ScalableVectorGraphic svg(svg_tag);

		for (xml::Tag::iterator child = svg_tag->children_begin(); child != svg_tag->children_end(); ++child)
		{
			visit_tag(*child, svg);
		}

		return svg;
	}
};
