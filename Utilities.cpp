#include "Utilities.h"
#include "iostream"
#include "string"

char Utilities::delimiter;
std::ofstream Utilities::logFile;

Utilities::Utilities()
{
	field_width = 1;

}

size_t Utilities::getFieldWidth() const
{
	return field_width;

}

const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more) {
	size_t ePos = str.find(delimiter, next_pos);
	std::string strn;

	if (((next_pos) == ePos) || (ePos == next_pos)) {
		throw ("Empty Value");

	}

	if (ePos != std::string::npos) {
		strn = str.substr(next_pos, (ePos - next_pos));

	}
	else
	{
		strn = str.substr(next_pos);
		more = false;

	}

	if (strn.length() > field_width) {
		field_width = strn.length();
	}

	next_pos = (ePos + 1);

	return strn;

}

void Utilities::setDelimiter(const char del)
{
	Utilities::delimiter = del;

}

void Utilities::setLogFile(const char *file)
{
	Utilities::logFile.open(file, std::ofstream::trunc);

}

std::ofstream & Utilities::getLogFile()
{
	return logFile;

}
