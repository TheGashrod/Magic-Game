#ifndef __MTG_CARD_INCLUDED__
#define __MTG_CARD_INCLUDED__


#include <iostream>
#include <list>
#include <memory>

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
        virtual shared_ptr<Card> clone() const = 0;


    // Getters/setters :
    public:
        long getId() const;
        string getName() const;
        std::list<Color> getColor() const;
        bool isEngaged() const;
        virtual bool isLand() const = 0;

        void engage();
        void disengage();


    // Methods
    public:
        bool hasSameId(const Card* c) const;


    // Print
    public:
        virtual ostream& print(ostream& os) const = 0;
};


ostream& operator<<(ostream& os, const Card* c);





#endif
