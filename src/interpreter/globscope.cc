#include "../include/stormscript.h"

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
}

void sts::interp(string fname, int psize, char *argv[], int argc){
    prs = parse(prg);

    globvars.resize(globvars.size()+1);
    for (int x = 1; x<=argc-1; x++){
        globvars.back().type='l';
        globvars.back().vals.resize(globvars[globvars.size()-1].vals.size()+1);
        globvars.back().vals.back().type = 's';
        globvars.back().vals.back().val=argv[x];
        globvars.back().name="arg";
        globvars.back().glob=1;
        globvars.back().length = argc-1;
    }
    
    for (int x = 0; x<prs.size(); x++){

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
                        int endreq = 1;

                        while (endreq != 0) {
                            if (prs[n] == "}")
                                endreq--;
                                
                            if (prs[n] == "else") {
                                if (prs[n+1] == "if")
                                    n++;
                                n++;
                                endreq++;
                            }
                            else if ((prs[n] == "if") || (prs[n] == "while")) {
                                n++;
                                endreq++;
                            }
                            else
                                n++;
                        }
                        n--;
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
        else if (prs[x]=="do") {
            exec(&x, ((psize==-1) ? -2 : -1), {}, {}, new std::vector<stsvars>({}));
            exit(0);
        }
        else if (prs[x].back() == ':') {
            globvars.push_back(declare(&x, &globvars));
            for (int i = 0; i<globvars.size(); i++)
                globvars[i].glob = true;
        }
        else if ((prs[x]!=";") && (prs[x][0]!='\0')) {
            error(1, prs[x]);
        }
    }
}   