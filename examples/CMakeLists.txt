add_executable(example1 example1.cpp)

target_link_libraries(example1 PRIVATE pma::pma)

if(BUILD_17)
    message ( STATUS "example1 build with c++17")
    target_compile_options(example1 PUBLIC /Zc:__cplusplus)
    target_compile_features(example1 PUBLIC cxx_std_17)
else()
    message ( STATUS "example1 build with c++14")
    target_compile_options(example1 PUBLIC /Zc:__cplusplus)
    target_compile_features(example1 PUBLIC cxx_std_14)
endif()
