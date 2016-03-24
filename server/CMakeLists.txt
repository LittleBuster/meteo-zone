cmake_minimum_required(VERSION 2.8)
project(mzserver)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system REQUIRED)

include_directories(".")
include_directories("./net/")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -march=native -Wall -O2")
set(SRC_LIST app.cpp main.cpp configs.cpp server.cpp net/tcpclient.cpp net/tcpserver.cpp database.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} -lpq -llogger -lpthread)

install (FILES build/mzserver DESTINATION /usr/share/meteosrv/)
install (FILES meteosrv.cfg DESTINATION /etc/)
