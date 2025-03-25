#include <iostream>
#include "Station.cpp"  
#include "Train.cpp" 
#include <string>
#include <vector>
#include <random>
#include <cctype>

using namespace std;

vector<Station> GenerateStations(vector<string> stationNames, mt19937& gen, int sizeMin);
void displayMap(int width, int height, vector<Station> stations);
int main() 
{
    vector<string> stationNames{"Totonian", "Markarth", "Sevental", "Green Acres", "Lawnton", "Great Rock", "Tea Town"}; //{"A","B","C","D","E","F","G","H"};
    random_device rd;
    mt19937 gen(rd());
    int size = 8;
    
    // Generate stations with random names and coordinates
    vector<Station> stationList = GenerateStations(stationNames, gen, size);
    // Display the generated stations
    for (auto station : stationList)
    {
        station.display();
    }
    //cout<<"rip"<<endl;
    for (int i = 0; i<stationList.size(); i++) 
    {
	 stationList[i].displayDestinations();
    }

	displayMap(size,size,stationList);
    Train player = Train("player",&stationList[0],2.0);
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
	    displayMap(size,size,stationList);
        cout<<"what do you select? Q,R, or number presented"<<endl;
        int counter = 1;
        //1 display stations
        for(auto x : stationList)
        {
            //destinations.push_back(x);
            cout<<counter<<". "<<x.getName()<<", ";
	    for(auto y: x.getDestinations())//only names and distances to points
		{

		}
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
		int targetIndex = (selection - '0');
		cout<<endl<<"line 166"<<endl;
		Station* dest = currentStation->getDestinations()[targetIndex];
		player.setDest(dest);
		if (targetIndex >= 1 && targetIndex <= currentStation->getDestinations().size())
		{
			//debug display stuff
			if(targetIndex == currentStation->getDestinations().size())
			{
				Station* dest = currentStation->getDestinations()[targetIndex-1];
				player.setDest(dest);
			}
			cout<<"curr ";
			player.getCurrent()->display();
			cout<<"dest ";
			player.getDest()->display();
			cout<<endl;
			cout<<"REEE  ";		
			//actual variable changes
			//vector<Station*> dests = player.getCurrent()->getDestinations();
			//player.setDest(dest);
			cout<<"tar "<<targetIndex;
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

vector<Station> GenerateStations(vector<string> stationNames, mt19937& gen, int sizeMin) {
    //min must be "size" of array to do all stations.//not relevent anymore but keeping here in case I need it.

    int numStations = min(sizeMin, static_cast<int>(stationNames.size())); 
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
	//cout<<"test"<<endl;
	//vector<string> tempStationNames = stationNames;//for removing names
        //cout<<"Setting destinations for "<<ogStationList[x].getName()<<endl;
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
void displayMap(int width, int height, vector<Station> stations)
{
	//get x and y value to determine the size of the map
	//build left to right by repeating a character util the x value is hit
	//place char value of first letter of the station name followed by the number in the sequence of that letter.
	//ex Broville and Boston. Broville = B1 next Boston = B2. Claifications may follow.
	//add rest of empty char spaces with width -x -1
	//ex
	//***T1**
	//*I1**B1
	//*******
	//B2*****
	vector<string> map;
	string mapLine;
	vector<int> xlist;
	vector<int> ylist;
	for(auto z: stations)
	{
		xlist.push_back(z.getX());
		ylist.push_back(z.getY());
	}

	cout<<"X :"<<xlist.size()<<" Y "<<ylist.size()<<endl;
	//loop (*s for x times. step+2.) 
	for(int a = ylist.size(); a < height; a--)
	{
		cout<<"A "<<a<<endl;
		//get topmost/top down current line of the grid 
		int curX = xlist[a];
		//find what stations are in that line
		for(int b = 0; b < xlist[b]; b++)
		{
			cout<<"\t"<<"B "<<b<<endl;
			//get y cords and first letters of those stations
			//ys resets and letters doesnt to maintain checks of duplicate numbers to add B2 and such
			vector<int> ys;
			vector<char> letters;
			char letter;
			for(int c = 0; c < xlist.size(); c++)
			{				
				cout<<"\t\t"<<"C "<<c<<endl;
				if(c==xlist[c])
				{
					ys.push_back(xlist[c]);
					cout<<xlist[c];
					string name = stations[a].getName();
					letter = name[0];
					cout<<letter<<"letter";
					letters.push_back(letter);
					cout<<"X ";
				}
			}
			for(auto y: ys)
			{
				cout<<y<<" ";
			}
			for(int d = 0; d < ylist.size(); d++)
			{
				cout<<"\t\t"<<"D "<<d<<endl;
				cout<<ys.at(d);
				if(!ys.at(d))
				{
					string temp = string(d,'*');
					mapLine = mapLine + temp;
					int num;
					for(int e = 0; e < letters.size();e++)
					{
						cout<<"\t\t\t"<<"E "<<e<<" ";
						if(letter == letters.at(e))
						{
							num++;
						}
					}
					mapLine = mapLine+letter+(char)num;
					d++;
				}
			}
			//make string to be printed of that line. 
		}
		cout<<"ML :"<<mapLine<<endl;
	}

}

