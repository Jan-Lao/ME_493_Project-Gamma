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

using namespace std;

int numofcities = 10;
int pop_size = 10;

class City{
public:
    int city_x;
    int city_y;
};

class Policy{
public:
    double fitness;
    
    void mutate();
    void policyeval();
    
    //vector<City> Policy;
    //vector<vector<City>> Population;
};

class Agent{
    void agentinit();
};

class Map{
    void mapinit();
    void run();
};


/////=======================================POlICY FUNCTIONS======================================

////---------------------------------------MAKE A POLICY-----------------------------------------
vector<vector<City>> EA_init(){
    City city;
    vector<City> Policy;
    vector<vector<City>> Population;
    
    //Create a policy = A vector of cities in a certan arrangement.
    for(int i=0; i<pop_size; i++){ //Population = vector of policies
        for(int j=0; j<numofcities; j++){ //Policy =  vector of cities
            //for(int k = 0; k<100; k++){//Setting the characteristics of each city
                //city = k
                city.city_x = rand()%100; //Should this be random or preset?
                city.city_y = rand()%100;
            //}
            Policy.push_back(city);
        }
        Population.push_back(Policy);
    }
    //Each city has certain characteristcs. Take those characteristics to calculate distance (aka fitness)
    
    return Population;
}

////---------------------------------------MUTATE-----------------------------------------
void Policy::mutate(){
    //mutate a policy here
}

////---------------------------------------EA REPLICATE-----------------------------------------
vector<vector<City>> EA_replicate(int pop_size){
    vector<vector<City>> Population;
    //Population = P;
    
    //assert(population.size() == pop_size/2);
    
    while(Population.size()<pop_size){
        int spot = rand()%Population.size();
        Policy A;
        A = Population.at(spot); //broken here: "No viable overloaded ="
        A.mutate();
        
        Population.push_back(A); //broken here
    }
    
    //assert(Population.size() == pop_size);
    return Population;
}

////---------------------------------------SET POLICY FITNESS-----------------------------------------
void Policy::policyeval(){
    
    for (int l=0; l<numofcities; l++){
        int city_a = Population.at(Policy).at(l); //Take one                //broken here
        int city_b = Population.at(Policy).at(l+1); //Take the one after    //broken here
        //Fix this.
    }
    
    //First calculate the distance from city to city
    vector<int> distvect;
    for(int q=0; q<numofcities-1; q++){
        //Summing the distance between the cities in the arrangement
        int x1 = city_a.city_x; //broken here
        int y1 = city_a.city_y; //broken here
        int x2 = city_b.city_x; //broken here
        int y2 = city_b.city_y; //broken here
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
vector<Policy> EA_evaluate(int pop_size){ //TAKEN FROM CLASS
    vector<vector<City>> Population;
    //Population = P;
    for(int testing=0; testing<Population.size(); testing++){
        Population.at(testing).fitness = -1;
    }
    
    /// assign fitness
    for(int i=0; i<Population.size(); i++){
        Population.at(i).policyeval();
        //assert(Population.at(i).fitness != -1);
    }
    
    //for(int testing=0; testing<Population.size(); testing++){
        //assert(Population.at(testing).fitness != -1);
    //}
    //assert(population.size() == pop_size);
    return Population;
}

////---------------------------------------EA DOWNSELECT-----------------------------------------
vector<policy> EA_downselect(int pop_size){ //TAKEN FROM CLASS
    vector<vector<City>> Population;
    /// population is empty
    //assert(Population.size() == 0);
    //assert(P.size() == pop_size);
    
    bool binarytournament = false;
    bool strict = true;
    
    if(strict){
        /// select the top half, only.
        vector<double> fits;
        for(int i=0; i<P.size(); i++){
            fits.push_back(P.at(i).fitness);
        }
        sort(fits.begin(),fits.end());
        //cout << fits.at(0) << "\t" << fits.back() << endl;
        double survivorline = fits.at(pop_size/2);
        for(int i=P.size(); i>0; i--){
            if(P.at(i).fitness > survivorline){
                P.erase(P.begin()+i);
            }
        }
    }
    
    if(binarytournament){
        /// remove half by binary tournament
        while(population.size() < pop_size / 2){
            /// choose 2 at random
            int spot1 = rand()%P.size();
            int spot2 = rand()%P.size();
            while(spot2 == spot1){
                spot2 = rand()%P.size();
            }
            assert(spot1!=spot2);
            double fit1 = P.at(spot1).fitness;
            double fit2 = P.at(spot2).fitness;
            
            if(fit1<fit2){
                //// fit1 wins
                //  copy fit1 into "population"
                policy A1 = P.at(spot1);
                Population.push_back(A1);
            }
            else if(fit2<=fit1){
                //// fit2 wins
                // copy fit2 into "population"
                policy A2 = P.at(spot2);
                Population.push_back(A2);
            }
        }
    }
    
    assert(Population.size() == pop_size/2);
    return Population;
}

/////=====================================AGENT FUNCTIONS======================================
////---------------------------------------INITIALIZE AGENT-----------------------------------------
void agent::agentinit(){
    //state that agent starts at City 0
}

/////=====================================MAP FUNCTIONS========================================
////---------------------------------------INITIALIZE MAP-----------------------------------------
void map::mapinit(){ //SEE BELOW
    x_dim = 100;
    y_dim = 100;
}

////---------------------------------------RUN THE PROGRAM-----------------------------------------
void map::run(){
    //GOING TO DELETE THIS. ASSIGNMENT IS JUST THE COMBINATIONS OF CITIES WITH THE LEAST AMOUNT OF DISTANCE.
    //CONSIDERING DELETING AGENT AND MAP CLASSES. THE SALESPERSON IS NOT MOVING IN REAL TIME.
}

/////===================================MAIN FUNCTION==========================================
int main() {
    Agent agent; //SEE ABOVE
    Map map;
    
    Agent*p1= &agent;
    map.p1=p1;
    
    map.run();
    
    return 0;
}
