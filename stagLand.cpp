#include <iostream>
#include <limits>
#include <math.h>
#include <windows.h>
#include <time.h>

//////////////// colors
#define bg_brown "\u001b[48;5;94m"
#define bg_blue "\u001b[48;5;17m"
#define bg_red "\u001b[48;5;52m"
#define bg_black "\u001b[0m"
#define red "\u001b[38;5;1m"
#define niceBlue "\u001b[38;5;51m"
#define pink "\u001b[38;5;206m"
#define yellow "\u001b[38;5;228m"
#define green "\u001b[38;5;70m"
#define purple "\u001b[38;5;99m"
#define greenBlue "\u001b[38;5;6m"
#define brightGreen "\u001b[38;5;83m"
#define orange "\u001b[38;5;208m"
#define white "\u001b[38;5;255m"

#define earthRadiusKm 6371.0
#define Xplayer 0
#define Oplayer 1

using namespace std;

//////////////// Data Structures
struct City{
    string city;
    int longitude;
    int latitude;
} cities[]={{"Tehran\0",51,35},
            {"Hamedan\0",48,34},
            {"Abadan",48,30},
            {"Esfahan",51,32},
            {"Babol",52,36},
            {"Bandar Abbas",56,27},
            {"Tabriz",46,38},
            {"Dezfoul",48,32},
            {"Rasht",49,37},
            {"Zahedan",60,29},
            {"Semnan",53,35},
            {"Shiraz",52,29},
            {"Ghom",50,34},
            {"Kashan",51,33},
            {"Karaj",51,35}
        };

//////////////// functions
void logo();
void startPage();
void menu();
void calculator_form();
void calculator(float,float,char);
char getchar_Clear(char='\n');
int getint_Clear(char='\n');
float getfloat_Clear(char='\n');
void BMI_form();
void citiesDistance_Form();
double distanceEarth(City p1, City p2);
double deg2rad(double);
double rad2deg(double);
void setting_Form();
void Info_Form();
void tiktoktoe_Form();
void display_board(char(*)[9],int);
bool player_turn(char(*)[9],bool,int,bool&);
int gameover(char(*)[9],int);
void notepad_Form();

int main(){
    char input='\0';
    srand(time(0));
    startPage();
    while(input!='Q'){
        menu();
        input = getchar_Clear();
        switch(input){
            case 'A':
                calculator_form();
                break;
            case 'B':
                BMI_form();
                break;
            case 'C':
                citiesDistance_Form();
                break;
            case 'D':
                setting_Form();
                break;
            case 'E':
                //notepad_Form();
                break;
            case 'F':
                tiktoktoe_Form();
                break;
            case 'I':
                Info_Form();
                break;
            case 'Q':
                exit(0);
                break;
            case '\0':
                break;
            default:
                cout << "INVALID INPUT !!\n";
                Sleep(1000);
                break;
        }
    }
}

void tiktoktoe_Form(){
    int level;
    char input;
    char board[9][9];
    for(int i=0;i<9*9;board[i/9][i%9]=' ',i++);
    bool turn = Xplayer;
    do{
        system("cls");
        printf("\n%s##############################################%s\n\n",greenBlue,bg_black);
        printf(" %s! TICK -- TAC -- TOE -- GAME %s\n",white,white);
        printf(" %s? choose the game level, then you have to write %s\n",white,white);
        printf(" %s? number of cell to put your character on it%s\n",white,white);
        printf(" ? note that you are %sPlayer X%s\n\n",greenBlue,white);
        printf(" %s1.%s Level 1 (3*3)\n",greenBlue,white);
        printf(" %s2.%s Level 2 (6*6)\n",greenBlue,white);
        printf(" %s3.%s Level 3 (9*9)\n",greenBlue,white);
        level = getint_Clear();
        while(level<1 || level>3){
            cout << "\nSorry?! try again\n";
            level = getint_Clear();
        }
        level*=3;
        ////////
        for(int i=0;i<9*9;board[i/9][i%9]=' ',i++);
        turn = Xplayer;
        bool Exit=false;
        while(true){
            if(gameover(board,level)!=0 || Exit)   break;
            display_board(board,level);
            turn = player_turn(board,turn,level,Exit);
        }
        if(Exit){
            cout<<"\n\nOh :( sad to see you leaving";
        }else if(turn==Oplayer){
            cout<<"\n\nCongratulations!YOU has won the game with 'X'";
        }
        else if(turn==Xplayer){
            cout<<"\n\nSorry! you LOST.. SYSTEM has won the game with 'O'";
        }
        else
            cout<<"\n\nGAME DRAW!!!\n\n";
        //////
        printf("\n %sC.%s Try again..\n",greenBlue,white);
        printf(" %sZ.%s Back to menu..\n",greenBlue,white);
        printf(" %sQ.%s Exit..\n",greenBlue,white);
        input = getchar_Clear();
        while(input!='C' && input!='Z' && input!='Q'){
            cout << "\nSorry?! try again\n";
            input = getchar_Clear();
        }
        if (input=='Q')
            exit(0);
        if (input=='Z')
            return;
    }while(input=='C');
}

