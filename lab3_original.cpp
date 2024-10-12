#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <limits.h>

using namespace std;
static struct termios oldt;

long sum(long a, long b)
{
    long c;
    c = a + b;
    return c;
}

long mul (long a, long b)
{
    long c;
    c = a * b;
    return c;
}

long vich(long a, long b)
{
    long c;
    c = a - b;
    return c;
}

long del(long a, long b) 
{
    long c = 0;
    c = a / b;
    return c;
}

void clean_stdin(void)
{
int c;
do {
c = getchar();
} while (c != '\n' && c != EOF);
}

long step(long a, long b) {
    int c = 1;
    for (int i = 1; i <= b; i++) {
        c *= a;
    }

    return c;
}



void restore_terminal_settings(void)
{
    tcsetattr(0, TCSANOW, &oldt); /* Apply saved settings */
}

void disable_waiting_for_enter(void)
{
    struct termios newt;

    /* Make terminal read 1 char at a time */
    tcgetattr(0, &oldt); /* Save terminal settings */
    newt = oldt; /* Init new settings */
    newt.c_lflag &= ~(ICANON | ECHO); /* Change settings */
    tcsetattr(0, TCSANOW, &newt); /* Apply settings */
    atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends */
}

void print_menu(int comand)
{
    cout << "1. Ввод первого числа " << (comand == 1 ? "<--" : "") << endl;
    cout << "2. Ввод второго числа " << (comand == 2 ? "<--" : "") << endl;
    cout << "3. Сложение " << (comand == 3 ? "<--" : "") << endl;
    cout << "4. Вычитание " << (comand == 4 ? "<--" : "") << endl;
    cout << "5. Умножение " << (comand == 5 ? "<--" : "") << endl;
    cout << "6. Деление " << (comand == 6 ? "<--" : "") << endl;
    cout << "7. Возведение в степень " << (comand == 7 ? "<--" : "") << endl;
    cout << "Для выхода нажмите кнопку q" << endl;
}

long symbol_scanning(long overfmax, bool &count) //эта функция занимается посимвольной читкой введенного числа
{
    bool inputfailure = false, r = false, overf = false;
    bool nummin = false;
    long num = 0, counter = 0; //отобрать возможность сразу нажать "энтр"
    while(true)
    {
        overf = false;
        inputfailure = false;
        char c = '\0';
        c = getchar();
        if(c == '-' && counter == 0) {r = 0; nummin = true;}
        else {
        if (c < '0' || c > '9') //если прочитанный символ - не цифра, лезем проверять что же это
        {
            if (c != '\n') {std::cout<<"Вы ввели неверный символ, повторите попытку"<<std::endl; clean_stdin();} // если это не перенос строки - кидаем ошибку
            else if(counter != 0) {count = true; if(nummin == true) num *= -1; break;} //если это перенос строки не первым же символом - все круто, прерываем цикл
            else {std::cout<<"Вы ввели неверный символ, повторите попытку"<<std::endl;} //если первым - выдаем ошибку
        }
        else
        {
            if(nummin == false) {if (num*10+c-'0' > overfmax) {overf = true; num = 0; clean_stdin(); r = true;} else r = false;} //если дописывание полученной цифры к имеющемуся (см. ниже)
            else {if (num*10+c-'0' > overfmax+1) {overf = true; num = 0; clean_stdin(); r = true;} else r = false;}
             //числу не выйдет за установленные нами рамки (число, которое мы указали при вызове функции) - записываем его (см. ниже)
            if(r == false) //если же выйдет - выходим из цикла с ошибкой overf
            num = num*10+c-'0';
        }
        if(overf == true) {printf("Число превысило максимальный размер. (%ld) Повторите попытку\n", overfmax); overf = true;}
        }
        if(overf == false) counter++; overf = false;
    }
    return num;
}

