cmake_minimum_required(VERSION 3.0)

set (PROJECT_NAME luascirpt)

project(${PROJECT_NAME} VERSION 1.0)

set (LUA_LIB lua54)

SET (LUA_ROOT E:/dev/thirdparty/lua/lua-5.4.2_Win64_vc15_lib/)

include_directories(${LUA_ROOT}/include)
link_directories(${LUA_ROOT}/)

set (LIB_LUASOCKET libluasocket)
set (LIB_LUASOCKET_PATH LibLuasocket)

file(GLOB_RECURSE LIB_LUASOCKET_SRC "${LIB_LUASOCKET_PATH}/*.cpp" "${LIB_LUASOCKET_PATH}/*.c" "${LIB_LUASOCKET_PATH}/*.h" "${LIB_LUASOCKET_PATH}/*.inc")

add_library(${LIB_LUASOCKET} STATIC ${LIB_LUASOCKET_SRC})

target_include_directories (${LIB_LUASOCKET} PUBLIC ${LIB_LUASOCKET_PATH}/Public)
target_link_libraries ( ${LIB_LUASOCKET} ${LUA_LIB} )

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB SOURCES "*.cpp" "*.h")
file(GLOB LUA_FILES "*.lua")

#Generate the shared library from the sources
#add_library(testStudent SHARED ${SOURCES})

#Generate the static library from the sources
#add_library(testStudent STATIC ${SOURCES}) 

add_executable ( ${PROJECT_NAME} ${SOURCES} ${LUA_FILES} )

# target_include_directories (${PROJECT_NAME} PUBLIC ${LUA_ROOT}/include)
# target_link_directories(${PROJECT_NAME} PUBLIC ${LUA_ROOT}/)

target_link_libraries ( ${PROJECT_NAME} ${LUA_LIB} ${LIB_LUASOCKET} Ws2_32 )


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LUA_FILES} ${CMAKE_CURRENT_BINARY_DIR}
				)

			
