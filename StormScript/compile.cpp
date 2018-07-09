#include "stsclasses.h" 

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

    return x;
}

void sts::compile(string fname, std::vector<string> prg, int psize){
    std::vector<string> prs= parse(prg);

    system("compilecheck.sh");
    system("echo '#include <iostream>\\nint main(){' > stscompile/stscomp.cpp");

    for (int x = 0; x<=prs.size()-1; x++){
        string wtp = "";
        if (prs[x]=="\tout"){
            for (int y=0; y<=prs[x+1].size();y++){
                if ((prs[x+1][y]!='\"') && (prs[x+1][y]!=';')){
                    wtp+=prs[x+1][y];
                }
            }

            string a = "echo '\tstd::cout << \""; 
            const char *c = "\" << std::endl;' >> stscompile/stscomp.cpp";
            a+=wtp.c_str();
            a+=c;
            const char *prnc = a.c_str(); //kind of a hack, but it works. Makes c_str and concatinates.

            system(prnc);
        }
    }

    system("echo '\treturn 0;\\n}\\n' >> stscompile/stscomp.cpp");
    system("g++ stscompile/stscomp.cpp -o stsprg.out");

    cout << "Successfully Compiled" << endl;

}


























