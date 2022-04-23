shell:  shell.o print.o tools.o config.o filecmd.o advanced.o main.o 
	g++  $^ -o shell 
main.o:  main.cc shell.h
	g++ -c main.cc
shell.o: shell.cc shell.h
	g++ -c shell.cc
print.o: print.cc shell.h
	g++ -c print.cc
tools.o: tools.cc shell.h tools.h
	g++ -c tools.cc 
filecmd.o: filecmd.cc shell.h
	g++ -c filecmd.cc
config.o: config.cc shell.h tools.h
	g++ -c config.cc
advanced.o: advanced.cc shell.h tools.h
	g++ -c advanced.cc
clean:
	rm -f *.o
cleanfile:
	rm [0-9]*
	rm .history
