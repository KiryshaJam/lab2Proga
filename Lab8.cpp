#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>

static struct termios oldt;

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

void clean_stdin(void) //очистка потока ввода, применяется там где без нее scanf начнет читать всякие необработанные символы
{
int c;
do {
c = getchar();
} while (c != '\n' && c != EOF);
}

int symbol_scanning_time(int overfmax, int time[3], int hm) //эта функция занимается посимвольной читкой введенного числа
{
    bool inputfailure = false, count = false, r = false, overf = false;
    int num = 0, counter = 0; //отобрать возможность сразу нажать "энтр"
    while(true){
                overf = false;
                inputfailure = false;
                char c = '\0';
                scanf("%c", &c);
                if (c < '0' || c > '9')   //если прочитанный символ - не цифра, лезем проверять что же это              
                {
                    if (c != '\n') {printf("Вы ввели неверный символ, повторите попытку\n"); clean_stdin();} // если это не перенос строки - кидаем ошибку
                    else if(counter != 0) {count = true; break;} //если это перенос строки не первым же символом - все круто, прерываем цикл
                    else {printf("Вы ввели неверный символ, повторите попытку\n");} //если первым - выдаем ошибку
                }
                else{
                if (num*10+c-'0' > overfmax) {overf = true; num = 0; clean_stdin(); r = true;} //если дописывание полученной цифры к имеющемуся (см. ниже)
                else r = false;  //числу не выйдет за установленные нами рамки (число, которое мы указали при вызове функции) - записываем его (см. ниже) 
                if(r == false)   //если же выйдет - выходим из цикла с ошибкой overf
                num = num*10+c-'0';
                }
                if(overf == true) 
                {
                    system("clear");
                    printf("Число превысило максимум (%d). Повторите попытку\n", overfmax);      
                    if(hm == 0) 
                        printf("Введите первое время. Введите часы, затем нажмите Enter\n");   
                    if(hm == 1) 
                    {
                        printf("Введите первое время. Введите минуты, затем нажмите Enter\n");
                        printf("%02d:", time[0]);
                    }   
                    if(hm == 2)
                    {
                        printf("Введите первое время. Введите секунды, затем нажмите Enter\n");
                        printf("%02d:%02d:", time[0], time[1]);
                    }        
                }
                counter++;
    }
    return num;
}

int symbol_scanning_date(int overfmax, int date[3], int hm) //эта функция занимается посимвольной читкой введенного числа
{
    bool inputfailure = false, count = false, r = false, overf = false;
    int num = 0, counter = 0; //отобрать возможность сразу нажать "энтр"
    while(true){
                overf = false;
                inputfailure = false;
                char c = '\0';
                scanf("%c", &c);
                if (c < '0' || c > '9')   //если прочитанный символ - не цифра, лезем проверять что же это              
                {
                    if (c != '\n') {printf("Вы ввели неверный символ, повторите попытку\n"); clean_stdin();} // если это не перенос строки - кидаем ошибку
                    else if(counter != 0) {count = true; break;} //если это перенос строки не первым же символом - все круто, прерываем цикл
                    else {printf("Вы ввели неверный символ, повторите попытку\n");} //если первым - выдаем ошибку
                }
                else{
                if (num*10+c-'0' > overfmax) {overf = true; num = 0; clean_stdin(); r = true;} //если дописывание полученной цифры к имеющемуся (см. ниже)
                else r = false;  //числу не выйдет за установленные нами рамки (число, которое мы указали при вызове функции) - записываем его (см. ниже) 
                if(r == false)   //если же выйдет - выходим из цикла с ошибкой overf
                num = num*10+c-'0';
                }
                if(overf == true) 
                {
                    system("clear");
                    printf("Число превысило максимум (%d). Повторите попытку\n", overfmax);      
                    if(hm == 0) 
                        printf("Введите год\n");   
                    if(hm == 1) 
                    {
                        printf("Введите месяц\n");                        
                    }   
                    if(hm == 2)
                    {
                        printf("Введите день\n");                        
                    }        
                }
                counter++;
    }
    return num;
}

