#include <stdio.h>
#include <stdlib.h>

void display(char pos[]);
int arrLen(char arr[]);
int minimax(char pos[], char player);
int win(char pos[], char player);
void reset(char pos[]);

char AI = 'O';
char Hu = 'X';
int checker = 0;

int main(){
    char pos[9] = {'0','1','2','3','4','5','6','7','8'};
    display(pos);

    return 0;
}

void display(char pos[]){
    int userPos = 0;


    while(1){
    printf("\n\n\n");
    printf("       |     |                \n");
    printf("    %c  |  %c  |  %c             \n",pos[0],pos[1],pos[2]);
    printf("  _____|_____|_____          \n");
    printf("       |     |                \n");
    printf("    %c  |  %c  |  %c              \n",pos[3],pos[4],pos[5]);
    printf("  _____|_____|_____          \n");
    printf("       |     |                \n");
    printf("    %c  |  %c  |  %c             \n",pos[6],pos[7],pos[8]);
    printf("       |     |                \n\n\n");

    /*
        CHECKER
    */

    if(win(pos,AI)){
        char des;
        printf(" AI WINS!!");
        printf("\n\n Would you like to continue [Y] or [N] => ");
        scanf("%s",&des);
        if(des=='Y'){
            reset(pos);
            system("cls");
            continue;
        }else{
            break;
        }

    }else if(win(pos,Hu)){
        char des;
        printf(" Human Wins!!");
        printf("\n\n Would you like to continue [Y] or [N] => ");
        scanf("%s",&des);
        if(des=='Y'){
            reset(pos);
            system("cls");
            continue;
        }else{
            break;
        }

    }else if(arrLen(pos)==0){
        char des;
        printf(" It is a draw!!");
        printf("\n\n Would you like to continue [Y] or [N] => ");
        scanf("%s",&des);
        if(des=='Y'){
            reset(pos);
            system("cls");
            continue;
        }else{
            break;
        }

    }


    printf(" What position would you like : ");
    scanf("%i",&userPos);

    if(pos[userPos] == AI || pos[userPos] == Hu){
        system("cls");
        printf("  It is already filled  ");
        continue;
    }


    pos[userPos] = Hu;
    int bestspot = minimax(pos,Hu);

    // LINE 98-107 IS TEMPORARY IT WILL BE UPGRADED SOON

    if(checker==0 && (pos[4] != AI && pos[4] != Hu) ){
        pos[4] = AI;
    }else if(checker==1 && (pos[2] != AI && pos[2] != Hu) &&  pos[4] == Hu && pos[3] != Hu && pos[5] != Hu){
        pos[2] = AI;
    }else{
        while(pos[bestspot] == Hu || pos[bestspot] == AI){
            bestspot++;
        }
        pos[bestspot] = AI;
    }


    checker = 1;
    system("cls");
  }


}

void reset(char pos[]){
    char origVal[9] = {'0','1','2','3','4','5','6','7','8'};
    for(int i=0; i < 9; i++){
        pos[i] = origVal[i];
    }
    checker=0;
}

// 1 = true, 0 = false
int win(char pos[], char player){

    if(
       (pos[0] == player && pos[1] == player && pos[2] == player) ||
       (pos[3] == player && pos[4] == player && pos[5] == player) ||
       (pos[6] == player && pos[7] == player && pos[8] == player) ||
       (pos[0] == player && pos[3] == player && pos[6] == player) ||
       (pos[1] == player && pos[4] == player && pos[7] == player) ||
       (pos[2] == player && pos[5] == player && pos[8] == player) ||
       (pos[0] == player && pos[4] == player && pos[8] == player) ||
       (pos[2] == player && pos[4] == player && pos[6] == player)
       ){
        return 1;
    }

    return 0;
}

int minimax(char pos[], char player){

    // EMPTY SPOT
    int arrNewLen = arrLen(pos);
    int emptySpot[arrNewLen];
    int counterSpot = 0;

    for(int i=0; i < 9;i++){
        if(pos[i] != AI && pos[i] != Hu){
            emptySpot[counterSpot] = i;
            counterSpot++;
        }
    }

    //Check if there is a winner
    if(win(pos,Hu)){
        return -10;
    }else if(win(pos,AI)){
        return 10;
    }else if(arrNewLen == 0){
        return 0;
    }

    int score[arrNewLen];

    for(int i=0; i < arrNewLen; i++){
        char index = pos[emptySpot[i]];
        pos[emptySpot[i]] = player;

        if(player == AI){
            int result = minimax(pos,Hu);
                if(result == 10 || result == -10 || result == 0){
                    score[i] = result;
                }else{score[i] = 0;}
        }else{
            int result = minimax(pos,AI);
                if(result == 10 || result == -10 || result == 0){
                    score[i] = result;
                }else{score[i]= 0;}
        }

        pos[emptySpot[i]] = index;
    }

/*          TESTER
    for(int i=0; i < arrNewLen; i++){
        printf(" %i return %i \n",emptySpot[i],score[i]);
    }
*/
    int bestMove = 0;
    if(player == AI){
        int bestScore = -10000;
        for(int i=0; i < arrNewLen; i++){
            if(score[i] > bestScore){
                bestScore = score[i];
                bestMove = i;
            }
        }
    }else{
        int bestScore = 10000;
        for(int i=0; i < arrNewLen; i++){
            if(score[i] < bestScore){
                bestScore = score[i];
                bestMove = i;
            }
        }
    }



    return emptySpot[bestMove];
}

int arrLen(char arr[]){
    int total = 0;
    for(int i=0; i < 9; i++){
        if(arr[i] != AI && arr[i] != Hu){
            total++;
        }
    }

    return total;
}


