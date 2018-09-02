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
            // this is what checks for chars to remove from parsed version
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
    std::vector<string> names; // the names of imported libraries
    globvars.resize(globvars.size()+1);
    if (argc-1==2){
        globvars[globvars.size()-1].valstring=argv[2];
        globvars[globvars.size()-1].name="arg"; 
        globvars[globvars.size()-1].type='s';
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
            else {
                error(2,prs[x]);
                x++;
            }
        }
        else if (prs[x]=="do{"){
            std::vector<stsvars> vars;
            vars.resize(globvars.size());
            vars = globvars;
            int y = x+1;
            bool looped=0;
            int endreq = 1;

            while (true){
                if (prs[y]=="print"){
                    y++;
                    while (prs[y]!=";"){
                        print(y, vars);
                        y++;
                    }
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
                else if (prs[y]=="str"){
                    y++;
                    vars.resize(vars.size()+1);
                    vars[vars.size()-1]=declare('s',y);
                    vars[vars.size()-1].glob=0; //tells the interpreter not to modify the global value
                    y++;
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
                else{
                    bool is = 0;
                    if (vars.size()!=0){
                        string s = prs[y];
                        s.pop_back();
                        for (int z = 0; z<=vars.size()-1; z++){
                            if (s == vars[z].name){
                                is = 1;
                                if (vars[z].type=='i'){
                                    vars[z].valint = std::stoi(prs[y+1]);
                                    if (vars[z].glob==1) { globvars[z].valint = std::stoi(prs[y+1]); }
                                }
                                else{
                                    prs[y+1].pop_back();
                                    prs[y+1].erase(prs[y+1].begin());
                                    vars[z].valstring = prs[y+1];
                                    if (vars[z].glob==1) { globvars[z].valstring = prs[y+1]; }
                                }
                                y++;
                                break;
                            }
                            else if (s == vars[z].name+'+'){ // plus operator
                                is=1;

                                if (vars[z].type=='i'){
                                    vars[z].valint += std::stoi(prs[y+1]);
                                    if (vars[z].glob==1) { globvars[z].valint += std::stoi(prs[y+1]); }
                                }
                                else if (vars[z].type=='j'){
                                    vars[z].valsint.resize(vars[z].valsint.size()+1);
                                    vars[z].valsint[vars[z].valsint.size()-1]=std::stoi(prs[y+1]);
                                }
                                else{
                                    prs[y+1].pop_back();
                                    prs[y+1].erase(prs[y+1].begin());
                                    vars[z].valstring += prs[y+1];
                                    if (vars[z].glob==1) { globvars[z].valstring += prs[y+1]; }
                                }
                                y+=2;
                                break;
                            }
                            else if (s == vars[z].name+'-'){ // minus operator
                                is=1;
                                if (vars[z].type=='i'){
                                    vars[z].valint -= std::stoi(prs[y+1]);
                                    if (vars[z].glob==1) { globvars[z].valint += std::stoi(prs[y+1]); }
                                }
                                else {
                                    char type = vars[z].type;
                                    string types;
                                    if (type=='s') types="str"; 
                                    error(4, types);
                                }
                                y++;
                                break;
                            }
                        }
                    }
                    if (names.size()!=0){
                        for (int z = 0; z<=names.size()-1; z++){
                            if (names[z]==prs[y]){
                                y++;
                                string cmd1;
                                string cmd0 = names[z];
                                if (PLATFORM=="Windows"){
                                    cmd1 = "stslib.exe ";
                                }
                                else{
                                    cmd1 = ".stslib ";
                                }
                                cmd0+=cmd1.c_str();
                                cmd0+=prs[y].c_str();
                                if (prs[y][prs[y].size()-1]==':'){
                                    cmd0[cmd0.size()-1]=' ';
                                    y++;
                                    prs[y].erase(prs[y].begin());
                                    prs[y].pop_back();
                                    cmd0+=prs[y].c_str();
                                }
                                system(cmd0.c_str());
                                is = 1;
                                y++;
                            }
                        }
                    }
                    if ((prs[y]!="") && (prs[y]!=";") && (prs[y]!="\0")&& (is==0)) { //if not function give error
                        cout << y << endl << prs.size() << endl << prs[y-1] << endl;
                        error(1,prs[y]);
                    }
                }
                y++;
            }
        }
    }
}   
