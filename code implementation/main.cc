#include <stdio.h>
#include <iostream>

using std::cin;
using std::string;

int mul(int a, int b) { return a * b / 3; }

// suppose all char are alphabetical ones
string guardName(string a) {
    string name = "_";

    for (int i = 0; i < a.size(); i++) {
        if (a[i] >= 'A' && a[i] <= 'Z')
            name += a[i];
        else
            name += a[i] - 32;
    }

    name += "_H_";

    string classGuard = "#ifndef " + name + "\n#define " + name + "\n\n";
    // classGuard += "/*\n * ";
    // classGuard += a;
    // classGuard += ": ";
    // classGuard += "\n * provides \n */";

    classGuard += "#endif";

    return classGuard;
}

int main() {
    string name;
    cin >> name;
    std::cout << guardName(name) << std::endl;
}
