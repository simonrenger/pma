add_executable(tests std_tests.cpp)

target_link_libraries(tests PRIVATE pma::pma EASTL)

if(BUILD_17)
    target_compile_features(tests PUBLIC cxx_std_17)
else()
    target_compile_features(tests PUBLIC cxx_std_14)
endif()
