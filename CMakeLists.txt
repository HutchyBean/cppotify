cmake_minimum_required (VERSION 3.10)
project(cppotify)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/imtui)
add_executable(cppotify src/main.cpp src/spotify.cpp src/tui.cpp)

target_include_directories(cppotify PUBLIC
  src
  extern
  extern/rapidjson/include
)

target_link_libraries(cppotify PUBLIC
  imtui-ncurses
  ssl
  crypto
)
