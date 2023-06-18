# objetivo : dependencias
#	comandos
#	comandos2
#	comandos3 etc


bin/gaussSeidel.exe : src/main2.cpp 
	@echo Compilando codigo fuente 
	g++ -o bin/gaussSeidel2  src/main2.cpp -Iinclude
run: bin/gaussSeidel2
	bin/gaussSeidel2
clean:
	@echo Se Borraron todos los archivos .exe
	rm -f bin/*.exe