#include "../include/stormscript.h"

void sts::runfunc(int *y, std::vector<stsfunc> functions, int num) {
    sts functionsts;

    functionsts.expressions = functions[num].contents;

    functionsts.newScope(new int(0), {}, functions);
}