void display_board(char board[9][9],int level){
    system("cls");
    printf("\n%s##############################################%s\n\n",greenBlue,bg_black);
    printf(" \t%s! TICK -- TAC -- TOE -- GAME %s\n",white,white);
    printf("%s \tPLAYER [X]\t SYSTEM [O]\n\n %s",greenBlue,white);
    /*first row border*/
    cout<<"\t\t";
    for(int i=0 ; i<level-1 ; i++)
        printf("%02d   |",i);
    printf("%02d\n",level-1);
    /*end border*/
    for(int i=0 ; i<level-1 ; i++){
        /*each cell indexes*/
        cout<<"\t\t  ";
        for(int j=0 ; j<level-1 ; j++)
            cout<<board[i][j]<<"  |  ";
        cout << '\n';
        /*end indexes*/
        /*lower borders*/
        cout<<"\t\t_____";
        for(int j=0 ; j<level-1 ; j++)
            cout << "|_____";
        cout << '\n';
        /*end middle border*/
        /*upper borders*/
        cout<<"\t\t";
        for(int j=0 ; j<level-1 ; j++)
            printf("%02d   |",(i+1)*level+j);
        printf("%02d\n",(i+1)*level+level-1);
        /*end border*/
    }
    /*last row cells indexes*/
    cout<<"\t\t  ";
    for(int j=0 ; j<level-1 ; j++)
        cout<<board[level-1][j]<<"  |  ";
    cout<<board[level-1][j]"<< '\n';
    /*end indexes*/
    /*last row lower border*/
    cout<<"\t\t";
    for(int i=0 ; i<level-1 ; i++)
        printf("     |");
    cout << '\n';
    /*end border*/
}

bool player_turn(char board[9][9],bool turn, int level,bool& Exit){
    int choice,row,column;
    if(turn==Xplayer){
        printf(" %s\n\tIf you wanna end up the game enter -1\n\t Player [X] turn :  %s",greenBlue,white);
        choice = getint_Clear();
        if (choice==-1){
            Exit=true;
            return turn;
        }
        while(choice<-1 || choice>=level*level){
            cout<<"\nIf you wanna end up the game enter -1\nInvalid Move\n";
            choice = getint_Clear();
        }
    }else{
        printf(" %s\n\tSystem [O] turn :  %s",greenBlue,white);
        choice= rand()%(level*level);
    }

    row=choice/level;
    column=choice%level;

    if(turn == Xplayer && board[row][column] != 'X' && board[row][column] != 'O'){
        board[row][column] = 'X';
        turn = Oplayer;
    }else if(turn == Oplayer && board[row][column] != 'X' && board[row][column] != 'O'){
        board[row][column] = 'O';
        turn = Xplayer;
    }else {
        cout<<"Box already filled!n Please choose another!!\n\n";
        turn = player_turn(board,turn,level,Exit);
    }
    return turn;
}

