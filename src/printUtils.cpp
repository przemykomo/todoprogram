#include "printUtils.hpp"
#include <iostream>
#include "constants.hpp"

void printOptionError(const std::string &error) {
    std::cout << PROGRAM_NAME << ": " << error << "\nTry '"
              << PROGRAM_NAME << " --help' for more information."
              << std::endl;
}

std::ostream &operator<<(std::ostream &os, const TodoEntry &entry) {
    return os << static_cast<int>(entry.ymd.year()) << '-'
              << static_cast<unsigned>(entry.ymd.month()) << '-'
              << static_cast<unsigned>(entry.ymd.day()) << ' '
              << entry.description;
}
