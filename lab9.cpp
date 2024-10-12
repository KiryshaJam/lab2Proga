#include <iostream>
#include <termios.h>
#include <list>
using namespace std;

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

int symbol_scanning(int overfmax) //эта функция занимается посимвольной читкой введенного числа
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

struct st
{
    int holex;
    int holey;
    bool vyxod_est;
};

struct st creating(int pitch[20][20], int n, int m, int codesymb, bool fenceerr)
{
    struct st s1;
    int holex, holey;
    bool err = false, foundpl = false, endd = false; 
    if(codesymb == 1010) s1.vyxod_est = false;
    if(n % 2 != 0) holey = n/2+1; else (holey = n/2);
    if(m % 2 != 0) holex = m/2+1; else (holex = m/2);
    if(pitch[holey][holex] != 1000)
    {
        for(int d = 0; d < n; d++)
        {
            for(int s = 0; s < m; s++)
            {
                if(pitch[d][s] == 1000) {holey = d; holex = s; foundpl = true;}
            }
        }
        if(foundpl == false) {printf("Место закончилось");}
    }
    system("clear");     
    printf("\n\n"); 
    while(true)
    {
        pitch[holey][holex] = codesymb;  
        for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            switch(pitch[i][j])
            {
            case 1000:  printf("%s", "\U0001f9f1"); break;   
            case 1010: printf("%s", "\U0001f300"); break;     
            case 1020: printf("%s", "\U0001f6a7"); break;
            case 0: printf("%s", "\U0001f600"); break;
            case 1070: printf("%s", "\U0001f9f1"); break;
            default: printf("%s", "\U0001f300");
            } 
        }
        printf("\n");
    }
    if(err == true) printf("Введен неверный символ\n");
    if(codesymb == 1010)
    {
        printf("Эта часть программы создана для удаления границ. Перемещайте символ %s клавишами w, a, s, d\n", "\U0001f300");
        printf("Чтобы удалить стенку займите ее место и нажмите клавишу p, для перехода к установке стенок - Q\n");
    }
    if(codesymb == 1020) 
    {
        printf("Установите стенки. Для передвижения используйте w, a, s, d\n");
        printf("Для устновки стенки нажмите клавишу p, для перехода к установке смайлика - Q\n");
    }
    if(codesymb == 0) 
    {
        printf("Установите положение смайлика. Для передвижения используйте w, a, s, d\n");
        printf("Для установки смайлика нажмите p или Q\n");
    }
    char getbut;
    disable_waiting_for_enter();
    getbut = getchar();
    restore_terminal_settings();
    bool fin = false, rdy = false;
    system("clear");      
    if((holex == 0 || holex == m-1 || holey == 0 || holey == n-1) && pitch[holey][holex] != 1070) pitch[holey][holex] = 1020;
    if(fenceerr == false) pitch[holey][holex] = 1000;
    else pitch[holey][holex] = 1020;
    fenceerr = false;
    switch(getbut) 
    {
        case 119: //w
         if(codesymb == 1010) {if(holey == 0) printf("Невозможно смещение в указанном направлении\n"); else holey--; 
         if(pitch[holey][holex] == 1020) fenceerr = true; break;}
         if(holey == 1) printf("Невозможно смещение в указанном направлении\n"); else holey--; break;
        case 97:  //a
         if(codesymb == 1010) {if(holex == 0) printf("Невозможно смещение в указанном направлении\n"); else holex--; 
         if(pitch[holey][holex] == 1020) fenceerr = true; break;}
         if(holex == 1) printf("Невозможно смещение в указанном направлении\n"); else holex--; break;
        case 115: //s
         if(codesymb == 1010) {if(holey == n-1) printf("Невозможно смещение в указанном направлении\n"); else holey++; 
         if(pitch[holey][holex] == 1020) fenceerr = true; break;} 
         if(holey == n) printf("Невозможно смещение в указанном направлении\n"); else holey++; break;
        case 100: //d
         if(codesymb == 1010) {if(holex == m-1) printf("Невозможно смещение в указанном направлении\n"); else holex++; 
         if(pitch[holey][holex] == 1020) fenceerr = true; break;}
         if(holex == m) printf("Невозможно смещение в указанном направлении\n"); else holex++; break;
        case 112: //p
        if(codesymb != 0) pitch[holey][holex] = codesymb; 
        if(codesymb == 1010) {pitch[holey][holex] = 1070; s1.vyxod_est = true;}
        if(codesymb == 0) {if(pitch[holey][holex] != 1020) {endd = true; s1.holex = holex; s1.holey = holey; return s1;}
        else printf("Невозможно установка смайлика на этом месте\n"); break;}
        if(holex != m-2 && pitch[holey][holex+1] != 1020 && pitch[holey][holex+1] != 0 && codesymb != 1010) 
        {
            holex++;    
        }  
        else {
            for(int d = 1; d < n; d++)
        {
            if(rdy == true) break;
            for(int s = 1; s < m; s++)
            {
                if(rdy == true) break;
                if(pitch[d][s] == 1000) {
                    holey = d; holex = s; foundpl = true; rdy = true;
                }
            }
        }
        if(foundpl == false) {printf("Место закончилось");}
        }
        break; 
        case 81: endd = true; if(codesymb == 0) {s1.holex = holex; s1.holey = holey; return s1;} break;
        default: printf("Введен неверный символ\n\n"); err = true;
    }
    if(endd == true) break;
    if(err == false) printf("\n");
    }
    return s1;
}

