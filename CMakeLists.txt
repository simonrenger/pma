cmake_minimum_required(VERSION 3.10)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(pma VERSION 0.0.1 DESCRIPTION "A great new project")

#define global warning settings this will be for all projects! If one spscific target shall only have something see target ... cmake folder!
if(MSVC)
add_compile_options(/W4 /MP)
else()
add_compile_options(-W -Wall -fPIC)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    #add_compile_options( -fdiagnostics-format=json)
    endif()
endif()

option(BUILD_TESTING "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_17 "With 17" ON)

# Include third-party components we need for the build
# add_subdirectory(third_party/EASTL)

add_subdirectory(src)

if(BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    add_subdirectory(examples)
endif()


