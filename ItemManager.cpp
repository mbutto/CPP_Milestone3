#include "ItemManager.h"

void ItemManager::display(std::ostream& os, bool desc) const
{
		for (size_t i = 0; i < this->size(); i++)
		{
			this->at(i).display(os, desc);

		}

}