int symbol_scanning_digits(int overfmax) //эта функция занимается посимвольной читкой введенного числа
{
    bool inputfailure = false, count = false, r = false, overf = false;
    int num = 0, counter = 0; //отобрать возможность сразу нажать "энтр"
    while(true){
                overf = false;
                inputfailure = false;
                char c = '\0';
                scanf("%c", &c);
                if (c < '0' || c > '9')   //если прочитанный символ - не цифра, лезем проверять что же это              
                {
                    if (c != '\n') {printf("Вы ввели неверный символ, повторите попытку\n"); clean_stdin();} // если это не перенос строки - кидаем ошибку
                    else if(counter != 0) {count = true; break;} //если это перенос строки не первым же символом - все круто, прерываем цикл
                    else {printf("Вы ввели неверный символ, повторите попытку\n");} //если первым - выдаем ошибку
                }
                else{
                if (num*10+c-'0' > overfmax) {overf = true; num = 0; clean_stdin(); r = true;} //если дописывание полученной цифры к имеющемуся (см. ниже)
                else r = false;  //числу не выйдет за установленные нами рамки (число, которое мы указали при вызове функции) - записываем его (см. ниже) 
                if(r == false)   //если же выйдет - выходим из цикла с ошибкой overf
                num = num*10+c-'0';
                }
                if(overf == true) printf("Число превысило максимальный размер (%d). Повторите попытку\n", overfmax);
                counter++;
    }
    return num;
}

int p_det(int date[3], bool visoc)
{
    if(date[1] == 2)
    {
        if(visoc) return 29;
        else return 28;
    }
    if(date[1] == 2 || date[1] == 4 || date[1] == 6 || date[1] == 9 || date[1] == 11)
        return 30;
    return 31;
}

/* int weekdayja_det(int date[3])
{
    if (date[0] == 2024) return 0;
    if (date[0] == 2023) return 7;
} */

const char* weekday_det(int date[3], bool visoc)
{ 
    int a;
    /* int weekdayja = weekdayja_det(date);
    int days = 0;
    for(int i = 1; i < date[1]; i++)
    {
        int p = p_det(date, visoc);
        days += p;
    }
    days += date[2]-1;
    int a = ((days % 7) + weekdayja);
    if(a >= 7) a -= 7; */
    int m;
    m = date[1] - 2; if(m < 1) m += 12;
    int c = date[0] / 100;
    int y = date[0] % 100;
    if(m == 11 || m == 12) y--; if(y < 0) {c--; y += 100;}
    int b = (13*m - 1) / 5, g = y / 4, r = c / 4;

    int u = date[2] + b + y + g + r - 2*c;
    a = u % 7;

    /* где d - число месяца;
    m - номер месяца, начиная с марта (март=1, апрель=2, ..февраль=12);
    y - номер года в столетии (например, для 1965 года y=65. Для января и февраля 1965 года, т. е. для m=11 или m=12 номер года надо брать предыдущий, т. е. y=64);
    c - количество столетий (например, для 2000 года c=20. И здесь для января и февраля 2000 года надо брать предыдущее столетие с=19);
    квадратные скобки означают целую часть полученного числа (отбрасываем дробную) .

    Результат W делите на 7 и модуль остатка от деления даст день недели (воскресенье=0, понедельник=1, ..суббота=6) */
    switch(a)
    {
        case 1: return "Понедельник"; break;
        case 2: return "Вторник"; break;
        case 3: return "Среда"; break;
        case 4: return "Четверг"; break;
        case 5: return "Пятница"; break;
        case 6: return "Суббота"; break;
        case 0: return "Воскресенье"; break;
        default: return "Error";
    }
}

