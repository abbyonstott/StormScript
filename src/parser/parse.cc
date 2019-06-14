#include "../include/stormscript.h" 
/*
the interpreter parses the file and calls functions in other files
*/
void sts::parse(std::vector<string> prg){
    int y = 0;
    while (y!=prg.size()){
        int z = 0;
        bool inquotes = false;
        if (expressions.size() > 0)
            expressions.resize(expressions.size()+1);
        
        while (prg[y][0]==' ')
            prg[y].erase(prg[y].begin());
        

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
                if ((expressions.back().contents.size() != 0))
                    expressions.resize(expressions.size()+1);
                z++;
                expressions.back().line = y;
                continue;
            }
            else if ((prg[y][z]=='#')) {
                break;
            }
            else if  (((prg[y][z]==';') || (prg[y][z]=='}') || (prg[y][z]=='{')) && (inquotes==false)) {
                expressions.resize(expressions.size() + 1);
                expressions.back() = string(1,prg[y][z]);
                expressions.back().line = y;
                break;
            }
            else if (((prg[y][z]=='+') || (prg[y][z]=='-') || (prg[y][z]=='*') || ((prg[y][z]=='/') && (expressions[expressions.size()-2].contents!="mod")) || (prg[y][z]=='[') || (prg[y][z]==',') || (prg[y][z]==']') || (prg[y][z] == ':') || (prg[y][z] == '|')) && (inquotes==false)) {
                expressions.push_back( string(1,prg[y][z]) );
                expressions.back().line = y;
                expressions.resize(expressions.size()+1);
            }
            else if ((prg[y][z]=='\t')  && (inquotes==false)) {
                z++;
                expressions.back().line = y;
                continue;
            }
            else {
                if (expressions.size() == 0)
                    expressions.resize(expressions.size() + 1);
                expressions.back().contents+=prg[y][z];
            }
            expressions.back().line = y;
            z++;
        }
        y++;
    }

    for (int i = 0; i<expressions.size(); i++) {
        if ((expressions[i].contents=="\0") || (expressions[i].contents.size() == 0) || (expressions[i].contents=="\n") || 
            (expressions[i].contents.size() == 1 && expressions[i].contents[0] == 0)) { //this part makes sure that the last empty line is not parsed at all
            expressions.erase(expressions.begin() + i);
            i--; // we want to subtract one so that the parser does leave one of two consecutive blank expressions
        }
     }

    evaluateProgram();
}