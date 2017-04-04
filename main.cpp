//
//  main.cpp
//  Project Gamma: Draft 3
//
//  Created by Jan Lao on 4/3/17.
//  Copyright © 2017 University Nevada, Reno. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
#include <assert.h>
#include <time.h>

using namespace std;

int numofpolicies = 100;
int numofcities = 10;

class City{
public:
    void init();
    
    int city_xdim;
    int city_ydim;
};

class Policy{
public:
    double fitness;
    
    void mutate();
    void policyeval();
    
    vector<City> policy;
    vector<vector<City>> population;
};

/////===================================EA INIT===================================
void City::init(){
    city_xdim = rand()%100;
    city_ydim = rand()%100;
}

vector<City> policyinit(vector<City> Po){
    vector<City> policy;
    policy = Po;
    
    for(int j=0; j<numofcities; j++){
        City A;
        A.init();
        policy.push_back(A);
    }
    return policy;
}

vector<vector<City>> EA_init(vector<vector<City>> P, vector<City> Po){
    vector<vector<City>> population;
    population = P;
    
    vector<City> policy;
    policy = Po;
    
    for(int i=0; i<numofpolicies; i++){
        vector<City> B;
        B.policyinit(Po);
        population.push_back(B);
    }
    return population;
}


/////===================================EA REPL===================================
vector<vector<City>> EA_replicate(vector<vector<City>> P, vector<City> Po, int pop_size){
    vector<vector<City>> population;
    population = P;
    
    vector<City> policy;
    policy = Po;
    
    while(population.size()<pop_size){
        int spot = rand()%population.size();
        Policy A = population.at(spot);;
        

        
        City Temporary;
        
        for(int m=0; m<4; m++){
            int place1 = rand()%numofcities;
            int place2 = rand()%numofcities;
            
            //Swapping newly created temporary with 2 places etc. etc.
            Temporary = policy.at(place1);
            policy.at(place1) = policy.at(place2);
            policy.at(place2) = Temporary;
        }
    }
    
    return population;
}

/////===================================EA EVAL===================================
vector<vector<City>> EA_evaluate(vector<vector<City>> P, int pop_size){
    vector<vector<City>> population;
    population = P;
    
    return population;
}

vector<vector<City>> EA_downselect(vector<vector<City>> P, int pop_size){
    vector<vector<City>> population;
    population = P;
    
    return population;
}


/////===================================MAIN FUNC===================================
int main() {
    srand((unsigned)time(NULL));
    vector<vector<City>> pop;
    vector<City> pol;
    
    int pop_size = 100;
    
    pop = EA_init(pop, pol);
    
    int maxgenerations = 100;
    
    for(int generations; generations<maxgenerations; generations++){
        pop = EA_replicate(pop, pol, pop_size);
        pop = EA_evaluate(pop, pop_size);
        pop = EA_downselect(pop, pop_size);
    }
    
    return 0;
}
