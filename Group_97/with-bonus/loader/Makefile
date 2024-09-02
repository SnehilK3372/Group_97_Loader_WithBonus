#Create lib_simpleloader.so from loader.c
../bin/lib_simpleloader.so: loader.o
	gcc -m32 -fPIC -shared -o ../bin/lib_simpleloader.so loader.o

loader.o: loader.c loader.h
	gcc -m32 -fPIC -c loader.c
#Provide the command for cleanup
clean: 
	@rm -f ../bin/*.so
	@rm -f *.o
