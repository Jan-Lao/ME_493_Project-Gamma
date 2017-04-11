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

int numofcities = 25; //ARGUABLY HR_2, HR_3, AND HR_4
int numofmutations = 10;

using namespace std;

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
    long double fitness;
    
    //void policyinit();
    void mutate(vector<city>);
    void policyeval(vector<city>);
};

/////=====================================EA init=====================================
void city::cityinit(){
    city_x = rand()%100 + JLRAND - JLRAND;
    city_y = rand()%100 + JLRAND - JLRAND;
};

vector<city> policyinit(){
    vector<city> cityvector;
    for(int j=0; j<numofcities; j++){
        city B;
        B.cityinit();
        cityvector.push_back(B);
    }
    return cityvector;
};

vector<policy> EA_init(int pop_size){ //MR_1
    vector<policy> population;
    for(int i=0; i<pop_size/2; i++){
        policy A;                           //WRONG....NOTE: READ UP ON "SCOPE" -> See Dr. Logan's email
        //A.policyinit();                   //WRONG....NOTE: READ UP ON "SCOPE"
        vector<city> policyinit();          //WRONG....NOTE: READ UP ON "SCOPE"
        population.push_back(A);
    }
    return population;
};

/////=====================================EA repl=====================================
void policy::mutate(vector<city> cvect){ //LR_4
    vector<city> policytemp;
    policytemp = cvect; //passing a policy into the mutate function
    
    //Mutate a policy by changing the city placements
    //NEED TO EXAMINE MORE CLOSELY....From Cardshuffler
    for(int k=0; k<numofmutations; k++){
        //vector<city> placement;
        city B1;
        
        int place1 = rand()%numofcities;
        int place2 = rand()%numofcities;
        
        //cout << policytemp.size() << endl; //debugging....
        
        B1 = policytemp.at(place1);
        policytemp.at(place1)=policytemp.at(place2);
        policytemp.at(place2)=B1;
    }
}

vector<policy> EA_replicate(vector<policy> P, vector<city> poldef, int pop_size){
    vector<policy> population;
    population = P;
    
    vector<city> cv;
    cv = poldef;
    
    //cout << cv.size() << endl; //debugging
    //cout << P.size() << endl; //debugging
    
    while(population.size()<pop_size){
        int spot = rand()%population.size();
        policy A;
        A = population.at(spot);
        A.mutate(cv);
        population.push_back(A);
    }
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
        distbetweencities = sqrt(((delta_x)*(delta_x))+((delta_y)*(delta_y))); //LR_7
        distvect.push_back(distbetweencities);
    }
    
    totaldistance = accumulate(distvect.begin(),distvect.end(),0); //LR_8
    fitness = totaldistance; //MR_2
}

vector<policy> EA_evaluate(vector<policy> P, vector<city> poldef, int pop_size){
    vector<policy> population;
    population = P;
    
    vector<city> cv;
    cv = poldef;
    
    //Assign fitness
    for(int i=0; i<population.size(); i++){
        population.at(i).policyeval(cv); //MR_3
    }
    return population;
}

/////=====================================EA dselect=====================================
vector<policy> EA_downselect(vector<policy> P, int pop_size){
    vector<policy> population;
    assert(population.size() == 0);
    assert(P.size() == pop_size);
    
    //cout << P.size() << endl; //debugging
    
    //BINARY TOURNAMENT COMMENCED
    while(population.size() < pop_size/2){ //MR_4
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
    //cout << population.size() << endl; //debugging
    return population;
}

/////=====================================MAIN FUNC=====================================
int main() {
    srand((unsigned)time(NULL));
    int pop_size = 100;
    int maxgenerations = 300;

    
    vector<policy> pop;
    vector<city> pol;
    
    pol = policyinit();
    pop = EA_init(pop_size);
    
    for(int generation = 0; generation < maxgenerations; generation++){
        pop = EA_replicate(pop, pol, pop_size); //MR_5
        
        pop = EA_evaluate(pop, pol, pop_size);
        
        pop = EA_downselect(pop, pop_size);
        
        //cout << "Generation = " << generation+1 << "\t";
        //cout << "Fit = " << pop.at(generation).fitness << "\t";
        //cout << endl;
    }
    
    for(int i=0; i<pop.size(); i++){
        cout << i+1 << ": " << "\t";
        cout << "Fit = " << pop.at(i).fitness << "\t";
        cout << endl;
    }
    
    //~~CURRENT PROBLEM AS OF 4/4/17: FITNESS (TOTAL DISTANCE) DOES NOT SEEM TO SHOW ANY BEHAVIOR OF COVERGENCE TO A SMALLER NUMBER
    
    cout << "Evolutionary Algorithm: Terminated." << endl;
    return 0;
}
