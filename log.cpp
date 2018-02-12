#include "log.h"
#include "constants.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <iostream>

void log(const char* data, Log_Type type)
{
	std::ofstream of(FILES::LOG_NAME, std::ios::app);
	time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	// Www Mmm dd hh:mm:ss yyyy
	// Www = weekday, Mmm = month, dd = day, hh = hour, mm = minute, ss = second, yyyy = year
	of.write(std::ctime(&t), 24);
	of << " : " << static_cast<char>(type) << " :\t"
		<< data
		<< "\n";
	// Mon Jan 01 12:00:00 2017 : I : message
}
