#ifndef LOG_H
#define LOG_H

namespace savfe
{
enum Log_Type
{
	Info = 'I',
	Debug = 'D',
	Error = 'E',
	Fatale_Error = 'F'
};

enum Log_Output
{
	Stdout = 0b01,
	Fileoutput = 0b10,
	File_And_Stdout = 0b11
};

void log(const char* data, Log_Type type = Log_Type::Info, Log_Output output = Fileoutput);
}
#endif // LOG_H
