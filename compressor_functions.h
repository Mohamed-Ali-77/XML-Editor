#include <iostream>
#include <string>
#include <vector>

using namespace std;

//vector<char> codeing_chars;      // keeping track of the encoding process ( coded pairs and code chars) for decompression or non recursive compression
//vector<string> coded_pairs;

// to convert between an array of char and string
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

// first we remove the new line characters to reduce size 

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

// we are using the byte pair encoding to replace a recurring pair of chars (s) with an unused char (code_char)

string byte_pair_encoding(string str, char code_char, string s) {
	vector<char>result;
	for (int i = 0; i < str.size() - 1; i++) {
		if (str.at(i) == s.at(0) && str.at(i+1) == s.at(1)) {
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
	return char_to_str( result);

}

// for decompression

/*string byte_pair_decoding(string str, char code_char, string s) {
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

}*/




// we decide on the code_char ( a char that is unused in the string (str) ) from an array of characters (code)

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

// we find the most recurring pair in the string 
string most_recurring_pair(string s) {
	int count1 = 0;
	int pair_index = -1;
	bool encoded = false;
  
  
  // the following is in case we don't want a recursive encoding   ( encoding an already encoded pair )
  
	/*for (int i = 0; i < codeing_chars.size(); i++) {
		if (s.at(0) == codeing_chars[i] || s.at(1) == codeing_chars[i]) {
			encoded = true;
		}
	}*/
  
  
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
	if (pair_index == -1 || encoded == true) {
		return "no recurrence";
	}
	else {
		return s.substr(pair_index, 2);
	}
}

// we create the code chars array that can be used in encoding generally 
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
	while (pair != "no recurrence" && cd != '?' ) {
		s = byte_pair_encoding(s, cd, pair);
		codeing_chars.push_back(cd);
		coded_pairs.push_back(pair);
		pair = most_recurring_pair(s);
		cd = code_char(s, codes);
	}
	return s;
}

// to test if the code is valid we decompress the file compressed and check for mistakes 

/*string decompression(string s) {
	for (int i = coded_pairs.size()-1 ; i >= 0; i--) {
		s = byte_pair_decoding(s, codeing_chars[i], coded_pairs[i]);
	}
	return s;
}*/
