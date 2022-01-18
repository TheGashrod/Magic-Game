 
#include <iostream>
#include <list>

#include "enums/Color.cpp"

using namespace std;



 class Card{

    // Members :
    protected:
        static unsigned long c_nextId;
    public:
        const unsigned long c_id;
        const string c_name;
        const std::list<Color> c_colors = std::list<Color>();

    // Constructors :
    public:
        Card(string name, std::list<Color> colors);
        ~Card();
    

    // Methods
    public:
        bool hasSameId(Card* c) const;
        
};