int gameover(char board[9][9], int level){
    for(int i=0; i<level-2; i++)
        for(int j=0; j<level; j++)
            if(board[j][i]!=' ' && board[i][j]!=' ' &&
            (board[j][i] == board[j][i+1] && board[j][i] == board[j][i+2] || board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j]))
                return 1;

    for(int i=0; i<level-2; i++)
        if(board[i][i]!=' ' && board[i][level-(i+1)]!=' ' &&
        (board[i][i] == board[i+1][i+1] && board[i][i] == board[i+2][i+2] || board[i][level-(i+1)] == board[i+1][level-(i+2)] && board[i][level-(i+1)] == board[i+2][level-(i+3)]))
            return 1;

    for(int i=0; i<level; i++)
        for(int j=0; j<level; j++)
            if(board[i][j] != 'X' || board[i][j] != 'O')
                return 0;

    return -1;
}

void Info_Form(){
    int a;
    char input;
    system("cls");
    printf("\n%s##############################################%s\n\n",greenBlue,bg_black);
    printf(" %s! about this app %s\n",white,white);
    printf(" %s  Stag Land is a simple form of an assistant %s\n",white,white);
    printf(" %s  application, made as an exercise for\n   programming abilities%s\n\n",white,white);
    printf(" %s  compony: %s Mositto\n",greenBlue,white);
    printf(" %s  programmer: %s Fatemeh Razaqnejad\n",greenBlue,white);
    printf(" %s  version: %s V0\n",greenBlue,white);
    printf(" %s  contact: %s razaqnejad@gmail.com\n\n",greenBlue,white);
    do{
        printf("\n %sC.%s Try again..\n",greenBlue,white);
        printf(" %sZ.%s Back to menu..\n",greenBlue,white);
        printf(" %sQ.%s Exit..\n",greenBlue,white);
        input = getchar_Clear();
        while(input!='C' && input!='Z' && input!='Q'){
            cout << "\nSorry?! try again\n";
            input = getchar_Clear();
        }
        if (input=='Q')
            exit(0);
        if (input=='Z')
            return;
    }while(input=='C');
}

void setting_Form(){
    int a;
    char input;
    system("cls");
    printf("\n%s##############################################%s\n\n",yellow,bg_black);
    printf(" %s! change theme %s\n",white,white);
    printf(" %s? enter the number%s\n",white,white);
    printf(" %s? be careful about the spaces and enters%s\n",white,white);
    printf(" %s  1. %s black theme\n",yellow,white);
    printf(" %s  2. %s blue theme\n",yellow,white);
    printf(" %s  3. %s red theme\n",yellow,white);
    printf(" %s  example: 1 %s\n\n",yellow,white);
    do{
        printf(" %s  your turn: %s\n\n",white,white);
        a= getint_Clear();
        if(a==1) printf("%s",bg_black);
        else if(a==2) printf("%s",bg_blue);
        else if(a==3) printf("%s",bg_red);
        printf("\n\n %sC.%s Try again..\n",yellow,white);
        printf(" %sZ.%s Back to menu..\n",yellow,white);
        printf(" %sQ.%s Exit..\n",yellow,white);
        input = getchar_Clear();
        while(input!='C' && input!='Z' && input!='Q'){
            cout << "\nSorry?! try again\n";
            input = getchar_Clear();
        }
        if (input=='Q')
            exit(0);
        if (input=='Z')
            return;
    }while(input=='C');
}

