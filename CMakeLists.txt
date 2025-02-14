cmake_minimum_required(VERSION 3.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (PROJECT_NAME luascirpt)

project(${PROJECT_NAME} VERSION 1.0)

set (LUA_LIB lua54)

SET (LUA_ROOT_PATH thirdparty/lua/lua-5.4.2_Win64_vc15_lib/)
set (LIB_LUASOCKET_PATH thirdparty/LibLuasocket)


include_directories(${LUA_ROOT_PATH}/include thirdparty/luawrapper thirdparty/LuaBridge-2.6/Source)
link_directories(${LUA_ROOT_PATH}/)

set (LIB_LUASOCKET libluasocket)

file(GLOB_RECURSE LIB_LUASOCKET_SRC "${LIB_LUASOCKET_PATH}/*.cpp" "${LIB_LUASOCKET_PATH}/*.c" "${LIB_LUASOCKET_PATH}/*.h" "${LIB_LUASOCKET_PATH}/*.inc")

add_library(${LIB_LUASOCKET} STATIC ${LIB_LUASOCKET_SRC})

target_include_directories (${LIB_LUASOCKET} PUBLIC ${LIB_LUASOCKET_PATH}/Public)
target_link_libraries ( ${LIB_LUASOCKET} ${LUA_LIB} )

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE SOURCES 
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    "src/*.cpp" "src/*.h")

file(GLOB_RECURSE LUA_FILES 
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    "src/lua/*.lua")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LUA_FILES})

#source_group(lua FILES ${LUA_FILES})

#Generate the shared library from the sources
#add_library(testStudent SHARED ${SOURCES})

#Generate the static library from the sources
#add_library(testStudent STATIC ${SOURCES}) 

add_executable ( ${PROJECT_NAME} ${SOURCES} ${LUA_FILES} )

# target_include_directories (${PROJECT_NAME} PUBLIC ${LUA_ROOT_PATH}/include)
# target_link_directories(${PROJECT_NAME} PUBLIC ${LUA_ROOT_PATH}/)

target_link_libraries ( ${PROJECT_NAME} ${LUA_LIB} ${LIB_LUASOCKET} Ws2_32 )

# copy lua files
set (LUA_FILES_FULLPATH "")

foreach(FILENAME ${LUA_FILES})
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}")
    list(APPEND LUA_FILES_FULLPATH ${SRC})
endforeach(FILENAME)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                #COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/lua
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LUA_FILES_FULLPATH} ${CMAKE_CURRENT_BINARY_DIR}
				)
