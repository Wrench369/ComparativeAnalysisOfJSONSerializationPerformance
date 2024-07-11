cmake_minimum_required(VERSION 3.10)

project(demo)

include_directories(ScoperTimer/inc)

include_directories(yyjson/inc)
aux_source_directory(yyjson/src SRC_YYJSON)

include_directories(nlohmann)

add_executable(demo main.cc ${SRC_YYJSON})