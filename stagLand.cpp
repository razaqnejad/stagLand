#include <iostream>
#include <limits>
#include <math.h>
#include <windows.h>
#include <fstream>
#include <time.h>
//#include <string>

//////////////// colors
#define bg_brown "\u001b[48;5;94m"
#define bg_blue "\u001b[48;5;17m"
#define bg_red "\u001b[48;5;52m"
#define bg_black "\u001b[0m"
#define red "\u001b[38;5;1m"            //calculator
#define niceBlue "\u001b[38;5;51m"      //BMI
#define pink "\u001b[38;5;206m"         //Citis
#define yellow "\u001b[38;5;228m"       //setting
#define green "\u001b[38;5;70m"         //notepad
#define purple "\u001b[38;5;99m"        //exit
#define greenBlue "\u001b[38;5;6m"      //info
#define brightGreen "\u001b[38;5;83m"   //tiktaktoe
#define orange "\u001b[38;5;208m"       //
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
struct Account{
    bool login = false;
    string username="\0";
    char password[8]={' ',' ',' ',' ',' ',' ',' ',' '};
}account;
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
void display_board(char(*)[5],int);
bool player_turn(char(*)[5],bool,int,bool&);
int gameover(char(*)[5],int);
void notepad_Form();
void login();
void signup();
bool account_valid();
void set_account_data();
void set_note_data(string);
void load_note();
void delete_note();
void delete_stagland_data();

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
                notepad_Form();
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
void delete_stagland_data(){
    int a;
    char input;
    system("cls");
    printf("\n%s##############################################%s\n\n",yellow,bg_black);
    printf(" %s! you are deleting all the datas %s\n",white,white);
    printf(" %s? are you sure? enter y for yes or n for no %s\n",white,white);
    printf(" %s  example: y %s\n\n",green,white);
    input = getchar_Clear();
    while(input!='Y' && input!='N'){
        cout << "\nSorry?! try again\n";
        input = getchar_Clear();
    }
    if(input=='Y'){
    /* delete dir */
        system("rmdir /s /Q stagland_data");
        printf("\n :( your data %sdeleted%s\n",green,white);
        account.login=false;
    }
    printf("\n %sZ.%s Back to menu..\n",green,white);
    printf(" %sQ.%s Exit..\n",green,white);
    input = getchar_Clear();
    while(input!='Z' && input!='Q'){
        cout << "\nSorry?! try again\n";
        input = getchar_Clear();
    }
    if (input=='Q')
        exit(0);
    if (input=='Z')
        return;
}
void delete_note(){
    int a;
    char input;
    system("cls");
    printf("\n%s##############################################%s\n\n",green,bg_black);
    printf(" %s! you are deleting your note %s\n",white,white);
    printf(" %s? are you sure? enter y for yes or n for no %s\n",white,white);
    printf(" %s  example: y %s\n\n",green,white);
    input = getchar_Clear();
    while(input!='Y' && input!='N'){
        cout << "\nSorry?! try again\n";
        input = getchar_Clear();
    }
    if(input=='Y'){
    /* delete dir */
        string deleteNote="del /f stagland_data\\notes\\"+account.username+".txt";
        system(deleteNote.c_str());
        printf("\n :( your note %sdeleted%s\n",green,white);
    }
    printf("\n %sZ.%s Back to menu..\n",green,white);
    printf(" %sQ.%s Exit..\n",green,white);
    input = getchar_Clear();
    while(input!='Z' && input!='Q'){
        cout << "\nSorry?! try again\n";
        input = getchar_Clear();
    }
    if (input=='Q')
        exit(0);
    if (input=='Z')
        return;
}
void load_note(){
    int a;
    char input;
    system("cls");
    printf("\n%s##############################################%s\n\n",green,bg_black);
    printf(" %s! here is your note dear %s%s%s\n",white,green,account.username.c_str(),white);
    /* make accounts file */
    fstream  file;
    file.open(".\\stagland_data\\notes\\"+account.username+".txt",ios::in);
    if(!file){
        printf(" %ssorry but you dont have any note%s\n",green,white);
        return;
    }
    char data[100];
    //file.getline(username,100);
    file.flush();
    while(!file.eof()){
        file.getline(data,100);
        cout << '\t' << data << '\n';
    }
    file.close();
    ///
    printf(" %sZ.%s Back to menu..\n",green,white);
    printf(" %sQ.%s Exit..\n",green,white);
    input = getchar_Clear();
    while(input!='C' && input!='Z' && input!='Q'){
        cout << "\nSorry?! try again\n";
        input = getchar_Clear();
    }
    if (input=='Q')
        exit(0);
    if (input=='Z')
        return;
}
void add_note(){
    string data;
    char input;
    bool flagAnotherNote=false;
    while(true){
        system("cls");
        printf("\n%s##############################################%s\n\n",green,bg_black);
        printf(" %s! add a note to your notes %s\n",white,white);
        printf(" %s  write anything you want in a single line\n",green,white);
        printf(" %s  example: Hello my new note %s\n\n",green,white);
        //
        getline(cin,data);
        do{
            printf("\n %sS.%s Save and try again..\n",green,white);
            printf(" %sM.%s Save and back to menu..\n",green,white);
            printf(" %sE.%s Save and exit\n",green,white);
            printf(" %sC.%s Just try again..\n",green,white);
            printf(" %sZ.%s Just back to menu..\n",green,white);
            printf(" %sQ.%s Just exit..\n",green,white);
            input = getchar_Clear();
            while(input!='C' && input!='Z' && input!='Q' && input!='S' && input!='M' && input!='E'){
                cout << "\nSorry?! try again\n";
                input = getchar_Clear();
            }
            switch(input){
                case 'S':
                    set_note_data(data);
                    flagAnotherNote=true;
                    break;
                case 'M':
                    set_note_data(data);
                    return;
                    break;
                case 'E':
                    set_note_data(data);
                    exit(0);
                    break;
                case 'Q':
                    exit(0);
                    break;
                case 'Z':
                    return;
                    break;
                case 'C':
                    break;
            }
        }while(input=='C');
        if (flagAnotherNote==true)
            continue;
    }
    
}
void set_note_data(string data){
    fstream  file;
    file.open(".\\stagland_data\\notes\\"+account.username+".txt",ios::app);
    if(!file){
        /* make directory of data */
        system("rmdir /S /Q notes");
        system("rmdir -r stagland_data\\notes");
        system("mkdir stagland_data\\notes");
        system("cd ..");
        file.open(".\\stagland_data\\notes\\"+account.username+".txt",ios::out);
        file.close();
        file.open(".\\stagland_data\\notes\\"+account.username+".txt",ios::app);
    }
    file << data << '\n';
    file.close();
}
void login(){
    while(true){
        system("cls");
        printf("\n%s##############################################%s\n\n",yellow,bg_black);
        printf(" %s! use this part to login %s\n",white,white);
        printf(" %s  enter username and password in seperated lines\n",yellow,white);
        printf(" %s  example: \n   razaqnejad\n   12345678 %s\n\n",yellow,white);
        //
        cin >> account.username;
        cin >> account.password;
        if(!account_valid()){
            int option2;
            printf(" %s? the username is not exist%s\n",white,white);
            printf(" %s  1. %s try again\n",yellow,white);
            printf(" %s  2. %s signup\n",yellow,white);
            printf(" %s  example: 1 %s\n\n",yellow,white);
            option2 = getint_Clear();
            while(option2<1 || option2>2){
                cout << "\nSorry?! try again\n";
                option2 = getint_Clear();
            }
            if(option2==1){
                continue;
            }else{
                signup();
                return;
            }
        }else{
            system("cls");
            printf("\n%s##############################################%s\n\n",bg_brown,bg_black);
            printf(" Welcome dear %s%s %s\n",bg_brown,account.username.c_str(),bg_black);
            Sleep(2000);
            system("cls");
            account.login=true;
            return;
        }
    }
}
void signup(){
    while(true){
        system("cls");
        printf("\n%s##############################################%s\n\n",yellow,bg_black);
        printf(" %s! you are making an account%s\n",white,white);
        printf(" %s?  enter username and password in seperated lines\n",white,white);
        printf(" %s?  notic username could be anything up to 20\n     characters but without witespaces\n",red,white);
        printf(" %s?  and password have to be exact 8 characters\n",red,white);
        printf(" %s  example: \n   stagland\n   12345678 %s\n\n",yellow,white);
        cin >> account.username;
        while(account.username=="\0"){
            cout << "\nCome on -_- dont be funny\n";
            cin >> account.username;
        }
        cin >> account.password;
        do{
            bool flag=true;
            for(int i=0 ; i<8 ; i++){
                if(account.password[i]==' '){
                    flag=false;
                    break;
                }
            }
            if(flag==true)
                break;
            cout << "\nExact EIGHT charcters..\n";
            cin >> account.password;
        }while(true);
        system("cls");
        printf("\n%s##############################################%s\n\n",bg_brown,bg_black);
        printf(" Welcome dear%s %s %s\n",bg_brown,account.username.c_str(),bg_black);
        Sleep(2000);
        break;
    }
    set_account_data();
    account.login=true;
}
void set_account_data(){
    /* make accounts file */
    fstream  file;
    file.open(".\\stagland_data\\accounts.txt",ios::app);
    if(!file){
        /* make directory of data */
        system("rmdir /S /Q stagland_data");
        system("mkdir stagland_data");
        file.open(".\\stagland_data\\accounts.txt",ios::app);
    }
    file << account.username << '\n';
    file << account.password << '\n';
    file.close();
}
bool account_valid(){
    /* make accounts file */
    fstream  file;
    file.open(".\\stagland_data\\accounts.txt",ios::in);
    if(!file){
        file.close();
        return false;
    }
    char username[20]="\0";
    char pass[8];
    //file.getline(username,100);
    file.flush();
    while(!file.eof()){
        file >> pass;
        file >> username;
        /* for debug //
        cout << "account.password" <<": ";
        cout << account.password <<'\t';
        cout << "pass" << ": ";
        cout << pass <<'\n';
        cout << "account.username" <<": ";
        cout << account.username << '\t';
        cout << "username" <<": ";
        cout << username <<'\n';
        // end of debug */
        if (username==account.username){
            bool flag=true;
            for(int i=0 ; i<8 ; i++){
                if(pass[i]!=account.password[i]){
                    flag=false;
                    break;
                }
            }
            if(flag==true){
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}
void notepad_Form(){
    int option;
    char input;
    bool flag = false;
    system("cls");
    printf("\n%s##############################################%s\n\n",green,bg_black);
    printf(" %s! use this part as a notepad %s\n",white,white);
    if(account.login){
        printf(" %s? choose your option%s\n",white,white);
        printf(" %s  1. %s add note\n",green,white);
        printf(" %s  2. %s load note\n",green,white);
        printf(" %s  3. %s delete note\n",green,white);
        printf(" %s  4. %s none of them\n",green,white);
        printf(" %s  example: 1 %s\n\n",green,white);
        option = getint_Clear();
        while(option<1 || option>4){
            cout << "\nSorry?! try again\n";
            option = getint_Clear();
        }
        switch (option)
        {
        case 1:
            add_note();
            break;
        case 2:
            load_note();
            break;
        case 3:
            delete_note();
            break;
        case 4:
            flag=true;
            break;
        default:
            break;
        }
    }else{
        printf(" %s? you have to login to use this part%s\n",white,white);
        login();
        return;
    }
    if(flag){
        system("cls");
        printf("\n%s##############################################%s\n\n",green,bg_black);
        printf(" %s! use this part as a notepad %s\n",white,white);
        ////////
        //////
        printf("\n %sC.%s Try again..\n",green,white);
        printf(" %sZ.%s Back to menu..\n",green,white);
        printf(" %sQ.%s Exit..\n",green,white);
        input = getchar_Clear();
        while(input!='C' && input!='Z' && input!='Q'){
            cout << "\nSorry?! try again\n";
            input = getchar_Clear();
        }
        if (input=='Q')
            exit(0);
        if (input=='Z')
            return;
    }
}

void tiktoktoe_Form(){
    int level;
    char input;
    char board[5][5];
    for(int i=0;i<5*5;board[i/5][i%5]=' ',i++);
    bool turn = Xplayer;
    do{
        system("cls");
        printf("\n%s##############################################%s\n\n",brightGreen,bg_black);
        printf(" %s! TICK -- TAC -- TOE -- GAME %s\n",white,white);
        printf(" %s? choose the game level, then you have to write %s\n",white,white);
        printf(" %s? number of cell to put your character on it%s\n",white,white);
        printf(" ? note that you are %sPlayer X%s\n\n",brightGreen,white);
        printf(" %s1.%s Level 1 (3*3)\n",brightGreen,white);
        printf(" %s2.%s Level 2 (4*4)\n",brightGreen,white);
        printf(" %s3.%s Level 3 (5*5)\n",brightGreen,white);
        level = getint_Clear();
        while(level<1 || level>3){
            cout << "\nSorry?! try again\n";
            level = getint_Clear();
        }
        level+=2;
        ////////
        for(int i=0;i<5*5;board[i/5][i%5]=' ',i++);
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
        printf("\n %sC.%s Try again..\n",brightGreen,white);
        printf(" %sZ.%s Back to menu..\n",brightGreen,white);
        printf(" %sQ.%s Exit..\n",brightGreen,white);
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

void display_board(char board[5][5],int level){
    system("cls");
    printf("\n%s##############################################%s\n\n",brightGreen,bg_black);
    printf(" \t%s! TICK -- TAC -- TOE -- GAME %s\n",white,white);
    printf("%s \tPLAYER [X]\t SYSTEM [O]\n\n %s",brightGreen,white);
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
    cout<<board[level-1][level-1]<< '\n';
    /*end indexes*/
    /*last row lower border*/
    cout<<"\t\t";
    for(int i=0 ; i<level-1 ; i++)
        printf("     |");
    cout << '\n';
    /*end border*/
}

bool player_turn(char board[5][5],bool turn, int level,bool& Exit){
    int choice,row,column;
    if(turn==Xplayer){
        printf(" %s\n\tIf you wanna end up the game enter -1\n\t Player [X] turn :  %s",brightGreen,white);
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
        printf(" %s\n\tSystem [O] turn :  %s",brightGreen,white);
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

int gameover(char board[5][5], int level){
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
    char input;
    int num;
    do{
        system("cls");
        printf("\n%s##############################################%s\n\n",yellow,bg_black);
        printf(" %s! welcome to settings %s\n",white,white);
        printf(" %s? enter the number%s\n",white,white);
        printf(" %s  1. %s login\n",yellow,white);
        printf(" %s  2. %s logout\n",yellow,white);
        printf(" %s  3. %s signup\n",yellow,white);
        printf(" %s  4. %s delete all datas\n",yellow,white);
        printf(" %s  example: 1 %s\n\n",yellow,white);
        
        printf(" %s  your turn: %s\n\n",white,white);
        num= getint_Clear();
        while(num<1 || num>4){
            cout << "\nSorry?! try again\n";
            num = getint_Clear();
        }
        switch (num){
        case 1:
            login();
            break;
        case 2:
            account.login=false;
            cout << "\nDone..\n";
            break;
        case 3:
            signup();
            break;
        case 4:
            delete_stagland_data();
            cout << "\nDone..\n";
            break;
        default:
            break;
        }
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
void cin_Clear(){
    cin.clear();
    cin.ignore();
}