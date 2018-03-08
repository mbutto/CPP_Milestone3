#include "CustomerItem.h"
#include "Item.h"
#include <iomanip>

CustomerItem::CustomerItem(const std::string& str)
{
	if (str != "")
	{
		name = str;

	}

	filled = false;
	code = 0;

}

bool CustomerItem::asksFor(const Item& item) const
{
	bool corIt = false;

	if (item.getName() == name)
	{
		corIt = true;

	}

	return corIt;
}

bool CustomerItem::isFilled() const
{
	bool fil = false;

	if (filled == true)
	{
		fil = true;

	}

	return fil;

}

void CustomerItem::fill(const unsigned int cod)
{
	code = cod;
	filled = true;

}

void CustomerItem::clear()
{
	code = 0;
	filled = false;

}

const std::string & CustomerItem::getName() const
{
	return name;
}

void CustomerItem::display(std::ostream& os) const
{
	if (filled == true)
	{
		os << "+ " << "[" << std::right << std::setw(5) << std::setfill('0') << code << "] " << name << std::endl;

	}
	else
	{
		os << "- " << "[" << std::setw(5) << std::setfill('0') << 0 << "] " << name << std::endl;

	}

}