cmake_minimum_required(VERSION 3.0)

set (PROJECT_NAME luascirpt)

project(${PROJECT_NAME} VERSION 1.0)

# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

add_executable ( ${PROJECT_NAME} ${SOURCES} ${HEADERS} )

SET (LUA_ROOT E:/dev/thirdparty/lua/lua-5.4.2_Win64_vc15_lib/)

target_include_directories (${PROJECT_NAME} PUBLIC ${LUA_ROOT}/include)
target_link_directories(${PROJECT_NAME} PUBLIC  ${LUA_ROOT}/)

set (LUA_LIB lua54)
target_link_libraries ( ${PROJECT_NAME} ${LUA_LIB} )

