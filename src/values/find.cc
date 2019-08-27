#include "../stormscript.h"

bool find(std::vector<stsvars> vars, string query, int *num) {
	bool isvar = false;

	for (int i = 0; i < vars.size() && !isvar; i++) {
		isvar = (vars.at(i).name == query);
		if (isvar)
			*num = i;
	}

	return isvar;
}

bool find(std::vector<stsfunc> functions, string query, int *num) {
	for (int i = 0; i < functions.size(); i++) {
		if (functions[i].name == query) {
			*num = i;
			return 1;
		}
	}

	return 0;
}

bool find(std::vector<type> types, string query, int *num) {
	for (int i = 0; i < types.size(); i++) {
		if (types[i].name == query) {
			*num = i;
			return 1;
		}
	}

	return 0;
}

bool find(std::vector<stsObject> vars, string query, int *num) {
	for (int i = 0; i < vars.size(); i++) {
		if (vars[i].name == query) {
			*num = i;
			return 1;
		}
	}

	return 0;
}