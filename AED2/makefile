all: tests_unitarios test_oraculo tiempos regresion

tiempos: tiempos.cpp dyv.o
	g++ tiempos.cpp dyv.o -o tiempos
	./tiempos

tests_unitarios: tests_unitarios.cpp dyv.o
	g++ tests_unitarios.cpp dyv.o -o tests_unitarios
	./tests_unitarios

test_oraculo: test_oraculo.cpp dyv.o
	g++ test_oraculo.cpp dyv.o -o test_oraculo
	./test_oraculo

dyv.o: dyv.cpp dyv.h
	g++ -c dyv.cpp

regresion:
	python3 regresion.py

clean:
	rm -f *.o tests_unitarios test_oraculo tiempos *.pdf *.csv