#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

using namespace std;

//node of Fibonacci heap
class Node {
	//allow these two classes have accesses to its values
	friend class FibonacciHeap;
	friend class HashTagCounter;
private:
	int Degree;
	int Value;
	string Hashtag;
	bool ChildCut;
	Node *Parent;
	Node *Child;
	Node *LeftSib;
	Node *RightSib;

	~Node();

};

class FibonacciHeap {
//allow derived class have access to its values and functions
private :
	int TopDegree = 0;
	int NodeNum = 0;

	//function of melding two heaps
	void Meld(Node *pl, Node *ql);
	//function of removing one element from its siblings' list
	void inline Remove_From_List(Node *p);
	//function of finding node with max value after removing max
	void Find_Max();
	//function of doing pairwise combining which combines all trees
	//which have same degree in the heap
	void PairwiseCombine(vector<Node*> &TreeTable, Node* &p);
	//function of cascading cut
	void Cascading_Cut(Node *p);

protected:
	Node *Max = nullptr;

	~FibonacciHeap();
	//function of inserting
	Node *Insert(string word, int value);
	void Insert(Node *p);
	//function of removing max
	bool Remove_Max();
	//function of increasing key
	void Increase_Key(Node *p, int newdata);
	//function of arbitrary remove
	void Arbitrary_Remove(Node *p);
};

#endif // !FIBONACCI_HEAP_H

