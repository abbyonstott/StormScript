#include "stsclasses.h" 
/*
the interpreter parses the file and calls functions in other files
*/

std::vector<string> sts::parse(std::vector<string> prg){
    std::vector<string> x;
    int y = 0;
    while (y!=prg.size()){
        int z = 0;
        x.resize(x.size()+1);
        bool inquotes = false;
        while (z!=prg[y].size()){
            if (prg[y][z]=='"'){
                if (inquotes == false){
                    inquotes = true;
                }
                else{
                    inquotes = false;
                }
            }
            // this is what checks for chars to remove from prs version
            if (((prg[y][z]==' ') || (prg[y][z]=='\n') || (prg[y][z]=='(') || (prg[y][z]==')') || (prg[y][z]=='.')) && (inquotes==false)){
                x.resize(x.size()+1);
                z++;
                continue;
            }
            else if ((prg[y][z]=='\t') || (prg[y][z]==',') && (inquotes==false)){
                z++;
                continue;
            }
            else if (((prg[y][z]==';') || (prg[y][z]=='[') || (prg[y][z]==']')) && (inquotes==false)){
                x.resize(x.size()+1);
                x[x.size()-1]+=prg[y][z];
                x.resize(x.size()+1);
            }
            else{
                x[x.size()-1]+=prg[y][z];
            }
            z++;
        }
        y++;
    }
    x[x.size()-1].pop_back(); //removes EOF char from end of file so it can parse
    return x;
}

void sts::interp(string fname, std::vector<string> prg, int psize, char *argv[], int argc){
    prs = parse(prg);

    globvars.resize(globvars.size()+1);
    for (int x = 1; x<=argc-1; x++){
        globvars[globvars.size()-1].type='t';
        globvars[globvars.size()-1].valsstring.resize(
            globvars[globvars.size()-1].valsstring.size()+1
        );
        globvars[globvars.size()-1].valsstring[globvars[globvars.size()-1].valsstring.size()-1]=argv[x];
        globvars[globvars.size()-1].name="arg"; 
        globvars[globvars.size()-1].glob=1;
    }

    for (int x = 0; x<=prs.size()-1; x++){
        if (prs[x]=="lib"){
            names.resize(names.size()+1);
            x++;
            names[names.size()-1]=prs[x];
        }
        else if (prs[x]=="glob"){
            globvars.resize(globvars.size()+1);
            x++;
            if (prs[x]=="int") {
                x++;
                globvars[globvars.size()-1]=declare('i', x);
                globvars[globvars.size()-1].glob=1;
            }
            else if (prs[x]=="str") {
                x++;
                globvars[globvars.size()-1]=declare('s', x);
                globvars[globvars.size()-1].glob=1;
            }
            else if (prs[x]=="bool") {
                x++;
                globvars[globvars.size()-1]=declare('b', x);
                globvars[globvars.size()-1].glob=1;
            }
            else {
                error(2,prs[x]);
                x++;
            }
        }
        else if (prs[x]=="func"){
            prs[x+1].pop_back();
            functions.resize(functions.size()+1);
            functions[functions.size()-1].name=prs[x+1];
            functions[functions.size()-1].linestarted=x+2;
        }
        else if (prs[x]=="do{"){
            exec(x, names, -1);
        }
    }
}   

void sts::exec(int x, std::vector<string> names, int function){ //THIS FUNCTION IS HOW EACH COMMAND IS EXECUTED
    std::vector<stsvars> vars;
    vars.resize(globvars.size());
    vars = globvars;
    int y = x+1;
    bool looped=0;
    int endreq = 1;

    while (true){
        if ((prs[y]=="print") || (prs[y]=="printl")){
            bool l = 0;
            if (prs[y]=="printl") { l = 1; }

            y++;
            while (prs[y]!=";"){
                print(y, vars);
                y++;
            }
            
            if (l){ cout << endl; }
        }
        else if (prs[y]=="exit"){
            exit(0);
        }
        else if (prs[y]=="in"){
            vars.resize(vars.size()+1);
            y++;
            vars[vars.size()-1]=in(y);
            y+=2;
        }
        else if (prs[y]=="if"){
            y++;
            if (compare(y,vars)){
                endreq+=1;
                y+=2;
            }
            else{
                while (prs[y]!="}end"){
                    y++;
                    if (prs[y]=="}else{"){
                        endreq+=1;
                        break;
                    }
                }
                if (prs[y]!="}end") {
                    y++;
                }
            }
        }
        else if (prs[y]=="}else{"){
            while (prs[y]!="}end"){
                y++;
            }
            endreq-=1;
            y++;
        }
        else if (prs[y]=="int"){
            y++;
            vars.resize(vars.size()+1);
            if (prs[y+2]==";"){
                vars[vars.size()-1]=declare('i',y);
                vars[vars.size()-1].glob=0; //tells the interpreter not to modify the global value
            }
            else{
                vars[vars.size()-1]=declare('j',y);
                vars[vars.size()-1].glob=0;
            }
            while (prs[y]!=";"){
                y++;
            }
        }
        else if (prs[y]=="bool"){
            y++;
            vars.resize(vars.size()+1);
            if (prs[y+2]==";"){
                vars[vars.size()-1]=declare('b',y);
            }
            y++;
        }
        else if (prs[y]=="str"){
            y++;
            vars.resize(vars.size()+1);
            if (prs[y+2]==";"){
                vars[vars.size()-1]=declare('s',y);
                vars[vars.size()-1].glob=0; //tells the interpreter not to modify the global value
            }
            else{
                vars[vars.size()-1]=declare('t',y);
                vars[vars.size()-1].glob=0;
            }
            while (prs[y]!=";"){
                y++;
            }
        }
        else if (prs[y]=="sys"){
            y++;
            sys(y);
        }
        else if ((prs[y]=="}end") || (prs[y]=="}loop")){
            if (prs[y]=="}loop"){
                if (looped==0){
                    if (prs[y+1]!="inf"){
                        looped=1;
                        endreq=std::stoi(prs[y+1]);
                    }
                    else{
                        endreq=2;
                    }
                }
                vars.resize(globvars.size());
                vars = globvars;
                prs=parse(prg);
                y=x+1;
            }
            endreq-=1;
            if (endreq==0){
                break;
            }
            y++;
        }
        else if (prs[y]=="return"){
            if (function>-1){
                for (int z = 0; z<=vars.size()-1; z++){
                    if (prs[y+1]==vars[z].name){
                        functions[function].value=vars[z];
                    }
                }
                break;
            }
            else{
                error(7, "");
            }
        }
        else{
            valchange(&vars, &y);
            if ((prs[y]!="") && (prs[y]!=";") && (prs[y]!="\0")) { //if not function give error
                error(1,prs[y]);
            }
        }
        y++;
    }
}