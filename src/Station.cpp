#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

//locations train moves to

class Station{
    
    private:
        string name;
        pair<int,int> cords;
        //name1, 4.4 etc
	vector<Station> destinations;
        vector<string> destinations2;

    public:
        Station(){};
        Station(const string& name, const pair<int,int>& cords)
        : name(name), cords(cords), destinations() {};
        Station(const string& name, const pair<int,int>& cords, const vector<string> dest)
        : name(name), cords(cords), destinations2(dest){}
        Station(const string& name, const pair<int,int>& cords, const vector<Station> dest)
        : name(name), cords(cords), destinations(dest){};
        void display() const
        {
            cout<<" "<<name<<": X:"<<cords.first<<": Y:"<<cords.second<<endl;
        }
        void displayDestinations() const
        {
            cout<<name<<":"<<endl;
	    int counter = 1;
            for(Station destination: destinations)
            {
                cout<<"\t"<<counter<<". "<<destination.getName()<<", "<<"dist calc()"<<endl;
		counter++;
            }
        }
        int getX()
        {
            return cords.first;
        }
        int getY()
        {
            return cords.second;
        }
        string getName()
        {
            return name;
        }
        void setDestinations(vector<string>& destinations)
        {
            this->destinations2=destinations;
        }
        vector<Station> getDestinations()
        {
            return destinations;
        }
        void setDestinations(vector<Station>& destinations)
        {
            this->destinations=destinations;
        }
};
