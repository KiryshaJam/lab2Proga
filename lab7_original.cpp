#include <iostream>
#include <stdio.h>
#include <cstdio>

using namespace std;

int main() {
    system("clear");
    char iS[71];
    int i = 0;

    cout<<"Введите строку (максимальная длина 70 символов): "<<endl;
    char c = getchar();
    while (c != '\n' && i < 70) {
        iS[i] = c;
        c = getchar();
        i++;
    }
    iS[i] = '\0';

    int maxL = 0, start = 0, end = 0;

    for (int j = 0; j < i; j++) {
        for (int k = j; k < i; k++) {
            int polindrome = 1;
            int m = j, n = k;
            while (m < n) {
                if (iS[m] != iS[n]) {
                    polindrome = 0;
                    break;
                }
                m++;
                n--;
            }
            if (polindrome && k - j + 1 > maxL) {
                start = j;
                end = k;
                maxL = k - j + 1;
            }
        }
    }

    if (maxL > 1) {
        cout<<"Самый длинный полиндром: ";
        for (int l = start; l <= end; l++) {
            printf("%c", iS[l]);
        }
        cout<<endl<<"Длина: "<< maxL<<endl;
    }
    else {
        cout<<"В введённой стороке нет полиндрома длиннее 1 символа"<<endl;
    }

    return 0;
}
