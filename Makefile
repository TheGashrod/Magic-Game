CXX=g++
CXXFLAGS=-Wall -Wextra -Werror

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

main: build/main.o build/Player.o
	$(CXX) $^ -o $@
	./$@


.PHONY: run clean

run: main
	./$<

clean:
	rm -f *.o *~ *.core 

