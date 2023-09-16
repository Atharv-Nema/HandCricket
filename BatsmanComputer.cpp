#include <bits/stdc++.h>
using namespace std;
class Batsman{
    private:
        const double INF = 1000000000;
        const vector<double> RANDOMIFIER = {0.6, 0.3, 0.04, 0.03, 0.01, 0.01};//This the batsman's distribution for a given bowler's distribution
        unordered_map<int,double> distribution;
    public:
        Batsman();
        void UpdateDistribution(unordered_map<int,int> bowlers_history);
        int NextMove();
    
};
Batsman :: Batsman(){
    //This is the nash equilibrium distribution for the batsman(i.e. no matter what the bowler's distribution is, expected value will be constant
    // = 16.78)
    distribution[1] = 0.1887;
    distribution[2] = 0.1787;
    distribution[3] = 0.1696;
    distribution[4] = 0.1615;
    distribution[5] = 0.1542;
    distribution[6] = 0.1473;
}
void Batsman :: UpdateDistribution(unordered_map<int,int> bowlers_history){
    double sum = 0;
    for(int i = 1; i <= 6; i++){
        sum += bowlers_history[i];
    }
    //Making bowler's history bowler's distribution
    for(int i = 1; i <= 6; i++){
        bowlers_history[i] /= sum;
    }
    /*Now, we can easily use the formula to find the best number the batsman needs to play.
    However, I want to include some randomness so that a sneaky player does not precalculate the best move the computer can play
    In other words, I am willing to sacrifice perfect play to include some randomness
    This is what I will do
    I will make a pair of vector E where the pairs are of form {expected val, i}. The expected value of the batsman if the batsman only plays 
    i(assuming that currently the batsman has 0 runs)
    I will assign the probabilities like this
    r[0] for the max, r[1] for the 2nd max, r[2] for 3rd max, r[3] for 4th max, r[4] for 5th max and r[5] for 6th max.(I will use a constant vector
    r = RANDOMIFIER to specify this)
    (This choice has no mathematical basis, it is just what I thought would be a good compromise between randomness and expected value)
    (Notice that the goal of the batsman is to maximize the expected value, hence higher probabilites for the numbers which give higher expected value)
    */
    vector<pair<int, double> > E_of_batsman;
    //Filling E_of_batsman
    for(int i = 1; i <= 6; i++){
        if(bowlers_history[i] == 0){
            E_of_batsman.push_back({INF,i});
        }
        else{
            E_of_batsman.push_back({(1 - bowlers_history[i])*i/(bowlers_history[i]), i});
        }
    }
    sort(E_of_batsman.begin(), E_of_batsman.end());
    //Updating the distribution
    for(int i = 0; i < 6; i++){
        int current_number = E_of_batsman[i].second;
        distribution[E_of_batsman[i].second] = RANDOMIFIER[5 - i];//Notice that this way, the lowest gets r[5] and highest gets r[0] because
        //the list is sorted
    }
}
int Batsman::NextMove(){
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