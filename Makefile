CC=g++
CFLAGS=-Wall -Wextra -std=c++2a -g
LDFLAGS=-lncurses

SRCS=\
src/tools/random.cpp \
src/assets/Creatures.cpp \
src/assets/Lands.cpp \
src/Duel_interface.cpp \
src/Duel.cpp \
src/Card.cpp \
src/CardsSet.cpp \
src/Land.cpp \
src/Creature.cpp \
src/Contender.cpp \
src/Player.cpp \
src/AttackAction.cpp \
src/AttackRound.cpp \
src/enums/Color.cpp \
src/consoleInterface/ConsoleInterface.cpp \
src/test/testConsoleInterface.cpp \

OBJS=$(subst .cpp,.o,$(subst src/,build/, $(SRCS)))

.PHONY: clean

all: build/magic run

build/%.o: src/%.cpp headers/%.hpp
	$(CC) $(CFLAGS) -c $< -o $(subst .cpp,.o,$(subst src/,build/,$<))

build/%.o: test/%.cpp
	$(CC) $(CFLAGS) -c $< -o $(subst .cpp,.o,$(subst test/,"build/test",$<))


build/magic: $(OBJS) src/main.cpp
	g++ $(CFLAGS) $(OBJS) src/main.cpp -o build/magic $(LDFLAGS)

run: build/magic
	./$<


clean:
	rm -f build/magic
	rm -f build/*.o
	rm -f build/actions/*.o
