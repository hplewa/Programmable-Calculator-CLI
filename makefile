SRCS = $(wildcard *.c) #list of all .c files

main: $(SRCS)
	g++ ProgrammableCalculator.cpp -o ProgrammableCalculator

clean:
	rm ProgrammableCalculator
