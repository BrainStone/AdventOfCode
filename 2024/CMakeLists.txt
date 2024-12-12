project(aoc_2024)

# Define the number of days
set(NUM_DAYS 7)

# Create a list of solution files dynamically
set(SOLUTION_FILES)
foreach (DAY RANGE 1 ${NUM_DAYS})
    list(APPEND SOLUTION_FILES solutions/day${DAY}.cpp)
endforeach ()

# Add the executable with all sources
add_executable(
        ${PROJECT_NAME}
        main.cpp range_helper.hpp registry.cpp registry.hpp util.cpp util.hpp
        ${SOLUTION_FILES}
)
