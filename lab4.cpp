#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <limits.h>
#include <fstream>

using namespace std;
static struct termios oldt;

void restore_terminal_settings(void)
{
    tcsetattr(0, TCSANOW, &oldt); /* Apply saved settings */
}

void clean_stdin(void)
{
    int c;
    do 
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
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





void print_menu(int comand)
{
    cout << "1. Ввод первого числа " << (comand == 1 ? "<--" : "") << endl;
    cout << "2. Ввод второго числа " << (comand == 2 ? "<--" : "") << endl;
    cout << "3. Раскручивание из левого верхнего угла по часовой стрелке " << (comand == 3 ? "<--" : "") << endl;
    cout << "4. Раскручивание из правого верхнего угла против часовой стрелки " << (comand == 4 ? "<--" : "") << endl;
    cout << "5. Раскручивание из правого нижнего угла по часовой стрелке " << (comand == 5 ? "<--" : "") << endl;
    cout << "6. Раскручивание из правого нижнего угла против часовой стрелки " << (comand == 6 ? "<--" : "") << endl;
    cout << "7. Выгрузить спираль из текстового файла " << (comand == 7 ? "<--" : "") << endl;
    cout << "8. Выгрузить спираль из бинарного файла " << (comand == 8 ? "<--" : "") << endl;
    cout << "Для выхода нажмите q + enter" << endl;
}

void print_vopros(int mtx[20][20], int n, int m)
{
    cout<< "Нажмите клавишу b, чтобы записать спираль в бинарный файл"<< endl;
    cout<< "Нажмите клавишу t, чтобы записать спираль в текстовый файл"<< endl;
    cout<< "Для продолжения нажмите любую другую клавишу "<< endl;
    disable_waiting_for_enter();
    char q = getchar();
    restore_terminal_settings();
   
    if (q == 'b')
    {
       
       ofstream fout("piska.bin", ios_base::binary);

       fout.write((char*)&m, sizeof(int));
       fout.write((char*)&n, sizeof(int));

       for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				fout.write((char*)&mtx[i][j], sizeof(int));

                /* fout.write((char*)&mtx[i][j], sizeof(int)); */
            }
        }
       fout.close();
    }

    
    if (q == 't')
    {
        char z = 0;
        
        ofstream file("jopa.txt");

        if (file.is_open()) {
            file << "   ";
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                   file << mtx[i][j] << setw(4);
            }
                file << endl;
        }
            file.close();
        /* disable_waiting_for_enter();
        z = getchar();
        restore_terminal_settings(); */
        }
    }

}

void printBin(int n, int m)
{
    int arrr[20][20];

    ifstream fin("binaryFile.bin", ios_base::binary);

    if (!fin.is_open()){
        cout<< "Ошибка открытия файла"<< endl;
        fin.close();
        disable_waiting_for_enter();
        char q = getchar();
        restore_terminal_settings();
    }
    else {
        ifstream fin("piska.bin", ios_base::binary);
		fin.read((char*)&n, sizeof(int));
		fin.read((char*)&m, sizeof(int));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				fin.read((char*)&arrr[i][j], sizeof(int));
				cout << arrr[i][j] << "\t";
			}
			cout << endl;
		}
        disable_waiting_for_enter();
        char q = getchar();
        restore_terminal_settings();
        fin.close();
    }
}


int matrix1(int x, int y)
{
    const int(n) = 20;
    const int(m) = 20;
    int A[20][20];
    int j = 0;
    int i = 0;
    int k = 0;
    int p = 0;
    int a = x;
    int b = y;
    int mx = x * y;
    for (int i = 0; i < n; ++i) {  
        for (int j = 0; j < m; ++j) {
            A[i][j] = 0;
        }
    }
    for (int d = 0; d <= 10; d++) {
        if (k == mx) { break; }
        for (int j = p; j < x; ++j) {
            if (k == mx) { break; }
            k++;
            A[p][j] = k;
        }
        if (k == mx) { break; }
        for (int i = p + 1; i < y; ++i) {
            if (k == mx) { break; }
            k++;
            A[i][x - 1] = k;
        }
        if (k == mx) { break; }
        for (int j = x - 2; j >= p; j = j - 1) {
            if (k == mx) { break; }
            k++;
            A[y - 1][j] = k;
        }
        if (k == mx) { break; }
        for (int i = y - 2; i > p; i = i - 1) {
            if (k == mx) { break; }
            k++;
            A[i][p] = k;
        }
        p = p + 1;
        x = x - 1;
        y = y - 1;
    }
    for (int i = 0; i < b; ++i) { 
        for (int j = 0; j < a; ++j) {
            cout.width(4);
            cout << A[i][j];
        }
        cout << endl; 
    }
    print_vopros(A, a , b);
    return 0;
}

