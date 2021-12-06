#include "iostream"
#include "string"
#include "vector"
#include "compression.h"


using namespace std;

vector<char> str_to_char(string s) {
	vector<char> copy;
	for (int i = 0; i < s.size(); i++) {
		copy.push_back(s.at(i));
	}
	return copy;
}
string char_to_str(vector<char> vec) {

	string result(vec.begin(), vec.end());
	return result;
}

string minifying(string s) {
	vector<char> copy;
	for (int i = 0; i < s.size(); i++) {
		if (s.at(i) != '\n') {
			copy.push_back(s.at(i));
		}
	}
	string result(copy.begin(), copy.end());
	return result;
}


string byte_pair_encoding(string str, char code_char, string s) {
	vector<char>result;
	for (int i = 0; i < str.size() - 1; i++) {
		if (str.at(i) == s.at(0) && str.at(i + 1) == s.at(1)) {
			result.push_back(code_char);
			i++;
		}
		else {
			result.push_back(str.at(i));
		}
	}
	if (str.at(str.size() - 2) != s.at(0) && str.at(str.size() - 1) != s.at(1)) {
		result.push_back(str.at(str.size() - 1));
	}
	return char_to_str(result);

}

char code_char(string str, vector<char>code) {
	int cd_index = -1;
	for (int i = 0; i < code.size(); i++) {
		bool good_cd = true;
		for (int j = 0; j < str.size(); j++) {
			if (code[i] == str[j]) {
				good_cd = false;
				break;
			}
		}
		if (good_cd) {
			cd_index = i;
			break;
		}

	}
	if (cd_index == -1) {
		return '?';
	}
	else {
		return code[cd_index];
	}
}

string most_recurring_pair(string s) {
	int count1 = 0;
	int pair_index = -1;
	for (int i = 0; i < s.size() - 1; i++) {
		int count2 = 0;
		for (int j = 0; j < s.size() - 1; j++) {
			if (s.at(i) == s.at(j) && s.at(i + 1) == s.at(j + 1)) {
				count2++;
				j++;


			}
		}
		if (count2 > count1 && count2 > 1) {
			pair_index = i;
			count1 = count2;
		}
	}
	if (pair_index == -1) {
		return "no recurrence";
	}
	else {
		return s.substr(pair_index, 2);
	}
}

 
vector<char>code_wds() {
	vector<char>result;
	for (int i = 33; i < 127; i++) {
		if (i != 63 || i != 34) {
			result.push_back(char(i));
		}
	}
	return result;
}

string compression(string s) {
	s = minifying(s);
	vector<char>codes = code_wds();
	string pair = most_recurring_pair(s);
	char cd = code_char(s, codes);
	while (pair != "no recurrence" && cd != '?') {
		s = byte_pair_encoding(s, cd, pair);
		XML_CodingCharacters.push_back(cd);
		XML_EncodedPairs.push_back(pair);
		pair = most_recurring_pair(s);
		cd = code_char(s, codes);
	}
	return s;
}
string byte_pair_decoding(string str, char code_char, string s) {
	vector<char>result;
	stack<char> temp; 
	for (int i = 0 ; i < str.size(); i++) {
		if (str.at(i) == code_char) {
			result.push_back(s.at(0));
			result.push_back(s.at(1));
		}
		else {
			result.push_back(str.at(i));
		}
	}
	return char_to_str(result);

}
string decompression(string s) {
	for (int i = coded_pairs.size()-1 ; i >= 0; i--) {
		s = byte_pair_decoding(s, codeing_chars[i], coded_pairs[i]);
	}
	return s;
}
