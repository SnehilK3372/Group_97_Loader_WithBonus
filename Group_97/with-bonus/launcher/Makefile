#Compile the launch.c by linking it with the lib_simpleloader.so
../bin/launch: launch.c
	gcc -m32 -o ../bin/launch launch.c -L../bin/ -l_simpleloader -Wl,-rpath=../bin
#linking done after compiling 
#Provide the command for cleanup
clean:
	@rm -f ../bin/launch