int matrix2(int x, int y) {
    const int(n) = 20;
    const int(m) = 20;
    int A[20][20];
    int j = 0;
    int i = 0;
    int k = 0;
    int p = 0;
    int a = x;
    int b = y;
    int mx = x * y;
    for (int i = 0; i < n; ++i) {  
        for (int j = 0; j < m; ++j) {
            A[i][j] = 0;
        }
    }

    for (int d = 0; d <= 10; d++) {
        if (k == mx) { break; }
        for (int j = x - 1; j >= p; j = j - 1) {
            if (k == mx) { break; }
            k++;
            A[p][j] = k;
        }
        if (k == mx) { break; }
        for (int i = p + 1; i < y; ++i) {
            if (k == mx) { break; }
            k++;
            A[i][p] = k;
        }
        if (k == mx) { break; }
        for (int j = p + 1; j < x; j++) {
            if (k == mx) { break; }
            k++;
            A[y - 1][j] = k;
        }
        if (k == mx) { break; }
        for (int i = y - 2; i > p; i = i - 1) {
            if (k == mx) { break; }
            k++;
            A[i][x - 1] = k;
        }
        if (k == mx) { break; }
        p = p + 1;
        x = x - 1;
        y = y - 1;

    }

    for (int i = 0; i < b; ++i) { 
        for (int j = 0; j < a; ++j) {
            cout.width(4);
            cout << A[i][j];
        }
        cout << endl; 
    }
    print_vopros(A, a , b);
    return 0;
}

int matrix3(int x, int y) {
    const int(n) = 20;
    const int(m) = 20;
    int A[20][20];
    int j = 0;
    int i = 0;
    int k = 0;
    int p = 0;
    int a = x;
    int b = y;
    int mx = x * y;
    for (int i = 0; i < n; ++i) {  
        for (int j = 0; j < m; ++j) {
            A[i][j] = 0;
        }
    }

    for (int d = 0; d <= 10; d++) {
        if (k == mx) { break; }
        for (int j = x - 1; j >= p; j = j - 1) {
            if (k == mx) { break; }
            k++;
            A[y - 1][j] = k;
        }
        if (k == mx) { break; }
        for (int i = y - 2; i >= p; i = i - 1) {
            if (k == mx) { break; }
            k++;
            A[i][p] = k;
        }
        if (k == mx) { break; }
        for (int j = p + 1; j < x; ++j) {
            if (k == mx) { break; }
            k++;
            A[p][j] = k;
        }
        if (k == mx) { break; }
        for (int i = p + 1; i < y - 1; ++i) {
            if (k == mx) { break; }
            k++;
            A[i][x - 1] = k;
        }
        if (k == mx) { break; }
        p = p + 1;
        x = x - 1;
        y = y - 1;

    }

    for (int i = 0; i < b; ++i) {  
        for (int j = 0; j < a; ++j) {
            cout.width(4);
            cout << A[i][j];
        }
        cout << endl; 
    }
    print_vopros(A, a , b);
    return 0;
}

int matrix4(int x, int y) {
    const int(n) = 20;
    const int(m) = 20;
    int A[20][20];
    int j = 0;
    int i = 0;
    int k = 0;
    int p = 0;
    int a = x;
    int b = y;
    int mx = x * y;
    for (int i = 0; i < n; ++i) {  
        for (int j = 0; j < m; ++j) {
            A[i][j] = 0;
        }
    }

    for (int d = 0; d <= 10; d++) {
        for (int i = y - 1; i >= p; i = i - 1) {
            if (k == mx) { break; }
            k++;
            A[i][x - 1] = k;
        }
        for (int j = x - 2; j >= p; j = j - 1) {
            if (k == mx) { break; }
            k++;
            A[p][j] = k;
        }
        if (k == mx) { break; }
        for (int i = p + 1; i < y; ++i) {
            if (k == mx) { break; }
            k++;
            A[i][p] = k;
        }
        for (int j = p + 1; j < x - 1; j++) {
            if (k == mx) { break; }
            k++;
            A[y - 1][j] = k;
        }
        p = p + 1;
        x = x - 1;
        y = y - 1;

    }

    for (int i = 0; i < b; ++i) {  
        for (int j = 0; j < a; ++j) {
            cout.width(4);
            cout << A[i][j];
        }
        cout << endl; 
    }
    print_vopros(A, a , b);
    return 0;
}



