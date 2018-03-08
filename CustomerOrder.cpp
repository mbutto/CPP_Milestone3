#include "CustomerOrder.h"
#include "CustomerItem.h"
#include "Item.h"
#include "Utilities.h"
#include <iomanip>

size_t CustomerOrder::field_width = 0;

CustomerOrder::CustomerOrder(const std::string& ord)
{
	nOrders = 0;
	order = nullptr;
	Utilities* util = new Utilities();
	size_t next_pos = 0;
	bool more = true;

	name = util->nextToken(ord, next_pos, more);


	if (name == "") {
		throw"No name has been specified";
	}

	if (more) {
		product = util->nextToken(ord, next_pos, more);

	}
	else
	{
		throw"No filler task has been specified";

	}

	while (more)
	{
		CustomerItem* temp = new CustomerItem[nOrders];

		for (size_t i = 0; i < nOrders; i++)
		{
			temp[i] = order[i];

		}

		delete[] order;

		order = new CustomerItem[nOrders + 1];

		for (size_t i = 0; i < nOrders; i++)
		{
			order[i] = temp[i];
		}

		order[nOrders] = util->nextToken(ord, next_pos, more);

		nOrders++;

	}

	if (util->getFieldWidth() > field_width)
	{
		field_width = util->getFieldWidth();

	}

}

CustomerOrder::~CustomerOrder()
{
	delete[] order;
}

unsigned int CustomerOrder::noOrders() const
{
	return nOrders;

}

CustomerOrder::CustomerOrder(CustomerOrder&& ord)
{
	*this = std::move(ord);

}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& ord) NOEXCEPT
{
	if (this != &ord)
	{
		if (order != nullptr) {
			delete[] order;

		}

		name = ord.name;
		product = ord.product;
		order = ord.order;
		nOrders = ord.nOrders;

		ord.name = "";
		ord.product = "";
		ord.order = nullptr;
		ord.nOrders = 0;
	}

	return *this;

}

const std::string & CustomerOrder::operator[](unsigned int i) const
{
	return order[i].getName();

}

void CustomerOrder::fill(Item& it)
{
	for (size_t i = 0; i < nOrders; i++)
	{
		if (it.getName() == order[i].getName())
		{
			order[i].fill(it++);

		}

	}

}

void CustomerOrder::remove(Item& it)
{
	for (size_t i = 0; i < nOrders; i++)
	{
		if (it.getName() == order[i].getName() && order[i].isFilled() == true)
		{
			order[i].clear();

		}

	}

}

bool CustomerOrder::empty() const
{
	bool safe = false;

	if (order == nullptr && noOrders() == 0) {
		safe = true;

	}

	return safe;

}

void CustomerOrder::display(std::ostream& os) const
{
	os << std::setfill(' ') << std::left << std::setw(field_width) << name << ": " << std::left << std::setw(field_width) << product << std::endl;

	for (size_t i = 0; i < nOrders; i++)
	{
		order[i].display(os);

	}

}
