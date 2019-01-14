#include "../include/stormscript.h"

void sts::exec(int *x, int function, std::vector<stsclasstype> *pclasstypes, std::vector<stsvars*> objects) { // how each command is executed
    std::vector<stsvars> vars;
    std::vector<stsclasstype> classtypes;
    std::vector<string> originalnames;
    stsclasstype ct;
    vars = globvars;
    int y = ((prs[*x]=="do") ? *x+1 : *x);
    bool looped=0;
    int endreq = 1;


    if (function>-1) {
        for (int i = 0; i<functions[function].args.size(); i++)  {
            vars.push_back(functions[function].args[i]);

            if (vars.back().type == 's') {
                vars.push_back(stsvars());
                vars.back().name = functions[function].args[i].name + "|length";
                vars.back().val = functions[function].args[i].length;
                vars.back().type = 'i';
            }
        }

        if (functions[function].classmethod) {
            classtypes = *pclasstypes;
            
            for (int i = 0; i<classtypes.size(); i++)
                if (functions[function].cof == classtypes[i].name) 
                    ct = classtypes[i];
            
            for(int i = 0; i<objects.size(); i++) {
                vars.push_back(*objects.at(i));
                originalnames.push_back(objects.at(i)->name);
                vars.back().name = ct.tpe.variables[i].name;
            }
        }
    }

    while (true){
        if (function == -2) { // if running in terminal
            y = 0;
            char command[256];

            cout << "stormscript >>> ";
            std::cin.getline(command, 256);

            prg.back() = string(command);
            if (prg.back()=="") {
                y++;
                continue;
            }
            prs = parse(prg);

            if (prs[y]=="lib") {
                y++;
                names.push_back(prs[y]);
                y++;
            }
            else if (prs[y]=="set") {
                y++;
                set(prs[y], prs[y+2], y);
            }
        }


        if ((prs[y]=="print") || (prs[y]=="printl")){
            bool l = (prs[y]=="printl");
            y++;
            for (y; prs[y]!=";"; y++)
                print(y, &y, vars);
            
            if (l)
                cout << "\n";
        }
        else if (prs[y]=="exit") {
            exit(0);
        }  
        else if (prs[y]=="in") {
            vars.resize(vars.size()+1);
            y++;
            vars.push_back(in(y));
            y++;
            vars.push_back(stsvars());
            vars.back().name = vars[vars.size()-2].name + "|length";
            vars.back().val = std::to_string(vars[vars.size()-2].length);
            vars.back().type = 'i';
        }
        else if ((prs[y]=="if")) {
            endreq+=1;
            ifs(&y, &endreq, vars);
            if (prs[y]!="else")
                y--;
        }
        else if (prs[y] == "else") {
            while (prs[y] != "}") {
                y++;
            }
            y--;
        }
        else if (prs[y]=="sys")
            sys(&y, vars);
        else if ((prs[y]=="}") || (prs[y]=="loop")) {
            if (prs[y]=="loop"){
                if (looped==0){
                    if (prs[y+1]!="inf"){
                        endreq=std::stoi(getval(vars, new int(y+1)).val);
                        looped = 1;
                    }
                    else
                        endreq=2;
                }
                vars = globvars;
                prs=parse(prg);
                y = ((function>-1) ? *x-1 : *x); //set y equal to x to rerun from start of scope
                if (function>-1) {
                    for (int i = 0; i<functions[function].args.size(); i++)  {
                        vars.push_back(functions[function].args[i]);
                        if (functions[function].args[i].type == 's') {
                            vars.push_back(stsvars());
                            vars.back().name = functions[function].args[i].name + "|length";
                            vars.back().val = std::to_string(functions[function].args[i].length);
                            vars.back().type = 'i';
                        }
                    }
                }
            }

            for (int i = 0; i<ct.indexes.size(); i++) {
                for (int z = 0; z<vars.size(); z++) {
                    if (vars[z].name == ct.tpe.variables[i].name) {
                        *objects.at(i) = vars[z];
                        objects.at(i)->name = originalnames[i];
                    }
                }
            }

            endreq--;
            if (endreq==0)
                break;
        }
        else if (prs[y]=="return"){
            if (function>-1) {
                // check variables
                y++;
                functions[function].value = getval(vars, &y);

                break;
            }
            else
                error(7, "");
        }
        else{
            bool changed = valchange(&vars, &classtypes, &y);

            if ((prs[y]!=";") && (changed==false)) //if not function give error
                error(1,prs[y]);
        }
        if (y+1!=prs.size())
            y++;
    }
    if (function==-1)
        *x = y;
}
