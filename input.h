#ifndef INPUT_H
#define INPUT_H

#include <string>

namespace savfe
{
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
bool analyze_input(const std::string& input);
}
#endif // INPUT_H
