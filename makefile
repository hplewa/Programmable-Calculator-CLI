SRCS = $(wildcard *.c) #list of all .c files

main: $(SRCS)
	gpp ProgrammableCalculator.cpp -o programmableCalculator

clean:
	rm programmableCalculator
