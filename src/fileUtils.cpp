#include "fileUtils.hpp"
#include <fstream>

std::vector<TodoEntry> readEntries(const std::filesystem::path &directory) {
    std::vector<TodoEntry> entries;

    for (const std::filesystem::directory_entry &file :
         std::filesystem::directory_iterator{directory}) {
        std::ifstream myFile{file.path()};

        for (std::string toParse; std::getline(myFile, toParse);) {
            int year, month, day;
            std::string description;
            std::stringstream line(toParse);

            line >> year >> month >> day;
            getline(line, description);

            entries.emplace_back(std::chrono::year(year) /
                                     std::chrono::month(month) /
                                     std::chrono::day(day),
                                 description);
        }
    }

    return entries;
}
