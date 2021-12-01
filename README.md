Compiled with:

    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build

Tested with:

    env LUA_CPATH="build/?.so;/usr/lib/lua/5.4/?.so" ./build/main 'print(require("mylib").mykey)' 'print(require("lpeg"))'

This example showcases an application statically linking Lua, that still wants
to make it possible to use external Lua C modules.

The example application is split accross two files (`main.c` and `main2.c`),
and has two interesting symbols to watch for "new_lua_state" which is a static
function and "process_arguments" which is an extern function. Both don't need
to be present in any symbol table for the application to work.

The example module is defined in `module.c`. It is compiled against the exact
same Lua headers and with same compiler flags (this is the correct thing to
do).

In CMake the crucial part is:

    set_target_properties(main PROPERTIES ENABLE_EXPORTS 1)
    set_target_properties(main PROPERTIES C_VISIBILITY_PRESET hidden)

First line makes the all symbols dynamically exported (`-E`,
`--export-dynamic`, `-rdynamic`). The second line makes the default symbol
visiblity "hidden". Note that this only applies to the application - since Lua
is built separately as static library, its visibility applies - and Lua
manually marks all private symbols with "internal" visibility.

See the `readelf*` files for `readelf -a` output before and after full strip
(`strip -s`).
