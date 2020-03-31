add_library(
    pma
    astd/monotonic.cpp
    astd/pool.cpp
    astd/freelist.cpp
    astd/multipool.cpp
    )
add_library(pma::pma ALIAS pma)
target_include_directories(pma
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    )

# target_link_libraries(pma PUBLIC EASTL)
if(BUILD_17)
    message ( STATUS "pma build with c++17")
    target_compile_options(pma PUBLIC /Zc:__cplusplus)
    target_compile_features(pma PUBLIC cxx_std_17)
else()
    message ( STATUS "pma build with c++14")
    target_compile_options(pma PUBLIC /Zc:__cplusplus)
    target_compile_features(pma PUBLIC cxx_std_14)
endif()