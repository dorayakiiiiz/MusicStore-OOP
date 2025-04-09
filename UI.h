#ifndef _UI_H_
#define _UI_H_

#include <string>
#include <vector>
using std::string, std::vector;

class UI {
public:
    static void displayMenu(const vector<string>&);
    static string getInput(const string&);
};

#endif