#include "../include/stormscript.h"

void sts::runBuiltin(int *y, std::vector<stsvars> *scpvars) {
    switch (expressions[*y].btn) {
        case PRINT: 
            while (expressions[*y].t != ENDEXPR)
                cout << print(y, *scpvars);
                
            break;
        case PRINTL: 
            while (expressions[*y].t != ENDEXPR)
                cout << print(y, *scpvars);

            cout << '\n';
            break;
        case IN: scpvars->push_back(in(*y));
            break;
    }
}

void sts::runUnknown(int *y, std::vector<stsvars> *scpvars) {
    // first, check for definitions of variables

    if (expressions[*y+1].t == TOKEN) {
        switch (expressions[*y+1].tktype) {
            case COLON: // definition
                define(y, scpvars);
                break;
        }
    }
    else
        error(1, expressions[*y].contents);
}

void sts::interp(string fname, int psize, char *argv[], int argc){
    parse(prg);

    globvars.resize(globvars.size()+1);
    for (int x = 1; x<=argc-1; x++) {
        globvars.back().type='l';
        globvars.back().vals.resize(globvars[globvars.size()-1].vals.size()+1);
        globvars.back().vals.back().type = 's';
        globvars.back().vals.back().val=argv[x];
        globvars.back().name="arg";
        globvars.back().glob=1;
        globvars.back().length = argc-1;
    }
    
    for (int x = 0; x < expressions.size(); x++) {
        
        switch(expressions[x].t) { // don't need to worry about TOKEN and ENDEXPR because they will be handled inside of functions
            case BUILTIN: 
                runBuiltin(&x, &globvars);
                break;
            case UNKNOWN: 
                runUnknown(&x, &globvars);
                break;
        }
    
    }
}   

/*
bool checkifforward(sts *script, int y) {
    if (script->prs[y+2] == ";") 
        return 1;
    else if (script->prs[y+2] == "=>") {
        y+= 3;

        while (script->prs[y]!="{" && script->prs[y]!=";")
            y++;
        
        return (script->prs[y] == ";");
    }
    else
        return 0;
}*/

    /*    if (prs[x]=="type") { // declares a class
            classes.resize(classes.size()+1);
            classes[classes.size()-1].declare(&x, this);
        }

        else if (prs[x]=="set") {
            x++;
            set(prs[x], prs[x+2], x);
            x+=2;
        }
        else if (prs[x]=="func"){
            functions.push_back(stsfunc());
            x++;
            functions.back().name=prs[x];
            x++;
            if (prs[x]=="=>") {
                x++;
                std::vector<stsvars> args;

                while ((prs[x]!="{") && (prs[x]!=";")) {
                    args.resize(args.size()+1);

                    args[args.size()-1].name = prs[x];
                    
                    x++;
                }
                functions.back().args=args;
            }
            
            if (prs[x] == ";") {
                int n = x; // searches for actual declaration of function

                for (n; n < prs.size() && prs[n] != functions.back().name; n++) { // iterate over prs until definition is found
                    if ((prs[n] == "func" && !checkifforward(this, n)) || prs[n] == "do" || prs[n] == "type") {
                        scopedown(&n, prs);
                    }
                }

                if (n == prs.size()) // if n is equal to the size of prs, then it could not find the function so it will give an error
                    error(14, functions.back().name);

                n++;

                if (prs[n] == "=>") {
                    while (prs[n] != "{")
                        n++;
                    n++;
                }

                functions.back().linestarted = n; // sets linestarted to the actual code of the forward declared function
            }
            else {
                if (functions.back().args.size() > 0)
                    x++;

                functions.back().linestarted = x;
                int endreq = 1;
                while (endreq != 0) {
                    if (prs[x] == "}")
                        endreq--;
                        
                    if (prs[x] == "else") {
                        if (prs[x+1] == "if")
                            x++;
                        x++;
                        endreq++;
                    }
                    else if ((prs[x] == "if") || (prs[x] == "while")) {
                        x++;
                        endreq++;
                    }
                    else
                        x++;
                }
                x--;
                if (prs[x]=="loop")
                    x+=2;
            }
        }
        else if (prs[x] == "mod") {
            std::vector<string> mod = readmod(prs[x+1]);
            std::vector<string>::iterator it = prs.begin();
            prs.insert(it + 3, mod.begin(), mod.end());
            x += 2;
        }

    }*/