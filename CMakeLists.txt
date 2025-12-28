cmake_minimum_required(VERSION 3.20)
project(playground LANGUAGES CXX)

# Globale Defaults für alle Subprojekte
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Subprojekte
add_subdirectory(statemachine)

# later:
# add_subdirectory(project2)
# add_subdirectory(project3)
