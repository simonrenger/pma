add_executable(tests std_tests.cpp)

target_link_libraries(tests PRIVATE pma::pma)

if(BUILD_17)
    message ( STATUS "tests build with c++17")
    target_compile_options(tests PUBLIC /Zc:__cplusplus)
    target_compile_features(tests PUBLIC cxx_std_17)
else()
    message ( STATUS "tests build with c++14")
    target_compile_options(tests PUBLIC /Zc:__cplusplus)
    target_compile_features(tests PUBLIC cxx_std_14)
endif()

