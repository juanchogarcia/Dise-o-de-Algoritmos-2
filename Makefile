cliente.o: cliente.c
	gcc cliente.c Par.c Vector.c Metaheuristicas.c Lectura.c -lm -o cliente

clean:
	-rm -f cliente.o
	-rm -f cliente
