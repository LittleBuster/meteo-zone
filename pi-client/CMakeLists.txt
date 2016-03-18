cmake_minimum_required(VERSION 2.8)
project(mzclient)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system thread REQUIRED)

include_directories(".")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -O2")
set(SRC_LIST app.cpp main.cpp configs.cpp sender.cpp tcpclient.cpp lcd.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} -ldht22 -llogger -lwiringPi -lwiringPiDev)

install (FILES build/mzclient DESTINATION /usr/share/meteo/)
install (FILES meteo.cfg DESTINATION /etc/)
