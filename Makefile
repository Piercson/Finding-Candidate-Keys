all: fd

fd: fd_testrunner.o FuncDependency.o
					g++ -Wall -o fd fd_testrunner.o FuncDependency.o
fd_testrunner.o: fd_testrunner.cpp FuncDependency.h
					g++ -Wall -c fd_testrunner.cpp
FuncDependency.o: FuncDependency.cpp FuncDependency.h
					g++ -c FuncDependency.cpp

clean:
				rm -rf fd fd.exe *.o *~ *.err *.out
