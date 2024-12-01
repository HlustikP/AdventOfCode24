add_executable(AdventOfCode24 "main.cpp" "day1.cpp" "pch.h" "AdventSolutionFactory.cpp")

target_precompile_headers(AdventOfCode24 PRIVATE "pch.h")

set_property(TARGET AdventOfCode24 PROPERTY CXX_STANDARD 23)
