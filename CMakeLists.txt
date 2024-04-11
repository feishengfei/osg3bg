cmake_minimum_required(VERSION 2.6)
project(osg3bg)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configuration/root_directory.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/configuration/root_directory.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/configuration)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenThreads REQUIRED)
find_package(osgDB REQUIRED)
find_package(osgGA REQUIRED)
find_package(osg REQUIRED)
find_package(osgText REQUIRED)
find_package(osgUtil REQUIRED)
find_package(osgViewer REQUIRED)
find_package(GLUT REQUIRED)

add_library(utils "utils/utils.cpp")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_STRIP_COMMAND "strip")
    set(CMAKE_STRIP "strip")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
endif()

macro(link_to_library PROJNAME LIBNAME)
    include_directories(${${LIBNAME}_INCLUDE_DIR})
    target_link_libraries(${PROJNAME} ${${LIBNAME}_LIBRARY})
endmacro()

macro(add_executable_with_core_libraries EXECUTABLE)
    add_executable(${EXECUTABLE} ${EXECUTABLE}.cpp)
    link_to_library(${EXECUTABLE} OPENTHREADS)
    link_to_library(${EXECUTABLE} OSG)
    link_to_library(${EXECUTABLE} OSGDB)
    link_to_library(${EXECUTABLE} OSGGA)
    link_to_library(${EXECUTABLE} OSGUTIL)
    link_to_library(${EXECUTABLE} OSGVIEWER)
    set_target_properties(${EXECUTABLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")
    install(TARGETS ${EXECUTABLE} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/osg3bg)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${EXECUTABLE}>
            COMMENT "Stripping ${EXECUTABLE}"
        )
    endif()
endmacro()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION "${CMAKE_INSTALL_PREFIX}/share/osg3bg/")

add_subdirectory(ch1)
add_subdirectory(ch3)
add_subdirectory(ch4)
add_subdirectory(ch5)
add_subdirectory(ch6)
add_subdirectory(ch7)
add_subdirectory(ch9)
add_subdirectory(ch11)
