#pragma once

#include "DomElement.h"
#include "Shape.h"
#include "Region.h"

class ScalableVectorGraphic : public DomElement
{
private:

	void delete_shape_by_id(int id)
	{
		DomElement* parent;
		Shape* item = find_by_id<Shape>(id, parent);
		parent->children().remove(item);
	}

	template <typename T>
	T* find_by_id(int id, DomElement*& parent)
	{
		T* found_element = nullptr;
		auto find_action = [id, &found_element, &parent](T* element, DomElement* element_parent)
		{
			if (element->id() == id)
			{
				found_element = element;
				parent = element_parent;
			}
		};

		traverse_tree<T>(find_action);
		return found_element;
	}

	std::vector<Shape*> get_shapes_within(const Region* region)
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

public:
	ScalableVectorGraphic(xml::Tag& tag)
		: DomElement(tag)
	{
	}

	void print(std::ostream& ostream)
	{
		const auto print_action = [&ostream](const Shape* shape)
		{
			shape->print(ostream);
		};

		this->traverse_tree<Shape>(print_action);
	}

	void erase(int id)
	{
		delete_shape_by_id(id);
	}

	void translate(int x, int y, Shape* shape = nullptr)
	{
		if (shape != nullptr)
		{
			shape->translate(x, y);
		}

		const auto translate = [x, y](Shape* shape)
		{
			shape->translate(x, y);
		};

		traverse_tree<Shape>(translate);
	}

	void within(const Region* region, std::ostream& out)
	{
		std::vector<Shape*> shapes = this->get_shapes_within(region);
		for(Shape* shape : shapes)
		{
			out << shape << std::endl;
		}
	}
};
