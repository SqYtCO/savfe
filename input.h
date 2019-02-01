#ifndef INPUT_H
#define INPUT_H

#include <string>

/* input:
 * h / help / ?
 * q / quit / exit
 * R / run / u / update
 * a / add <dirs/files>
 * i / ignore <dirs/files>
 * r / remove / x <dirs/files>
 * d / destination <dir>
 * l / list
 * clear list
 * check
 * log
 * config
 * behavior <already-existing-behavior> <symlink-behavior>
 */

void analyze_input(const std::string& input);

#endif // INPUT_H
