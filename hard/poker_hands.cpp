#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
#include<map>
using namespace std;


int suite_arr[4]={0};
enum HandType { HIGH_CARD=1,
		ONE_PAIR,
		TWO_PAIRS,
		THREE_OF_A_KIND,
		STRAIGHT,
		FLUSH,
		FULL_HOUSE,
		FOUR_OF_A_KIND,
		STRAIGHT_FLUSH,
		ROYAL_FLUSH};



class PlayingCard {

	public:
	string card;
	PlayingCard(string & c):card(c) {}
	char getCardValue(){return card[0];}
	
};

int pair_one=0,pair_two=0,three_of_a_kind=0,four_of_a_kind=0;

std::map<char,int> cardValueRankingMap;




struct CardComparator {

public :
	bool operator()(const PlayingCard & card1,const PlayingCard & card2) {
		return cardValueRankingMap[card1.card[0]] < cardValueRankingMap[card2.card[0]];	
	}
}myCardComparator;


bool cardComparator(const PlayingCard & card1, const PlayingCard & card2) {
		return cardValueRankingMap[card1.card[0]] < cardValueRankingMap[card2.card[0]];	
}


bool isStraight(vector<PlayingCard> & hand) {

	vector<int> cardIntValues;
	for(int i=0;i<hand.size();i++) {
		cardIntValues.push_back(cardValueRankingMap[hand[i].card[0]]);
	}
	int firstCardValue = cardIntValues[0];

	for(int i=0;i<5;i++){ 
		cardIntValues[i] = cardIntValues[i]-firstCardValue;	
//		cout<<cardIntValues[i]<<",";
	}
//	cout<<endl;
	
	return (cardIntValues[0]==0 && cardIntValues[1]==1 && cardIntValues[2]==2 && cardIntValues[3]==3 && (cardIntValues[4]==4 || cardIntValues[4]==12));
	
}

bool isFlush(vector<PlayingCard> & hand) {

	if(hand.size() < 5) return false;
	
	PlayingCard & first_card = hand[0];
	for(int i=1;i<5;i++){
		if(first_card.card[1] != hand[i].card[1]) return false; 
	}
	return true;
}

HandType typeOfNumberOfKind(vector<PlayingCard> & hand) {

	pair_one=0;
	pair_two=0;
	::three_of_a_kind=0;
	::four_of_a_kind=0;

	std::map<int,int> kindMap;
	for(int i = 0;i<hand.size();i++) {
		if(kindMap.find(cardValueRankingMap[hand[i].card[0]]) == kindMap.end()){
			kindMap[cardValueRankingMap[hand[i].card[0]]] = 1;		
		}
		else {
			kindMap[cardValueRankingMap[hand[i].card[0]]]+=1;		
		}
	
	}
	
       std::map<int,int>::iterator it = kindMap.begin();
       std::map<int,int>::iterator it_end = kindMap.end();
	
	int two_of_a_kind=0;
	bool three_of_a_kind=false;
	while(it != it_end)
	{
		if(it->second == 4)
		{
			four_of_a_kind = it->first;
			return FOUR_OF_A_KIND;
		}                
		if(it->second == 2) {
			if(!pair_one) pair_one=it->first;
			if(!pair_two) pair_two=it->first;
			two_of_a_kind++;
		}
		if(it->second == 3){
			::three_of_a_kind = it->first;
			three_of_a_kind = true;
		}
		it++;
	}
	
	if(two_of_a_kind==1 && three_of_a_kind) return FULL_HOUSE;
	if(two_of_a_kind==2) return TWO_PAIRS;
	if(three_of_a_kind) return THREE_OF_A_KIND;
	if(two_of_a_kind==1) return ONE_PAIR;
	return HIGH_CARD;

}
HandType determineHandType(vector<PlayingCard> & hand) {

	bool bool_is_straight=false, bool_is_flush=false;

		bool_is_straight=isStraight(hand);
		bool_is_flush=isFlush(hand);
		if(bool_is_straight && bool_is_flush)
		{
			if(cardValueRankingMap[hand[0].card[0]]==10) return ROYAL_FLUSH;
			else
			return STRAIGHT_FLUSH;
		}
		if(bool_is_straight) {
		 return STRAIGHT;
		}
		if(bool_is_flush) { return FLUSH;}
		return typeOfNumberOfKind(hand);
}


void reportHighestCardWinner(vector<PlayingCard> &hand1,vector<PlayingCard> & hand2)
{
	for( int i =4; i>=0; i--) {
		if( cardValueRankingMap[hand1[i].card[0]] > cardValueRankingMap[hand2[i].card[0]]){ cout<<"left"<<endl; return; }
	
		if( cardValueRankingMap[hand1[i].card[0]] < cardValueRankingMap[hand2[i].card[0]]){ cout<<"right"<<endl; return; }
		
	}
	cout<<"none"<<endl;
}

void displayHand(vector<PlayingCard> & hand){

	for(int i=0;i<5;i++) {
	
		cout<<hand[i].card<<" ";
	}
	cout<<endl;
}

