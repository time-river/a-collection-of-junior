#include <iostream>
#include <regex>

using namespace std;

int main(int argc, char *argv[]){
    string line;
    string lines = "";
    while(getline(cin, line)){
        lines = lines + line + '\n';
    }

    regex pattern_h1("^# (\W)*$");
    regex_replace(lines, pattern_h1, "sub-$2");
    cout << lines << endl;
    return 0;
}
