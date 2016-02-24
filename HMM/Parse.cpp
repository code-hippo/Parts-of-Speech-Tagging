/*
 * Parse.cpp
 *
 *  Created on: May 7, 2015
 *      Author: cs5120301
 */




#include <bits/stdc++.h>
using namespace std;

class dictionary{
public:
	vector<string> wordset;
	vector<string> tagset;
	vector<int> num_wordtags;

	vector< vector<int > > wordtagset;
	vector< vector<int > > wordtagfreq;

	std::map<int,int> tagfreq1;
	std::map<pair<int,int>,int> tagfreq2;
	std::map< pair< pair<int,int >, int >, int> tagfreq3;

};

class HMM{
public:
	vector<string> words;
	vector<int> index;
	vector<int> maxargs;
	vector<int> args_instance;
	int total_args;
	int num_words;
	vector<float>   CPT;
};


//int getIndex(vector<int> id, vector<int> values){
//
//    int ind=0;
//    for(int i=0;i<id.size()-1;i++){
//     //   ind=(ind+values[i])*((Alarm.Pres_Graph[id[i+1]]).nvalues);
//    }
//
//    return ind+values[id.size()-1];
//}

int main(void){

	ifstream myfile("wsj.tree");
	ofstream myfile2("tagdata.txt");

	dictionary* Data=new dictionary();
	string sentence="";
	bool finish_sentence=false;
	string dataLine="";

	if(myfile.is_open())
	{

		while(!myfile.eof())
		{
			getline (myfile,dataLine);

			stringstream ss(dataLine);
			string temp1="";
			char chars[] = "()-";
			string temp2="";
			string temp3="";
			bool append_sentence=false;
//			ss>> temp1;
//			temp2=temp1;

			//cout<< "ruing2\n";
			while(    (ss>>temp1)){
				append_sentence=true;
				//myfile2 << temp1;
				//ss >> temp1;
			//	cout<< "ruing3\n";

			    if (temp1.find(".)") != string::npos && temp2.find("(.") != string::npos) {
				//.. found.
			    	cout<<". .";
			    	append_sentence=false;
			    	finish_sentence=true;
//			    	myfile2 << "\n";
			    	break;
			    }
			    else if((temp1.find(":)") != string::npos ) || (temp1.find(";)") != string::npos)||(temp1.find(",)") != string::npos) || temp1.find("--)") != string::npos || temp2.find("--") != string::npos){
			    	append_sentence=false;
			    	continue;
			    }
			    else if(temp1.at(0)=='\n'){
			    	append_sentence=false;
			    	continue;
			    }
			    //temp2=temp1;
			    temp3=temp2;
			    temp2=temp1;
//			    if()
			}
			//cout<<temp1<<"\n";

			if(finish_sentence==true){
				myfile2 << sentence << "\n\n";
				cout<< "ruing\n";
				sentence="";
				finish_sentence=false;
			}
			if(append_sentence==true){
				if(((temp1.find("`") != string::npos) && (temp3.find("`") != string::npos)) || (temp3.find("NONE") != string::npos) ||((temp1.find("'") != string::npos) && temp3.find("'") != string::npos)){
					continue;
				}
				temp1.erase (std::remove(temp1.begin(), temp1.end(), chars[1]), temp1.end());
				temp3.erase (std::remove(temp3.begin(), temp3.end(), chars[0]), temp3.end());
				//append_sentence=false;
				sentence+=(temp1+"//"+temp3+"	");
			}



		}

	}
	cout<< "ruing5\n";
	myfile.close();
	myfile2.close();

	ifstream myfile3("tagdata.txt");

	if(myfile3.is_open())
	{
		cout<< "ruing6\n";
		while(!myfile3.eof())
		{
			getline (myfile3,dataLine);
			//cout<< "ruing7\n";
			stringstream ss(dataLine);
			string temp1="";
			int t1=-1;
			int t2=-1;
			int t3=-1;
			int num=-1;


			while(ss>>temp1){

				num++;
				string wi="";string ti="";
				int index =temp1.find( "//");
				wi = temp1.substr (0,index);
				ti = temp1.substr (index+2);
				int foundword=-1;
				int t1=-1;
				bool found=false;
				for(int i=0;i<Data->wordset.size();i++){
					if(Data->wordset[i]==wi){
						foundword=i;
						break;
					}
				}
				if(foundword==-1){
					vector<int> p;
					Data->wordset.push_back(wi);
					(Data->wordtagset).push_back(p);
					(Data->wordtagfreq).push_back(p);
					foundword=Data->wordset.size()-1;
				}

				for(int i=0;i<Data->tagset.size();i++){
					if(Data->tagset[i]==ti){
						t1=i;
						break;
					}
				}

				if(t1==-1){
					Data->tagset.push_back(ti);
					t1=Data->tagset.size()-1;
				}

				for(int i=0;i<Data->wordtagset[foundword].size();i++){
					//cout<<i<<"why not\n";
					if(t1==Data->wordtagset[foundword][i]){
						found=true;
						Data->wordtagfreq[foundword][i]++;
						break;
					}
				}

				if(found==false){
					(Data->wordtagset[foundword]).push_back(t1);
					(Data->wordtagfreq[foundword]).push_back(1);
				}

				if(num>=2){
					Data->tagfreq3[make_pair(make_pair(t1,t2),t3)]++;
				}
				if(num>=1){
					Data->tagfreq2[make_pair(t1,t2)]++;
				}

				if(num>=0){
					Data->tagfreq1[t1]++;
				}

				t3=t2;
				t2=t1;

			}
		}
	}

	myfile3.close();
	cout<< "ruing6\n";
	ofstream myfile8("dictionary.txt");
	myfile8 << "TAGSET\n\n";
	ofstream myfile4("tagset.txt");
	for(int i=0;i<Data->tagset.size();i++){
		myfile4<<Data->tagset[i]<<"\n";
		myfile8<<Data->tagset[i]<<"\n";
	}
	myfile8<<"\n\n\n";
	myfile8 << "WORDSET			WORD_TAGLIST\n";
	ofstream myfile5("wordset.txt");
	for(int i=0;i<Data->wordset.size();i++){
		myfile5<<Data->wordset[i]<<"\n";
	}

	for(int i=0;i<Data->wordset.size();i++){
		myfile8<<Data->wordset[i]<<" ";
		//cout<<"running2\n";
		for(int j=0;j<Data->wordtagset[i].size();j++){
			//cout<<"running\n";
			myfile8<<Data->wordtagset[i][j]<<"//"<<Data->wordtagfreq[i][j]<<"	";
		}
		myfile8<<"\n";
	}
	myfile8<<"\n\n\n";
	myfile8<<"TAG_FREQ1\n";
	for(int i=0;i<Data->tagset.size();i++){
		myfile8<< i<<"	"<<Data->tagset[i]<<"	"<<Data->tagfreq1[i]<<"\n";
	}
	myfile8<<"\n\n\n";
	myfile8<<"TAG_FREQ2\n";
	typedef std::map<pair<int,int>, int>::iterator freq2;

	for(freq2 iterator = Data->tagfreq2.begin(); iterator !=Data->tagfreq2.end(); iterator++) {
		myfile8<<(iterator->first).first<<"	"<<(iterator->first).second<<"	"<<(iterator->second)<<"\n";
	}
	myfile8<<"\n\n\n";

	myfile8<<"TAG_FREQ3\n";
	typedef std::map<pair<pair<int,int>, int> , int>::iterator freq3;

	for(freq3 iterator = Data->tagfreq3.begin(); iterator !=Data->tagfreq3.end(); iterator++) {
		myfile8<<(iterator->first).first.first<<"	"<<(iterator->first).first.second<<"	"<<(iterator->first.second)<<"	"<<(iterator->second)<<"\n";
	}

	myfile4.close();
	myfile5.close();
	myfile8.close();



return 0;


}
