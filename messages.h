#ifndef MESSAGES_H
#define MESSAGES_H

namespace MSG
{
    constexpr const char* NO_FILE_TO_REMOVE_SPECIFIED_MSG = "No file or directory to remove specified";
    constexpr const char* NO_FILE_TO_ADD_SPECIFIED_MSG = "No file or directory to add specified";
    constexpr const char* INVALID_ARGUMENT_W_ARG_MSG = "Invalid argument: ";
    constexpr const char* UNKNOWN_COMMAND_W_ARG_MSG = "Unknown command: ";
    constexpr const char* OPERATION_SUCCESS_MSG = "Operation success!";
	constexpr const char* OPERATION_FAILURE_MSG = "Operation failed!";
    constexpr const char* NO_SUCH_FILE_OR_DIRECTORY_W_ARG_MSG = " is nor a file nor a directory.";
    constexpr const char* FILE_NOT_FOUND_W_ARG_MSG = " not found!";
    constexpr const char* NO_DIRECTORY_W_ARG = " is no valid directory!";
    constexpr const char* NOT_ON_THE_LIST_W_ARG_MSG = " is not on the list!";
	constexpr const char* ALREADY_ON_THE_LIST_W_ARG_MSG = " is already on the list!";
	constexpr const char* ALREADY_ON_THE_LIST_INCLUDED_IN_PARENT_1_W_ARG_MSG = " is a subdirectory of ";
	constexpr const char* ALREADY_ON_THE_LIST_INCLUDED_IN_PARENT_2_W_ARG_MSG = " which is already included in the list.";
	constexpr const char* REMOVE_TO_ADD_REQUEST_ANSWER_1_W_ARG_MSG = "Remove ";
	constexpr const char* REMOVE_TO_ADD_SPACES_FOR_LISTING_MSG = "       ";
	constexpr const char* REMOVE_TO_ADD_REQUEST_ANSWER_2_W_ARG_MSG = "to add ";
	constexpr const char* REMOVE_TO_ADD_REQUEST_ANSWER_3_W_ARG_MSG = "?\nThis action can not be undone! (y/n): ";
    constexpr const char* SUCCESSFUL_REMOVED_W_ARG_MSG = " successfully removed!";
    constexpr const char* SUCCESSFUL_ADDED_W_ARG_MSG = " successfully added!";
	constexpr const char* OPERATION_CANCELED_MSG = "Operation canceled";
    constexpr const char* CLEAR_LIST_REQUEST_ANSWER_MSG = "Clear all directories and files? This action can not be undone! (y/n): ";
}

#endif // MESSAGES_H
