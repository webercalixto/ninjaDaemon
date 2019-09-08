cmake_minimum_required(VERSION 3.8)
project (ninjaDaemon)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror ")

set(INCPATH_RAPIDJSON "${CMAKE_CURRENT_SOURCE_DIR}/third-party/rapidjson/include/")
set(INCPATH_PISTACHE "${CMAKE_CURRENT_SOURCE_DIR}/third-party/pistache/include/")
set(LIBPATH_PISTACHE "${CMAKE_CURRENT_SOURCE_DIR}/third-party/pistache/build/src/")
set(INCPATH_INIPP "${CMAKE_CURRENT_SOURCE_DIR}/third-party/inipp/")

LINK_DIRECTORIES(${LIBPATH_PISTACHE})

find_package(Threads REQUIRED)

##### Git submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --remote --init
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --remote --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
#####

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${INCPATH_RAPIDJSON} ${INCPATH_INIPP} ${INCPATH_PISTACHE})
file(GLOB SOURCES 
				  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(ninjaDaemonStatic STATIC ${SOURCES})
set_target_properties(ninjaDaemonStatic PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(ninjaDaemonStatic PUBLIC 
	Threads::Threads 
	stdc++fs
	libpistache.a)
	
add_executable(ninjaDaemon ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/example/simpleExample.cpp")
target_link_libraries(ninjaDaemon PUBLIC 
	Threads::Threads 
	stdc++fs
	libpistache.a)

add_executable(ninjaDaemonPistacheExample01 ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/example/simpleExample.cpp")
target_link_libraries(ninjaDaemonPistacheExample01 PUBLIC 
	Threads::Threads 
	stdc++fs
	libpistache.a)