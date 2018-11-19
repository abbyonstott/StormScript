#include "../core/stsclasses.h"

void sts::exec(int x, int function, std::vector<stsclasstype> *pclasstypes, std::vector<stsvars> *objects) { // how each command is executed
    std::vector<stsvars> vars;
    std::vector<stsclasstype> classtypes;
    vars = globvars;
    int y = ((prs[x]=="do") ? x+1 : x);
    bool looped=0;
    int endreq = 1;


    if (function>-1) {
        for (int i = 0; i<functions[function].args.size(); i++) 
             vars.push_back(functions[function].args[i]);

        if (functions[function].classmethod) {
            classtypes = *pclasstypes;
            stsclasstype ct;
            for (int i = 0; i<classtypes.size(); i++)
                if (functions[function].cof == classtypes[i].name) 
                    ct = classtypes[i];
            
            for(int i = 0; i<objects->size(); i++) {
                vars.push_back(objects->at(i));
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
            vars[vars.size()-1]=in(y);
            y+=2;
        }
        else if ((prs[y]=="if")) {
            endreq+=1;
            ifs(&y, &endreq, vars);
            if (prs[y]!="else")
                y--;
        }
        else if (prs[y] == "else") {
            while (prs[y] != "end") {
                y++;
            }
            y--;
        }
        else if (prs[y]=="int") {
            y++;
            vars.resize(vars.size()+1);
            vars[vars.size()-1]=declare('i',y, vars);
            vars[vars.size()-1].glob=0; //tells the interpreter not to modify the global value
            while (prs[y]!=";"){
                y++;
            }
        }
        else if (prs[y]=="bool") {
            y++;
            vars.push_back(declare('b',y, vars));
            y++;
        }
        else if (prs[y]=="list") {
            y++;
            vars.push_back(declare('l', y, vars));
            
            while (prs[y]!=";") 
                y++;
        }
        else if (prs[y]=="str") {
            y++;
            vars.push_back(declare('s',y, vars));
            vars.back().glob=0; //tells the interpreter not to modify the global value
            while (prs[y]!=";")
                y++;
        }
        else if (prs[y]=="sys")
            sys(&y, vars);

        else if ((prs[y]=="end") || (prs[y]=="loop")) {
            if (prs[y]=="loop"){
                if (looped==0){
                    if (prs[y+1]!="inf"){
                        looped=1;
                        endreq=std::stoi(prs[y+1]);
                    }
                    else{
                        endreq=2;
                    }
                }
                vars = globvars;
                prs=parse(prg);
                y=x; //set y equal to x to rerun from start of scope
            }
            endreq-=1;
            if (endreq==0)
                break;
        }
        else if (prs[y]=="return"){
            if (function>-1){
                // check variables
                for (int z = 0; z<vars.size(); z++) {
                    if (prs[y+1]==vars[z].name)
                        functions[function].value=vars[z];
                }

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
}
