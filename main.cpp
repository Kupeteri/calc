#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

string calculate_expression(string s){
    string str = s;
    int flag = 0;
    vector <string> sorted;
    //TODO: check if string has spaces or if first symbol is not a number
    for (int i = 0; i < str.size(); i++){
        if((str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/')){
            sorted.push_back(str.substr(flag, i - flag));
            flag = i + 1;
            string ch = "";
            ch += str[i];
            sorted.push_back(ch);
        }
    }
    sorted.push_back(str.substr(flag, str.size() - flag));
    for(int i = 0; i < sorted.size(); i++){
        if((sorted[i] == "*")) {
            float n = stof(sorted[i - 1]) * stof(sorted[i + 1]);
            sorted.erase(sorted.begin() + i - 1, sorted.begin() + i + 2);
            int new_place = i - 1;
            sorted.insert(sorted.begin() + new_place, to_string(n));
            i -= 1;
        }
        if((sorted[i] == "/")) {
            float n = stof(sorted[i - 1]) / stof(sorted[i + 1]);
            sorted.erase(sorted.begin() + i - 1, sorted.begin() + i + 2);
            int new_place = i - 1;
            sorted.insert(sorted.begin() + new_place, to_string(n));
            i -= 1;
        }
    }
    for(int i = 0; i < sorted.size(); i++){
        if((sorted[i] == "-")) {
            float n = stof(sorted[i - 1]) - stof(sorted[i + 1]);
            sorted.erase(sorted.begin() + i - 1, sorted.begin() + i + 2);
            int new_place = i - 1;
            sorted.insert(sorted.begin() + new_place, to_string(n));
            i -= 1;
        }
        if((sorted[i] == "+")) {
            float n = stof(sorted[i - 1]) + stof(sorted[i + 1]);
            sorted.erase(sorted.begin() + i - 1, sorted.begin() + i + 2);
            int new_place = i - 1;
            sorted.insert(sorted.begin() + new_place, to_string(n));
            i -= 1;
        }
    }
    return sorted[0];
}

int main() {
    string s = "2*8+11.0001+2.13-4-4*7.54/123*1212311";
    string a = calculate_expression(s);
    cout << a;
    return 0;
}