int main()
{
    int first_digit = 0, second_digit = 0, comand = 1, max_zn = 20;
    bool need_to_start = false, counter1 = false,
    counter2 = false;
    char a = 0, check = 0, z = 0;
    while (true)
{
        system("clear");
        disable_waiting_for_enter();
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
                if (comand != 8)comand++; else{comand = 8;}
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
                need_to_start = false;
                break;
            case 52:
                comand = 4;
                need_to_start = false;
                break;
            case 53:
                comand = 5;
                need_to_start = false;
                break;
            case 54:
                comand = 6;
                need_to_start = false;
                break;
            case 55:
                comand = 7;
                need_to_start = false;
                break;
            case 56:
                comand = 8;
                need_to_start = false;
                break;
            case 113:
                comand = 9;
                need_to_start = false;
                break;
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
        if (comand >= 1 && comand <=9)
        {
            if (comand == 1)
            {
                cout<<"Введите первое число"<<endl;
                first_digit = symbol_scanning(max_zn, counter1);
                system("clear");
            }
            if (comand == 2)
            {
                cout<<"Введите второе число"<<endl;
                second_digit = symbol_scanning(max_zn, counter2);
                system("clear");
            }
            if (comand == 3)
            {
                if (counter1 == true && counter2 == true)
                {
                   if (first_digit > 0 && second_digit > 0)
                {
                    matrix1(first_digit, second_digit);
                    disable_waiting_for_enter();
                    z = getchar();
                    restore_terminal_settings();

                }
                else
                {
                    cout<< "Введены отрицательные значения, это недопустимо"<<endl;
                }
                }
            }    
            if (comand == 4)
            {
                if (counter1 == true && counter2 == true)
                {
                    if (first_digit > 0 && second_digit > 0)
                    {
                    matrix2(first_digit, second_digit);
                    disable_waiting_for_enter();
                    z = getchar();
                    restore_terminal_settings();
                    }
                    else
                    {
                        cout<< "Введены отрицательные значения, это недопустимо"<<endl;
                    }
                }
            }
            if (comand == 5)
            {
                if (counter1 == true && counter2 == true)
                {
                    if (first_digit > 0 && second_digit > 0)
                    {
                    matrix3(first_digit, second_digit);
                    disable_waiting_for_enter();
                    z = getchar();
                    restore_terminal_settings();
                    }
                    else
                    {
                        cout<< "Введены отрицательные значения, это недопустимо"<<endl;
                    }
                }
            }
            if (comand == 6)
            {
                if (counter1 == true && counter2 == true)
                {
                    if (first_digit > 0 && second_digit > 0)
                    {
                    matrix4(first_digit, second_digit);
                    disable_waiting_for_enter();
                    z = getchar();
                    restore_terminal_settings();
                    }
                    else
                    {
                        cout<< "Введены отрицательные значения, это недопустимо"<<endl;
                    }
                }
            }
            if (comand == 7)
            {
                if (first_digit == 0 || second_digit==0){
                cout<<"Вы ввели не все значения"<<endl;
                disable_waiting_for_enter();
                z = getchar();
                restore_terminal_settings();
                }
                else{
                    string path = "jopa.txt";

                    ifstream fin;

                    fin.open(path);

                    if (!fin.is_open()){
                        cout<< "Ошибка открытия файла"<<endl;
                    }
                    else
                    {
                        char ch;
                        while (fin.get(ch))
                        {
                            cout << ch;
                        }
                        disable_waiting_for_enter();
                        z = getchar();
                        restore_terminal_settings();
                        
                    }
                    fin.close();
                }
            }
            if (comand == 8)
            {   
                if (first_digit == 0 || second_digit==0){
                    cout<<"Вы ввели не все значения"<<endl;
                    disable_waiting_for_enter();
                    z = getchar();
                    restore_terminal_settings();
                }
                else{
                printBin(first_digit, second_digit);
                }
            }
            if (comand == 9 ){break;}
        
        }
    }
}
return 0;
}
