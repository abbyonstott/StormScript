#include "stsclasses.h"

void sts::set(string command, string setto, int x) {
    for (int i = x; i<prs.size(); i++) {
        if (prs[i]==setto) {
            prs[i]=command;
        }
    }  
}