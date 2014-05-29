#include<iostream>
#include<map>
#include<cmath>
using namespace std;
char visited_block_key[256];
map<string,int> visited_blocks;
int sum_digits(int m,int n)
{
	unsigned int u_m = abs(m);
	unsigned int u_n = abs(n);
	int sum_d =0;
	while(u_m)
	{
		sum_d +=u_m%10;
		u_m/=10;
	}
	while(u_n)
	{	
		sum_d+=u_n%10;
		u_n/=10;
	}
	return sum_d;
}

string form_key(int m, int n)
{
	unsigned int temp_m = abs(m);
	unsigned int temp_n= abs(n);
	int len=0;
	if (m<0)
		visited_block_key[len++] = 'm';
//	if(temp_m==0)
//		visited_block_key[len++] = '0' ;		
	while(temp_m)
	{
		char x = '0'+temp_m%10;
		visited_block_key[len++] = x ;
		temp_m/=10;
	}
	visited_block_key[len++]='_';
	if (n<0)
		visited_block_key[len++] = 'm';
//	if(temp_n==0)
//		visited_block_key[len++] = '0' ;		
	while(temp_n)
	{
		char x = '0'+temp_n%10;
		visited_block_key[len++] = x;
		temp_n/=10;
	}
	visited_block_key[len] = '\0';
	return string(visited_block_key);
}
void mark_visited(int m, int n)
{

	string block_key = form_key(m,n);
	if(sum_digits(m,n)>19 || visited_blocks.find(block_key) != visited_blocks.end()) return;
	visited_blocks[block_key]=1;
	mark_visited(m-1,n);
	mark_visited(m,n-1);
	mark_visited(m+1,n);
	mark_visited(m,n+1);

}

int main()
{
	mark_visited(0,0);
	cout<<visited_blocks.size();
	return 0;
}

