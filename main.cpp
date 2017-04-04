//
//  main.cpp
//  Project Gamma: Draft 2
//
//  Created by Jan Lao on 4/2/17.
//  Copyright © 2017 University Nevada, Reno. All rights reserved.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <assert.h>
#include <time.h>
#include <random>

using namespace std;

int numofcities = 10;
int pop_size = 10;
int maxgenerations = 100;

class City{
public:
    int city_xdim;
    int city_ydim;
};

class Policy{
public:
    double fitness;
    
    void mutate(vector<City> Policy);
    void policyeval(vector<vector<City>> Population, vector<City> Policy);
};


/////=======================================POlICY FUNCTIONS======================================

////---------------------------------------MAKE A POLICY-----------------------------------------
vector<vector<City>> EA_init(){
    vector<vector<City>> Population;
    vector<City> Policy;
    City city;
    
    //Create a policy = A vector of cities in a certan arrangement.
    for(int i=0; i<pop_size; i++){ //Population = vector of policies
        for(int j=0; j<numofcities; j++){ //Policy =  vector of cities
            city.city_xdim = rand()%100; //Should this be random or preset?
            city.city_ydim = rand()%100;
            Policy.push_back(city);
        }
        Population.push_back(Policy);
    }
    //Each city has certain characteristcs. Take those characteristics to calculate distance (aka fitness)
    
    return Population;
}

////-------------------------------------MUTATE A POLICY-----------------------------------------
void Policy::mutate(vector<City> Policy){
    //mutate a policy here by shuffling the order of the cities just a little bit
    //So lets swap 4 times? Arbitrarily 4 times
    
    City Temporary;
    
    for(int m=0; m<4; m++){
        int place1 = rand()%numofcities;
        int place2 = rand()%numofcities;
        
        //Swapping newly created temporary with 2 places etc. etc.
        Temporary = Policy.at(place1);
        Policy.at(place1) = Policy.at(place2);
        Policy.at(place2) = Temporary;
        
        //This is found from the Card shuffler.
    }
}

////---------------------------------------EA REPLICATE-----------------------------------------
vector<vector<City>> EA_replicate(vector<vector<City>> P, vector<City> Poli, int pop_size){
    vector<vector<City>> Population;
    vector<City> Policy;
    Population = P;
    Policy = Poli;
    
    //assert(population.size() == pop_size/2);
    
    while(Population.size()<pop_size){
        int spot = rand()%Population.size();
        class Policy A;
        A = Population.at(spot);                                            //***** BROKEN HERE
        A.mutate(vector<City> Policy);                                      //***** BROKEN HERE
        Population.push_back(A);                                            //***** BROKEN HERE
    }
    
    //assert(Population.size() == pop_size);
    return Population;
}

////---------------------------------------SET POLICY FITNESS-----------------------------------------
void Policy::policyeval(vector<vector<City>>P, vector<City> Poli){
    vector<vector<City>> Population;
    vector<City> Policy;
    Population = P;
    Policy = Poli;
    
    for (int l=0; l<numofcities; l++){
        int city_a = Population.at(Policy).at(l); //Take one                //***** BROKEN HERE
        int city_b = Population.at(Policy).at(l+1); //Take the one after    //***** BROKEN HERE
        //Fix this.
    }
    
    //First calculate the distance from city to city
    vector<int> distvect;
    for(int q=0; q<numofcities-1; q++){
        //Summing the distance between the cities in the arrangement
        int x1 = city_a.city_xdim;                                          //***** BROKEN HERE
        int y1 = city_a.city_ydim;                                          //***** BROKEN HERE
        int x2 = city_b.city_xdim;                                          //***** BROKEN HERE
        int y2 = city_b.city_ydim;                                          //***** BROKEN HERE
        //Fix this.
        
        double distance = sqrt(((x2-x1)*(x2-x1))+((y2-x1)*(y2-y1)));
        distvect.push_back(distance);
    }
    //Assert the size of this vector to be num of cities-1
    
    //Calculate entire distance
    double totaldistance = accumulate(distvect.begin(), distvect.end(), 0);
    
    //Take that distance and assign it a fitness
    fitness = totaldistance;
}

////---------------------------------------EA EVALUATE-----------------------------------------
vector<vector<City>> EA_evaluate(vector<vector<City>> P, vector<City> Poli, int pop_size){ //TAKEN FROM CLASS
    vector<vector<City>> Population;
    vector<City> Policy;
    Population = P;
    Policy = Poli;
    
    /// assign fitness
    for(int i=0; i<Population.size(); i++){
        Population.at(i).policyeval(P, Pol);                                     //***** BROKEN HERE
    }
    return Population;
}

////---------------------------------------EA DOWNSELECT-----------------------------------------
vector<vector<City>> EA_downselect(vector<vector<City>> P, vector<City> Poli, int pop_size){ //TAKEN FROM CLASS
    vector<vector<City>> Population;
    vector<City> Policy;
    /// population is empty
    //assert(Population.size() == 0);
    //assert(P.size() == pop_size);
   
    /// Remove half by binary tournament
    while(Population.size() < pop_size / 2){
        
        //Choosing two policies within the population at random
        int contestant1 = rand()%P.size();
        int contestant2 = rand()%P.size();
        while(contestant2 == contestant1){
            contestant2 = rand()%P.size();
        }
        assert(contestant1!=contestant2);
        double fitness1 = P.at(contestant1).fitness;
        double fitness2 = P.at(contestant2).fitness;
            
        if(fit1<fit2){
            policy fitwinner1 = P.at(contestant1);
            Population.push_back(fitwinner1);
        }
        else if(fit2<=fit1){
            policy fitwinner2 = P.at(contestant2);
            Population.push_back(fitwinner2);
        }
    }
    
    assert(Population.size() == pop_size/2);
    return Population;
}

/////===================================MAIN FUNCTION==========================================
int main() {
    srand((unsigned)time(NULL));
    vector<vector<City>> pop;
    vector<City> Pol;
    
    pop = EA_init();
    
    for(int generation = 0; generation<maxgenerations; generation++){
        pop = EA_replicate(pop, Pol, pop_size);
        //assert something
        
        pop = EA_evaluate(pop, Pol, pop_size);
        //assert something
        
        pop = EA_downselect(pop, Pol, pop_size);
        //assert something
        
    }
    
    for(int n=0; n<pop.size(); n++){
        
        //cout some stuff haven't decided yet...
        //Need to work on this.
        
    }
    
    return 0;
}
