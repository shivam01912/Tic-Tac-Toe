#include<stdlib.h>
#include<iostream>
using namespace std;

bool *painted = new bool[9];
int *content = new int[9];
int wincombo[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
int turn;
char choice;
int filled;

class Game{
public:
    void reload(){
        turn=1;
        filled=0;
        for(int i=0;i<9;i++){
            painted[i]=false;
            content[i]=i+1;
        }
        cout<<"Enter X or O : ";
        cin>>choice;
        update();
    }

    void update(){
        int ch;
        while(1){
            printing();
            if(!checkForWinner()){
                cout<<"\n\n\n"<<"Please enter the number where you want to enter "<<choice<<" : ";
                cin>>ch;
                ch;
            }
            else{
                break;
            }

            if(painted[ch-1]==true){
                char trial;
                cout<<"THAT SPACE IS ALREADY OCCUPIED WITH YOUR HEART!...Press any key to TRY AGAIN";
                cin>>trial;
                continue;
            }

            if(turn%2==0){
                painted[ch-1]=true;
                content[ch-1]=100;
                turn++;
                filled++;
            }
            else{
                painted[ch-1]=true;
                content[ch-1]=99;
                turn++;
                filled++;
            }

            if(filled==9){
                printing();
                cout<<"\n\nGAME OVER...!!";
                break;
            }
        }
        playAgain();
    }

    int checkForWinner(){
        int sym;
        if(turn%2==0)sym=99;
        else sym=100;

        int flag=0;
        for(int a=0;a<8;a++){
            if(content[wincombo[a][0]]==sym&&content[wincombo[a][1]]==sym&&content[wincombo[a][2]]==sym){
                if(sym==99){cout<<"\n\n"<<"X has WON...!!";flag=1;}
                else if(sym==100){cout<<"\n\n"<<"O has WON...!!";flag=1;}
            }
        }
        return flag;
    }

    void playAgain(){
        char conf;
        cout<<"Play Again ?y/n  :   ";
        cin>>conf;
        if(conf=='y'){reload();}
        else{cout<<"BYE...!!";}
    }

    int printing(){
        system("cls");
        cout<<"-------------------------------------------------------\n"<<endl;
        for(int i=0;i<9;i++){
            if(i==3||i==6){cout<<"\n\n";}
            if(content[i]==99)
            cout<<"\t"<<"X";
            else if(content[i]==100)
            cout<<"\t"<<"O";
            else
            cout<<"\t"<<content[i];
        }
    }
};

int main(){
    Game gamer;
    gamer.reload();
}
