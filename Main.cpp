#include <bits/stdc++.h>
#include "BatsmanComputer.cpp"
#include "BowlerComputer.cpp"
using namespace std;
int Toss(){
    const long max_rand = 3456L;
    double lower_bound = 0;
    double upper_bound = 1;
    srand(100000*time(NULL) % 12343);
    double random_double = lower_bound + (upper_bound - lower_bound) * ((rand() % max_rand) / double(max_rand));

    double sum = 0;
    for(int i = 1; i <= 6; i++){
        sum += 1.0/6;
        if(sum >= random_double){
            return i;
        }
    }
}
int TakeMove(int &numPlayer){//A function that modifies numPlayer to the number entered by the player
    cout << "Enter a number from 1 to 6 for your move" << endl;
    while(true){
        cin >> numPlayer;
        if(numPlayer >= 1 && numPlayer <= 6){
            break;
        }
        else{
            cout << "Please enter a number from 1 to 6" << endl;
        }
    }
}
int computerBall(){
    //This means that the computer is bowling and he is bowling first
    cout << "Your goal is to score as many runs as possible, you are out if the computer and you play the same number" << endl;
    Bowler b = Bowler();
    int playerScore = 0;
    int numPlayer;
    int numComputer;
    while(true){
        TakeMove(numPlayer);
        numComputer = b.NextMove();
        cout << "The computer has played " << numComputer << endl;
        if(numComputer == numPlayer){
            cout << "Oh no! You are out" << endl;
            cout << "Your final score is " << playerScore << endl;
            //The score the computer needs to win will be displayed in computerBat(int score) function
            return playerScore;
        }
        else{
            playerScore += numPlayer;
            cout << "Your current score is " << playerScore << endl;
        }
    }
}
int computerBat(){
    //This means that the computer is batting first
    cout << "Your goal is to minimize the computer's runs, the computer is out if you and the computer play the same number" << endl;
    Batsman b = Batsman();
    int compScore = 0;
    int numPlayer;
    int numComputer;
    while(true){
        TakeMove(numPlayer);
        numComputer = b.NextMove();
        cout << "The computer has played " << numComputer << endl;
        if(numComputer == numPlayer){
            cout << "You have got the computer out!" << endl;
            cout << "The computer's final score is " << compScore << endl;
            //The score the player needs to win will be displayed in computerBowl(int score) function
            return compScore;
        }
        else{
            compScore += numComputer;
            cout << "The computer's current score is " << compScore << endl;
        }
    }
}
void computerBall(int score){
    //This means the the computer is bowling after the player has already batted
    cout << "You need " << score + 1 << " runs to win" << endl;
    cout << "You are now batting, try to reach your goal before the computer gets you out!" << endl;
    Bowler b = Bowler();
    int playerScore = 0;
    int numPlayer;
    int numComputer;
    while(true){
        TakeMove(numPlayer);
        numComputer = b.NextMove();
        cout << "The computer has played " << numComputer << endl;
        if(numComputer == numPlayer){
            cout << "Uh oh, the computer has got you out!" << endl;
            if(score == playerScore){
                cout << "This legendary game has ended in a draw" << endl;
            }
            else{
                cout << "You lost by " << score - playerScore << " runs" << endl;
            }
            return;
        }
        else{
            playerScore += numPlayer;
            if(playerScore > score){
                cout << "Congratulations! You have won the game" << endl;
                cout << "Computer's score = " << score << endl;
                cout << "Your score = " << playerScore << endl;
                return;
            }
            cout << "You need " << score - playerScore << " runs to win(your score = " << playerScore << ")" << endl;
        }
    }
}
void computerBat(int score){
    //This means the the computer is batting after the player has already bowled
    cout << "The computer needs " << score + 1 << " runs to win" << endl;
    cout << "You are now bowling, try to get the computer out before it reaches its goal!" << endl;
    Batsman b = Batsman();
    int compScore = 0;
    int numPlayer;
    int numComputer;
    while(true){
        TakeMove(numPlayer);
        numComputer = b.NextMove();
        cout << "The computer has played " << numComputer << endl;
        if(numComputer == numPlayer){
            cout << "Congratulations, you have got the computer out" << endl;
            if(score == compScore){
                cout << "This legendary game has ended in a draw" << endl;
            }
            else{
                cout << "You have won by " << score - compScore << " runs" << endl;
            }
            return;
        }
        else{
            compScore += numComputer;
            if(compScore > score){
                cout << "Uh ohh, you have lost." << endl;
                cout << "Computer's score = " << compScore << endl;
                cout << "Your score = " << score << endl;
                return;
            }
            cout << "The computer needs " << score - compScore << " runs to win(computer's score = " << compScore << ")" << endl;
        }
    }
}
void Play(){
    cout << "TOSS!" << endl;
    cout << "Odd(1) or even(2)?" << endl;
    int choice;//Will be used for all the choices
    while(true){
        cin >> choice;
        if(!(choice == 1 || choice == 2)){
            cout << "Please enter either 1 for odd or 2 for even" << endl;
        }
        else{
            break;
        }
    }
    int numPlayer;
    while(true){
        cout << "Enter a number from 1 to 6 for the toss" << endl;
        cin >> numPlayer;
        if(numPlayer >= 1 && numPlayer <= 6){
            break;
        }
        else{
            cout << "Please enter a number from 1 to 6" << endl;
        }
    }
    int numComputer = Toss();
    cout << "The computer played "<< numComputer << endl;
    bool firstBowl = true;//denotes if the computer will bowl first
    if((numComputer + numPlayer) % 2 == (choice % 2)){
        cout << "You won the toss, please choose if you want to bat(1) or bowl(2) first" << endl;
        cin >> choice;
        firstBowl = (choice == 1) ? true : false;//If the player wants to bat first, the computer will bowl first
    }
    else{
        cout << "You lost the toss, the computer chooses to bowl first, you will bat" << endl;
    }
    if(firstBowl){
        int scorePlayer = computerBall();
        computerBat(scorePlayer);
    }
    else{
        int scoreComputer = computerBat();
        computerBall(scoreComputer);
    }
}
int main(){
    Play();
}