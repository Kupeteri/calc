#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

string calculate_expression(string s) {
    string str = s;
    int flag = 0;
    vector<string> sorted;
    //TODO: check if string has spaces or if first symbol is not a number
    for (int i = 0; i < str.size(); i++) {
        if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/')) {
            sorted.push_back(str.substr(flag, i - flag));
            flag = i + 1;
            string ch = "";
            ch += str[i];
            sorted.push_back(ch);
        }
    }
    sorted.push_back(str.substr(flag, str.size() - flag));
    for (int i = 0; i < sorted.size(); i++) {
        if ((sorted[i] == "*")) {
            float n = stof(sorted[i - 1]) * stof(sorted[i + 1]);
            sorted.erase(sorted.begin() + i - 1, sorted.begin() + i + 2);
            int new_place = i - 1;
            sorted.insert(sorted.begin() + new_place, to_string(n));
            i -= 1;
        }
        if ((sorted[i] == "/")) {
            float n = stof(sorted[i - 1]) / stof(sorted[i + 1]);
            sorted.erase(sorted.begin() + i - 1, sorted.begin() + i + 2);
            int new_place = i - 1;
            sorted.insert(sorted.begin() + new_place, to_string(n));
            i -= 1;
        }
    }
    for (int i = 0; i < sorted.size(); i++) {
        if ((sorted[i] == "-")) {
            float n = stof(sorted[i - 1]) - stof(sorted[i + 1]);
            sorted.erase(sorted.begin() + i - 1, sorted.begin() + i + 2);
            int new_place = i - 1;
            sorted.insert(sorted.begin() + new_place, to_string(n));
            i -= 1;
        }
        if ((sorted[i] == "+")) {
            float n = stof(sorted[i - 1]) + stof(sorted[i + 1]);
            sorted.erase(sorted.begin() + i - 1, sorted.begin() + i + 2);
            int new_place = i - 1;
            sorted.insert(sorted.begin() + new_place, to_string(n));
            i -= 1;
        }
    }
    return sorted[0];
}

string calculate_full(string s) {
    vector<string> exp;
    int now_max;
    do {
        int max_bal = 0;
        int bal = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                bal += 1;
                if (max_bal < bal) max_bal = bal;
            }
            if (s[i] == ')') {
                bal -= 1;
            }
        }
        int flag = 0;
        bal = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                bal += 1;
                if (max_bal == bal) flag = i;
            }
            if (s[i] == ')') {
                if (max_bal == bal) {
                    string ans_temp = calculate_expression(s.substr(flag + 1, i - flag - 1));
                    s.replace(flag, i - flag + 1, ans_temp);
                    i -= (i - flag + 1) - ans_temp.size();
                }
                bal -= 1;
            }
        }
        now_max = max_bal;
    } while (now_max != 0);
    return calculate_expression(s);
}

int main() {
    string s = "((2*(2+1))-1)*2";
    string a = calculate_full(s);
    cout << a;
    return 0;
}
