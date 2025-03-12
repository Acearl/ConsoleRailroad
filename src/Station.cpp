#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

//locations train moves to

class Station{
    
    private:
        string name;
        pair<int,int> cords;
        //name1, 4.4 etc
	vector<Station *> destinations;
	//vector<Station> destinations;
        vector<string> destinations2;

    public:
        Station(){};
        Station(const string& name, const pair<int,int>& cords)
        : name(name), cords(cords), destinations() {};
        Station(const string& name, const pair<int,int> cords, const vector<string> dest)
        : name(name), cords(cords), destinations2(dest){}
        Station(const string& name, const pair<int,int>& cords, const vector<Station *> dest)
        : name(name), cords(cords), destinations(dest){};
        void display() const
        {
            cout<<" "<<name<<": X:"<<cords.first<<": Y:"<<cords.second<<endl;
        }
        void displayDestinations() const
        {
	    if(destinations.empty())
	    {
		    cout<<"no destinations"<<endl;
	    }
	    else
	    {
		Station temp;
		cout<<name<<":"<<endl;
		int counter = 1;
		//cout<<destinations[counter]->name;	
		//cout<<"target : "<<target<<endl;
		for(auto x: destinations)
		{
			cout<<"\t"<<counter+1<<". "<<x->getName()<<", "<<x->distCalc(counter)<<endl;
			counter++;
		}
		/*
	        for(int counter = 0; counter < destinations.size(); counter++)
       		{
			if(destinations[counter] != nullptr)
			{
				temp = *destinations[counter];
               			cout<<"\t"<<counter+1<<". "<<temp.getName()<<", "<<temp.distCalc(counter)<<endl;
			}
		}
		*/
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
	/*
        void setDestinations(vector<string *> destinations)
        {
            this->destinations2=*destinations;
        }*/

        vector<Station*> getDestinations()
        {
            return destinations;
        }
        void setDestinations(vector<Station*> destinations)
        {
            this->destinations=destinations;
        }
	double distCalc(int target)
	{
		//Take in station destination from this instance of a station class.
		//print the total distance calculation with euclidian geometry.
		target--;//quick mod to be indexes of arrays.
		cout<<"dist calc:  ";
		int size = 0;
		for(auto x: destinations)
		{size++;}
		cout<<"target :"<<target+1<<": destinations size = "<<size;
		if(target >= 0 && target < size)
		{
			//cout<<"REEEEEE"<<endl;
			double dist;
			Station dest = *destinations[target];
			
			dist = sqrt(
			pow((cords.first - dest.getX()),2.0) +
			pow((cords.second - dest.getY()),2.0)
			);
			return dist;
		}
		else
		{
			cout<<endl<<"dist calc error. target :"<<target<<" for station "<<name<<" to "<<destinations[target]->getName()<<endl;
		return -1.0;
		}
				
	}
};
