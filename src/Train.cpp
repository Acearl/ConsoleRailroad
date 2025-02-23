#include <iostream>
#include "Station.cpp"
#include <cmath>

//train has values to know where it goes
//gets distance, uses speed for time

class Train{
    private:
        Station current;
        Station dest;
        double speed;
        std::string name;
        
    public:
    Train(){};
    Train(std::string name, Station current, double speed)
    : name(name), current(current), speed(speed){};
    Train(std::string name, Station current, Station dest, double speed)
    : name(name), current(current), dest(dest), speed(speed){};

    void display()
    {
        cout<<name<<":";
        current.display();
        cout<<":";
        dest.display();
        cout<<":"<<speed<<endl;
    }
    
    void setDest(const Station *x)
    {
        dest = *x;
    }
    void setCurrent(const Station *x)
    {
        current = *x;
    }
    void travel()
    {
	float time;
	float dist = distCalc();

    }
    float distCalc()
    {
	double distance = sqrt( 
		pow(dest.getY() - current.getY(), 2.0) + 
		pow(dest.getX() - current.getX(), 2.0)
        );

        return distance;
    }

};

