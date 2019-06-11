#pragma once
#include "Length.h"

struct Boxable
{
	virtual Length leftmost() const = 0;

	virtual Length rightmost() const = 0;

	virtual Length topmost() const = 0;

	virtual Length downmost() const = 0;

	virtual ~Boxable() = default;
};
