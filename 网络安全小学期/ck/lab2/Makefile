.PHONY: all
all : test d r
d: des.o 
	 g++ $^ -o d d.cc
r: rsa.o bigint.o
	 g++ $^ -o r r.cc -lgmp -lgmpxx
test: test.o rsa.o bigint.o des.o
	   g++ $^ -o test -g -lgmp -lgmpxx 
rsa.o: rsa.cc rsa.h
	   g++ -g -c rsa.cc
bigint.o : bigint.cc bigint.h
	   g++ -g -c bigint.cc
test.o: test.cc 
	   g++ -g -c test.cc
des.o: des.cc des.h
	   g++ -g -c des.cc
clean:
	   rm -f *.o
