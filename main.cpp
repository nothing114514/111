#include <iostream>
#include <fstream>
#include <stack>
#include <string>

bool isMatchingPair(char char1, char char2) {
    return (char1 == '(' && char2 == ')') ||
           (char1 == '{' && char2 == '}') ||
           (char1 == '[' && char2 == ']');
}

bool checkBrackets(const std::string& str, std::stack<char>& unmatched) {
    std::stack<char> s;
    for (char ch : str) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.empty() || !isMatchingPair(s.top(), ch)) {
                unmatched.push(ch);
                return false;
            } else {
                s.pop();
            }
        }
    }
    
    while (!s.empty()) {
        unmatched.push(s.top());
        s.pop();
    }
    
    return unmatched.empty();
}

std::string fixBrackets(const std::string& str) {
    std::stack<char> unmatched;
    if (checkBrackets(str, unmatched)) {
        return str;
    }
    
    std::string fixedStr = str;
    while (!unmatched.empty()) {
        char unmatchedChar = unmatched.top();
        unmatched.pop();
        if (unmatchedChar == '(' || unmatchedChar == '{' || unmatchedChar == '[') {
            fixedStr += (unmatchedChar == '(') ? ')' :
                        (unmatchedChar == '{') ? '}' :
                        ']';
        } else {
            fixedStr = (unmatchedChar == ')') ? '(' + fixedStr :
                       (unmatchedChar == '}') ? '{' + fixedStr :
                       '[' + fixedStr;
        }
    }
    
    return fixedStr;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open file";
        return 1;
    }

    std::string line;
    std::string content;

    while (std::getline(file, line)) {
        content += line + "\n";
    }

    file.close();

    std::stack<char> unmatched;
    if (checkBrackets(content, unmatched)) {
        std::cout << "Brackets are balanced." << std::endl;
    } else {
        std::cout << "Brackets are not balanced." << std::endl;
        std::string fixedContent = fixBrackets(content);
        std::cout << "Fixed content:\n" << fixedContent << std::endl;

        std::ofstream outFile("output.txt");
        outFile << fixedContent;
        outFile.close();
    }

    return 0;
}

