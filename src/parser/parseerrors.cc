#include "../include/stormscript.h"

void sts::parseErrors() { 
    /*
    * this function does not parse runtime errors for:
    * a. speed: it is significantly faster to parse unknown command and missing semicolons before the program is run
    * b. there are certain errors that should only be triggered at runtime
    */
    std::vector<string> globnames;

    std::vector<string> localnames = globnames;

    bool glob = 1;

    for (int i = 0; i < expressions.size(); i++) {
        if ((expressions[i].line == prg.size() - 1  && i == expressions.size()-1) || expressions[i + 1].line != expressions[i].line) { // this checks if there is no semicolon at the end of line
            if (expressions[i].t != ENDEXPR && expressions[i].tktype != CLOSEDCURL && expressions[i].tktype != OPENCURL) 
                error(1, std::to_string(expressions[i].line + 1)); // add 1 to line because line gives index, which always starts at 0
        }
        else if (expressions[i].tktype == OPENCURL) {
            glob = 0;
        }
        else if (expressions[i].tktype == CLOSEDCURL) {
            glob = 1;
            localnames = globnames;
        }
        else if ((expressions[i].t == UNKNOWN && 
            (expressions[i-1].btn == FUNCTION || expressions[i+1].tktype == COLON || 
            expressions[i-1].btn == TYPE ||
            expressions[i-1].btn == TYPE_INTEGER || expressions[i-1].btn == TYPE_STRING || expressions[i-1].btn == TYPE_LIST || expressions[i-1].btn == TYPE_STS_BOOL)) || 
            expressions[i].btn == CONSTRUCTOR_SCOPE)
        { // names vector allows names to be "marked" as known expressions
            localnames.push_back(expressions[i].contents);
            if (expressions[i+1].tktype == ARROW) {
                i+= 2;
                while (expressions[i].tktype != OPENCURL) {
                    if (expressions[i].tktype == COMMA) i++;
                    
                    localnames.push_back(expressions[i].contents);

                    i++;
                }
                i--;
                glob = 0;
            } 
        }
        else if (expressions[i].t == UNKNOWN && expressions[i+1].t == UNKNOWN &&  
            std::find(localnames.begin(), localnames.end(), expressions[i].contents) != localnames.end()) 
        {
            localnames.push_back(expressions[++i].contents);
        }
        else if (expressions[i-1].btn == MODULE) {
            /*
            * It's easier to import modules before runtime because it allows
            * for checks to be run on the modules at the same time that they are
            * run on the original program
            */
            i--;
            importModules(&i);
        }
        else if (expressions[i].btn == STSSOCKET) {
            if (expressions[++i].t != UNKNOWN) 
                error(11, std::to_string(expressions[i].line));
            
            localnames.push_back(expressions[i].contents);

            i += 6;
        }
        else if // written like this to make it more clear what is happening
            (
            (expressions[i].t == UNKNOWN && (expressions[i+1].t == ENDEXPR || expressions[i+1].tktype == ARROW || expressions[i+1].tktype == COMMA)) && 
                (localnames.size() == 0 || // if size is 0 it must be an error
                    std::find(localnames.begin(), localnames.end(), expressions[i].contents) == localnames.end() // true if not in names
                )
            ) // make sure it is not a function before throwing unknown command error
        {
            error(3, expressions[i].contents);
        }
        
        if (glob) globnames = localnames;
    }
}