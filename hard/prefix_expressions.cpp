#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
using namespace std;
 void split(const string&s, char delim, vector<string> &elems) 
{
	stringstream ss(s);
	string item;
	while(getline(ss,item,delim))
		elems.push_back(item);
}

bool isOperator(string & s)
{
	if(s.length()==1 && (s[0]=='*' || s[0]=='+' || s[0]=='/')) return true;
	return false;
	
}

void evaluateExpression(vector<string> & operatorsAndOperands)
{
	vector<int> evaluationQueue;
//	vector<string>::iterator it = operatorsAndOperands.begin();
//	vector<string>::iterator it_end = operatorsAndOperands.end();
//	while(it !=it_end)
	for(int i=0;i<operatorsAndOperands.size();i++)
	{
		string it = operatorsAndOperands[i];
		if(isOperator(it)){
			int  op1 = evaluationQueue.back();
			evaluationQueue.pop_back();
			int op2 = evaluationQueue.back();
			evaluationQueue.pop_back();
			int result;
			if(it[0]=='*') result = op1*op2;
			if(it[0]=='+') result = op1+op2;
			if(it[0]=='/') result = op2/op1;
			evaluationQueue.push_back(result);
		}
		else{
			int value=0;
			for(int i=0;i< it.length();i++)
				value = value*10 + int(it[i])-'0';
			evaluationQueue.push_back(value);
		}
		
	}
	cout<<evaluationQueue.back()<<endl;
}
int main(int argc, char * argv[])
{
	
	if(argc>1) {
		string expression;
		vector<string> operands;
		ifstream inputFile;
		inputFile.open(argv[1]);
		while(!inputFile.eof()){
			expression.clear();
			operands.clear();
			getline(inputFile,expression);
			if(expression.length()) {
				split(expression,' ',operands);
				reverse(operands.begin(),operands.end());
				evaluateExpression(operands);
			}
	
		}
		inputFile.close();
	
	}
	
}

