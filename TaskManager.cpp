#include "TaskManager.h"
#include "Task.h"
#include "ItemManager.h"
#include "Item.h"
#include <vector>  
#include <algorithm> 

void TaskManager::validate(std::ostream& os)
{

	std::for_each(this->begin(), this->end(), [this, &os](Task i){
		std::for_each(this->begin(), this->end(), [this, &i, &os](Task x)
		{
			bool val = false;

			if (i.validate(x))
			{
				val = true;

			}
			else{
				val = false;

			}

			return val;

		});

	});

}

void TaskManager::validate(const ItemManager& itMan, std::ostream& os)
{
	std::for_each(itMan.begin(), itMan.end(), [this, &os](Item i) {
		bool val = false;
		
		std::find_if(this->begin(), this->end(), [&i, &os, &val](Task n){
			std::string fName = i.getFiller();
			std::string tName = n.getName();

			if (fName == tName)
			{
				val = true;

			}
			else
			{
				val = false;

			}
			
			return val; 
		
		});

		if (!val)
		{
			os << i.getFiller() << " is unavailable\n";

		}
	});

	std::for_each(itMan.begin(), itMan.end(), [this, &os](Item i) {
		bool val = false;

		std::find_if(this->begin(), this->end(), [&i, &os, &val](Task n) {
			std::string rName = i.getRemover();
			std::string tName = n.getName();

			if (rName == tName)
			{
				val = true;

			}
			else
			{
				val = false;

			}

			return val;

		});

		if (!val)
		{
			os << i.getRemover() << " is unavailable\n";

		}
	});
}

void TaskManager::display(std::ostream& os) const
{
	for (size_t i = 0; i < this->size(); i++)
	{
		this->at(i).display(os);

	}
}
