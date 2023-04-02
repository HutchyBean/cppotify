cmake_minimum_required (VERSION 3.10)
project(cppotify)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/imtui)
add_executable(cppotify src/main.cpp)

target_include_directories(cppotify PRIVATE
  ..
)

target_link_libraries(cppotify PRIVATE
  imtui-ncurses
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
