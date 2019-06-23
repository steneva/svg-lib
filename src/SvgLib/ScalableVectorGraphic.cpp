#include "ScalableVectorGraphic.h"

void ScalableVectorGraphic::delete_shape_by_id(int id)
{
	DomElement* parent;
	Shape* item = find_by_id<Shape>(id, parent);
	if (item == nullptr)
	{
		throw std::runtime_error("Could not find shape with id \"" + std::to_string(id) + "\".");
	}

	parent->children().remove(item);
}

ScalableVectorGraphic::ScalableVectorGraphic(xml::Tag* tag): DomElement(tag)
{
}

ScalableVectorGraphic::ScalableVectorGraphic(const ScalableVectorGraphic& other): DomElement(other)
{
}

void ScalableVectorGraphic::print(std::ostream& ostream)
{
	const auto print_action = [&ostream](const Shape* shape)
	{
		shape->print(ostream);
	};

	this->traverse_tree<Shape>(print_action);
}

void ScalableVectorGraphic::erase(int id)
{
	delete_shape_by_id(id);
}

void ScalableVectorGraphic::translate(const Vector& offset)
{
	const auto translate_action = [offset](Shape* shape)
	{
		shape->translate(offset);
	};

	traverse_tree<Shape>(translate_action);
}

void ScalableVectorGraphic::translate(int id, const Vector& offset)
{
	Shape* shape = find_by_id<Shape>(id);
	shape->translate(offset);
}

std::vector<Shape*> ScalableVectorGraphic::shapes_within(const Region* region)
{
	std::vector<Shape*> shapes;
	const auto within_region = [&shapes, &region](Shape* shape, DomElement* parent)
	{
		if (region->contains(*shape))
		{
			shapes.push_back(shape);
		}
	};

	traverse_tree<Shape>(within_region);

	return shapes;
}
