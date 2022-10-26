#pragma once
#include <string>
#include <iostream>
using namespace std;

string delSpaces(string str) {
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == ' ') {
			str.erase(i, 1);
		}
	}
	return str;
}

string calcSubstr(string param, string first, string second) {
	if (second == "end") {
		return delSpaces(param.substr(param.find(first) + 3,
			param.length() - param.find(first) - 2));
	}

	return delSpaces(param.substr(param.find(first) + 3, param.find(second) - param.find(first) - 3));
}

string* parsParam(string param) {
	string* parameters = new string[3];

	if (param.find("-m") != string::npos) {
		parameters[0] = calcSubstr(param, "-m", "-b");
	}
	if (param.find("-b") != string::npos) {
		parameters[1] = calcSubstr(param, "-b", "-l");
	}
	if (param.find("-l") != string::npos) {
		parameters[2] = calcSubstr(param, "-l", "end");
	}
	return parameters;
}

bool checkDig(string blSize) {
	for (int i = 0; i < blSize.length() - 1; ++i) {
		if (!isdigit(blSize[i]))
			return false;
	}
	return true;
}

long long parsBlock(string blSize) {
	if (checkDig(blSize)) {
		return stoll(blSize);
	}
	if (blSize.find("Kb") != string::npos) {
		return stoll(blSize.substr(0, blSize.find("Kb"))) * 1024;
	}
	if (blSize.find("Mb") != string::npos) {
		return stoll(blSize.substr(0, blSize.find("Mb"))) * 1048576;
	}
	return 0;
}
