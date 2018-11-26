SRCS = $(wildcard *.c) #list of all .c files

main: $(SRCS)
	g++ ProgrammableCalculator.cpp -o programmableCalculator

clean:
	rm programmableCalculator
