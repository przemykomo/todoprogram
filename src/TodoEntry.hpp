#pragma once
#include <chrono>
#include <string>

struct TodoEntry {
    std::chrono::year_month_day ymd;
    std::string description;
};
