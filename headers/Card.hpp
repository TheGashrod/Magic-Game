 
#include <iostream>
#include <list>

#include "enums/Color.cpp"

using namespace std;



 class Card{
    
    public :
        string c_name;
        std::list<Color> c_colors;

        virtual void AbstractMemberFunction() = 0; 

    	Card (string);
    	// // Card();
     //    ~Card();

    	

        
        
};
