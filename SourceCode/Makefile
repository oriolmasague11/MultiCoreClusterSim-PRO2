	OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Proceso.o Procesador.o Cluster.o Area_espera.o
	g++ -o program.exe program.o Proceso.o Procesador.o Cluster.o Area_espera.o
	
Cluster.o: Cluster.cc Cluster.hh Procesador.hh BinTree.hh
	g++ -c Cluster.cc $(OPCIONS)
	
Area_espera.o: Area_espera.cc Area_espera.hh Proceso.hh Cluster.hh
	g++ -c Area_espera.cc $(OPCIONS)
	
Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(OPCIONS)

Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS)

program.o: program.cc Cluster.hh Area_espera.hh
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
	
tar: 
	tar -cvf practica.tar Cluster.cc Cluster.hh Area_espera.cc Area_espera.hh Procesador.cc Procesador.hh Proceso.cc Proceso.hh program.cc Makefile
