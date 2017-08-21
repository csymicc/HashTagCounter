#ifndef HASHTAGCOUNTER_H
#define HASHTAGCOUNTER_H

#include "Fibonacci_Heap.h"

//HashTagCounter is a derived class of FibonacciHeap
class HashTagCounter : public FibonacciHeap {
private:
	unordered_map<string, Node*> Hashtable;

public:
	~HashTagCounter() {};
	//function of inserting elements into hashtag
	void HashTag_input(string word, int count);
	//function of outputing elements with max counts
	vector<string> HashTag_output(int times);
};

#endif // !HASHTAGCOUNTER_H