int main(int argc, char * argv[])
{
	
	if(argc>1) {
	
		//Initialize map
		cardValueRankingMap['A']=14;
		cardValueRankingMap['2']=2;
		cardValueRankingMap['3']=3;
		cardValueRankingMap['4']=4;
		cardValueRankingMap['5']=5;
		cardValueRankingMap['6']=6;
		cardValueRankingMap['7']=7;
		cardValueRankingMap['8']=8;
		cardValueRankingMap['9']=9;
		cardValueRankingMap['T']=10;
		cardValueRankingMap['J']=11;
		cardValueRankingMap['Q']=12;
		cardValueRankingMap['K']=13;
		
		string input_line;
		ifstream inputFile;
		int lh_pair_one, lh_pair_two, lh_three,lh_four;
		int rh_pair_one, rh_pair_two, rh_three,rh_four;
		vector<PlayingCard> left_hand;
		vector<PlayingCard> right_hand;
		HandType left_hand_type=HIGH_CARD,right_hand_type=HIGH_CARD;
		inputFile.open(argv[1]);
		while(getline(inputFile,input_line)){
			left_hand_type=HIGH_CARD;
			right_hand_type=HIGH_CARD;
			left_hand.clear();
			right_hand.clear();
			stringstream sstr(input_line);
			for(int i=0;i<5;i++) {
				string str;
				sstr>>str;
				left_hand.push_back(PlayingCard(str));
			}
			std::sort(left_hand.begin(),left_hand.end(),cardComparator);
		//	displayHand(left_hand);
			left_hand_type = determineHandType(left_hand);
			lh_pair_one = pair_one;
			lh_pair_two = pair_two;
			lh_three = three_of_a_kind;
			lh_four = four_of_a_kind;
			for(int i=0;i<5;i++) {
				string str;
				sstr>>str;
				right_hand.push_back(PlayingCard(str));
			}
			std::sort(right_hand.begin(),right_hand.end(),cardComparator);
		//	displayHand(right_hand);
			right_hand_type = determineHandType(right_hand);
			rh_pair_one = pair_one;
			rh_pair_two = pair_two;
			rh_three = three_of_a_kind;
			rh_four = four_of_a_kind;
			
			//cout<<"Left Hand Type : "<<left_hand_type<<endl;
			//cout<<"Right Hand Type : "<<right_hand_type<<endl;
			if(left_hand_type > right_hand_type) std::cout<<"left"<<std::endl;
			else
				if(left_hand_type < right_hand_type) std::cout<<"right"<<std::endl;
				else
				{
				if(left_hand_type == ONE_PAIR) {
				 if(lh_pair_one>rh_pair_one) cout<<"left"<<endl;
					else
					if(lh_pair_one<rh_pair_one) cout<<"right"<<endl;
					else
					    reportHighestCardWinner(left_hand,right_hand);
				}
				

				if(left_hand_type== TWO_PAIRS){
					int greater_lh = (lh_pair_one<lh_pair_two?lh_pair_two:lh_pair_one);	
					int greater_rh = (rh_pair_one<rh_pair_two?rh_pair_two:rh_pair_one);	
					int lower_lh = (lh_pair_one>lh_pair_two?lh_pair_two:lh_pair_one);	
					int lower_rh = (rh_pair_one>rh_pair_two?rh_pair_two:rh_pair_one);	
					if(greater_lh>greater_rh) cout<<"left"<<endl;
					else
					if(greater_lh<greater_rh) cout<<"right"<<endl;
					else
					if(lower_lh>lower_rh) cout<<"left"<<endl;
					else
					if(lower_lh<lower_rh) cout<<"right"<<endl;
					else
					reportHighestCardWinner(left_hand,right_hand);
				}


				if(left_hand_type == THREE_OF_A_KIND){

				 if(lh_three>rh_three) cout<<"left"<<endl;
					else
					if(lh_three<rh_three) cout<<"right"<<endl;
					else
					reportHighestCardWinner(left_hand,right_hand);
				}

				
				if(left_hand_type == STRAIGHT ){
				  if(cardValueRankingMap[left_hand[0].card[0]] > cardValueRankingMap[right_hand[0].card[0]])
					cout<<"left"<<endl;
				  else
				  if(cardValueRankingMap[left_hand[0].card[0]] < cardValueRankingMap[right_hand[0].card[0]])
					cout<<"right"<<endl;
				  else
					cout<<"none"<<endl;	
				}

				if(left_hand_type == FLUSH || left_hand_type == STRAIGHT_FLUSH ){
					reportHighestCardWinner(left_hand,right_hand);
				}

				
				if(left_hand_type == FULL_HOUSE ){
				
				 if(lh_three>rh_three) cout<<"left"<<endl;
					else
					if(lh_three<rh_three) cout<<"right"<<endl;
					else
					if(lh_pair_one>rh_pair_one) cout<<"left"<<endl;
					else
					if(lh_pair_one<rh_pair_one) cout<<"right"<<endl;
					else
					cout<<"none"<<endl;
					
					
				}

				
				if(left_hand_type == FOUR_OF_A_KIND ){
				 if(lh_four>rh_four) cout<<"left"<<endl;
					else
					if(lh_four<rh_four) cout<<"right"<<endl;
					else
					reportHighestCardWinner(left_hand,right_hand);
				}

				if(left_hand_type == ROYAL_FLUSH  ){
					cout<<"none"<<endl;
				}

				if(left_hand_type == HIGH_CARD  ){
					reportHighestCardWinner(left_hand,right_hand);
				}


			}
		}
		inputFile.close();
	
	}
	
}

