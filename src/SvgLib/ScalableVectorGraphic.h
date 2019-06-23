#pragma once

#include "DomElement.h"
#include "Shape.h"
#include "Region.h"
#include "Rectangle.h"
#include "Circle.h"

class Line;

class ScalableVectorGraphic : public DomElement
{
private:
	void delete_shape_by_id(int id)
	{
		DomElement* parent;
		Shape* item = find_by_id<Shape>(id, parent);
		if (item == nullptr)
		{
			throw std::runtime_error("Could not find shape with id \"" + std::to_string(id) + "\".");
		}

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

	template <typename T>
	T* find_by_id(int id)
	{
		DomElement* parent = this;
		return find_by_id<T>(id, parent);
	}

public:
	ScalableVectorGraphic(xml::Tag* tag)
		: DomElement(tag)
	{
	}

	ScalableVectorGraphic(const ScalableVectorGraphic& other)
		: DomElement(other)
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

	void translate(const Vector& offset)
	{
		const auto translate_action = [offset](Shape* shape)
		{
			shape->translate(offset);
		};

		traverse_tree<Shape>(translate_action);
	}

	void translate(int id, const Vector& offset)
	{
		Shape* shape = find_by_id<Shape>(id);
		shape->translate(offset);
	}

	template <typename T>
	T* create()
	{
		const type_info& type = typeid(T);

		std::string tag_name;
		if (type == typeid(Rectangle))
		{
			tag_name = "rect";
		}
		else if (type == typeid(Circle))
		{
			tag_name = "circle";
		}
		else if (type == typeid(Line))
		{
			tag_name = "line";
		}
		else
		{
			throw std::runtime_error("Shape is not supported.");
		}

		xml::Tag* tag = new xml::Tag(tag_name);
		T* shape = new T(tag);
		DomElement* result = children().add(*shape);

		delete shape;

		return dynamic_cast<T*>(result);
	}

	std::vector<Shape*> shapes_within(const Region* region)
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
};
