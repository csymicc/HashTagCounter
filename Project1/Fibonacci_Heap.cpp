#include "Fibonacci_Heap.h"

//destructor of Node structure
Node::~Node() {
	ChildCut = false;
	Parent = nullptr;
	Child = nullptr;
	LeftSib = nullptr;
	RightSib = nullptr;
}

//destructor of Fibonacci heap
//destruct all Nodes int Fibonacci heap
FibonacciHeap::~FibonacciHeap() {
	queue<Node*> s;
	Node *p = Max;
	//push all elements in top level into the queue
	for (int i = 0; i < TopDegree; ++i) {
		s.push(p);
		p = p->RightSib;
	}
	//add remain elements into the queue and delete them all
	while (s.size()) {
		Node *p = s.front();
		Node *q;
		//push all children of first element of queue into queue
		if(p->Child) {
			q = p->Child;
			for (int i = 0; i < p->Degree; ++i) {
				s.push(q);
				q = q->RightSib;
			}
		}
		//delete the first element of queue
		s.pop();
		delete p;
	}
}

//function of inserting an element
//create a new node
//initialize all attributes
//insert new node into top level\
//return node location for storing
Node *FibonacciHeap::Insert(string word, int value) {
	//create a new node
	Node *p = new Node;
	//initialize or adjust all attributes
	++NodeNum;
	p->Value = value;
	p->Hashtag = word;
	p->ChildCut = false;
	p->Degree = 0;
	p->Child = nullptr;
	p->Parent = nullptr;
	++TopDegree;
	//estimate if p is the first elements in the heap
	if (!Max) {
		p->LeftSib = p;
		p->RightSib = p;
		Max = p;
	}
	else {
		p->LeftSib = Max;
		p->RightSib = Max->RightSib;
		Max->RightSib = p;
		p->RightSib->LeftSib = p;
	}
	//change Max's value if necessary
	if (value > Max->Value)
		Max = p;
	return p;
}

//function of inserting an element
//insert node p into top level
void FibonacciHeap::Insert(Node *p) {
	++NodeNum;
	++TopDegree;
	//estimate if p is the first elements in the heap
	if (!Max) {
		p->LeftSib = p;
		p->RightSib = p;
	}
	else {
		p->LeftSib = Max;
		p->RightSib = Max->RightSib;
		Max->RightSib = p;
		p->RightSib->LeftSib = p;
	}
	//change Max's value if necessary
	if (p->Value >= Max->Value)
		Max = p;
	return;
}

//function of meld operation
//meld two Fibonacci heaps
void FibonacciHeap::Meld(Node *pl, Node *qr) {
	Node *pr = pl->RightSib;
	Node *ql = qr->LeftSib;
	pl->RightSib = qr;
	qr->LeftSib = pl;
	pr->LeftSib = ql;
	ql->RightSib = pr;
}

//remove p from its siblings' list and change its parent's pointer if necessary
void inline FibonacciHeap::Remove_From_List(Node * p)
{
	//remove p from its siblings' list
	p->LeftSib->RightSib = p->RightSib;
	p->RightSib->LeftSib = p->LeftSib;
	//if p has parent's
	Node *pp = p->Parent;
	if (pp) {
		//change parent's child pointer if parent still has any child
		if (p->Parent->Degree != 1) {
			p->Parent->Child = p->LeftSib;
			p->Parent = nullptr;
		}
		//set parent's child pointer to NULL if it doesn't have any child
		else {
			p->Parent->Child = nullptr;
			p->Parent = nullptr;
		}
		//decrease parent's degree
		--pp->Degree;
	}
}

//function of remove max operation
//remove node with max value from heap and reset Max pointer point to node with max value
bool FibonacciHeap::Remove_Max() {
	//return error value if there is no element in the heap
	if (!TopDegree)
		return false;
	if (TopDegree == 1) {
		--NodeNum;
		TopDegree = Max->Degree;
		//save Max's value
		Node *temp = Max;
		//if Max has child, insert its child list into top level
		if (Max->Degree) {
			//change Max's children's parent pointers into NULL
			Node *p = Max->Child;
			for (int i = 0; i != Max->Degree; ++i) {
				p->Parent = nullptr;
				p = p->RightSib;
			}
			Max = Max->Child;
			//find node having largest value
			Find_Max();
		}
		else Max = nullptr;
		//delete former node
		delete temp;
		return true;
	}
	else {
		--NodeNum;
		--TopDegree;
		//remove Max from its sibling's list
		Max->LeftSib->RightSib = Max->RightSib;
		Max->RightSib->LeftSib = Max->LeftSib;
		//if Max has children
		if (Max->Degree) {
			//change Max's children's parent pointers into NULL
			Node *p = Max->Child;
			for (int i = 0; i != Max->Degree; ++i) {
				p->Parent = nullptr;
				p = p->RightSib;
			}
			TopDegree += Max->Degree;
			//meld Max's children into top level
			Meld(Max->LeftSib, Max->Child);
		}
		//save Max's value
		Node *temp = Max;
		Max = Max->LeftSib;
		//find node having largest value
		Find_Max();
		delete temp;
		return true;
	}
}

