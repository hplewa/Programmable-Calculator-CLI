main: ProgrammableCalculator.o
	gcc -o main ProgrammableCalculator.o

ProgrammableCalculator.o: ProgrammableCalculator.cpp
	gcc -c ProgrammableCalculator.cpp

clean:
	rm main ProgrammableCalculator.o