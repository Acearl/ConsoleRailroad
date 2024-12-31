#include <iostream>
#include <station.cpp>

//train has values to know where it goes
//gets distance, uses speed for time

class Train{
    private:
        Station current;
        Station dest;
        double speed;
        std::string name;
    public:
    Train(std::string name, Station current, Station dest, double speed)
    : name(name), current(current), dest(dest), speed(speed) {}

    void display()
    {
        cout<<name<<":";
        current.display();
        cout<<":";
        dest.display();
        cout<<":"<<speed<<endl;
    }
    
    void setDest(const Station& x)
    {
        dest = x;
    }
    void setCurrent(const Station& x)
    {
        current = x;
    }

};