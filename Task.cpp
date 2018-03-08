#include "Task.h"
#include "Utilities.h"
#include <iomanip>  

size_t Task::field_width;

Task::Task(const std::string &e)
{
	Utilities* util = new Utilities();
	bool more = false;
	size_t next_pos = 0;
	slots = "1";

	pNextTask[passed] = nullptr;
	pNextTask[redirect] = nullptr;
	
	name = util->nextToken(e, next_pos, more);
	
	if (more) {
		slots = util->nextToken(e, next_pos, more);

	}
	else
	{
		slots = "1";

	}

	if(more) {
		nextTask[passed] = util->nextToken(e, next_pos, more);
		

	}

	if (more) {
		nextTask[redirect] = util->nextToken(e, next_pos, more);
	
	}	

	if(field_width < util->getFieldWidth()){
		field_width = util->getFieldWidth();

	}	
	
}

bool Task::validate(const Task& task)
{
	bool valid = true;

	if (nextTask[passed] == task.getName() && pNextTask[passed] == nullptr) {
		pNextTask[passed] = &task;

	}

	if (nextTask[redirect] == task.getName() && pNextTask[redirect] == nullptr) {
		pNextTask[redirect] = &task;
	
	}

	if (!((nextTask[passed] == "") && (nextTask[redirect] == ""))) {
		if ((nextTask[passed] != "") && (pNextTask[passed] == nullptr)) {
			valid = false;

		}

		if (valid) {
			if ((nextTask[redirect] != "") && (pNextTask[redirect] == nullptr)) {
				valid = false;

			}

		}

	}

	return valid;

}

const std::string & Task::getName() const
{
	return name;

}

unsigned int Task::getSlots() const
{
	return std::stoul(slots);

}

const Task * Task::getNextTask(Quality quantity) const
{
	const Task* next = pNextTask[quantity];

	if (next == nullptr) {
		throw("*** Validate [" + nextTask[quantity] + "] @ [" + getName() + "] ***");
	}

	return next;
}

void Task::display(std::ostream& os) const
{
	os << std::setw(13) << std::left << "Task Name" << ": " << std::setw(field_width + 2) << "[" + getName() + "]" << " [" + slots + "]" << std::endl;

	if (nextTask[passed] != "" && pNextTask[passed] == nullptr)
	{
		os << " Continue to : " << std::setw(field_width + 2) << std::left << "[" + nextTask[passed] + "]" << " *** to be validated" << std::endl;

	}
	else if(nextTask[passed] != "" && pNextTask[passed] != nullptr){
		os << " Continue to : " << std::setw(field_width + 2) << std::left << "[" + nextTask[passed] + "]" << std::endl;

	}

	if (nextTask[redirect] != "" && pNextTask[redirect] == nullptr) {
		os << " Redirect to : " << std::setw(field_width + 2) << std::left << "[" + nextTask[redirect] + "]" << " *** to be validated" << std::endl;
	
	}
	else if (nextTask[redirect] != "" && pNextTask[redirect] != nullptr){
		os << " Redirect to : " << std::setw(field_width + 2) << std::left << "[" + nextTask[redirect] + "]" << std::endl;
	}
}

size_t Task::getFieldWidth()
{
	return field_width;
}

bool operator==(const Task& a, const Task& b)
{
	bool eq = false;

	if (a.getName() == b.getName()) {
		eq = true;

	}

	return eq;

}
