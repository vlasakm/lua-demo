#include <lualib.h>

int
luaopen_mylib(lua_State *L)             // [...]
{
	lua_createtable(L, 0, 1);       // [...] {}
	lua_pushliteral(L, "myvalue");  // [...] {} "myvalue"
	lua_setfield(L, -2, "mykey");   // [...] {myvalue="mykey"}
	return 1;
}