void citiesDistance_Form(){
    int a,b;
    char input;
    system("cls");
    printf("\n%s##############################################%s\n\n",pink,bg_black);
    printf(" %s! use this part to calculate distance between cities %s\n",white,white);
    printf(" %s? enter number of 2 cities of the list%s\n",white,white);
    printf(" %s? be careful about the spaces and enters%s\n",white,white);
    int numberOfCities=sizeof(cities)/sizeof(City);
    for(int i=0 ; i<numberOfCities ; i++){   
        printf(" %s  %d. %s%s\n",pink,i+1,white,cities[i].city.c_str());
    }
    printf(" %s  example: 1 2 %s\n\n",pink,white);
    do{
        printf(" %s  your turn: %s\n\n",white,white);
        a= getint_Clear(' ');
        b= getint_Clear();
        while(a>numberOfCities || b>numberOfCities){
            cout << "\n enter valid numbers\n";
            a= getint_Clear(' ');
            b= getint_Clear();
        }
        printf(" distance between %s and %s is: %lf km",cities[a-1].city.c_str(),cities[b-1].city.c_str(),distanceEarth(cities[a-1],cities[b-1]));
        printf("\n\n %sC.%s Try again..\n",pink,white);
        printf(" %sZ.%s Back to menu..\n",pink,white);
        printf(" %sQ.%s Exit..\n",pink,white);
        input = getchar_Clear();
        while(input!='C' && input!='Z' && input!='Q'){
            cout << "\nSorry?! try again\n";
            input = getchar_Clear();
        }
        if (input=='Q')
            exit(0);
        if (input=='Z')
            return;
    }while(input=='C');
}

double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

double rad2deg(double rad) {
  return (rad * 180 / M_PI);
}

double distanceEarth(City p1, City p2) {
  double p1lat_rad, p1long_rad, p2lat_rad, p2long_rad, u, v;
  p1lat_rad = deg2rad(p1.latitude);
  p1long_rad = deg2rad(p1.longitude);
  p2lat_rad = deg2rad(p2.latitude);
  p2long_rad = deg2rad(p2.longitude);
  u = sin((p2lat_rad - p1lat_rad)/2);
  v = sin((p2long_rad - p1long_rad)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(p1lat_rad) * cos(p2lat_rad) * v * v));
}

void BMI_form(){
    float w,h,result=0;
    char input;
    system("cls");
    printf("\n%s##############################################%s\n\n",niceBlue,bg_black);
    printf(" %s! BMI or Body Mass Index calculator %s\n",white,white);
    printf(" %s? Enter your weight then you height in kg/cm %s\n",white,white);
    printf(" %s? be careful about the spaces and enters%s\n",white,white);
    printf(" %s  example:  56.2 196%s\n\n",niceBlue,white);
    do{
        printf(" %s  your turn: %s\n\n",white,white);
        w= getfloat_Clear(' ');
        h= getfloat_Clear();
        result = (w*10000)/(h*h);
        cout << " Yout BMI is equal to: " << result;
        if(result<18.5){
            printf("\n %s Yout BMI is UnderWight\n  you need to eat more%s",niceBlue,white);
        } else if(result<25){
            printf("\n %s Yout BMI is Normal\n  keep going body :)%s",brightGreen,white);
        } else if(result<30){
            printf("\n %s Yout BMI is OverWeight\n  you better stop eating%s",yellow,white);
        } else if(result<35){
            printf("\n %s Yout BMI is Obese\n  seriously stop eating man%s",orange,white);
        } else{
            printf("\n %s Yout BMI is Extremely Obese\n  Your going to explosive :/%s",red,white); 
        }

        printf("\n\n %sC.%s Try again..\n",niceBlue,white);
        printf(" %sZ.%s Back to menu..\n",niceBlue,white);
        printf(" %sQ.%s Exit..\n",niceBlue,white);
        input = getchar_Clear();
        while(input!='C' && input!='Z' && input!='Q'){
            cout << "\nSorry?! try again\n";
            input = getchar_Clear();
        }
        if (input=='Q')
            exit(0);
        if (input=='Z')
            return;
    }while(input=='C');
}

