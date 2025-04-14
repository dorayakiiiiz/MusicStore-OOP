#ifndef _IVIEW_H_
#define _IVIEW_H_

#include <vector>
#include <string>
using std::vector, std::string;

class IView {
public:
    virtual ~IView() = default;
    virtual void displayMenu(const vector<string>&) = 0;
    virtual string getInput(const string&) = 0;
    virtual void showMessage(const string&) = 0;
};

#endif