//find node with max value and make Max pointer point to node with max value
void FibonacciHeap::Find_Max()
{
	//calculate the size of treetable and initialize essential attributes
	const float logGoldenRatio = log2(0.5*(1 + sqrt(5)));
	int TableSize = log2(NodeNum) / logGoldenRatio + 1;
	vector<Node*> TreeTable(TableSize);
	Node *p = Max;
	int degree = TopDegree;
	for (int i = 0; i < TableSize; ++i)
		TreeTable[i] = nullptr;
	//find max value through this loop
	for (int i = 0; i < degree; ++i) {
		Max = p->Value > Max->Value ? p : Max;
		//if p's degree exists in the heap, do a pairwise combining
		if (TreeTable[p->Degree]) {
			Node *q = p->RightSib;
			PairwiseCombine(TreeTable, p);
			//set result tree with new degree into treetable
			TreeTable[p->Degree] = p;
			p = q;
		}
		//store p's location into treetable if p's degree doesn't exist in the treetable
		else {
			TreeTable[p->Degree] = p;
			p = p->RightSib;
		}
	}
	
}

//function of pairwise combining
//recursively doing pairwise combining if node's degree still exists in the treetable
//after doing one pairwise combining
void FibonacciHeap::PairwiseCombine(vector<Node*> &TreeTable, Node* &p) {
	//keep doing pairwisecombing if p's degree exists in the treetable
	while (TreeTable[p->Degree]) {
		//decide which root is bigger
		Node *big, *small;
		big = TreeTable[p->Degree]->Value > p->Value ? TreeTable[p->Degree] : p;
		small = TreeTable[p->Degree]->Value > p->Value ? p : TreeTable[p->Degree];
		//reset related treetable's value because degree of p changes
		TreeTable[p->Degree] = nullptr;
		//change Max's pointer if necessary
		Max = big->Value >= Max->Value ? big : Max;
		//remove small node from its siblings' list
		small->LeftSib->RightSib = small->RightSib;
		small->RightSib->LeftSib = small->LeftSib;
		//insert small node into big's child list
		if (big->Degree) {
			small->Parent = big;
			small->LeftSib = big->Child;
			small->RightSib = big->Child->RightSib;
			big->Child->RightSib = small;
			small->RightSib->LeftSib = small;
		}
		else {
			small->Parent = big;
			big->Child = small;
			small->LeftSib = small;
			small->RightSib = small;
		}
		//adjust big node's degree
		++big->Degree;
		//change smaller node's childcut value because it becomes a child
		small->ChildCut = false;
		p = big;
		--TopDegree;
	}
}

//function of increase key operation
void FibonacciHeap::Increase_Key(Node *p, int value) {
	//increase p's value
	p->Value += value;
	//change Max to point to p if p's value is bigger
	//if p's new value is bigger than it's parent's
	if (p->Parent && p->Value > p->Parent->Value) {
		Node *pp = p->Parent;
		//remove p from siblings' list
		Remove_From_List(p);
		//re-insert p into top level
		Insert(p);
		pp->ChildCut = true;
		//doing cascading cut
		Cascading_Cut(pp);
	}
	Max = Max->Value < p->Value ? p : Max;
	return;
}

//function of arbitrary remove operation
void FibonacciHeap::Arbitrary_Remove(Node *p) {
	//reset p's parent's pointers and do cascading cut
	if(p->Parent)
		Cascading_Cut(p->Parent);
	//remove p from siblings' list
	Remove_From_List(p);
	//meld p's children into top level
	if (p->Child)
		Meld(Max, p->Child);
	//set all children's parent pointers to NULL
	Node *q = p->Child;
	for (int i = 0; i != p->Degree; ++i) {
		q->Parent = nullptr;
		q = q->RightSib;
	}
	TopDegree += p->Degree;
	//delete this node
	delete p;
	return;
}

//function of cascading cut operation
void FibonacciHeap::Cascading_Cut(Node *p) {
	//end if p reaches the root or p hasn't lose any child
	while (p->Parent && p->ChildCut) {
		//save p's parent's location
		Node *pp = p->Parent;
		Remove_From_List(p);
		//re-insert p into top level
		Insert(p);
		pp->ChildCut = true;
		//set p point to its parent
		p = pp;
	}
	return;
}