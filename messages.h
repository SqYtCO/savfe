#ifndef MESSAGES_H
#define MESSAGES_H

namespace savfe
{
namespace MSG
{
	constexpr const char* NO_FILE_TO_REMOVE_SPECIFIED = "No file or directory to remove specified";
	constexpr const char* NO_FILE_TO_ADD_SPECIFIED = "No file or directory to add specified";
	constexpr const char* NO_FILE_TO_IGNORE_SPECIFIED = "No file or directory to ignore specified";
	constexpr const char* INVALID_ARGUMENT_W_ARG = "Invalid argument: ";
	constexpr const char* UNKNOWN_COMMAND_W_ARG = "Unknown command: ";
	constexpr const char* FATALE_TERMINAL_ERROR = "\n\nFatale Terminal Error!\nPlease contact the developer!\n\n";
	constexpr const char* FATALE_RUNNING_ERROR = "\n\nFatale Running Error!\nPlease contact the developer!\n\n";
	constexpr const char* NO_SUCH_FILE_OR_DIRECTORY_W_ARG = " is neither a file nor a directory.";
	constexpr const char* FILE_NOT_FOUND_W_ARG = " not found!";
	constexpr const char* NO_DIRECTORY_W_ARG = " is no valid directory!";
	constexpr const char* NEEDS_ARGUMENT_W_ARG = " needs an argument!";
	constexpr const char* NOT_ON_THE_LIST_W_ARG = " is not on the list!";
	constexpr const char* ALREADY_ON_THE_LIST_W_ARG = " is already on the list!";
	constexpr const char* ALREADY_ON_THE_LIST_INCLUDED_IN_PARENT_1_W_ARG = " is a subdirectory of ";
	constexpr const char* ALREADY_ON_THE_LIST_INCLUDED_IN_PARENT_2_W_ARG = " which is already included in the list.";
	constexpr const char* REMOVE_TO_ADD_REQUEST_ANSWER_1_W_ARG = "Remove ";
	constexpr const char* REMOVE_TO_ADD_REQUEST_ANSWER_2_W_ARG = "to add ";
	constexpr const char* REMOVE_TO_ADD_REQUEST_ANSWER_3_W_ARG = "?\nThis action can not be undone! (y/n): ";
	constexpr const char* REMOVE_TO_ADD_SPACES_FOR_LISTING = "       ";
	constexpr const char* SUCCESSFULLY_REMOVED_W_ARG = " successfully removed!";
	constexpr const char* SUCCESSFULLY_ADDED_W_ARG = " successfully added!";
	constexpr const char* SUCCESSFULLY_IGNORED_W_ARG = " successfully ignored!";
	constexpr const char* OPERATION_CANCELED = "Operation canceled";
	constexpr const char* CLEAR_LIST_REQUEST_ANSWER = "Clear all directories and files? This action can not be undone! (y/n): ";
	constexpr const char* SUCCESSFULLY_SET_AS_DESTINAION_W_ARG = " successfully set as destination!";
	constexpr const char* IS_NO_DIRECTORY_W_ARG = " is no directory!";
	constexpr const char* NO_CONFIGFILE_FOUND = "No configuration found!";
	constexpr const char* NO_LOGFILE_FOUND = "No log found!";
	constexpr const char* NO_LISTFILE_FOUND = "No listfile found!";
	constexpr const char* IS_NO_VALID_BEHAVIOR_W_ARG = " is no valid behavior code!";
	constexpr const char* INVALID_INDEXFILE = "Indexfile invalid!";
	constexpr const char* UNABLE_TO_OPEN_FILE = "Unable to open file!";
	constexpr const char* ELEMENTS_REMOVED_W_ARG = " elments removed!";
}

namespace LOG_MSG
{
	constexpr const char* UNKNOWN_TERMINAL_ERROR = "unknown terminal error";
	constexpr const char* UNKNOWN_PARAMETER_ERROR = "unknown parameter error";
	constexpr const char* RUN_ERROR = "run error";
	constexpr const char* LIST_CLEARED = "list cleared";
}
}

#endif // MESSAGES_H
