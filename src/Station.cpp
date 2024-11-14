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
        //Name and distance from station
        //Name1 4.4
        //Name2 1.7 etc
        vector<pair<string, double>> destinations;
        vector<string> destinations2;

    public:
        Station(const string& name, const pair<int,int>& cords)
        : name(name), cords(cords), destinations() {};

        Station(const string& name, const pair<int,int>& cords, const vector<string> dest)
        : name(name), cords(cords), destinations2(dest){};

        Station(const string& name, const pair<int,int>& cords, const vector<pair<string,double>> dest)
        : name(name), cords(cords), destinations(dest){};
        void display() const
        {
            cout<<" "<<name<<": X:"<<cords.first<<": Y:"<<cords.second<<endl;
        }
        void displayDestinations() const
        {
            for(pair<string,double> destination: destinations)
            {
                cout<<"First "<<destination.first<<" Second "<<destination.second<<endl;
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
        void setDestinations(vector<pair<string,double>>& destinations)
        {
            this->destinations=destinations;
        }
};