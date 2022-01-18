
#define UNUSED(x) (void)(x) 


class Player {

	private :
		string p_name;

	public:

		//Constructors :
		Player (string name);
		~Player();

	    string getName();
	    void setName(string playerName);

};
