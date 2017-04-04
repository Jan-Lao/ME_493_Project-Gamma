//
//  main.cpp
//  Project Gamma: Draft 6
//
//  Created by Jan Lao on 4/4/17.
//  Copyright © 2017 University Nevada, Reno. All rights reserved.
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <numeric>
#include <stdlib.h>
#include <math.h>

#define JLRAND (double)rand()/RAND_MAX

using namespace std;

int numofcities = 10;
int pop_size = 10;
int maxgenerations = 100;
int numofmutations = 3;

class city{
public:
    double city_x;
    double city_y;
    void cityinit();
};

class policy{
public:
    double distbetweencities;
    vector<int> distvect;
    double totaldistance;
    double fitness;
    
    void policyinit();
    void mutate();
    void policyeval(vector<city>);
};

/////=====================================EA init=====================================
void city::cityinit(){
    city_x = rand()%100 + JLRAND - JLRAND;
    city_y = rand()%100 + JLRAND - JLRAND;
};

void policy::policyinit(){
    vector<city> cityvector;
    for(int j=0; j<numofcities; j++){
        city B;
        B.cityinit();
        cityvector.push_back(B);
    }
};

vector<policy> EA_init(){
    vector<policy> population;
    
    for(int i=0; i<pop_size/2; i++){
        policy A;
        A.policyinit();
        population.push_back(A);
    }
    return population;
};

/////=====================================EA repl=====================================
void policy::mutate(){
    //Mutate a policy by changing the city placements
    //NEED TO EXAMINE MORE CLOSELY....From Cardshuffler
    for(int k=0; k<numofmutations; k++){
        vector<city> placement;
        city B1;
        B1.cityinit();
        placement.push_back(B1);
        
        int place1 = rand()%numofcities;
        int place2 = rand()%numofcities;
        
        B1 = placement.at(place1);
        placement.at(place1)=placement.at(place2);
        placement.at(place2)=B1;
    }
}

vector<policy> EA_replicate(vector<policy> P, int pop_size){
    vector<policy> population;
    population = P;
    
    assert(population.size() == pop_size/2);
    
    while(population.size()<pop_size){
        int spot = rand()%population.size();
        policy A;
        A = population.at(spot);
        A.mutate();
        population.push_back(A);
    }
    
    assert(population.size() == pop_size);
    
    return population;
}

/////=====================================EA eval=====================================
void policy::policyeval(vector<city> cvect){
    vector<city> cityvector;
    cityvector = cvect;
    //Assign the fitness by total distance
    
    for(int l=0; l<numofcities-1; l++){
        double delta_x = cityvector.at(l+1).city_x - cityvector.at(l).city_x;
        double delta_y = cityvector.at(l+1).city_y - cityvector.at(l).city_y;
        distbetweencities = sqrt(((delta_x)*(delta_x))+((delta_y)*(delta_y)));
        distvect.push_back(distbetweencities);
    }
    
    totaldistance = accumulate(distvect.begin(),distvect.end(),0);
    fitness = totaldistance;
}

vector<policy> EA_evaluate(vector<policy> P, vector<city> poldef, int pop_size){
    vector<policy> population;
    population = P;
    
    vector<city> cv;
    cv = poldef;
    
    for(int testing=0; testing<population.size(); testing++){
        population.at(testing).fitness = -1;
    }
    
    //Assign fitness
    for(int i=0; i<population.size(); i++){
        population.at(i).policyeval(cv);
        assert(population.at(i).fitness != -1);
    }
    
    for(int testing=0; testing<population.size(); testing++){
        assert(population.at(testing).fitness != -1);
    }
    assert(population.size() == pop_size);
    return population;
}

/////=====================================EA dselect=====================================
vector<policy> EA_downselect(vector<policy> P, int pop_size){
    vector<policy> population;
    assert(population.size() == 0);
    assert(P.size() == pop_size);
    
    //BINARY TOURNAMENT COMMENCED
    while(population.size() < pop_size/2){
        int spot1 = rand()%P.size();
        int spot2 = rand()%P.size();
        while(spot2 == spot1){
            spot2 = rand()%P.size();
        }
        assert(spot1!=spot2);
        double fit1 = P.at(spot1).fitness;
        double fit2 = P.at(spot2).fitness;
        
        if(fit1<fit2){
            //fit 1 wins -> put into population vector
            policy A1 = P.at(spot1);
            population.push_back(A1);
        }
        else if(fit2<=fit1){
            //fit 2 wins -> put into population vector
            policy A2 = P.at(spot2);
            population.push_back(A2);
        }
    }
    assert(population.size() == pop_size/2);
    return population;
}

/////=====================================MAIN FUNC=====================================
int main() {
    srand((unsigned)time(NULL));
    
    vector<policy> pop;
    vector<city> pol;
    
    pop = EA_init();
    
    for(int generation = 0; generation < maxgenerations; generation++){
        pop = EA_replicate(pop, pop_size);
        assert(pop.size() == pop_size);
        
        pop = EA_evaluate(pop, pol, pop_size);
        assert(pop.size() == pop_size);
        
        pop = EA_downselect(pop,pop_size);
        assert(pop.size() == pop_size/2);
    }
    
    for(int i=0; i<pop.size(); i++){
        //cout << "Generation= " << generation << "\t"; //generation counter?
        //cout << "Total Distance =  " << pop.at(i).R << "\t";
        cout << "fit= " << pop.at(i).fitness << "\t";
        cout << endl;
    }
    cout << "Evolutionary Algorithm: Terminated." << endl;
    return 0;
}
