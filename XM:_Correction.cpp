#include<iostream>
#include<stack>
#include <fstream>
using namespace std;
#include<string>
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}


void inline_C(string &s) {
     s = removeSpaces(s);

    int close1 = s.find(">");
    int open1 = s.find("<");

    if ((s.length() > close1 + 1) && open1 != -1) {
        int open1 = s.find("<");
      int open2 = s.find("<",2);
      if (open2 == -1) {
          string s2 = s +'<'+'/'+ "         ";
          int close1 = s.find(">");
          open2 = s2.find("<", 2);
          //   s2[open2 + 1] = '/';

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
          //   s2[open2 + 1] = '/';
      
          while (open1 < close1) {
              s2[open2 + 2] = s2[open1 + 1];
              open1++;
              open2++;
          }
          s = s2;
        }
    }
}

string ReadTXT(string F_NAME) {
    fstream file(F_NAME.c_str());   // sample.xml
    string s,ss = "";
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // using printf() in all tests for consistency
            s = line.c_str();
            inline_C(s);
            //cout << s << endl;
            ss += s;

        }
        file.close();
        return ss;
    }
}


int main() {
    cout << ReadTXT("sample.xml")<<endl;
    string x = "<And>";
    inline_C(x);
    //cout << x;

}

