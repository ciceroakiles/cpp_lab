#include <iostream>
#include <bitset>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const string base64seq = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const map<char, string> hex2binMap = {
	{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"},
	{'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"},
	{'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
	{'a', "1010"}, {'b', "1011"}, {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}
};

string hex2bin(char hexChar) {
	auto it = hex2binMap.find(hexChar);
	if (it != hex2binMap.end()) return it->second;
	return "";
}

char bin2hex(string binary) {
    for (auto it = hex2binMap.begin(); it != hex2binMap.end(); ++it) {
        if (it->second == binary) return it->first;
    }
	return ' ';
}

vector<string> split(const string str) {
	vector<string> words;
	istringstream iss(str);
	string w;
	while (iss >> w) words.push_back(w);
	return words;
}

string bin8(const int x) {
	return bitset<8>(x).to_string();
}

int bin2dec(string str) {
	double res = 0;
	for (int i = 0; i < str.length(); i++) {
		res += (double(str[i])-'0')*pow(2, str.length()-1-i);
	}
	return res;
}

void str_hex(string str) {
	int i = 0;
	auto words = split(str);
	for (const auto& word : words) {
		for (char c : word) {
			cout << hex << int(c);
		}
		i++;
		if (i < words.size()) cout << hex << int(' ');
	}
}

string str_binseq(string str) {
	int i = 0;
	auto words = split(str);
	string binseq;
	for (const auto& word : words) {
		for (char c : word) {
			binseq += bin8(int(c));
		}
		i++;
		if (i < words.size()) binseq += bin8(int(' '));
	}
	return binseq;
}

void binseq_base64(string binseq) {
	vector<string> groupsix;
	string temp;
	for (int i = 0; i < binseq.length(); i++) {
		if (i % 6 == 0) {
			groupsix.push_back(temp);
			temp = "";
		}
		temp += binseq[i];
	}
	groupsix.push_back(temp);
	groupsix.erase(groupsix.begin());

	if (groupsix[groupsix.size()-1].length() < 6) {
		groupsix[groupsix.size()-1] += "00";
		groupsix.push_back("=");
		if (groupsix[groupsix.size()-2].length() < 6) {
			groupsix[groupsix.size()-2] += "00";
			groupsix[groupsix.size()-1] += "=";
		}
	}

	for (string group : groupsix) {
		if (group[0] != '=') {
			group = base64seq[bin2dec(group)];
		}
		cout << group;
	}
}

void hex_base64(string str) {
	vector<string> grouptwo;
	string temp;
	for (int i = 0; i < str.length(); i++) {
		if (i % 2 == 0) {
			grouptwo.push_back(temp);
			temp = "";
		}
		temp += str[i];
	}
	grouptwo.push_back(temp);
	grouptwo.erase(grouptwo.begin());

	string grouptwoTotal;
	for (string group : grouptwo) {
		group = hex2bin(int(group[0])) + hex2bin(int(group[1]));
		grouptwoTotal += group;
	}
	binseq_base64(grouptwoTotal);
}

int xor_bin(int x1, int x2) {
    return (x1 != x2) ? 1 : 0;
}

char xor_hex(char x1, char x2) {
    string temp;
    for (int i = 0; i < 4; i++) {
        temp += to_string(xor_bin(hex2bin(x1)[i], hex2bin(x2)[i]));
    }
    return tolower(bin2hex(temp));
}

string xor_hexseqs(string str1, string str2) {
    string temp;
    for (int i = 0; i < str1.length(); i++) {
        temp += xor_hex(str1[i], str2[i]);
    }
    return temp;
}

int main()
{
    /*
    string str1 = "I'm killing your brain like a poisonous mushroom";
    cout << str1 << endl;

    cout << "hex> ";
    str_hex(str1);
    cout << endl;

    cout << "b64> ";
    binseq_base64(str_binseq(str1));
    cout << endl;
    */

    /*
    cout << "hexStr: ";
    string str2 = "";
    cin >> str2;
    cout << "b64> ";
    hex_base64(str2);
    cout << endl;
    */
	
    string str3 = "1c0111001f010100061a024b53535009181c";
    string str4 = "686974207468652062756c6c277320657965";
    cout << xor_hexseqs(str3, str4) << endl;

    return 0;
}
