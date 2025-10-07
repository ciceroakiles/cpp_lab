#include <iostream>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const string base64seq = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string hexCharToBinary(char hexChar) {
    const map<char, string> hexToBinaryMap = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"},
        {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"},
        {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
        {'a', "1010"}, {'b', "1011"}, {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}
    };
    
    auto it = hexToBinaryMap.find(hexChar);
    if (it != hexToBinaryMap.end()) {
        return it->second;
    }
    return "";
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
        group = hexCharToBinary(int(group[0])) + hexCharToBinary(int(group[1]));
        grouptwoTotal += group;
    }
    binseq_base64(grouptwoTotal);
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
    
    cout << "hexStr: ";
    string str2 = "";
    cin >> str2;
    cout << "b64> ";
    hex_base64(str2);
    
    return 0;
}
