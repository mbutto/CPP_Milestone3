#include "Item.h"
#include "Utilities.h"
#include <iomanip>  

size_t Item::field_width = 0;

Item::Item(const std::string& str) {
	Utilities* util = new Utilities();
	bool more = true;
	size_t next_pos = 0;

	description = "no detailed description";
	code = 1;

	name = util->nextToken(str, next_pos, more);

	if (name == "") {
		throw"No name has been specified";
	}

	if (more) {
		filler = util->nextToken(str, next_pos, more);

	}
	else
	{
		throw"No filler task has been specified";

	}

	if (more) {
		remover = util->nextToken(str, next_pos, more);

	}
	else {
		throw"No remover task has been specified";

	}

	if (more) {
		code = std::stoi(util->nextToken(str, next_pos, more));

	}

	if (more) {
		description = util->nextToken(str, next_pos, more);

		if (description == "")
		{
			description = "no detailed description";
		}

	}

	if (field_width < name.length()) {
		field_width = name.length();
	}

}

bool Item::empty() const {
	bool safe = false;

	if (code == 1 && description == "no detailed description") {
		safe = true;

	}

	return safe;
}

int Item::operator++(int) {
	int pCode = code;

	code++;

	return pCode;
}

unsigned int Item::getCode() const {
	unsigned int cop = code;

	return cop;
}

const std::string& Item::getName() const {
	return name;

}

const std::string& Item::getFiller() const {
	return filler;

}

const std::string& Item::getRemover() const {
	return remover;

}

void Item::display(std::ostream& os, bool full) const {
	os << std::setw(field_width) << std::left << std::setfill(' ') << name;
	os << std::right << "[" << std::setw(CODE_WIDTH) << std::setfill('0') << code << "]";

	os << std::setfill(' ');

	if (full == true) {
		os << std::setw(field_width) << std::left << " From " + filler << std::left << std::setw(field_width) << " To " + remover << '\n';
		os << std::setw((field_width + CODE_WIDTH) + 3) << std::right << ": " << description << std::endl;

	}

}