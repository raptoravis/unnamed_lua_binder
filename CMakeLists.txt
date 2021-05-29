cmake_minimum_required(VERSION 3.0)

set (PROJECT_NAME luascirpt)

project(${PROJECT_NAME} VERSION 1.0)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB SOURCES "*.cpp" ".h")

file(GLOB LUA_FILES "*.lua")

#Generate the shared library from the sources
#add_library(testStudent SHARED ${SOURCES})

#Generate the static library from the sources
#add_library(testStudent STATIC ${SOURCES}) 

add_executable ( ${PROJECT_NAME} ${SOURCES} ${LUA_FILES} )

SET (LUA_ROOT E:/dev/thirdparty/lua/lua-5.4.2_Win64_vc15_lib/)


#include_directories(${LUA_ROOT}/include)
 

target_include_directories (${PROJECT_NAME} PUBLIC ${LUA_ROOT}/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${LUA_ROOT}/)

set (LUA_LIB lua54)
target_link_libraries ( ${PROJECT_NAME} ${LUA_LIB} )


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LUA_FILES} ${CMAKE_CURRENT_BINARY_DIR}
				)

			
