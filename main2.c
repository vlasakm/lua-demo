#include <lualib.h>
#include <lauxlib.h>

#include "main2.h"

int
process_arguments(lua_State *L, int argc, char **argv)
{
	for (size_t i = 1; i < argc; ++i)
		if (luaL_dostring(L, argv[i]) != 0)
			break;
}
