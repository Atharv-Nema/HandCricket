#include <bits/stdc++.h>
using namespace std;
class Bowler{
    private:
        unordered_map<int,double> distribution;
    public:
        Bowler();
        int NextMove();
    
};
Bowler :: Bowler(){
    distribution[1] = 0.0562;
    distribution[2] = 0.1065;
    distribution[3] = 0.152;
    distribution[4] = 0.1925;
    distribution[5] = 0.23;
    distribution[6] = 0.2628;
}
int Bowler::NextMove(){
    const long max_rand = 3456L;
    double lower_bound = 0;
    double upper_bound = 1;
    srand(100000*time(NULL) % 12343);
    double random_double = lower_bound + (upper_bound - lower_bound) * (rand() % max_rand) / max_rand;
    int sum = 0;
    for(int i = 1; i <= 6; i++){
        sum += distribution[i];
        if(sum >= random_double){
            return i;
        }
    }
}