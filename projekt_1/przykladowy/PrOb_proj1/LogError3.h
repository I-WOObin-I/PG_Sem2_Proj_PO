#pragma once
#include <ostream>
#include <sstream>
#define ERR LogError3().err()
#define ERROR_LOG_FILE_PATH "logs/error.log"

class LogError3
{
private:
	std::ostringstream os;

public:
	LogError3();
	virtual ~LogError3();

	std::ostringstream& err();
	
	static void EmptyLog();
};

