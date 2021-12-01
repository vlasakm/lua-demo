cmake_minimum_required(VERSION 3.5)
project(lua_demo LANGUAGES C)

#
# lua static library
#
add_library(lua INTERFACE)
add_library(luastatic STATIC
	# core
	lua/lapi.c
	lua/lcode.c
	lua/lctype.c
	lua/ldebug.c
	lua/ldo.c
	lua/ldump.c
	lua/lfunc.c
	lua/lgc.c
	lua/llex.c
	lua/lmem.c
	lua/lobject.c
	lua/lopcodes.c
	lua/lparser.c
	lua/lstate.c
	lua/lstring.c
	lua/ltable.c
	lua/ltm.c
	lua/lundump.c
	lua/lvm.c
	lua/lzio.c
	# lib
	lua/lauxlib.c
	lua/lbaselib.c
	lua/lcorolib.c
	lua/ldblib.c
	lua/liolib.c
	lua/lmathlib.c
	lua/loadlib.c
	lua/loslib.c
	lua/lstrlib.c
	lua/ltablib.c
	lua/lutf8lib.c
	lua/linit.c
)
target_link_libraries(lua INTERFACE m)
target_include_directories(lua INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lua)
if (UNIX)
	target_compile_definitions(lua INTERFACE LUA_USE_POSIX LUA_USE_DLOPEN)
	target_link_libraries(lua INTERFACE ${CMAKE_DL_LIBS})
endif (UNIX)
target_link_libraries(luastatic PUBLIC lua)

#
# main executable (links lua statically, exports its symbols for "plugins")
#
add_executable(main
	main.c
	main2.c
)
target_link_libraries(main PRIVATE luastatic PUBLIC lua)
set_target_properties(main PROPERTIES ENABLE_EXPORTS 1)
set_target_properties(main PROPERTIES C_VISIBILITY_PRESET hidden)

#
# dynamic main module/plugin
#
add_library(module SHARED
	module.c
)
set_target_properties(module PROPERTIES PREFIX "" OUTPUT_NAME "mylib")
target_link_libraries(module PRIVATE lua)
