#ifndef _UI_H_
#define _UI_H_

#include <string>
#include <vector>
using std::string, std::vector;

// nên sửa class này lại ra design pattern mới

void printHeader(const string&);
void printMessage(const string&);
void printMenu(const vector<string>&);
void printDashLine();
string getInput(const string&);


#endif