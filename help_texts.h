#ifndef HELP_TEXTS_H
#define HELP_TEXTS_H

namespace HELP_TXT
{
	constexpr const char* PARAMETER_HELP_TXT = \
R"###(Help:
-u / --update / -R / --run
        run backup
-r <dirs/files> / --remove <dirs/files>
        remove files or directories from backup list
-a <dirs/files> / --add <dirs/files>
        add files or directories to backup list
-d <dir/file> / --destination <dir/file>
        set backup location
-l / --list
        show list
-c / --check
        check if every path in backup list and the destination path are valid
--log
        show logs
--behavior <already-existing-behavior> <symlink-behavior>
        set configuration of save-behavior if the file exists already:
            0: cancel save process and report an error
            1: keep old saved files
            2: overwrite old saved files
            4: update old saved files (default)
        and a symlink is found:
            0: follow symlink
            16: copy symlink as symlink
            32: skip symlinks (default)
--show-config
        show configurations
-? / --help
        show this help menu
)###";

	constexpr const char* TERMINAL_HELP_TXT = \
R"###(Commands:
h / help / ?
        show this help menu
q / quit / exit
        quit program
R / run / u / update
        run backup
a / add <dir/file>
        add directory or file to backup list
r / remove / x <dir/file>
        remove directory or file from backup list
d / destination <dir>
        set destination path to directory
l / list
        show backup list
clear list
        clear full list (can not be undone!)
check
        check if every path in backup list and the destination path are valid
log
        show logs
show config
        show configurations
show list
        show backup list (the same as 'l' or 'list')
show log
        show logs (the same as 'log')
)###";
}

#endif // HELP_TEXTS_H
