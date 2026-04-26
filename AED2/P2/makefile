all: tests_unitarios_AR tests_unitarios_BT tiempos_AR tiempos_BT regresion_AR regresion_BT

tiempos_AR: tiempos_AR.cpp organizacion_clase_AR.o
	g++ tiempos_AR.cpp organizacion_clase_AR.o -o tiempos_AR
	./tiempos_AR

tests_unitarios_AR: tests_unitarios_AR.cpp organizacion_clase_AR.o
	g++ tests_unitarios_AR.cpp organizacion_clase_AR.o -o tests_unitarios_AR
	./tests_unitarios_AR

organizacion_clase_AR.o: organizacion_clase_AR.cpp organizacion_clase_AR.h
	g++ -c organizacion_clase_AR.cpp

regresion_AR:
	python3 regresion_AR.py

tiempos_BT: tiempos_BT.cpp mi_camiseta_BT.o
	g++ tiempos_BT.cpp mi_camiseta_BT.o -o tiempos_BT
	./tiempos_BT

tests_unitarios_BT: tests_unitarios_BT.cpp mi_camiseta_BT.o
	g++ tests_unitarios_BT.cpp mi_camiseta_BT.o -o tests_unitarios_BT
	./tests_unitarios_BT

regresion_BT:
	python3 regresion_BT.py

clean:
	rm -f *.o tests_unitarios_AR tests_unitarios_BT tiempos_AR tiempos_BT regresion_AR regresion_BT *.pdf *.csv