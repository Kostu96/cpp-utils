cmake_minimum_required(VERSION 3.24)

project(game LANGUAGES CXX)

add_library(cut INTERFACE
    CMakeLists.txt
    src/include/cut/auto_release.hpp
    src/include/cut/exception.hpp
    src/include/cut/non_copyable.hpp
    src/include/cut/types.hpp
)

#target_compile_features(cut PRIVATE cxx_std_23)

target_include_directories(cut INTERFACE src/include)

if (UNIX)
    target_link_libraries(cut INTERFACE stdc++exp)
endif()
