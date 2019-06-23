#pragma once
#include <vector>

class DomElement;

class DomElementCollection
{
public:
	typedef std::vector<DomElement*>::iterator iterator;
	typedef std::vector<DomElement*>::const_iterator const_iterator;

private:
	std::vector<DomElement*> items;

	void delete_items();

public:
	DomElementCollection();

	DomElementCollection(const DomElementCollection& other);

	~DomElementCollection();

	DomElementCollection& operator=(const DomElementCollection& other);

	DomElement* add(const DomElement& item);

	void remove(const DomElement* item);

	iterator begin();

	iterator end();

	const_iterator begin() const;

	const_iterator end() const;

	bool empty() const;
};
