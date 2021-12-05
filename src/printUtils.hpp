#pragma once
#include <ostream>
#include "TodoEntry.hpp"

std::ostream &operator<<(std::ostream &os, const TodoEntry &entry);

void printOptionError(const std::string &error);
