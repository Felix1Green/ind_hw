include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/mainc.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
add_definitions(-DPATH_TO_SORT_TEST="${PROJECT_SOURCE_DIR}/test/files/sort_test.txt"
        -DPATH_TO_INPUT_TEST="${PROJECT_SOURCE_DIR}/test/files/input_test.txt"
        -DPATH_TO_INPUT_INT_TEST="${PROJECT_SOURCE_DIR}/test/files/input_int_test.txt"
        -DPATH_TO_INPUT_DATE="${PROJECT_SOURCE_DIR}/test/files/input_date.txt"
        -DPATH_TO_INCORRECT_DATA="${PROJECT_SOURCE_DIR}/test/files/incorrect_data.txt"
        -DPATH_TO_ADD_TEST="${PROJECT_SOURCE_DIR}/test/files/add_test.txt"
        )

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp")
    target_link_libraries("${name}_tests" gtest_main)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()