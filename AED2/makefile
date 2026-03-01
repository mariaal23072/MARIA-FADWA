tests_unitarios: tests_unitarios.cpp dyv.o
	g++ tests_unitarios.cpp dyv.o -o tests_unitarios

dyv.o: dyv.cpp dyv.h
	g++ -c dyv.cpp

clean:
	rm -f *.o tests_unitarios