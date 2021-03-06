#include "Logging.h"
#include<iomanip>
#include<sstream>
#pragma warning (disable:4996)

const char* LogLevelToString(Logger::Level level)
{
	switch (level)
	{
	case Logger::Level::Info:
		return "Info";
	case Logger::Level::Warning:
		return "Warning";
	case Logger::Level::Error:
		return "Error";
	default:
		return "";
	}
}

Logger::Logger(std::ostream & os, Logger::Level minimumLevel) :
	os{ os },
	minimumLevel{ minimumLevel }
{
	// Empty
}

std::string getCurrentTime()
{
	std::time_t const now_c = std::time(NULL);
	auto s = std::put_time(std::localtime(&now_c), "%F %T");
	std::stringstream timeStamp;
	timeStamp << s;
	return timeStamp.str();
}

void Logger::log(const char * message, Level level)
{
	if (static_cast<int>(level) < static_cast<int>(minimumLevel))
		return;

	os << "[" << LogLevelToString(level) << "] [" << getCurrentTime() << "] " << message << std::endl;
}

void Logger::log(const std::string & message, Level level)
{
	this->log(message.c_str(), level);
}

void Logger::setMinimumLogLevel(Level level)
{
	this->minimumLevel = level;
}
