#include "DomElementCollection.h"
#include "DomElement.h"

void DomElementCollection::delete_items()
{
	for (DomElement* item : items)
	{
		delete item;
	}
}

DomElementCollection::DomElementCollection(const DomElementCollection& other)
{
	*this = other;
}

DomElementCollection::~DomElementCollection()
{
	delete_items();
	items.clear();
}

DomElementCollection& DomElementCollection::operator=(const DomElementCollection& other)
{
	if (this == &other)
		return *this;

	delete_items();
	for (auto item : other.items)
	{
		this->items.push_back(item->clone());
	}

	return *this;
}

DomElement* DomElementCollection::add(const DomElement& item)
{
	DomElement* cloned = item.clone();
	this->items.push_back(cloned);

	return cloned;
}

void DomElementCollection::remove(const DomElement* item)
{
	const iterator iterator = std::find(items.begin(), items.end(), item);
	delete * iterator;
	this->items.erase(iterator);
}

DomElementCollection::iterator DomElementCollection::begin()
{
	return this->items.begin();
}

DomElementCollection::iterator DomElementCollection::end()
{
	return this->items.end();
}

DomElementCollection::const_iterator DomElementCollection::begin() const
{
	return this->items.begin();
}

DomElementCollection::const_iterator DomElementCollection::end() const
{
	return this->items.end();
}

bool DomElementCollection::empty() const
{
	return items.empty();
}

DomElementCollection::DomElementCollection() = default;
