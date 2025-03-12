#include <iostream>
#include "Station.cpp"
#include <cmath>
#include <string>
#include <chrono>
#include <thread>

//train has values to know where it goes
//gets distance, uses speed for time

class Train{
    private:
        Station *current;
        Station *dest;
        double speed;
        std::string name;
        
    public:
    Train(){};
    Train(std::string name, Station *current, double speed)
    : name(name), current(current), speed(speed){};
    Train(std::string name, Station *current, Station *dest, double speed)
    : name(name), current(current), dest(dest), speed(speed){};

    void display()
    {
        cout<<name<<":";
        current->display();
        cout<<":";
        dest->display();
        cout<<":"<<speed<<endl;
    }
    
    void setDest(Station x)
    {
        dest = &x;
    }
    void setDest(Station *x)
    {
	dest = x;
    }
    void setCurrent(Station x)
    {
        current = &x;
    }
    Station* getDest()
    {
	return dest;
    }
    Station* getCurrent()
    {
	return current;
    }
    void travel(int target)
    {
	 
	double dist = current->distCalc(target);
	int rounded = round(dist);
	for(int i = 0; i<= dist; ++i)
	{
		displayTravelBar(i,dist);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	current = dest;
	cout<<endl;
    }
    void displayTravelBar(int progress, double dist)
    {
	double time;
	int barWidth = 40;
	int filled_width;
	float percentage = static_cast<float>(progress) / dist;
	if(percentage > 99.9)
	{
		filled_width = barWidth;
	}
	else
	{
		filled_width = static_cast<int>(barWidth * percentage);
	}
	
	string bar = "[";
	for(int i = 0; i < barWidth; i+=speed)
	{
		if(i < filled_width)
		{
			bar+= "=";
		}else{
			bar += " ";
		}
	}
	bar += "]";
	cout<<"\r"<< bar << " " << static_cast<int>(percentage * 100) << "%"<< flush;
    }
};
