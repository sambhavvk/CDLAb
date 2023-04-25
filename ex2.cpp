#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
using namespace std;

bool isPunctuator(char ch) {
    return strchr(" +-*/<>=(),;[]{}&|", ch) != nullptr;
}

bool validIdentifier(char *str) {
    if (isdigit(str[0]) || isPunctuator(str[0])) return false;
    for (int i = 1; str[i]; i++) if (isPunctuator(str[i])) return false;
    return true;
}

bool isOperator(char ch) {
    return strchr("+-*/><=|&", ch) != nullptr;
}

bool isKeyword(char *str) {
    const char *keywords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return",
                              "char", "case", "long", "short", "typedef", "switch", "unsigned", "void", "static",
                              "struct", "sizeof", "volatile", "enum", "const", "union", "extern", "bool", nullptr};
    for (int i = 0; keywords[i]; i++) if (!strcmp(str, keywords[i])) return true;
    return false;
}

bool isNumber(char *str) {
    if (!str[0]) return false;
    int numOfDecimal = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '.') numOfDecimal++;
        if (numOfDecimal > 1 || (!isdigit(str[i]) && (str[i] != '.' || i == 0))) return false;
    }
    return true;
}

char *subString(char *realStr, int l, int r) {
    char *str = (char *) malloc(sizeof(char) * (r - l + 2));
    for (int i = l; i <= r; i++) str[i - l] = realStr[i];
    str[r - l + 1] = '\0';
    return str;
}

void parse(char *str) {
    int left = 0, right = 0, len = strlen(str);
    while (right <= len && left <= right) {
        if (!isPunctuator(str[right])) right++;
        else {
            if (left != right) {
                char *sub = subString(str, left, right - 1);
                if (isKeyword(sub)) cout << sub << " IS A KEYWORD\n";
                else if (isNumber(sub)) cout << sub << " IS A NUMBER\n";
                else cout << sub << (validIdentifier(sub) ? " IS A VALID IDENTIFIER\n" : " IS NOT A VALID IDENTIFIER\n");
            }
            if (isOperator(str[right])) cout << str[right] << " IS AN OPERATOR\n";
            right++, left = right;
        }
    }
}

int main() {
    char c[100] = "int a = b * c";
    parse(c);
    return 0;
}
