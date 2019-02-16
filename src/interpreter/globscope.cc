#include "../include/stormscript.h"

void sts::interp(string fname,int psize, char *argv[], int argc){
    prs = parse(prg);

    globvars.resize(globvars.size()+1);
    for (int x = 1; x<=argc-1; x++){
        globvars.back().type='l';
        globvars.back().vals.resize(globvars[globvars.size()-1].vals.size()+1);
        globvars.back().vals.back().type = 's';
        globvars.back().vals.back().val=argv[x];
        globvars.back().name="arg";
        globvars.back().glob=1;
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

                while (prs[x]!="{") {
                    args.resize(args.size()+1);

                    args[args.size()-1].name = prs[x];
                    
                    x++;
                }
                x++;
                functions.back().args=args;
            }
            
            functions.back().linestarted=x;
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
                else if (prs[x] == "if") {
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
        else if (prs[x]=="do"){
            exec(&x, ((psize==-1) ? -2 : -1), {}, {}, new std::vector<stsvars>({}));
        }
        else if ((prs[x]!=";") && (prs[x][0]!='\0')){
            error(1, prs[x]);
        }
    }
}   