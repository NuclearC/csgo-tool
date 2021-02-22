cmake_minimum_required(VERSION 3.1)
project(CSGOTool)

set(JSON_DIR ${PROJECT_SOURCE_DIR}/../third-party/json CACHE PATH "Nlohmann/json directory" )
set(CPPCODEC ${PROJECT_SOURCE_DIR}/../third-party/cppcodec CACHE PATH "cppcodec directory" )

include_directories(
	${PROJECT_SOURCE_DIR}/source/
    ${JSON_DIR}/include/
    ${CPPCODEC}/)

file(GLOB_RECURSE CSGOTOOL_SOURCE_FILES 
	${PROJECT_SOURCE_DIR}/source/**.cpp
	${PROJECT_SOURCE_DIR}/source/**.hpp
	)

# add_library(CSGOTool MODULE ${CSGOTOOL_SOURCE_FILES})
add_executable(CSGOTool ${CSGOTOOL_SOURCE_FILES})
