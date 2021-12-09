#include<iostream>
#include<stack>
#include <fstream>
#include<stack>
#include<string>
using namespace std;
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
stack<string> stac;
// to correct errors like   <name>5</id>
void outline_C(string& s) {
    int len;
    string s2, ss, pp = "";
    s2 = removeSpaces(s);
    int close1, open1, close2, open2;
    close1 = s2.find(">");
    open1 = s2.find("<");
    open2 = s2.find("<", 2);
    close2 = s2.find(">", 2);
    if (open1 != -1 && open2 == -1 && s.back() == '>') {
        if (s2[1] != '/') {
            while (open1 < close1 - 1) {
                pp += s2[open1 + 1];
                open1++;
            }
            stac.push(pp);
            pp = "";
        }
        else {
            while (open1 < close1 - 2) {
                pp += s2[open1 + 2];
                open1++;
            }
            //  cout << pp << endl;
            if (pp == stac.top()) {
                stac.pop();
            }

            else {
                s = "</" + stac.top() + ">" + s;
                stac.pop();
                if (!stac.empty()) {
                    stac.pop();
                }
            }

            pp = "";
        }
    }
    ss += s;
}
//correct closed tag in another line
void inline_C(string& s) {
    s = removeSpaces(s);
    int close1 = s.find(">");
    int open1 = s.find("<");
    if ((s.length() > close1 + 1) && open1 != -1) {
        int open1 = s.find("<");
        int open2 = s.find("<", 2);
        if (open2 == -1) {
            string s2 = s + '<' + '/' + "         ";
            int close1 = s.find(">");
            open2 = s2.find("<", 2);

            while (open1 < close1) {
                s2[open2 + 2] = s2[open1 + 1];
                open1++;
                open2++;
            }
            s = s2;
        }
        else {
            string s2 = s + "         ";

            int close1 = s.find(">");
            open2 = s2.find("<", 2);
            while (open1 < close1) {
                s2[open2 + 2] = s2[open1 + 1];
                open1++;
                open2++;
            }
            s = s2;
        }
    }
}
//The main correction function which calls other correction functions
string Correction(string F_NAME) {
    fstream file(F_NAME.c_str());   // sample.xml
    string s, ss = "";
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            s = line.c_str();
            int close1 = s.find(">");
            int open1 = s.find("<");
            if ((s.length() > close1 + 1) && open1 != -1){
                inline_C(s);
            }
            else {
                outline_C(s);
            }
            ss += s;
        }
        file.close();
        return ss;
    }
}

//main
int main() {
    cout << Correction("sample.xml");
   
}
