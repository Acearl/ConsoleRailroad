#include <iostream>
#include "Station.cpp"  // Ensure this is implemented correctly
#include <string>
#include <vector>
#include <random>
using namespace std;

vector<Station> GenerateStations(vector<string> stationNames, mt19937& gen) {
    //min must be "size" of array to do all stations.
    int numStations = min(8, static_cast<int>(stationNames.size())); 
    int gridLen = static_cast<int>(stationNames.size());
    vector<Station> ogStationList;
    uniform_int_distribution<> ogNameDistrib(0, stationNames.size()-1);
    uniform_int_distribution<> coordDistrib(0, gridLen - 1);
    //for every number of stations make a station using the name list with random grid cords
    //remove name from list and reduce max size of random int distribution.
    bool repeatFlag = false;
    for (size_t i = 0; i < numStations; i++) {
        uniform_int_distribution<> nameDistrib(0, static_cast<int>(stationNames.size()) - 1);
        int randIndex = nameDistrib(gen);

        //cout << "randIndex: " << randIndex << " -> " << stationNames[randIndex] << endl;

        int x = coordDistrib(gen); // x coordinate within grid bounds
        int y = coordDistrib(gen); // y coordinate within grid bounds
        //Picks any of the stations inside randomly unless the min is the size of the name list
        if(ogStationList.size() > 1)
        {
            for(auto& station: ogStationList)
            {
                if(station.getX() == x && station.getY() == y)
                {
                    repeatFlag = true;
                    cout<<"hit"<<endl;
                }
            }
        }
        
        if(repeatFlag == false)
        {
            Station temp(stationNames[randIndex], make_pair(x, y));
            ogStationList.push_back(temp);

            stationNames.erase(stationNames.begin() + randIndex);
        }
        else{
            i--;
            repeatFlag=false;
        }
        
    }
    //this distrib is for multiple destinations in a station. 
    //This removes duplicate destinations in the list
    //uniform_int_distribution<> stationDistrib(0, static_cast<int>(stationNames.size()) - 1);
    //out of generated stations find ones to connect to
    //then compute distance from source station

    //ogStation list for reuse/reference
    //stationList for modifications in scope
    //Thought process only. Not explaination of code!
    //make input list
    //update range of distribution to be smaller
    //get int of which station to take
    //get station at position int
    //calculate station distance
    //add pair to destinations list
    //when destinations are finished add them to the current station
    //update ogStationList
    for(int x = 0; x< ogStationList.size(); x++)
    {
        //cout<<"X "<<x<<endl;
        vector<Station> tempStationList = ogStationList;
        vector<string> tempStationNames = stationNames;
        //cout<<"Setting destinations for "<<tempStationList.at(x).getName()<<endl;

        tempStationList.erase(tempStationList.begin() + x);
        //I dont fully understand why this turns the input into a vector of
        //stations instead of just the number at the station to be removed
        //must be placed in number of stations x to prevent multiple removals of x place    
        vector<pair<string,double>> destinations{};
        for (size_t i = 0; i < 2; i++)
        {

            uniform_int_distribution<> stationDistrib(0, static_cast<int>(tempStationList.size()) - 1);
            //I dont fully understand why this turns the input into a vector of
            //stations instead of just the number at the station to be removed
            int randIndex = stationDistrib(gen);
            Station target = tempStationList[randIndex];

            //cout<<"randIndex "<<randIndex<<", ";

            double distance = sqrt(pow(target.getY() - tempStationList[x].getY(), 2.0) + pow(target.getX()+tempStationList[x].getY(),2.0));
            
            //cout<<tempStationList[x].getY()<<" "<<tempStationList[x].getX()<<" "<<distance<<" "<<randIndex<<endl;
            
            destinations.push_back(make_pair(target.getName(),distance));

            // cout<<"front of list"<<tempStationList[0].getName()<<" back of list "<<tempStationList[tempStationList.size()-i-1].getName()<<endl;

            tempStationList.erase(tempStationList.begin()+randIndex);
        }
        // cout<<"Station: "<<ogStationList[x].getName()<<" Goes to"<<endl;
        ogStationList[x].setDestinations(destinations);
        //ogStationList[x].displayDestinations();
        //cout<<endl;
        //ogStationList[];
    }
    return ogStationList;
}

int main() {
    vector<string> stationNames{"Totonian", "Markarth", "Sevental", "Green Acres", "Lawnton", "Great Rock", "Tea Town"}; //{"A","B","C","D","E","F","G","H"};
    random_device rd;
    mt19937 gen(rd());

    // Generate stations with random names and coordinates
    vector<Station> stationList = GenerateStations(stationNames, gen);

    // Display the generated stations
    for (auto& station : stationList) {
        station.display();
    }
    // for (auto& station : stationList) {
    //     station.displayDestinations();
    // }
    return 0;
}
