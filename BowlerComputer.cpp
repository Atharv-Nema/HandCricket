#include <bits/stdc++.h>
using namespace std;
class Bowler{
    private:
        const double INF = 1000000000;
        const vector<double> RANDOMIFIER = {0.6, 0.3, 0.04, 0.03, 0.01, 0.01};//This the bowler's distribution for a given batsman's distribution
        unordered_map<int,double> distribution;
    public:
        Bowler();
        void UpdateDistribution(unordered_map<int,int> batsmans_history);
        int NextMove();
    
};
Bowler :: Bowler(){
    //This is the nash equilibrium distribution for the bowler(i.e. no matter what the batsman's distribution is, expected value will be constant
    // = 16.78)
    distribution[1] = 0.0562;
    distribution[2] = 0.1065;
    distribution[3] = 0.152;
    distribution[4] = 0.1925;
    distribution[5] = 0.23;
    distribution[6] = 0.2628;
}
void Bowler :: UpdateDistribution(unordered_map<int,int> batsmans_history){
    double sum = 0;
    for(int i = 1; i <= 6; i++){
        sum += batsmans_history[i];
    }
    //Making batsman's history batsmans distribution
    for(int i = 1; i <= 6; i++){
        batsmans_history[i] /= sum;
    }
    /*Now, we can easily use the formula to find the best number the bowler needs to play.
    However, I want to include some randomness so that a sneaky player does not precalculate the best move the computer can play
    In other words, I am willing to sacrifice perfect play to include some randomness
    This is what I will do
    I will make a pair of vector E where the pairs are of form {expected val, i}. The expected value of the batsman if the bowler only plays 
    i(assuming that currently the batsman has 0 runs)
    I will assign the probabilities like this
    r[0] for the min, r[1] for the 2nd min, r[2] for 3rd min, r[3] for 4th min, r[4] for 5th min and r[5] for 6th min.(I will use a constant vector
    r = RANDOMIFIER to specify this)
    (This choice has no mathematical basis, it is just what I thought would be a good compromise between randomness and expected value)
    (Notice that the goal of the bowler is to minimize the expected value hence higher probabilites for the numbers which give lower expected value)
    */
    double sigmaVal = 0;//sigmaVal = sigma(P(i)*i)
    for(int i = 1; i <= 6; i++){
        sigmaVal += batsmans_history[i]*i;
    }
    vector<pair<int, double> > E_of_batsman;
    //Filling E_of_batsman
    for(int i = 1; i <= 6; i++){
        if(batsmans_history[i] == 0){
            E_of_batsman.push_back({INF,i});
        }
        else{
            E_of_batsman.push_back({(sigmaVal - batsmans_history[i]*i)/(batsmans_history[i]), i});
        }
    }
    sort(E_of_batsman.begin(), E_of_batsman.end());
    //Updating the distribution
    for(int i = 0; i < 6; i++){
        int current_number = E_of_batsman[i].second;
        distribution[E_of_batsman[i].second] = RANDOMIFIER[i];
    }
}
int Bowler::NextMove(){
    const long max_rand = 3456L;
    double lower_bound = 0;
    double upper_bound = 1;
    srand(100000*time(NULL) % 12343);
    double random_double = lower_bound + (upper_bound - lower_bound) * (rand() % max_rand) / double(max_rand);
    double sum = 0;
    for(int i = 1; i <= 6; i++){
        sum += distribution[i];
        if(sum >= random_double){
            return i;
        }
    }
}