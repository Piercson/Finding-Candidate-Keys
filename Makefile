all: ck

ck: Finding_Candidate_Keys.o Powerset.o FuncDependency.o
					g++ -o ck Finding_Candidate_Keys.o Powerset.o FuncDependency.o
Finding_Candidate_Keys.o: Finding_Candidate_Keys.cpp
					g++ -c Finding_Candidate_Keys.cpp
Powerset.o: Powerset.cpp Powerset.h
					g++ -c Powerset.cpp
FuncDependency.o: FuncDependency.cpp FuncDependency.h
					g++ -c FuncDependency.cpp
clean:
				rm -rf ck ck.exe *.o *~ *.err *.out
