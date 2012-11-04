HEADERS = circuits.h clock.h commander.h conversion.h interface.h light.h pump.h reporter.h scheduler.h water.h colours.h booldev.h
OBJECTS = circuits.o commander.o interface.o light.o main.o pump.o reporter.o scheduler.o water.o conversion.o clock.o colours.o

default: garden

main.o: main.cpp $(HEADERS)
	g++ -c main.cpp -o main.o

circuits.o: circuits.cpp pins.h
	g++ -c circuits.cpp -o circuits.o

commander.o: commander.cpp
	g++ -c commander.cpp -o commander.o

interface.o: interface.cpp
	g++ -c interface.cpp -o interface.o

light.o: light.cpp
	g++ -c light.cpp -o light.o

pump.o: pump.cpp
	g++ -c pump.cpp -o pump.o

reporter.o: reporter.cpp bounds.h
	g++ -c reporter.cpp -o reporter.o

scheduler.o: scheduler.cpp daemon.h
	g++ -c scheduler.cpp -o scheduler.o

water.o: water.cpp
	g++ -c water.cpp -o water.o

conversion.o: conversion.cpp
	g++ -c conversion.cpp -o conversion.o

clock.o: clock.cpp
	g++ -c clock.cpp -o clock.o

colours.o: colours.cpp
	g++ -c colours.cpp -o colours.o

garden: $(OBJECTS)
	g++ *.o -o garden

clean:
	-rm -f *.o
	-rm -f garden
