#include "../include/stormscript.h"

void sts::importModules(int *y) {
    /*
    * Importing a module works the same way as executing a normal program.
    * (Why should it be any different?)
    * 
    * Instead of being called, modules are actually just added to the parsed version of
    * the original program. This saves time as in this case the module only has to be opened
    * once during a single run
    */
    *y += 1;

    int endexprloc = 0;

    while (expressions[endexprloc].t != ENDEXPR) endexprloc++;

    while (*y < endexprloc) {
        if (expressions[*y].tktype != COMMA) {
            string modname, _filename; // filename adds .sts to the end of the modname
            modname = expressions[*y].contents;
            _filename = modname + ".sts";

            sts mod;

            mod.filename = _filename;
            mod.stsread({}, 0); // stsread() is run without argv

            expressions.insert(expressions.begin() + endexprloc + 1,
                mod.expressions.begin(), mod.expressions.end());
        }

        *y += 1;
    }

}