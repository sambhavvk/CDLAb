#include <iostream>
#include <cstring>
#define MAX 20
using namespace std;

char prod[MAX][10];
char ter[10], nt[10];
char first[10][10], follow[10][10];
int eps[10];
int count1 = 0;

int findPos(char ch) {
    for (int n = 0; nt[n] != '\0'; n++)
        if (nt[n] == ch)
            return n;
    return -1;
}

bool IsCap(char c) {
    return c >= 'A' && c <= 'Z';
}

void add(char *arr, char c) {
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == c)
            return;
    }
    arr[strlen(arr)] = c;
}

void addArr(char *s1, const char *s2) {
    for (int i = 0; s2[i] != '\0'; i++) {
        bool flag = false;
        for (int j = 0; s1[j] != '\0'; j++) {
            if (s2[i] == s1[j]) {
                flag = true;
                break;
            }
        }
        if (!flag)
            s1[strlen(s1)] = s2[i];
    }
}

void addProd(const char *s) {
    prod[count1][0] = s[0];
    for (int i = 3; s[i] != '\0'; i++) {
        if (!IsCap(s[i]))
            add(ter, s[i]);
        prod[count1][i - 2] = s[i];
    }
    prod[count1][strlen(s) - 2] = '\0';
    add(nt, s[0]);
    count1++;
}

void findFirst() {
    int e;
    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count1; j++) {
            int n = findPos(prod[j][0]);
            if (prod[j][1] == (char)238)
                eps[n] = 1;
            else {
                for (int k = 1, e = 1; prod[j][k] != '\0' && e == 1; k++) {
                    if (!IsCap(prod[j][k])) {
                        e = 0;
                        add(first[n], prod[j][k]);
                    } else {
                        int n1 = findPos(prod[j][k]);
                        addArr(first[n], first[n1]);
                        if (eps[n1] == 0)
                            e = 0;
                    }
                }
                if ( e == 1)
                    eps[n] = 1;
            }
        }
    }
}

void findFollow() {
    int n = findPos(prod[0][0]);
    add(follow[n], '#');
    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count1; j++) {
            for (int k = strlen(prod[j]) - 1; k > 0; k--) {
                if (IsCap(prod[j][k])) {
                    n = findPos(prod[j][k]);
                    if (prod[j][k + 1] == '\0') {
                                    int n1 = findPos(prod[j][0]);
                        addArr(follow[n], follow[n1]);
                    }
                    if (IsCap(prod[j][k + 1])) {
                        int n1 = findPos(prod[j][k + 1]);
                        addArr(follow[n], first[n1]);
                        if (eps[n1] == 1) {
                            n1 = findPos(prod[j][0]);
                            addArr(follow[n], follow[n1]);
                        }
                    } else if (prod[j][k + 1] != '\0') {
                        add(follow[n], prod[j][k + 1]);
                    }
                }
            }
        }
    }
}

int main() {
    char s[MAX];
    cout << "Enter the productions (type 'end' at the last of the production):" << endl;
    cin >> s;
    while (strcmp("end", s)) {
        addProd(s);
        cin >> s;
    }
    findFirst();
    findFollow();
    for (int i = 0; i < strlen(nt); i++) {
        cout << nt[i] << "\t";
        cout << first[i];
        if (eps[i] == 1)
            cout << ((char)238) << "\t";
        else
            cout << "\t";
        cout << follow[i] << "\n";
    }
    return 0;
}

/*
 E->TA
A->+TA
A->e
T->FB
B->*FB
B->e
F->(E)
F->i
end
*/