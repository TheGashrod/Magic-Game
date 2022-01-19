#ifndef __MTG_CARD_INCLUDED__
#define __MTG_CARD_INCLUDED__


#include <iostream>
#include <list>

#include "enums/Color.hpp"




using namespace std;



 class Card{

    // Members :
    private:
        bool c_isEngaged;
    protected:
            static unsigned long c_nextId;
    public:
        const unsigned long c_id;
        const string c_name;
        const std::list<Color> c_colors;

    // Constructors :
    private:
        Card(unsigned long id, string name, std::list<Color> colors, bool isEngaged);
    public:
        Card(string name, std::list<Color> colors, bool isEngaged);
        ~Card();


    // Getters/setters :
    public:
        bool isEngaged() const;
        void engage();
        void disengage();


    // Methods
    public:
        bool hasSameId(Card* c) const;

};




#endif
