#include <stdlib.h>
#include <string.h>
#include <lualib.h>
#include <lauxlib.h>

#include "main2.h"

static lua_State *
new_lua_state(void)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	return L;
}

int
main(int argc, char **argv)
{
	lua_State *L = new_lua_state();
	process_arguments(L, argc, argv);

	return EXIT_SUCCESS;
}
