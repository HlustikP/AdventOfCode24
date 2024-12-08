#include "pch.h"

#include <iostream>
#include <filesystem>

#include "AdventSolutionFactory.h"
#include "utils/misc.h"

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: " << fs::path(argv[0]).filename() << " <input file directory> <day number [1,25]>" << std::endl;
        return 0;
    }

    const auto lDay = std::stoi(argv[2]);

    const auto lDaySolution = CAdventSolutionFactory::create(argv[1], lDay);
    if (!lDaySolution.has_value())
    {
        std::cerr << "[ERROR] [MAIN] Could not create solution for day " << lDay << std::endl;
        return 1;
    }
    lDaySolution.value()->solve();

    return 0;
}
