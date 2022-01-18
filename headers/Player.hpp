
#define UNUSED(x) (void)(x) 


class Player {

public:
	
	string name;

    string getName();

    unsigned char getRemainingTurns();
    void setName(string playerName);

};
