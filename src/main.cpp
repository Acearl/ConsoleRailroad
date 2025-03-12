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
    uniform_int_distribution<> cordDistrib(0, gridLen - 1);

    //for every number of stations make a station using the name list with random grid cords
    //remove name from list and reduce max size of random int distribution.
    bool repeatFlag = false;
    for (size_t i = 0; i < numStations; i++) {
        uniform_int_distribution<> nameDistrib(0, static_cast<int>(stationNames.size()) - 1);
        int randIndex = nameDistrib(gen);

        //cout << "randIndex: " << randIndex << " -> " << stationNames[randIndex] << endl;

        int x = cordDistrib(gen); // x coordinate within grid bounds
        int y = cordDistrib(gen); // y coordinate within grid bounds
        //Picks any of the stations inside randomly unless the min is the size of the name list
        if(ogStationList.size() > 1)//rolls again for duplicate stations at thje same place
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
        
    }	//find for each station in the station list declared with only a string
	//setting their destinations of stations they connect to.
	//
	//vector<Station*> baseStations = {};
	//vector<Station*> tempDestinations;
    for(int x = 0; x < ogStationList.size(); x++)
    {
        //cout<<"X "<<x<<endl;
	vector<Station*> destinations;//reset destinations for next station
	vector<Station*> tempStationList;//for removing stations
	for(int k = 0; k<ogStationList.size(); k++)
	{
		if(k!=x)
		{
			tempStationList.push_back(&ogStationList[k]);
		}
	}
	cout<<"test"<<endl;
	//vector<string> tempStationNames = stationNames;//for removing names
        cout<<"Setting destinations for "<<ogStationList[x].getName()<<endl;
        //tempStationList.erase(tempStationList.begin() + x);//remove station's own name
	for (size_t i = 0; i < 2; i++)
        {

            uniform_int_distribution<> stationDistrib(0, static_cast<int>(tempStationList.size()) - 1);
            //I dont fully understand why this turns the input into a vector of
            //stations instead of just the number at the station to be removed
            int randIndex = stationDistrib(gen);
            Station* target = tempStationList[randIndex];//dest target
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
    
    // Generate stations with random names and coordinates
    vector<Station> stationList = GenerateStations(stationNames, gen);

    // Display the generated stations
    for (auto& station : stationList) 
    {
        station.display();
    }
    //cout<<"rip"<<endl;
    for (int i = 0; i<stationList.size(); i++) 
    {
	 stationList[i].displayDestinations();
    }
    Train player = Train("player",stationList[0],0.5);
    cout<<endl;

    //int targetIndex = 0;
    //Station curStation = *player.getCurrent();

    char selection = ' ';
    
    //vector<Station *> destinations;
    
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
        for(auto x : stationList)
        {
            //destinations.push_back(x);
            cout<<counter<<". "<<x.getName()<<", "<<endl;
            counter++;
        }
	Station *currentStation = player.getCurrent();
	//steps 2,3
	if(currentStation != nullptr)
	{
		//curStation = *player.getCurrent();
		cout<<"Current Station : "<<currentStation->getName()<<endl;
		//segmentation fault somehow
		currentStation->displayDestinations();

	}
	else
	{
		cout<<"no curr station set"<<endl;
	}
	
	cout<<"Selection: ";
	cin >> selection;

	//step 4
	if(isdigit(selection))
	{
		int targetIndex = (selection - '0')-1;
		if (targetIndex >= 0 && targetIndex < currentStation->getDestinations().size())
		{
			//debug display stuff
			/*
			cout<<"curr ";
			player.getCurrent()->display();
			cout<<endl;
			cout<<"dest ";
			player.getDest()->display();
			cout<<endl;*/

			//actual variable changes
			//vector<Station*> dests = player.getCurrent()->getDestinations();
			Station* dest = currentStation->getDestinations()[targetIndex];
			player.setDest(dest);
			player.travel(targetIndex);

			currentStation = player.getCurrent();
			cout<<"Curr :"<<currentStation->getName()<<endl;
			cout<<"Dest :"<<player.getDest()->getName()<<endl;
		}
		else
		{
			cout<<"invalid selection"<<endl;
		}
	}
    }    
    cout<<endl<<"Game Exit"<<endl;
    return 0;
    
}
