#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <assert.h>
#include <cassert>
#include <fstream>

using namespace std;

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

string ReadTXT(string F_NAME) {
    fstream file(F_NAME.c_str());   // sample.xml
    string s = "";
    string sum = "";
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // using printf() in all tests for consistency
            s = line.c_str();
            sum += s;
        }
        file.close();
    }
    return sum;
}

bool Detection(string str) {
    stack<char> s1;
    stack<char> s2;
    vector<char> v1;
    vector<char> v2;
    s1.push('a');
    for (int i = 0; i < str.length(); i++) {
        if (i > 0) {
            if (str[i] == '<' && s1.top() == '>') {
                s1.pop();
            }
        }
        if (str[i] == '<') {
            s1.push(str[i]);
            s2.push(str[i]);
        }
        if (s1.top() == '<' && s1.top() != '>' && str[i] != '<' && str[i] != '>' && str[i] != '/') {
            v1.push_back(str[i]);
        }
        if (s1.top() == '/' && str[i] != '>') {
            v2.push_back(str[i]);
        }
        if (str[i] == '>' && s1.top() != '/') {
            s1.pop();
            s1.push(str[i]);
        }
        if (str[i] == '>' && s1.top() == '/') {
            s1.pop();
            s1.pop();
        }
        if (str[i] == '/' && s2.top() == '<') {
            assert(s2.size() >= 2 && "it can't clsoe tag come before open tag </><>");
            s1.push(str[i]);
            s2.pop();
            s2.pop();
        }
    }
    s1.pop();

    if (s1.empty() && s2.empty() && (v1.size() == v2.size())) {
        return false;
    }
    else {
        return true;
    }
}

int main() {
    string sum = ReadTXT("sample.xml");
    cout << Detection(sum);
}
