#include <iostream>
#include "Station.cpp"  
#include "Train.cpp" 
#include <string>
#include <vector>
#include <random>
#include <cctype>

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
	//find for each station in the station list declared with only a string
	//setting their destinations of stations they connect to.
	//
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
        vector<Station> destinations{};

        for (size_t i = 0; i < 2; i++)
        {

            uniform_int_distribution<> stationDistrib(0, static_cast<int>(tempStationList.size()) - 1);
            //I dont fully understand why this turns the input into a vector of
            //stations instead of just the number at the station to be removed
            int randIndex = stationDistrib(gen);
            Station target = tempStationList[randIndex];

            //cout<<"randIndex "<<randIndex<<", ";
            // cout<<target.getY()<<"-"<<tempStationList[x].getY()<<"="<<target.getY() - tempStationList[x].getY();
            // cout<<" pow"<<pow(target.getY() - tempStationList[x].getY(), 2.0)<<endl;
            // cout<<target.getX()<<"-"<<tempStationList[x].getX()<<"="<<target.getX() - tempStationList[x].getX();
            // cout<<" pow"<<pow(target.getX() - tempStationList[x].getX(), 2.0)<<endl;
            // cout<<"added"<<(pow(target.getY() - tempStationList[x].getY(), 2.0)) + (pow(target.getX()-tempStationList[x].getY(),2.0))<<endl;
            // cout<<"sqrt"<<sqrt((pow(target.getY() - tempStationList[x].getY(), 2.0) + (pow(target.getX()-tempStationList[x].getY(),2.0))))<<endl;
            double distance = sqrt(
                pow(target.getY() - ogStationList[x].getY(), 2.0) + 
                pow(target.getX() - ogStationList[x].getX(), 2.0)
            );

            destinations.push_back(target);


            tempStationList.erase(tempStationList.begin()+randIndex);
        }
        ogStationList[x].setDestinations(destinations);
        
    }
    return ogStationList;
}

int main() 
{
    vector<string> stationNames{"Totonian", "Markarth", "Sevental", "Green Acres", "Lawnton", "Great Rock", "Tea Town"}; //{"A","B","C","D","E","F","G","H"};
    random_device rd;
    mt19937 gen(rd());
    
    //vector<char> selectionList = {'q','r'};
    // Generate stations with random names and coordinates
    vector<Station> stationList = GenerateStations(stationNames, gen);

    // Display the generated stations
    for (auto& station : stationList) {
        station.display();
    }
    for (auto& station : stationList) {
        station.displayDestinations();
    }
    Train player = Train("player",stationList.at(0),1.0);
    cout<<endl;
    int target = 0;
    Station curStation = stationList.at(0);
    char selection = ' ';
    vector<Station> destinations;
    //1 display all stations
    //2 show current station
    //3 show destinations of that current station with numbered selections
    //4 select user input of that station to be the destination
    //5 travel to said station
    //6 reapeat until user quits
    while (selection != 'q' && selection != 'Q')
    {
        cout<<"what do you select? Q,R, or number presented"<<endl;
        int counter = 1;
        //1 display stations
        for(Station x : stationList)
        {
            //destinations.push_back(x);
            cout<<counter<<". "<<x.getName()<<", "<<endl;
            counter++;
        }
	//steps 2,3
	cout<<"Current Station : "<<curStation.getName()<<endl;
	curStation.displayDestinations();
        cout<<"Selection: ";
	cin >> selection;
	//step 4
	
	if(isdigit(selection))
	{
		target = (selection - '0')-1;
		//cout<<"target : "<<target<<endl;
		if (target >= 0 && target < curStation.getDestinations().size())
		{
			vector<Station> dests = curStation.getDestinations();
			Station targetStation = dests.at(target);
			player.setDest(&targetStation);
			Station temp = player.getDest();
			temp.display();
		}
	}
    }    
    
    return 0;
    
}
