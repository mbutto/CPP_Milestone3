#include "OrderManager.h"
#include "CustomerOrder.h"
#include "ItemManager.h"
#include "Item.h"
#include <vector>  
#include <algorithm> 

CustomerOrder&& OrderManager::extract()
{
	CustomerOrder& back = this->back();
	this->pop_back();

	return std::move(back);

}

void OrderManager::validate(const ItemManager& itMan, std::ostream& os)
{
	std::for_each(this->begin(), this->end(), [&itMan, &os](CustomerOrder& o) {
		for (size_t i = 0; i < o.noOrders(); i++)
		{
			bool val = false;

			std::find_if(itMan.begin(), itMan.end(), [i, &o, &val](Item n) -> bool {
				std::string tName = n.getName();

				if (o[i] == tName)
				{
					val = true;

				}

				return val;
			});

			if (!val)
			{
				os << o[i] << " is unavailable\n";

			}
		}
	});
}

void OrderManager::display(std::ostream& os) const
{
	for (size_t i = 0; i < this->size(); i++)
	{
		this->at(i).display(os);

	}
}
