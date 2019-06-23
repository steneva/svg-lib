#pragma once
#include "DomElement.h"
#include "ScalableVectorGraphic.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class SvgLoader
{
private:
	static xml::Tag* find_svg_tag(xml::Tag& tag);

	static void visit_tag(xml::Tag& tag, DomElement& parent_dom_element);

public:
	static ScalableVectorGraphic load(xml::Tag& root);
};
