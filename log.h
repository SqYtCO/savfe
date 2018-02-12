#ifndef LOG_H
#define LOG_H

enum Log_Type
{
	Info = 'I',
	Debug = 'D',
	Error = 'E',
	Fatale_Error = 'F'
};

void log(const char* data, Log_Type type = Log_Type::Info);

#endif // LOG_H
