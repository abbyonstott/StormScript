#include "../include/stormscript.h"

void sts::runBuiltin(int *y, std::vector<stsvars> *scpvars, std::vector<stsfunc> *functions) {
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
        case SET:
            set(y);
            break;
        case IN: scpvars->push_back(in(*y));
            break;
        case IF:
            ifs(*scpvars, *functions, y);
            break;
        case FUNCTION:
            declareFunc(y, functions);
            break;
    }
}

void sts::runUnknown(int *y, std::vector<stsvars> *scpvars, std::vector<stsfunc> functions) {
    int fnum;
    bool shouldbreak;

    switch (expressions[*y+1].t) {
        case TOKEN:
            shouldbreak = 0;

            switch (expressions[*y+1].tktype) {
                case COLON: // definition
                    define(y, scpvars);
                    shouldbreak = 1;
                    break;
                case ARROW: break;
            }

            if (shouldbreak) break;
        case ENDEXPR:
            switch (isFunc(functions, expressions[*y].contents, &fnum)) { // if there is a semicolon directly after, it is either a function or not a command
                case 0: 
                    error(1, expressions[*y].contents);
                    break;
                case 1: 
                    runfunc(y, functions, fnum);
                    break;
            }
            break;
    }
}

void sts::interp(string fname, int psize, char *argv[], int argc){
    parse(prg);

    std::vector<stsfunc> functions;

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
    
    newScope(new int(0), globvars, functions);
}   

/*    
if (prs[x]=="type") { // declares a class
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
    }
    else if (prs[x] == "mod") {
        std::vector<string> mod = readmod(prs[x+1]);
        std::vector<string>::iterator it = prs.begin();
        prs.insert(it + 3, mod.begin(), mod.end());
        x += 2;
    }

}*/