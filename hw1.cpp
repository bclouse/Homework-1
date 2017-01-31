#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <iomanip>

using namespace std;

//===============================================
//	Card class and functions
//===============================================

class Card {
	int suite;
	int value;
	public:
		Card ();
		Card (int, int);
		void set_values(int, int);
		void c_display(FILE*);
		bool cmp_values(int, int);
};

Card::Card() {
	suite = 0;
	value = 0;
}

Card::Card(int s, int v) {
	assert((s > 0) && (s < 5));
	assert((v > 0) && (v < 14));
	suite = s;
	value = v;
}

void Card::set_values(int s, int v) {
	assert((s > 0) && (s < 5));
	assert((v > 0) && (v < 14));
	suite = s;
	value = v;
}

void Card::c_display(FILE *fp) {
	if ((value > 1) && (value < 11)) {
		fprintf(fp,"%5d of ", value);	
	} else {
		switch (value) {
			case 1: fprintf(fp,"  Ace of "); break;
			case 11: fprintf(fp," Jack of "); break;
			case 12: fprintf(fp,"Queen of "); break;
			case 13: fprintf(fp," King of "); break;
		}
	}
	switch (suite) {
		case 1: fprintf(fp,"Hearts"); break;
		case 2: fprintf(fp,"Diamonds"); break;
		case 3: fprintf(fp,"Clubs"); break;
		case 4: fprintf(fp,"Spades"); break;
	}
}

bool Card::cmp_values(int s, int v) {
	if ((s == suite) && (v == value)) return true;
	else return false; 
}

//===============================================
//	Deck class and functions
//===============================================

class Deck {
	int length;
	vector<Card> card_list;
	public:
		Deck (int);
		void d_display(FILE*);
		void shuffle();
		void TestA();
		void TestB(int);
};

Deck::Deck(int n) {
	if (n <= 0) {
		n = 1;
	}
	length = n*52;
	Card blank;
	for (int k = 0; k < n; k++) {
		for (int j = 1; j < 5; j++) {
			for (int i = 1; i < 14; i++) {
				blank.set_values(j,i);
				card_list.push_back(blank);
			}
		}
	}
	assert(card_list.size() == n*52);
}

void Deck::d_display(FILE *fp) {
	for (int i = 0; i < card_list.size(); i++) {
		card_list.at(i).c_display(fp);
		if (i != card_list.size()-1) {
			fprintf(fp, "\n");
		}
	}
}

void Deck::shuffle() {
	vector<Card> new_deck;
	int r;
	for (int i = 0; i < length; i++) {
		r = rand() % card_list.size();
		new_deck.push_back(card_list.at(r));
		card_list.erase(card_list.begin()+r);
	}
	card_list = new_deck;
}

void Deck::TestA() {
	int count = 0;
	for (int k = 1; k < 5; k++) {
		for (int j = 1; j < 14; j++) {
			for (int i = 0; i < card_list.size(); i++) {
				if (card_list.at(i).cmp_values(k,j)) count++;
			}
			assert(count == 1);
			count = 0;
		}
	}
}

void Deck::TestB(int n) {
	int count = 0;
	for (int k = 1; k < 5; k++) {
		for (int j = 1; j < 14; j++) {
			for (int i = 0; i < card_list.size(); i++) {
				if (card_list.at(i).cmp_values(k,j)) count++;
			}
			assert(count == n);
			count = 0;
		}
	}
}

//===============================================
//	Main function
//===============================================

int main() {
	int n = 4;	//number of decks
	FILE *fp;

	fp = fopen("deck.txt", "w");
/*
	cout << "How many decks do you want? ";
	cin >> n;
	cout << endl << endl; 
*/
	srand(time(NULL));
	Deck deck_full (n);
	deck_full.shuffle();
	if (n <= 1) {
		deck_full.TestA();
		//cout << "Test A was successful!" << endl;
	} else {
		deck_full.TestB(n);
		//cout << "Test B was successful!" << endl;
	}
	deck_full.d_display(fp);
	fclose(fp);

	return 0;
}