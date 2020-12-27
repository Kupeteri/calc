#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>

using namespace std;

string calculate_expression(string s) {
    string str = s;
    set <char> legal{'1','2','3','4','5','6','7','8','9','0','+','-','/','*', '(', ')', '.'};
    int flag = 0;
    vector<string> sorted;
    //TODO: check if string has spaces or if first symbol is not a number
    for (int i = 0; i < str.size(); i++) {
        if (legal.find(str[i]) == legal.end()) {
            cout << "Error: invalid char" << endl;
            return "!";
        }

        if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/')) {
            if(i == 0){
                if(str[i] == '-'){
                    flag = 1;
                    sorted.push_back("0");
                    sorted.push_back("-");
                    continue;
                }
            }
            if(flag == i && (str[i] == '-')){
                if(sorted[sorted.size() - 1] == "+") {
                    sorted.pop_back();
                    sorted.push_back("-");
                    flag++;
                    continue;
                }
                if(sorted[sorted.size() - 1] == "-") {
                    str.replace(i - 1, 2, "+");
                    sorted.pop_back();
                    sorted.push_back("+");
                    flag++;
                    continue;
                }
            }
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
            if(stof(sorted[i + 1]) == 0){
                cout << "Error: division by zero" << endl;
                return "!";
            }
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
                if (bal < 0){
                    cout << "Error: wrong number of brackets";
                    return "!";
                }
            }
        }
        if (bal != 0) {
            cout << "Error: wrong number of brackets";
            return "!";
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
                    if (ans_temp == "!") return "Wrong data";
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
    string s = "-1+(2-29)";
    set <char> legal{'+','-','/','*'};
    for(int i = 1; i < s.size(); i++){
        if((legal.find(s[i - 1]) != legal.end()) && (legal.find(s[i]) != legal.end())) {
            cout << "Error: invalid syntax";
            return 0;
        }
    }
    string a = calculate_full(s);
    cout << a;
    return 0;
}
