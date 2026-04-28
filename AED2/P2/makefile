all: test_unitarios_AR test_unitarios_BT tiempos_AR tiempos_BT regresion_AR regresion_BT

tiempos_AR: tiempos_AR.cpp organizacion_clase_AR.o
	g++ tiempos_AR.cpp organizacion_clase_AR.o -o tiempos_AR
	./tiempos_AR

test_unitarios_AR: test_unitarios_AR.cpp organizacion_clase_AR.o
	g++ test_unitarios_AR.cpp organizacion_clase_AR.o -o test_unitarios_AR
	./test_unitarios_AR

organizacion_clase_AR.o: organizacion_clase_AR.cpp organizacion_clase_AR.h
	g++ -c organizacion_clase_AR.cpp

regresion_AR: tiempos_AR
	python3 regresion_AR.py

tiempos_BT: tiempos_BT.cpp mi_camiseta_BT.o
	g++ tiempos_BT.cpp mi_camiseta_BT.o -o tiempos_BT
	./tiempos_BT

test_unitarios_BT: test_unitarios_BT.cpp mi_camiseta_BT.o
	g++ test_unitarios_BT.cpp mi_camiseta_BT.o -o test_unitarios_BT
	./test_unitarios_BT

regresion_BT: tiempos_BT
	python3 regresion_BT.py

clean:
	rm -f *.o test_unitarios_AR test_unitarios_BT tiempos_AR tiempos_BT regresion_AR regresion_BT *.pdf *.csv