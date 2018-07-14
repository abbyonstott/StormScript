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
            if (((prg[y][z]==' ') || (prg[y][z]=='\n')) && (inquotes==false)){
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
    system("echo 'int main(){' >> stscompile/stscomp.cpp");
    for (int x = 0; x<=prs.size(); x++){
        if (prs[x]=="do{"){
            int y = x;
            while (true){
                if ((prs[y]=="\tout") || (prs[y]=="out")){
                    system(out(y).c_str());
                }
                else if ((prs[y]=="\tstr") || (prs[y]=="str")){
                    system(declare('s',y).c_str());
                }
                else if ((prs[y]=="\tint") || (prs[y]=="int")){
                    system(declare('i',y).c_str());
                }
                else if (prs[y]=="}end;"){
                    system("echo '\treturn 0;\n}' >> stscompile/stscomp.cpp");
                    break;
                }
                y++;
            }
        }
    }   
    system("g++ stscompile/stscomp.cpp -o stsprg.out");

    cout << "Successfully Compiled" << endl;

}