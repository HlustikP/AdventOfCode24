add_executable(AdventOfCode24 
"main.cpp" "pch.h" "day1.cpp" "day2.cpp" "day3.cpp" "day4.cpp" "day5.cpp" "AdventSolutionFactory.cpp")

target_precompile_headers(AdventOfCode24 PRIVATE "pch.h")

set_property(TARGET AdventOfCode24 PROPERTY CXX_STANDARD 23)
