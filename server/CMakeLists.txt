cmake_minimum_required(VERSION 2.8)
project(mzserver)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system thread REQUIRED)

include_directories(".")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -O2")
set(SRC_LIST app.cpp main.cpp log.cpp configs.cpp server.cpp tcpsocket.cpp database.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} -lmysqlclient)

install (FILES build/mzserver DESTINATION /usr/share/meteosrv/)
install (FILES meteosrv.cfg DESTINATION /etc/)
