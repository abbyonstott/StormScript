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
        string name = "";
        string val = "";

        if (prs[x]=="\tout"){
            for (int y=0; y<=prs[x+1].size();y++){
                if (prs[x+1][y]!=';'){
                    val+=prs[x+1][y];
                }
            }

            string a = "echo '\tstd::cout << "; 
            const char *c = " << std::endl;' >> stscompile/stscomp.cpp";
            a+=val.c_str();
            a+=c;
            const char *prnc = a.c_str(); //kind of a hack, but it works. Makes c_str and concatinates.

            system(prnc);
        }
        else if (prs[x]=="\tstr"){
            for (int y=0; y<=prs[x+1].size();y++){
                if (prs[x+1][y]!=':'){
                    name+=prs[x+1][y];
                }
            }
            for (int y=0; y<=prs[x+2].size();y++){
                if (prs[x+2][y]!=';'){
                    val+=prs[x+2][y];
                }
            }
            
            string a = "echo '\tstd::string ";
            const char *c = name.c_str();
            const char *e = " = ";
            const char *d = val.c_str();
            const char *f = ";' >> stscompile/stscomp.cpp";
            a+=c;
            a+=e;
            a+=d;
            a+=f;
            const char *strc = a.c_str();

            system(strc);
        }
        else if (prs[x]=="\tint"){
            for (int y=0; y<=prs[x+1].size();y++){
                if (prs[x+1][y]!=':'){
                    name+=prs[x+1][y];
                }
            }
            for (int y=0; y<=prs[x+2].size();y++){
                if (prs[x+2][y]!=';'){
                    val+=prs[x+2][y];
                }
            }
            cout << "'" << val << "'" << endl;
            for (int y=0; y<=val.size()-2; y++){
                cout << isdigit(val[y]) << endl;
                if (isdigit(val[y])==false){
                    error(2, name);
                }
            }
            string a = "echo '\tint ";
            const char *c = name.c_str();
            const char *e = " = ";
            const char *d = val.c_str();
            const char *f = ";' >> stscompile/stscomp.cpp";
            a+=c;
            a+=e;
            a+=d;
            a+=f;
            const char *intc = a.c_str();

            system(intc);
        }
    }

    system("echo '\treturn 0;\\n}\\n' >> stscompile/stscomp.cpp");

    system("g++ stscompile/stscomp.cpp -o stsprg.out");

    cout << "Successfully Compiled" << endl;

}