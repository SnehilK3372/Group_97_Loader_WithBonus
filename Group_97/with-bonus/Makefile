#invoke make inside following directories and in this order: loader, launch, fib
.PHONY: all loader launcher test

all: loader launcher test

loader: 
	@cd loader && $(MAKE)
launcher:
	@cd launcher && $(MAKE)
test:
	@cd test && $(MAKE)

#lib_simpleloader.so and launch binaries -->> already inside bin directory

#Provide the command for cleanup
clean:
	@cd loader && $(MAKE) clean
	@cd launcher && $(MAKE) clean
	@cd test && $(MAKE) clean

