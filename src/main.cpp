#include "cxxopts.hpp"
#include "xdg.hpp"
#include <libnotifymm.h>
#include <thread>
#include "TodoEntry.hpp"
#include "fileUtils.hpp"
#include "printUtils.hpp"
#include "constants.hpp"

int main(int argc, char **argv) {

    const std::filesystem::path DATA_DIRECTORY{xdg::DataHomeDir() /
                                               PROGRAM_NAME};

    // create the data directory if it doesn't exist
    std::filesystem::create_directories(DATA_DIRECTORY);

    cxxopts::Options options(PROGRAM_NAME);
    options.allow_unrecognised_options();
    options.add_options()("h,help", "Print usage")(
        "d,daemon", "Run as a daemon")("l,list", "List TODOs");

    cxxopts::ParseResult parsedOptions = options.parse(argc, argv);

    if (!parsedOptions.unmatched().empty()) {
        printOptionError("invalid option -- '" + parsedOptions.unmatched().front() + '\'');
        return 0;
    }

    if (parsedOptions.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (parsedOptions.count("daemon")) {
        Notify::init(PROGRAM_NAME);

        std::vector<TodoEntry> entries(readEntries(DATA_DIRECTORY));

        while (true) {
            using namespace std::chrono;
            for (const TodoEntry &entry : entries) {
                if ((sys_days(entry.ymd) -
                     sys_days(floor<days>(system_clock::now())))
                        .count() == 0) {
                    Notify::Notification notification("Todo today!",
                                                      entry.description);
                    notification.set_urgency(Notify::URGENCY_CRITICAL);
                    notification.set_timeout(0);
                    notification.show();
                }
            }
            std::this_thread::sleep_for(30min);
        }

        return 0;
    }

    if (parsedOptions.count("list")) {
        std::vector<TodoEntry> entries(readEntries(DATA_DIRECTORY));
        for (const TodoEntry &entry : entries) {
            std::cout << entry << std::endl;
        }

        return 0;
    }

    printOptionError("missing option.");
    return 0;
}