void calculator_form(){
    float a,b;
    char c,input;
    system("cls");
    printf("\n%s##############################################%s\n\n",red,bg_black);
    printf(" %s! you can use this part to calculate */+-%% %s\n",white,white);
    printf(" %s? enter 2 operand and 1 operator in between%s\n",white,white);
    printf(" %s? be careful about the spaces and enters%s\n",white,white);
    printf(" %s  example: 13 + 15 %s\n\n",red,white);
    do{
        printf(" %s  your turn: %s\n\n",white,white);
        a= getint_Clear(' ');
        c= getchar_Clear(' ');
        b= getint_Clear();
        calculator(a,b,c);
        printf("\n\n %s%s if your answer is wrong..\n  maybe you entered bad numbers\n",red,white);
        printf(" %sC.%s Try again..\n",red,white);
        printf(" %sZ.%s Back to menu..\n",red,white);
        printf(" %sQ.%s Exit..\n",red,white);
        input = getchar_Clear();
        while(input!='C' && input!='Z' && input!='Q'){
            cout << "\nSorry?! try again\n";
            input = getchar_Clear();
        }
        if (input=='Q')
            exit(0);
        if (input=='Z')
            return;
    }while(input=='C');
}
void calculator(float a,float b, char c){
    cout << a << " " << c << " " << b << " = ";
    switch (c){
    case '+':
        cout << a+b;
        break;
    case '-':
        cout << a-b;
        break;
    case '*':
        cout << a*b;
        break;
    case '/':
        cout << a/b;
        break;
    case '%':
        cout << static_cast<int>(a)%static_cast<int>(b);
        break;
    default:
        cout << "Invalid Operations !!";
        break;
    }
}
void menu(){
    system("cls");
    printf("\n%s##############################################%s\n",bg_brown,bg_black);
    printf("\n %sChoose your option by typing\n the colored character..%s\n\n",white,white);
    printf("%s\t A.%s Calculator\n",red,white);
    printf("%s\t B.%s BMI\n",niceBlue,white);
    printf("%s\t C.%s Cities distance\n",pink,white);
    printf("%s\t D.%s Setting\n",yellow,white);
    printf("%s\t E.%s Notepad\n",green,white);
    printf("%s\t F.%s Tik Tok Toe\n",brightGreen,white);
    printf("%s\t I.%s Info\n",greenBlue,white);
    printf("%s\t Q.%s Exit\n",purple,white);
    printf("\n");
    printf("\n%s##############################################%s\n",bg_brown,bg_black);
}

void logo(){
    //printf(bg_brown);
    printf("%s\t%s",bg_black,bg_brown);
    printf("\n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("\\\\//                     \\\\//\n");
    printf("%s\t%s",bg_black,bg_brown);
    printf(" \\\\                       // \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("  \\\\ \\\\               // //  \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("   =====\\\\  || ||  //=====   \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("    =====================    \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("  #######/         \\#######  \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("   #####/           \\#####   \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("       /\\           /\\       \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("      /  \\  _____  /  \\      \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("     /    \\/     \\/    \\     \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("     \\     \\_____/     /     \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("      \\               /      \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("       \\             /       \n");
    printf("%s\t%s",bg_black,bg_brown);
    printf("        \\___________/        \n");
    printf("%s",bg_black);
    printf("\n");
}
void startPage(){
    for(int i=0 ; i<2 ; i++){
        if(i%3==0){
            system("cls");
            printf("\n##############################################\n");
            logo();
            printf("          $ welcome to stag land $\n");
            printf("            ~~~~~~~~~~~~~~~~~~~\n");
            printf("             please wait.\n");
            printf("              ~~~~~~~~~~~~~~~~~~~");
            printf("\n##############################################\n");
            Sleep(1000);
        }else if(i%3==1){
            system("cls");
            printf("\n##############################################\n");
            logo();
            printf("          $ welcome to stag land $\n");
            printf("             ~~~~~~~~~~~~~~~~~~~\n");
            printf("             please wait..\n");
            printf("             ~~~~~~~~~~~~~~~~~~~");
            printf("\n##############################################\n");
            Sleep(200);
        }else{
            system("cls");
            printf("\n##############################################\n");
            logo();
            printf("          $ welcome to stag land $\n");
            printf("              ~~~~~~~~~~~~~~~~~~~\n");
            printf("             please wait...\n");
            printf("            ~~~~~~~~~~~~~~~~~~~");
            printf("\n##############################################\n");
            Sleep(200);
        }
    }
}

char getchar_Clear(char ender){
    char c;
    cin >> c;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),ender);
    return toupper(c);
}
int getint_Clear(char ender){
    int n;
    cin >> n;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),ender);
    return n;
}
float getfloat_Clear(char ender){
    int n;
    cin >> n;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),ender);
    return n;
}