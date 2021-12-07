#include<iostream>
#include<stack>
#include <fstream>
using namespace std;
#include<string>

// Function to remove all spaces from a given string
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
string ReadTXT(string F_NAME) {
    fstream file(F_NAME.c_str());   // sample.xml
    string s, ss = "";
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // using printf() in all tests for consistency
            s = line.c_str();
           // s = removeSpaces(s);

            return s;
        }
        file.close();
    }
}

int main() {
    /*
    ifstream file("sample.xml");
    string s, ss = "";
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // using printf() in all tests for consistency
            s = line.c_str();
          //  s = removeSpaces(s);

            cout << s << endl;
          //  cout << "*************************************************\n";

        }
        file.close();
    }
    cout << endl;
    cout << "*************************************************\n";
    */
  //Inline Errors
    string s = "<name>a";
    int close1 = s.find(">");
    if (s.length() > close1+1) {
        string s2 = s + s[0]+'\\'+"         ";
        int open1=s.find("<");
        int close1 = s.find(">");
        int open2 = s2.find("<", 2);
        while (open1 < close1) {
            s2[open2 + 2] = s2[open1 + 1];
            open1++;
            open2++;
        }
        s = s2;
    }
    cout << s << endl;


}

