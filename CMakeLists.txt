cmake_minimum_required(VERSION 3.24)

project(cut-proj LANGUAGES CXX)

add_library(cut INTERFACE
    CMakeLists.txt
    src/include/cut/auto_release.hpp
    src/include/cut/exception.hpp
    src/include/cut/non_copyable.hpp
    src/include/cut/overloaded.hpp
    src/include/cut/pass_key.hpp
    src/include/cut/static_vector.hpp
    src/include/cut/string_map.hpp
    src/include/cut/types.hpp
)

target_include_directories(cut INTERFACE src/include)

if (UNIX)
    target_link_libraries(cut INTERFACE stdc++exp)
endif()

add_library(cut::cut ALIAS cut)
