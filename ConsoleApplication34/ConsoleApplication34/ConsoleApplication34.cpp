#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOpeningBracket(char c) {
    return (c == '(' || c == '[' || c == '{');
}

bool isClosingBracket(char c) {
    return (c == ')' || c == ']' || c == '}');
}

bool matches(char opening, char closing) {
    if (opening == '(' && closing == ')') return true;
    if (opening == '[' && closing == ']') return true;
    if (opening == '{' && closing == '}') return true;
    return false;
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    string input;
    cout << "Введите строку: ";
    getline(cin, input);

    stack<char> bracketStack;
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (isOpeningBracket(c)) {
            bracketStack.push(c);
        }
        else if (isClosingBracket(c)) {
            if (bracketStack.empty()) {
                cout << "Ошибка: Обнаружена закрывающая скобка без соответствующей открывающей на позиции " << i << endl;
                cout << "Строка до ошибки: " << input.substr(0, i) << endl;
                return 0;
            }

            char top = bracketStack.top();
            bracketStack.pop();

            if (!matches(top, c)) {
                cout << "Ошибка: Несоответствие скобок на позиции " << i << endl;
                cout << "Строка до ошибки: " << input.substr(0, i) << endl;
                return 0;
            }
        }
    }

    if (bracketStack.empty()) {
        cout << "Строка корректна." << endl;
    }
    else {
        cout << "Ошибка: Обнаружена открывающая скобка без соответствующей закрывающей." << endl;
        cout << "Строка до ошибки: " << input << endl;
        return 0;
    }

    return 0;
}
