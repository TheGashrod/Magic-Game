 #include "../headers/Land.hpp"


 Land::Land (string name, Color color, bool isEngaged)
 : Card(name, std::list<Color>(color), isEngaged) {
	 
 }