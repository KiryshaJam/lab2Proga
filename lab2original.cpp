#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int sum(int a, int b)
{
    int c;
    c = a + b;
    return c;
}

int mul (int a, int b)
{
    int c;
    c = a * b;
    return c;
}

int main(void)
{
    int first_digit = 0;
    int second_digit = 0;
    int comand = 0;
    int maxzn = 40000;
    int minzn = -40000;
    int number;
    int number2;
    cout << "\033[2J\033[1;1H";
    while (1)
    {
        cout << "выберите операцию\n 1-ввод первого числа\n 2-ввод второго числа\n 3-сложение\n 4-умножение\n 5-выйти из программы\n";
        scanf("%d", &comand);
        if (comand == 1 || comand == 2 || comand == 3 || comand == 4 || comand == 5)
        {
            if (comand == 1)
            {
                cout << "\033[2J\033[1;1H";
                cout <<"введите число в диапазоне от -39999 до 39999" << endl;
                if ((cin >> number) && number < maxzn && number > minzn)
                {
                    
                    first_digit = number;
                    cout << "\033[2J\033[1;1H";
                }
                else
                {
                    cout << "\033[2J\033[1;1H";
                    cout <<"введено слишком большое число или неверное значение" << endl;
                    cin.clear();
                }
            }
            if (comand == 2)
            {
                cout << "\033[2J\033[1;1H";
                cout <<"введите число в диапазоне от -39999 до 39999"<< endl;
                if ((cin >> number2).good() && number2 < maxzn && number2 > minzn)
                {
                    second_digit = number2;
                    cout << "\033[2J\033[1;1H";
                }
                else
                {
                    cout << "\033[2J\033[1;1H";
                    cout <<"введено слишком большое число или неверное значение" << endl;
                    cin.clear();
                }
            }
            if (comand == 3)
            {
                cout << "\033[2J\033[1;1H";
                cout << "ОТВЕТ: " << sum(first_digit, second_digit) << endl;
            }
            if (comand == 4)
            {
                cout << "\033[2J\033[1;1H";
                cout << "ОТВЕТ: " << mul(first_digit, second_digit) << endl;
            }
            if (comand == 5)
            {
                break;
            }
        }
        else
        {
            cout << "\033[2J\033[1;1H";
            cout << "выбрана неверная операция\n";
        }
    }
    return 0;
}






/*int symbol_scanning(int overfmax) //эта функция занимается посимвольной читкой введенного числа
{
    bool inputfailure = false, count = false, r = false, overf = false;
    int num = 0, counter = 0; //отобрать возможность сразу нажать "энтр"
    while(true)
    {
        overf = false;
        inputfailure = false;
        char c = '\0';
        scanf("%c", &c);
        if (c < '0' || c > '9') //если прочитанный символ - не цифра, лезем проверять что же это
        {
            if (c != '\n') {printf("Вы ввели неверный символ, повторите попытку\n"); clean_stdin();} // если это не перенос строки - кидаем ошибку
            else if(counter != 0) {count = true; break;} //если это перенос строки не первым же символом - все круто, прерываем цикл
            else {printf("Вы ввели неверный символ, повторите попытку\n");} //если первым - выдаем ошибку
        }
        else
        {
            if (num*10+c-'0' > overfmax) {overf = true; num = 0; clean_stdin(); r = true;} //если дописывание полученной цифры к имеющемуся (см. ниже)
            else r = false; //числу не выйдет за установленные нами рамки (число, которое мы указали при вызове функции) - записываем его (см. ниже)
            if(r == false) //если же выйдет - выходим из цикла с ошибкой overf
            num = num*10+c-'0';
        }
        if(overf == true) printf("Число превысило максимальный размер (%d). Повторите попытку\n", overfmax);
        counter++;
    }
    return num;
}*/