int main()
{
    long first_digit = 0, second_digit = 0, max_zn = 4294967294, min_zn = -4294967295, max_for_step = 9007199254740993, number = 0, number2 = 0;
    bool need_to_start = false, counter1 = false, counter2 = false;
    system("clear");
    int comand = 1;
    char a = 0, check = 0;
    while (1)
    {
       disable_waiting_for_enter();
        cout << "A = "<< first_digit<<" "<< "B = "<< second_digit<< endl;
        print_menu(comand);
        a = getchar();
        restore_terminal_settings();
        if (a == '\033') { 
        need_to_start = false;
        check = getchar();
        if (check == '[') 
        {
        switch(getchar()) 
        {
            case 'A':
                if (comand != 1)comand--; else{comand = 1;}
                system("clear");
                break;
            case 'B':
                if (comand != 7)comand++; else{comand = 7;}
                system("clear"); 
                break;
            default: 
                break;
                }
            }
        }
    else
    {
        system("clear");
        if (a != '\033')
        {
            need_to_start = false;
            switch (a)
            {
            case 49:
                comand = 1;
                need_to_start = false;
                break;
            case 50:
                comand = 2;
                need_to_start = false;
                break;
            case 51:
                comand = 3;
                break;
            case 52:
                comand = 4;
                break;
            case 53:
                comand = 5;
                break;
            case 54:
                comand = 6;
                break;
            case 55:
                comand = 7;
                break;
            case 113:
                comand = 8;
            case 10:
                need_to_start = true;
                break;
            default:
                break;
            }
        }
    }
    if (need_to_start == true)
    {
        system("clear");
        if (comand >= 1 && comand <=8)
        {
            if (comand == 1)
            {
                cout<<"Введите первое число"<<endl;
                first_digit = symbol_scanning(max_zn, counter1);
                system("clear");
                //cout << first_digit;
            }
            if (comand == 2)
            {
                cout<<"Введите второе число"<<endl;
                second_digit = symbol_scanning(max_zn, counter2);
                system("clear");
                //cout << second_digit;
            }
            if (comand == 3)
            {
                if (counter1 == true && counter2 == true)
                {
                    cout << "Oтвет : " << sum(first_digit, second_digit)<< endl;
                }
            }
            if (comand == 4)
            {
                if (counter1 == true && counter2 == true)
                {
                    cout << "Oтвет : " << vich(first_digit, second_digit)<< endl;
                }
            }
            if (comand == 5)
            {    
                if (counter1 == true && counter2 == true)
                    {
                        cout << "Oтвет : " << mul(first_digit, second_digit)<< endl;
                    }
            }
            if (comand == 6)
            { 
                if (counter1 == true && counter2 == true)
                {
                    if (second_digit == 0)
                    {
                        cout<< "На ноль делить нельзя!"<< endl;
                    }
                    else if (first_digit < 0 || second_digit < 0)
                    {
                        cout<<"Нельзя делить отрицательное число и на отрицательное число"<<endl;
                    }
                    else
                    {
                        cout<<"Ответ : "<< del(first_digit, second_digit)<< endl;
                    }
                }
            }
            if (comand == 7)
            {
                long stepen = step(first_digit, second_digit);
                if (counter1 == true && counter2 == true)
                {
                    if (first_digit < 0)
                    {
                        cout<<"Нельзя возводить отрицательное число в какую-либо степень"<<endl;
                    }
                    else if (second_digit < 0)
                    {
                        cout<<"Нельзя возводить число в отрицательную степень"<<endl;
                    }
                    else if (second_digit > 25)
                    {
                        cout<< "Вы пытаетесь возвести в сильно большую степень"<< endl;
                    }
                    else if (stepen > 100000000)
                    {
                        cout<< "Вы пытаетесь возвести в сильно большую степень"<< endl;
                    }
                    else if (first_digit == 0)
                    {
                        cout<< "Нельзя возводить число 0 в какую-либо степень"<<endl;
                    }
                    else if (stepen < 100000000)
                    {
                        cout << "Oтвет : " << step(first_digit, second_digit)<< endl;
                    }
                }
            }
            //break;
            if (comand == 8){break;}
        }
    }
    }
}