struct coordinates
{
    int x;
    int y;
};

struct exitin
{
    int x;
    int y;
    int len = 0;
};

int main()
{
    struct st s1;
    int pitch[20][20], escapes[] = {200, 200, 200, 200}, escapes_sub[4] = {200, 200, 200, 200};
    bool escapeses[] = {1, 1, 1, 1};
    int n = 0, m = 0, holex, holey;
    int endd[4] = {0, 0, 0, 0};
    printf("Введите длину лабиринта (максимум - 20)\n");
    n = symbol_scanning(20);
    printf("Введите ширину лабиринта (максимум - 20)\n");
    m = symbol_scanning(20);
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
        if(i == 0 || j == 0 || i == n-1 || j == m-1) pitch[i][j] = 1020;
        else pitch[i][j] = 1000;
        }
    }
    s1 = creating(pitch, n, m, 1010, 0); 
    creating(pitch, n, m, 1020, 0); 
    s1 = creating(pitch, n, m, 0, 0);
    struct coordinates sm;
    sm.x = s1.holex; sm.y = s1.holey;
    pitch[sm.y][sm.x] = 0;
    if(s1.vyxod_est == false)
    {
        for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            switch(pitch[i][j])
            {
            case 1000:  printf("%s", "\U0001f9f1"); break;   
            case 1010: printf("%s", "\U0001f300"); break;     
            case 1020: printf("%s", "\U0001f6a7"); break;
            case 0: printf("%s", "\U0001f600"); break;
            case 1070: printf("%s", "\U0001f9f1"); break;
            default: printf("%s", "\U0001f300");
            } 
        }
        printf("\n");
    }
        printf("Выхода нет\n"); 
        return 0;
    }
    list<coordinates> coorlist;
    struct coordinates check;
    struct exitin exiti;
    struct coordinates adder;
    int checker = 1;
    int Nchecker = 0;
    coorlist.push_front(sm);
    int len = 0;
    while(true)
    {
        len++;
        Nchecker = 0;
        for(int i = 0; i < checker; i++)
        {
            check = coorlist.back();
            coorlist.pop_back();

            if(pitch[check.y-1][check.x] == 1070) 
            {
            Nchecker = 0;
            exiti.y = check.y-1;
            exiti.x = check.x;
            exiti.len = len;
            break;
            }

            if(pitch[check.y+1][check.x] == 1070) 
            {
            Nchecker = 0;
            exiti.y = check.y+1;
            exiti.x = check.x;
            exiti.len = len;
            break;
            }

            if(pitch[check.y][check.x-1] == 1070) 
            {
            Nchecker = 0;
            exiti.y = check.y;
            exiti.x = check.x-1;
            exiti.len = len;
            break;
            }

            if(pitch[check.y][check.x+1] == 1070) 
            {
            Nchecker = 0;
            exiti.y = check.y;
            exiti.x = check.x+1;
            exiti.len = len;
            break;
            }

            if(pitch[check.y-1][check.x] == 1000) 
            {
            Nchecker++;
            adder = check;
            adder.y--;
            coorlist.push_front(adder);
            pitch[check.y-1][check.x] = len;
            }

            if(pitch[check.y+1][check.x] == 1000) 
            {
            Nchecker++;
            adder = check;
            adder.y++;
            coorlist.push_front(adder);
            pitch[check.y+1][check.x] = len;
            }

            if(pitch[check.y][check.x-1] == 1000) 
            {
            Nchecker++;
            adder = check;
            adder.x--;
            coorlist.push_front(adder);
            pitch[check.y][check.x-1] = len;
            }

            if(pitch[check.y][check.x+1] == 1000) 
            {
            Nchecker++;
            adder = check;
            adder.x++;
            coorlist.push_front(adder);
            pitch[check.y][check.x+1] = len;
            }
        }
        if(Nchecker == 0) break;
        else checker = Nchecker;
    }
    if(exiti.len == 0) printf("Выхода нет\n");
    else 
    {
        cout << "Кратчайшее расстояние до выхода: " << len << endl;
        pitch[exiti.y][exiti.x] = 777;
        check.x = exiti.x;
        check.y = exiti.y;
        for(int j = len-1; j > 0; j--)
        {
        if(pitch[check.y-1][check.x] == j) 
            {
            pitch[check.y-1][check.x] = 777;
            check.y--;
            }

        if(pitch[check.y+1][check.x] == j) 
            {
            pitch[check.y+1][check.x] = 777;
            check.y++;
            }

        if(pitch[check.y][check.x-1] == j) 
            {
            pitch[check.y][check.x-1] = 777;
            check.x--;
            }

        if(pitch[check.y][check.x+1] == j) 
            {
            pitch[check.y][check.x+1] = 777;
            check.x++;
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            switch(pitch[i][j])
            {
            case 1000:  printf("%s", "\U0001f9f1"); break;   
            case 1010: printf("%s", "\U0001f300"); break;     
            case 1020: printf("%s", "\U0001f6a7"); break;
            case 0: printf("%s", "\U0001f600"); break;
            case 1070: printf("%s", "\U0001f9f1"); break;
            case 777: printf("%s", "\U0001f7e9"); break;
            default: printf("%s", "\U0001f9f1");
            } 
        }
        printf("\n");
    }
    return 0;
}
