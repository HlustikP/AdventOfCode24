add_executable(AdventOfCode24 
"main.cpp" "pch.h" 
"day1.cpp" "day2.cpp" "day3.cpp" "day4.cpp" "day5.cpp"
"day6.cpp" "day7.cpp" "day8.cpp" "day9.cpp" "day10.cpp"
"day11.cpp" "day12.cpp" "day13.cpp" "day14.cpp" "day15.cpp"
"day16.cpp" "day17.cpp" "day18.cpp" "day19.cpp" "day20.cpp"
"day21.cpp" "day22.cpp" "day23.cpp" "day24.cpp" "day25.cpp"
"AdventSolutionFactory.cpp" "utils/CGrid.h" "utils/CGrid.cpp")

target_precompile_headers(AdventOfCode24 PRIVATE "pch.h")

set_property(TARGET AdventOfCode24 PROPERTY CXX_STANDARD 23)
