all: ps

ps: psTestrunner.o Powerset.o
					g++ -Wall -o ps psTestrunner.o Powerset.o
psTestrunner.o: psTestrunner.cpp Powerset.h
					g++ -Wall -c psTestrunner.cpp
Powerset.o: Powerset.cpp Powerset.h
					g++ -c Powerset.cpp
clean:
				rm -rf ps ps.exe *.o *~ *.err *.out
