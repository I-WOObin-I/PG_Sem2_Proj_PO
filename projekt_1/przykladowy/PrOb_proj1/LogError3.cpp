#include "LogError3.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

std::ostringstream & LogError3::err()
{
	//std::time_t time = std::time(nullptr);
	auto time = std::chrono::system_clock::now();
	auto time_t = std::chrono::system_clock::to_time_t(time);

	os << std::put_time(std::localtime(&time_t), "%X") << ":\t";
	return os;
}

void LogError3::EmptyLog()
{
	std::ofstream logFile(ERROR_LOG_FILE_PATH);
	if (logFile.good())
		logFile.close();
}

LogError3::LogError3()
{
}

LogError3::~LogError3()
{
	os << std::endl;
	std::ofstream logFile(ERROR_LOG_FILE_PATH, std::ios::app);
	if (!logFile.good())
		return;
	logFile << os.str();
	logFile.close();
}