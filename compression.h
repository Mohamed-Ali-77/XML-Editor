#pragma once
#include "iostream"
#include "string"
#include "vector"
#include "fstream"
#include "bits/stdc++.h"
#include "stdlib.h"

using namespace std;

vector<char> str_to_char(string s);
string char_to_str(vector<char> vec);
string minifying(string s);
string byte_pair_encoding(string str, char code_char, string s);
char code_char(string str, vector<char>code);
string most_recurring_pair(string s);
vector<char> code_wds();
string compression(string s);
