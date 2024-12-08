#include <thread>
#include <unordered_map>

#include "Day6.h"
#include "utils/CGrid.h"
#include "utils/misc.h"

//#define ANIMATE

CDay6::CDay6(const fs::path& aInputDir) : CAdventSolution{ aInputDir, "Day 6: Guard Gallivant" } {}

constexpr auto VISITED = 'X';
constexpr auto BLOCKADE = '#';
constexpr auto UNVISITED = '.';
constexpr auto GUARD = '^';

void CDay6::solve()
{
    printHeadline();
    mStart = std::chrono::high_resolution_clock::now();

    const auto lInput = loadFile("input6-1.txt");
    if (!lInput.has_value())
    {
        return;
    }
    const auto& lText = lInput.value();

    CGrid lGrid{ lText };
    EDirection lDirection = EDirection::Up;
    auto lGuardPos = lGrid.getFirstOccurrenceOf(GUARD);
    if (!lGuardPos.has_value())
    {
        std::cerr << "[ERROR] [SOLVE] Could not find initial guard position" << std::endl;
        return;
    }

    const auto lStartPosition = lGuardPos.value();
    lGrid.setCellDataAt(lGuardPos.value(), VISITED);

    while (true)
    {
        const auto lNextPos = lGrid.moveInDirection(lGuardPos.value(), lDirection);
        if (!lNextPos.has_value())
        {
            break;
        }

        if (lNextPos.value().getData() == BLOCKADE)
        {
            lDirection = CGrid::rotateDirectionRight(lDirection);
        }
        else
        {
            lGuardPos = lNextPos;
            lGrid.setCellDataAt(lGuardPos.value(), VISITED);
        }

#ifdef ANIMATE
        clearConsole();
        lGrid.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
#endif
    }

    const auto lTask1Visited = lGrid.getCount(VISITED);

    auto lVisitedCells = lGrid.getAllOccurrencesOf(VISITED);
    const CGrid lInputGrid{ lText };
    int lTask2LoopCount = 0;
    int lIteration = 0;
    std::unordered_map<CCell, std::vector<EDirection>> lVisitedCellsMap{};

    for (const auto& lVisitedCell : lVisitedCells)
    {
        lVisitedCellsMap.clear();
        CGrid lCurrentGrid = lInputGrid;
        lDirection = EDirection::Up;
        lGuardPos = lCurrentGrid.getFirstOccurrenceOf(GUARD);

        if (!lGuardPos.has_value())
        {
            std::cerr << "[ERROR] [SOLVE] Could not find initial guard position" << std::endl;
            return;
        }

        std::vector<EDirection> lStartPositionDirections{};
        lStartPositionDirections.reserve(4);
        lStartPositionDirections.push_back(EDirection::Up);

        lCurrentGrid.setCellDataAt(lVisitedCell, BLOCKADE);
        bool lFirstMove = true;

        while (true)
        {
            const auto lNextPos = lCurrentGrid.moveInDirection(lGuardPos.value(), lDirection);
            if (!lNextPos.has_value())
            {
                break;
            }

            auto& lUsedDiretionsInCell = lVisitedCellsMap[lGuardPos.value()];

            if (lNextPos.value().getData() == BLOCKADE)
            {
                lDirection = CGrid::rotateDirectionRight(lDirection);
            }
            else
            {
                if (!lFirstMove && std::ranges::find(lUsedDiretionsInCell, lDirection) != lUsedDiretionsInCell.end())
                {
                    ++lTask2LoopCount;
                    break;
                }
                lFirstMove = false;

                lCurrentGrid.setCellDataAt(lGuardPos.value(), VISITED);
                lUsedDiretionsInCell.push_back(lDirection);
                lGuardPos = lNextPos;
            }

#ifdef ANIMATE
            clearConsole();
            std::cout << std::format("Iteration: {} Loops found: {}\n", lIteration, lTask2LoopCount);
            lCurrentGrid.setCellDataAt(lGuardPos.value(), GUARD);
            lCurrentGrid.print();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            lCurrentGrid.setCellDataAt(lGuardPos.value(), VISITED);
#endif
        }

        lCurrentGrid.setCellDataAt(lVisitedCell, UNVISITED);
        ++lIteration;
    }

    mEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 Visited: " << lTask1Visited << std::endl;
    std::cout << "Task 2 Loop Count: " << lTask2LoopCount << std::endl;

    printTime();
}
