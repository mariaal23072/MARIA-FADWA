all: tests_unitarios tests_oraculo tiempos

tiempos: tiempos.cpp dyv.o
	g++ tiempos.cpp dyv.o -o tiempos

tests_unitarios: tests_unitarios.cpp dyv.o
	g++ tests_unitarios.cpp dyv.o -o tests_unitarios

tests_oraculo: tests_oraculo.cpp dyv.o
	g++ tests_oraculo.cpp dyv.o -o tests_oraculo

dyv.o: dyv.cpp dyv.h
	g++ -c dyv.cpp

clean:
	rm -f *.o tests_unitarios tests_oraculo tiempos *.pdf *.csv