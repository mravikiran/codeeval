#include<iostream>
#include<vector>
using namespace std;

#define GRID_DIMENSION 4 

int numOfPaths=0;
vector<pair<int,int> > pathSoFar;
void moveTo(int x, int y);

bool notInPath(int x, int y) {

	vector<pair<int, int> >::iterator it = pathSoFar.begin();
	vector<pair<int, int> >::iterator it_end = pathSoFar.end();
	while(it != it_end)
	{
		if(it->first == x && it->second == y) return false;
		it++;
	}
	return true;
}

void moveTo(int x, int y)
{
	if(x==GRID_DIMENSION && y==GRID_DIMENSION) {
	/*	 for(int i=0;i<GRID_DIMENSION;i++){
		 	for(int j=0;j<GRID_DIMENSION;j++){
				cout<<"|";
				if(notInPath(i+1,j+1)) cout<<" ";
				else
				cout<<"*";
			}
			cout<<"|"<<endl;


		}
			cout<<"_________________________________"<<endl;
	*/
		 numOfPaths++;
	}
	if(x+1 <=GRID_DIMENSION  && y <= GRID_DIMENSION && x+1 >=1  && y >=1  && notInPath(x+1,y)) {
		pathSoFar.push_back(pair<int,int>(x+1,y));
		moveTo(x+1,y);
		pathSoFar.pop_back();
	}
	if(x-1 <=GRID_DIMENSION   && y <= GRID_DIMENSION  && x-1 >=1  && y >=1  && notInPath(x-1,y)) {
		pathSoFar.push_back(pair<int,int>(x-1,y));
		moveTo(x-1,y);
		pathSoFar.pop_back();
	}
	if(x <=GRID_DIMENSION   && y+1 <= GRID_DIMENSION  && x >=1 && y+1 >=1 && notInPath(x,y+1)) {
		pathSoFar.push_back(pair<int,int>(x,y+1));
		moveTo(x,y+1);
		pathSoFar.pop_back();
	}
	if(x <=GRID_DIMENSION   && y-1 <= GRID_DIMENSION  && x >=1 && y-1 >=1 && notInPath(x,y-1)) {
		pathSoFar.push_back(pair<int,int>(x,y-1));
		moveTo(x,y-1);
		pathSoFar.pop_back();
	}
}


int main()
{

pathSoFar.push_back(pair<int,int>(1,1));
moveTo(1,1);

cout<<numOfPaths;

return 0;
}

