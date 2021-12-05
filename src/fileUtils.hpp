#pragma once
#include "TodoEntry.hpp"
#include <filesystem>
#include <vector>

std::vector<TodoEntry> readEntries(const std::filesystem::path &directory);
