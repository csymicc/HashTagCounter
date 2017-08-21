#include "HashtagCounter.h"

//function of inserting elements into hashtag
void HashTagCounter::HashTag_input(string word, int count)
{
	Node *p;
	unordered_map<string, Node*>::iterator iter;
	//check if word exists in the hashtable
	iter = Hashtable.find(word);
	//if it doesn't, insert it into hashtable and fibonacci heap
	if (iter != Hashtable.end()) {
		p = iter->second;
		Increase_Key(p, count);
	}
	//if it does, add count into its total count value
	else {
		p = Insert(word, count);
		Hashtable[word] = p;
	}
}

//function of outputing elements with max counts
vector<string> HashTagCounter::HashTag_output(int times)
{
	//create vectors to store elements being removed
	vector<string> result(times);
	vector<int> count(times);
	//get hashtag with max value from fibonacci heap's remove max operation
	for (int i = 0; i != times; ++i) {
		//send error back if there is not enough element in the heap
		if (!Max) {
			result[i] = "error";
			break;
		}
		else {
			//store elements being removed
			result[i] = Max->Hashtag;
			count[i] = Max->Value;
			Remove_Max();
		}
	}
	//re-insert removed elements into hashtable and heap
	for (int i = 0; i != times; ++i)
		Hashtable[result[i]] = Insert(result[i], count[i]);

	return result;
}
