#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}



bool Detection(string F_NAME) {
    fstream file(F_NAME.c_str());   // sample.xml
    string s = "";
    int close1, open1, close2, open2;
    string str1 = "", str2 = "";
    int numberofline = 1;
    stack<int> n;           // stack for lines numbers that have mistakes
    stack<string> stack1, stack2;
    bool a = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // using printf() in all tests for consistency
            s = removeSpaces(line.c_str());

            close1 = s.find(">");
            open1 = s.find("<");
            close2 = s.find(">", close1 + 1);
            open2 = s.find("<", open1 + 1);
            int l = s.length();

                if (open1 != -1 && close1 != -1 && open2 == -1 && close2 == -1)         // case open tag only in line
                {
                    if (s[open1 + 1] != '/') {
                        if ((s.length()-1) > close1) {
                            n.push(numberofline);
                            stack2.push(s);
                        }
                        if ((s.length()-1) == close1) {
                            str1.clear();
                            while (open1 < close1 - 1) {
                                str1 += s[open1 + 1];
                                open1++;
                            }
                            stack1.push(str1);
                        }
                    }
                    
                    else {
                        str2.clear();
                        while (open1 < close1 - 2) {
                            str2 += s[open1 + 2];
                            open1++;
                        }
                        if (str2 != stack1.top()) {
                            stack2.push(stack1.top());
                            stack1.pop();
                            n.push(numberofline);
                        }
                        if (str2 == stack1.top()) {
                            stack1.pop();
                        }
                    }


                }
            
            if (open1 == -1 && close1 == -1 && open2 == -1 && close2 == -1) {
                if (s.length() == 0) {
                    n.push(numberofline);
                    stack2.push(s);
                }
            }

            if (open1 != -1 && close1 != -1 && open2 != -1 && close2 != -1)         // case open and close tag in one line
            {
                str1.clear();
                while (open1 < close1 - 1) {
                    str1 += s[open1 + 1];
                    open1++;
                }
                stack1.push(str1);
                str2.clear();
                while (open2 < close2 - 2) {
                    str2 += s[open2 + 2];
                    open2++;
                }
                if (str2 == stack1.top()) {
                    stack1.pop();
                }
                if (str2 != stack1.top()) {
                    stack2.push(stack1.top());
                    stack1.pop();
                    n.push(numberofline);
                }
            }

            numberofline++;
        }
        if (!n.empty()) {
            cout << "wrong lines" << endl;
            while (!n.empty()) {
                cout << n.top() << endl;
                n.pop();
            }
        }

        if (stack2.empty()) {
            cout << "No errors" << endl;
            a = 0;           // no errors
        }
        else {
            cout << "error exist" << endl;
            a = 1;           //error
        }
        file.close();
    }
    return a;
}




int main() {
    cout << Detection("sample.xml");
}
