#include "stsclasses.h" 

/*
the compiler parses the file and calls functions in other files
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
            if (((prg[y][z]==' ') || (prg[y][z]=='\n') || (prg[y][z]=='(') || (prg[y][z]==')') || (prg[y][z]=='\t')) && (inquotes==false)){
                x.resize(x.size()+1);
                z++;
                continue;
            }

            else{
                x[x.size()-1]+=prg[y][z];
            }
            
            z++;
        }

        y++;
    }
    x[x.size()-1].pop_back(); //removes EOF char from end of file so I can parse
    return x;
}

void sts::compile(string fname, std::vector<string> prg, int psize){
    prs = parse(prg);

    system("compilecheck.sh");
    system("echo '#include <iostream>' > stscompile/stscomp.cpp");
    for (int x = 0; x<=prs.size(); x++){
        if (prs[x]=="do{"){
            system("echo 'int main(){' >> stscompile/stscomp.cpp");
            int y = x+1;
            int times;
            while (true){
                if (prs[y]=="out"){
                    system(out(y).c_str());
                }
                else if (prs[y]=="str"){
                    if (onloop==false){
                        system(declare('s',y).c_str());
                    }
                }
                else if (prs[y]=="int"){
                    if (onloop==false){
                        system(declare('i',y).c_str());
                    }
                }
                else if (prs[y]=="}end;"){
                    system("echo '\treturn 0;\n}' >> stscompile/stscomp.cpp");
                    break;
                }
                else if (prs[y]=="}loop"){
                    if (onloop==false){
                        times = std::stoi(prs[y+1]);
                        onloop = true;
                        y = x+1;
                        continue;
                    }
                    else if (times!=2){
                        y = x+1;
                        times--;
                    }
                    else{
                        system("echo '\treturn 0;\n}' >> stscompile/stscomp.cpp");
                        break;
                    }
                }
                else{
                    int cf = checkiffunction(prs[y]);
                    if ((cf == -1) && (prs[y]!="")){ // if it's not a function give error
                        error(5,prs[y]);
                    }
                    else if (prs[y]!=""){
                        string cmd1 = "echo '\t";
                        string cmd2 = "();' >> stscompile/stscomp.cpp";
                        cmd1 += functions[cf].c_str();
                        cmd1 += cmd2.c_str();
                        system(cmd1.c_str());
                    }
                }
                y++;
            }
        }
        else if (prs[x]=="func"){
            functions.resize(functions.size()+1);
            functions[functions.size()-1]=fdeclare(x);
            int y = x+1;
            while (true){
                if (prs[y]=="out") {
                    system(out(y).c_str());
                }
                else if (prs[y]=="int"){
                    system(declare('i',y).c_str());
                }
                else if (prs[y]=="str"){
                    system(declare('s',y).c_str());
                }
                /* else if (prs[y]=="}loop"){
                    loop  (will be added later)
                } */
                else if (prs[y]=="}end;"){
                    system("echo '}' >> stscompile/stscomp.cpp");
                    break;
                }
                y++;
            }
        }
    }
    system("g++ stscompile/stscomp.cpp -o stsprg.out");

    cout << "Successfully Compiled" << endl;
}   