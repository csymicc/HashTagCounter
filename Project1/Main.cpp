#include "HashtagCounter.h"
#include <fstream>


int main(int argc, char **argv) {
	//open input file and output file
	string ifile = argv[1];
	string ofile = "output_file.txt";
	ifstream infile(ifile.c_str());
	ofstream outfile(ofile.c_str());
	//judge if files are opened
	if (!infile) {
		cerr << "error: unable to open input file: "<< ifile << endl;
		return -1;
	}
	if (!outfile) {
		cerr << "error: unable to open output file: " << ofile << endl;
		return -1;
	}
	//get input form input file
	string Line = "";
	HashTagCounter HashTag;
	while (getline(infile, Line)) {
		//end input
		if (Line == "STOP")
			break;
		//get words and counts
		else if (Line[0] == '#') {
			string word;
			int count = 0;
			int i = 1;
			//get word
			for (; Line[i] != ' '; ++i)
				word += Line[i];
			//get count
			for (++i; Line[i]; ++i)
				count = count * 10 + int(Line[i]) - 48;
			//save them into HashtagCounter
			HashTag.HashTag_input(word, count);
		}
		//output words which have most counts
		else {
			int times = 0;
			//get how many words should be outputed
			for (int i = 0; Line[i]; ++i)
				times = times * 10 + int(Line[i]) - 48;
			//get words from HashtagCounter
			vector<string> output;
			output = HashTag.HashTag_output(times);
			//output the result to output file
			if (output[times - 1] == "error") {
				cerr << "error: HashTag doesn't have enough element" << endl;
				return -1;
			}
			else {
				for (int i = 0; i != times; ++i) {
					if (i == times - 1)
						outfile << output[i];
					else
						outfile << output[i] << ",";
				}
				outfile << endl;
			}
		}
	}
	//close files
	infile.close();
	outfile.close();
	return 0;
}
