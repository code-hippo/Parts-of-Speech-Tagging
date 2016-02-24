/*
 * HMM.cpp
 *
 *  Created on: May 7, 2015
 *      Author: cs5120301
 */

#ifndef HMM_CPP_
#define HMM_CPP_

//
#include <bits/stdc++.h>



#endif /* HMM_CPP_ */

using namespace std;

class dictionary{
public:
	vector<string> wordset;
	vector<string> tagset;
	int num_words;
	int num_tags;

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

int main(){

	dictionary* Data=new dictionary();
	HMM* Input = new HMM();
	string dataLine="";
	ifstream myfile("dictionary.txt");

	if(myfile.is_open())
	{
		int type=0;
		while(!myfile.eof())
		{
			getline (myfile,dataLine);

			stringstream ss(dataLine);
			string temp1="";
			char chars[] = "()-";
			string temp2="";
			string temp3="";
			

			while((ss>>temp1)){
				if(temp1.find("TAGSET")!=string::npos){
					//cout<<"push "<<Data->tagset.size()<<" "<<temp1<<" "<<type<<"\n";
					type=0;continue;
				}
				else if(temp1.find("WORDSET")!=string::npos){
					//cout<<"push "<<Data->tagset.size()<<" "<<temp1<<" "<<type<<"\n";
					type=1;continue;
					
				}
				else if(temp1.find("TAG_FREQ1")!=string::npos){
					//cout<<"push "<<Data->tagset.size()<<" "<<temp1<<" "<<type<<"\n";
					type=2;continue;
				}
				else if(temp1.find("TAG_FREQ2")!=string::npos){
					//cout<<"push "<<Data->tagset.size()<<" "<<temp1<<" "<<type<<"\n";
					type=3;continue;
				}
				else if(temp1.find("TAG_FREQ3")!=string::npos){
					type=4;continue;
				}
				if(type==0 ){
					//cout<<"push "<<Data->tagset.size()<<" "<<temp1<<" "<<type<<"\n";
					Data->tagset.push_back(temp1);
				}
				else if(type==1){

					Data->wordset.push_back(temp1);
					vector<int> p;
					vector<int> p1;
					while((ss>>temp1)){

						string wi="";string ti="";
						int index =temp1.find( "//");
						wi = temp1.substr (0,index);
						ti = temp1.substr (index+2);
						p.push_back(atoi(wi.c_str()));
						p1.push_back(atoi(ti.c_str()));


					}
					Data->wordtagset.push_back(p);
					Data->wordtagfreq.push_back(p1);
				}
				else if(type>=2){

					int a=(atoi(temp1.c_str()));
					ss>> temp1;
					int b=(atoi(temp1.c_str()));
					if(type==2){
						Data->tagfreq1[a]=b;continue;
					}
					if(type==3){
						ss >>temp1;
						int c=(atoi(temp1.c_str()));
						Data->tagfreq2[make_pair(a,b)]=c;
						continue;
					}
					if(type==4){
						ss >>temp1;
						int c=(atoi(temp1.c_str()));
						ss>>temp1;
						int d=(atoi(temp1.c_str()));
						Data->tagfreq3[make_pair(make_pair(a,b),c)]=d;
						continue;
					}
				}


			}
		}
	}
	Data->num_words=Data->wordset.size();
	Data->num_tags=Data->tagset.size();

	myfile.close();
	
		ifstream myfile2("input.txt");

		if(myfile2.is_open())
		{

		cout<<"runion_8\n";
			while(!myfile2.eof())
			{
				getline (myfile2,dataLine);

				stringstream ss(dataLine);
				string temp1="";

				while(ss>>temp1){
					int foundword=-1;

					(Input->words).push_back(temp1);

					for(int i=0;i<Data->wordset.size();i++){
						if(Data->wordset[i]==temp1){
							foundword=i;
							break;
						}
					}
					Input->index.push_back(foundword);
				}
			}
		}

		cout<<"runion_9\n";
		myfile2.close();
		Input->num_words=Input->index.size();
		Input->total_args=1;
		for(int i=0;i<Input->num_words;i++){
			(Input->maxargs).push_back(Data->wordtagset[Input->index[i]][0]);
			Input->total_args*=Data->wordtagset[Input->index[i]].size();
			Input->args_instance.push_back(Input->maxargs[i]);
			cout<< Input->words[i]<<"//"<<Data->tagset[Input->maxargs[i]]<<"	";
		}
		cout<<"runion_11\n";
		for(int args=0;args<Input->total_args;args++){

			int i=args;
			for(int j=Input->index.size()-1;j>=0;j--){
				int p=i%Data->wordtagset[Input->index[j]].size();
				Input->args_instance[j]=Data->wordtagset[Input->index[j]][p];
				i=(i-p)/Data->wordtagset[Input->index[j]].size();
			}

			//Input->args_instance[0]=Data->wordtagset[Input->index[0]][i];
			float p=0;

			for(int k=0;k<Input->num_words;k++){

				if(k==0){
					p+=log(Data->tagfreq1[Input->args_instance[0]]+1);

				}
				else if (k==1){
					p+=log(Data->tagfreq2[make_pair(Input->args_instance[0],Input->args_instance[1])]+1);
					p-=log(Data->tagfreq1[Input->args_instance[0]]+Data->num_tags);

				}
				else{
					p+=log(Data->tagfreq3[make_pair(make_pair(Input->args_instance[k-2],Input->args_instance[k-1]),Input->args_instance[k])]+1);
					p-=log(Data->tagfreq2[make_pair(Input->args_instance[k-2],Input->args_instance[k-1])]+Data->num_tags);
				}
				int w=-1;
				for(int iw=0;iw<(Data->wordtagfreq[Input->index[k]].size());iw++){
					if(Data->wordtagfreq[Input->index[k]][iw]==Input->args_instance[k]){
						w=iw;break;
					}

				}

				p+=log(Data->wordtagfreq[Input->index[k]][w]+1);
				p-=log(Data->tagfreq1[Input->args_instance[k]]+Data->num_words);
			}

			Input->CPT.push_back(p);

		}
		cout<<"runion_12\n";
		float max=-100000;

		for(int args=0 ; args<Input->total_args ; args++){
			//cout<<"args "<<Input->total_args<<"\n";
			int i=args;
			if(max<Input->CPT[args]){
				for(int j=Input->index.size()-1;j>=0;j--){
					int p=i%Data->wordtagset[Input->index[j]].size();

					Input->maxargs[j]=Data->wordtagset[Input->index[j]][p];
					i=(i-p)/Data->wordtagset[Input->index[j]].size();
				}
				//cout<<i<<" i\n";
				//Input->maxargs[0]=Data->wordtagset[Input->index[0]][i];
				max=Input->CPT[args];
			}
		}
		cout<<"runion_13\n";
		for(int i=0;i<Input->num_words;i++){
			//cout<<i<<" runion_13\n";
			cout<< Input->words[i]<<"//"<<Data->tagset[Input->maxargs[i]]<<"	";
		}
		cout<<"\nmax"<<max<<"\n";

	return 0;


}
