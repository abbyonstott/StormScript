#include "../core/stsclasses.h"

void sts::addmodule(int *ln) {
    char **args;
    string filename = prs[*ln]+".sts";
    sts module;

    module.read(args,1, filename);
    int ls = 5;
    if (module.prs[2]=="=>") {
        while (module.prs[ls]!="{")
            ls++;
        ls+=2;
    }

    for (int i = 0; i<module.functions.size(); i++) {
        module.functions[i].modname=prs[*ln];
        module.functions[i].linestarted=*ln+ls;
        functions.push_back(module.functions[i]);
    }
    
    for (int i = 0; i<module.globvars.size(); i++)
        globvars.push_back(module.globvars[i]);


    for (int i = module.prs.size()-1; i>=0; i--)
        prs.insert(prs.begin()+*ln+2, module.prs[i]);
}