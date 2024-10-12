#include <iostream>
#include <cmath>

bool check(int num, int proM[9999]) {
    for (int i = 1; proM[i] < sqrt(num + 1); i++) {
        if ((num % proM[i]) == 0)
            return false;
    }
    return true;
}

int main() {
    const uint32_t max = 4294967295;
    int size = 1;
    int prostM[9999];
    int suProM[100] = { 2, 3, 5, 7 };
    int Ind = 0;
    int suProMSize = 4;
    int EndM[4]={ 1, 3, 7, 9 };

    prostM[0] = 2;
    for (int i = 3; i < 65536; ++i) {
        bool toAdd = true;
        for (int j = 0; j < size; j++) {
            if (i % prostM[j] == 0) {
                toAdd = false;
                break;
            }
        }
        if (toAdd) {
            prostM[size] = i;
            ++size;
        }
    }

    int count = 1;
    while (true) {
        int mNum = suProM[Ind];
        Ind++;
        if (mNum == 0)
            break;
        for (int i = 0; i < 4; ++i) {
            int toCheck = mNum * 10 + EndM[i];
            if (toCheck > max)
                break;
            if (check(toCheck, prostM)) {
                suProM[suProMSize] = toCheck;
                ++suProMSize;
                count++;
            }
        }
    }

    for (int i = 0; i < suProMSize; i++) {
        printf("%d. %d\n", i + 1, suProM[i]);
    }

    return 0;
}