int main()
{
    system("clear");
    char a;
    bool timee = false, dataa = false, endd = false, insideend = false;
    system("clear");
    while(true)
    {
    printf("Выберите пункт меню\n");
    printf("1. Работа с временем\n");
    printf("2. Работа с датами\n");
    printf("Esc. Выход из программы\n");
    disable_waiting_for_enter();
    a = getchar();
    restore_terminal_settings();
    switch(a)
    {
        case 49: timee = true; break;
        case 50: dataa = true; break;
        case 27: endd = true; break;
        default: system("clear"); printf("Введен неверный символ, повторите попытку\n");
    }
    printf("\n");
    if(timee == true)
    {
        int time1[3], time2[3], time3[3];
        bool counter1 = false, counter2 = false, counterfailure = false, sum = false, dedu = false;
        while(true)
        {            
            system("clear");
            if(counterfailure) printf("Для начала введите оба времени\n\n"); counterfailure = false;
            if(sum) printf("Суммма равна %02d:%02d:%02d\n", time3[0], time3[1], time3[2]); sum = false;
            if(dedu) printf("Разность равна %02d:%02d:%02d\n", time3[0], time3[1], time3[2]); dedu = false;
            // printf("Выбрана работа со временем\n");
            printf("Выберете один из пунктов меню\n");
            printf("1. Ввести первое время\n");
            printf("2. Ввести второе время\n");
            printf("3. Сложение\n");
            printf("4. Вычитание\n");
            printf("Esc. Вернуться в основное меню\n");
            printf("Q. Выйти из программы\n\n");
            if(counter1) printf("Первое время - %02d:%02d:%02d\n", time1[0], time1[1], time1[2]); else printf("Первое время пока не введено\n");
            if(counter2) printf("Второе время - %02d:%02d:%02d\n\n", time2[0], time2[1], time2[2]); else printf("Второе время пока не введено\n\n");
            disable_waiting_for_enter();
            a = getchar();
            restore_terminal_settings();
            switch(a)
            {
                case 49: 
                    system("clear");
                    printf("Введите первое время. Введите часы, затем нажмите Enter\n");
                    time1[0] = symbol_scanning_time(23, time1, 0);
                    system("clear");
                    printf("Введите первое время. Введите минуты, затем нажмите Enter\n");
                    printf("%02d:", time1[0]);
                    time1[1] = symbol_scanning_time(59, time1, 1);
                    system("clear");
                    printf("Введите первое время. Введите секунды, затем нажмите Enter\n");
                    printf("%02d:%02d:", time1[0], time1[1]);
                    time1[2] = symbol_scanning_time(59, time1, 2);
                    system("clear");
                    printf("Введенное время: %02d:%02d:%02d\n", time1[0], time1[1], time1[2]);
                    printf("Нажмите любую клавишу для продолжения\n");
                    disable_waiting_for_enter();
                    getchar();
                    restore_terminal_settings();
                    counter1 = true;
                    break;

                case 50: 
                    system("clear");
                    printf("Введите второе время. Введите часы, затем нажмите Enter\n");
                    time2[0] = symbol_scanning_time(23, time2, 0);
                    system("clear");
                    printf("Введите второе время. Введите минуты, затем нажмите Enter\n");
                    printf("%02d:", time2[0]);
                    time2[1] = symbol_scanning_time(59, time2, 1);
                    system("clear");
                    printf("Введите второе время. Введите секунды, затем нажмите Enter\n");
                    printf("%02d:%02d:", time2[0], time2[1]);
                    time2[2] = symbol_scanning_time(59, time2, 2);
                    system("clear");
                    printf("Введенное время: %02d:%02d:%02d\n", time2[0], time2[1], time2[2]);
                    printf("Нажмите любую клавишу для продолжения\n");
                    disable_waiting_for_enter();
                    getchar();
                    restore_terminal_settings();
                    counter2 = true;
                    break;

                case 52: 
                    if(counter1 == false || counter2 == false)
                    {
                        counterfailure = true; break;
                    }
                    time3[0] = 0; time3[1] = 0; time3[2] = 0;
                    time3[2] = time1[2] - time2[2]; 
                    if(time3[2] < 0) 
                    {
                        time3[1]--; 
                        time3[2]+=60;
                    }
                    time3[1] += time1[1] - time2[1]; 
                    if(time3[1] < 0) 
                    {
                        time3[0]--; 
                        time3[1]+=60;
                    }
                    time3[0] += time1[0] - time2[0]; 
                    if(time3[0] < 0) 
                        time3[0]+=24;
                    dedu = true;
                    break;

                case 51: 
                    if(counter1 == false || counter2 == false)
                    {
                        counterfailure = true; break;
                    }
                    time3[0] = 0; time3[1] = 0; time3[2] = 0;
                    time3[2] = time1[2] + time2[2]; 
                    if(time3[2] > 59) 
                    {
                        time3[1]++; 
                        time3[2]-=60;
                    }
                    time3[1] += time1[1] + time2[1]; 
                    if(time3[1] > 59) 
                    {
                        time3[0]++; 
                        time3[1]-=60;
                    }
                    time3[0] += time1[0] + time2[0]; 
                    if(time3[0] > 23) 
                        time3[0]-=24;
                    sum = true;
                    break;

                case 27: 
                    insideend = true;
                    break;

                case 81:
                    endd = true;
                    break; 
                default: 
                    system("clear"); 
                    printf("Введен неверный символ, повторите попытку\n");
            }
            if(endd == true || insideend == true) break;
        }
    }
    insideend = false;
    if(dataa == true)
    {
        bool sum = false, dedu = false, counter1 = false, counter2 = false, countererr = false;
        int date1[3], dayss, date2[3], p, weekday;
        bool visoc = false;
        // printf("Выбрана работа с датой\n");
        while(true)
        {
        system("clear");        
        if(sum) printf("Сумма равна %02d.%02d.%04d (%s)\n\n", date2[2], date2[1], date2[0], weekday_det(date2, visoc)); sum = false;
        if(dedu) printf("Разность равна %02d.%02d.%04d (%s)\n\n", date2[2], date2[1], date2[0], weekday_det(date2, visoc)); dedu = false;
        if(countererr) printf("Для начала введите данные\n\n");
        printf("Выберете один из пунктов меню\n");
        printf("1. Ввести дату\n");
        printf("2. Ввести количество дней\n");
        printf("3. Прибавить\n");
        printf("4. Вычесть\n");
        printf("Esc. Вернуться в основное меню\n");
        printf("Q. Выйти из программы\n\n");    
        if(counter1) printf("Введенная дата - %02d.%02d.%04d (%s)\n", date1[2], date1[1], date1[0], weekday_det(date1, visoc)); else printf("Дата не введена\n");
        if(counter2) printf("Введенное количество дней равно %d\n\n", dayss); else printf("Количество дней не введено\n\n");
        disable_waiting_for_enter();
        a = getchar();
        restore_terminal_settings();
        switch(a)
        {
            case 49: 
                printf("Введите год\n");
                date1[0] = symbol_scanning_date(10000, date1, 0);
                if (date1[0] % 4 == 0 && date1[1] % 400 != 0) visoc = true; else visoc = false;
                printf("Введите месяц\n");
                date1[1] = symbol_scanning_date(12, date1, 1);
                printf("Введите день\n");
                if(date1[1] == 1 || date1[1] == 3 || date1[1] == 5 || date1[1] == 7 || date1[1] == 8 || date1[1] == 10 || date1[1] == 12)
                {
                    date1[2] = symbol_scanning_date(31, date1, 2);
                    //days31 = true; days30 = false; days29 = false; days28 = false;
                }
                if(date1[1] == 4 || date1[1] == 6 || date1[1] == 9 || date1[1] == 11)
                {
                    date1[2] = symbol_scanning_date(30, date1, 2);
                    //days31 = false; days30 = true; days29 = false; days28 = false;
                }
                if(date1[1] == 2)
                {
                    if(visoc) 
                    {
                        date1[2] = symbol_scanning_date(29, date1, 2);
                        //days31 = false; days30 = false; days29 = true; days28 = false;
                    }
                    else 
                    {
                        date1[2] = symbol_scanning_date(28, date1, 2);
                        //days31 = false; days30 = false; days29 = false; days28 = true;
                    }
                }
                /* if(days28) p = 28;
                if(days29) p = 29;
                if(days30) p = 30;
                if(days31) p = 31; */ 
                p = p_det(date1, visoc);
                /* printf("Введенная дата: %02d.%02d.%04d\n", date1[2], date1[1], date1[0]);
                    printf("Нажмите любую клавишу для продолжения\n");
                    disable_waiting_for_enter();
                    getchar();
                    restore_terminal_settings(); */
                    counter1 = true;
                break;
            
            case 50: 
                printf("Введите количество дней\n");
                dayss = symbol_scanning_digits(1000);
                counter2 = true;
                break;

            case 51: 
                if(!counter1 || !counter2)  //пересмотреть подход к прибавлению/вычитанию с двумя сменами месяца
                {
                    countererr = true;
                    break;
                }
                date2[0] = date1[0];
                date2[1] = date1[1];
                date2[2] = date1[2]; 
                date2[2] += dayss;
                while(date2[2] > p)
                {
                    date2[1]++;
                    if(date2[1] > 12)
                    {
                        date2[0]++;
                        date2[1] -= 12;
                        if (date2[0] % 4 == 0 && date2[1] % 400 != 0) visoc = true; else visoc = false;

                    }
                    date2[2] -= p;
                    p = p_det(date2, visoc);
                }
                sum = true;
                break;

            case 52: 
                if(!counter1 || !counter2) 
                {
                    countererr = true;
                    break;
                }
                date2[0] = date1[0];
                date2[1] = date1[1];
                date2[2] = date1[2]; 
                date2[2] -= dayss;
                while(date2[2] < 1)
                {
                    date2[1]--;
                    if(date2[1] < 1)
                    {
                        date2[0]--;
                        date2[1] += 12;
                        if (date2[0] % 4 == 0 && date2[1] % 400 != 0) visoc = true; else visoc = false;

                    }
                    p = p_det(date2, visoc);
                    date2[2] += p;
                }
                dedu = true;
                break;

            case 27:
                insideend = true;
                break;

            case 81:
                endd = true;
                break;
            
            default: 
                printf("Введен неверный символ\n");
        }    
        if(insideend == true || endd == true) break;
        }
    }
    if(endd == true) 
    {
        printf("Вы вышли из программы\n"); 
        break;
    }
    }
    return 0;
}
