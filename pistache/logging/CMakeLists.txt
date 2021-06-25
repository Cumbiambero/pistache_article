cmake_minimum_required(VERSION 3.16)
project(pistachedemo)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall")
add_compile_options(-DELPP_THREAD_SAFE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig)

pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

add_executable(${PROJECT_NAME} main.cpp /usr/local/include/easylogging++.cc)
target_link_libraries(${PROJECT_NAME} PkgConfig::Pistache)