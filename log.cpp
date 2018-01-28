#include "log.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <iostream>

void log(const char* data, Log_Type type)
{
    std::ofstream of("logfile", std::ios::app);
    time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    // Www Mmm dd hh:mm:ss yyyy
    // Www = weekday, Mmm = month, dd = day, hh = hour, mm = minute, ss = second, yyyy = year
    of.write(std::ctime(&t), 24);
    of << " : " << static_cast<char>(type) << " :\t"
        << data
        << "\n";
    // Mon Nov 06 11:00:00 2017 : I : message
}
