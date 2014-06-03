#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
typedef unsigned int u_int;
using namespace std;


string addLargeNumbers(string str1, string str2) {
			int len1 = str1.length();
			int len2 = str2.length();
			int remainingLen=0,r = len1+len2;
			string str3;
			string result;
			result.clear();
		    std::reverse(str1.begin(),str1.end());
			std::reverse(str2.begin(),str2.end());
			int i=0,j=0;
			int carry=0;
			while(i<len1 && j<len2) {
				
				int digit1 = str1[i++]-'0';
				int digit2 = str2[j++]-'0';
				int num = digit1+digit2+carry;
				carry = num/10;
				num=num%10;
				
				result+=(static_cast<char>('0'+num));
			}
			if(j<len2) {
				remainingLen = len2;
				str3=str2;
				r=j;
			}
			if(i<len1) {
				remainingLen = len1;
				str3=str1;
				r=i;
			}
			while(r<remainingLen){
					int digit = str3[r++]-'0';
					int num = carry+digit;
					carry= num/10;
					num = num%10;
					result+=(static_cast<char>('0'+num));
			}
			if(carry>0)
			result+=(static_cast<char>('0'+carry));
			reverse(result.begin(),result.end());
			return result;
}


unsigned long long distinctWays[1000];
string stringDistinctWays[1000];

unsigned long long countWays(int n) {

	
	if(n<=0) return 0;
	if(n<=2) return distinctWays[n-1];
	int num_of_steps=0;
	if(distinctWays[n-3] == -1)
	  distinctWays[n-3]=countWays(n-2);
	
	
	if(distinctWays[n-2] == -1)
	  distinctWays[n-2]= countWays(n-1);

	distinctWays[n-1] = distinctWays[n-2] + distinctWays[n-3];
	
	return distinctWays[n-1];

}

unsigned long long countWaysRecurse(int n) {

		if(n<=0)return 0;
		if(n<=2)return n;
		return countWaysRecurse(n-1)+countWaysRecurse(n-2);
}


int main(int argc, char* argv[])
{
	if(argc > 1) {
		
		ifstream input_file(argv[1]);
		string input_string;
		int num_of_steps;
		unsigned int index=0;
		char x;
		stringDistinctWays[0]+=static_cast<char>('1');
		stringDistinctWays[1]+=static_cast<char>('2');

		while(getline(input_file,input_string)) {
			if(!input_string.empty()) {
				stringstream sstr(input_string);
		        	sstr>>num_of_steps;
					for(int i=2;i<num_of_steps;i++)
						if(stringDistinctWays[i].empty())
							stringDistinctWays[i] = addLargeNumbers(stringDistinctWays[i-1],stringDistinctWays[i-2]);
					cout<<stringDistinctWays[num_of_steps-1]<<endl;
			}

		}
		input_file.close();
		

	}

	return 0;
}



