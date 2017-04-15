#include<stdlib.h>
#include<iostream>
#include<algorithm>
using namespace std;

bool *painted = new bool[9];
int *content = new int[9];
int scores[8][10];
int wincombo[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
int turn;
char choice;
int filled;
int oMovesCount;
int result;
int optimi;
int aiturn;

class Game{
public:
    void reload(){
        turn=1;
        filled=0;
        oMovesCount=0;
        result=1;
        for(int i=0;i<9;i++){
            painted[i]=false;
            content[i]=i+1;
        }
        //cout<<"Enter X or O : ";
        //cin>>choice;
        update();
    }

    void update(){
        int ch;
        while(1){
            printing();
            cout<<"here i am"<<optimi-1<<"\n\n";
            if(!checkForWinner()){
                if(turn%2!=0){
                    cout<<"\n\n\n"<<"Please enter the number where you want to enter X"<<" : ";
                    cin>>ch;
                    ch;
                }
            }
            else{
                if(result==88){cout<<"\n\n"<<"X has WON...!!";}
                else if(result==79){cout<<"\n\n"<<"O has WON...!!";}
                break;
            }

            if(turn%2!=0){
                if(painted[ch-1]==true){
                    char trial;
                    cout<<"\n\nTHAT SPACE IS ALREADY OCCUPIED WITH YOUR HEART!...Press any key to TRY AGAIN";
                    cin>>trial;
                    continue;
                }
            }

            if(turn%2==0){
                for (int i = 0; i < 8; i++) {
                    cout<<"LOOP 1"<<endl;
                    for (int j = 0; j < 10; j++) {
                        scores[i][j]=999;
                    }
                }
                aiturn=0;
                int a=ai();
                painted[optimi]=true;
                content[optimi]=79;
                turn++;
                filled++;
                oMovesCount++;
            }
            else{
                painted[ch-1]=true;
                content[ch-1]=88;
                turn++;
                filled++;
            }

            if(availability()){
                break;
            }
        }
        playAgain();
    }

    int availability(){
        if(filled==9){
            result=0;
            printing();
            cout<<"\n\nGAME OVER...!!";
            return 1;
        }
        else{
            return 0;
        }
    }

    int checkForWinner(){
        int sym;
        result=0;
        if(turn%2==0)sym=88;
        else sym=79;

        int flag=0;
        for(int a=0;a<8;a++){
            if(content[wincombo[a][0]]==88&&content[wincombo[a][1]]==88&&content[wincombo[a][2]]==88){
                flag=1;result=88;
            }
            if(content[wincombo[a][0]]==79&&content[wincombo[a][1]]==79&&content[wincombo[a][2]]==79){
                flag=1;result=79;
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
            if(content[i]==88)
            cout<<"\t"<<"X";
            else if(content[i]==79)
            cout<<"\t"<<"O";
            else
            cout<<"\t"<<content[i];
        }
    }

    int score(){
        if(result==88)
            return (10-oMovesCount);
        else if(result==79)
            return (-10+oMovesCount);
        else if(result==0){
            return 0;
        }
    }

    int ai(){
        if(checkForWinner()){
            aiturn--;
            return score();
        }

        int flag=0;
        int sc;
        aiturn++;
        for(int i=0;i<9;i++){
            //scores[i]=-1;
            if(painted[i]==false){
                flag=1;
                break;
            }
        }
        cout<<"aiturn : "<<aiturn<<endl;
        if(flag==0){
            aiturn--;
            return score();
        }
        else{
            for(int i=0;i<9;i++){
                if(painted[i]==false){
                    if(aiturn%2!=0){
                        painted[i]=true;
                        content[i]=79;
                        turn++;
                        filled++;
                        oMovesCount++;

                        sc=ai();
                        //scores[i]=sc;

                        painted[i]=false;
                        content[i]=i+1;
                        turn--;
                        filled--;
                        oMovesCount--;
                    }
                    else{
                        painted[i]=true;
                        content[i]=88;
                        turn++;
                        filled++;

                        sc=ai();
                        //scores[i]=sc;

                        painted[i]=false;
                        content[i]=i+1;
                        turn--;
                        filled--;
                    }
                    scores[aiturn][i]=sc;
                }
                cout<<aiturn<<"  : "<<i<<" LOOP 2 "<<sc<<endl;

            }
            if (aiturn%2==0) {
                int m=99;
                for (int k = 0; k < 10; k++) {
                    if(scores[aiturn][k]==99)continue;
                    else{
                        if(m>scores[aiturn][k]){m=scores[aiturn][k];optimi=k;scores[aiturn][k]=99;}
                    }
                    cout<<"LOOP 3"<<endl;
                }
                aiturn--;
                cout<<"min/max : "<<m<<endl;
                return m;
            }
            else{
                int m=-99;
                for (int k = 0; k < 10; k++) {
                    if(scores[aiturn][k]==99)continue;
                    else{
                        if(m<scores[aiturn][k]){m=scores[aiturn][k];optimi=k;scores[aiturn][k]=99;}
                    }
                    cout<<"LOOP 4"<<endl;
                }
                aiturn--;
                cout<<"min/max : "<<m<<endl;
                return m;
            }

        }
    }
};

int main(){
    Game gamer;
    gamer.reload();
}
