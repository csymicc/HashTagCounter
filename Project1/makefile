hashtagcounter.exe : Main.o HashtagCounter.o Fibonacci_Heap.o
	g++ -o hashtagcounter.exe Main.o HashtagCounter.o Fibonacci_Heap.o

Main.o : Main.cpp HashtagCounter.h
	g++ -std=c++11 -c Main.cpp

HashtagCounter.o : HashtagCounter.cpp HashtagCounter.h Fibonacci_Heap.h
	g++ -std=c++11 -c HashtagCounter.cpp

Fibonacci_Heap.o : Fibonacci_Heap.cpp Fibonacci_Heap.h
	g++ -std=c++11 -c Fibonacci_Heap.cpp