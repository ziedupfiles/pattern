cmake_minimum_required(VERSION 3.5)

project(pattern-matching LANGUAGES CXX)
set(APP_NAME "pattern-matching")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



SET(ROS_ROOT "/opt/ros/melodic" CACHE PATH "ROS Root")
SET(ROS_CUSTOM_ROOT "/home/zied/catkin_ws/devel" CACHE PATH "ROS Custom Root")


OPTION(USEROSSERIAL "use ros serial for serial communication" ON)

if (USEROSSERIAL)
  add_definitions("-DUSEROSSERIAL ")
endif (USEROSSERIAL)


include_directories("${ROS_ROOT}/include")
include_directories("${ROS_ROOT}/include/vehicle_msgs")
include_directories("${ROS_CUSTOM_ROOT}/include")
link_directories("${ROS_ROOT}/lib")



set(${APP_NAME}_HEADERS
  include/basicinteraction.h
  include/patternmatcher.h
  include/eventvector.h
  include/pattern.h
)

set(${APP_NAME}_SRC_FILES
  src/basicinteraction.cpp
  src/eventvector.cpp
  src/patternmatcher.cpp
  src/pattern.cpp
  src/main.cpp
)

add_executable(${APP_NAME}
${${APP_NAME}_SRC_FILES}
${${APP_NAME}_HEADERS}

)

SET(LINK_LIBRARY
roscpp
roscpp_serialization
rosconsole
rostime
)

target_link_libraries(${APP_NAME} ${LINK_LIBRARY})
