#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

class Card
{
private:
	char mCard; // 'A' ,'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q'
	int mValue, //1 or 11 , 2 , 3 , 4, 5 , 6 , 7 , 8 , 9, 10, 10, 10
		mSuite; //0 spades, 1 clubs, 2 hearts, 3 diamonds
	string cardName;
	bool given; //Check if it's been wether given or not. works as an index

	int assignValue();

public:
	Card(char, int);
	Card(const Card&);

	int getValue() const;
	int getSuite() const;
	string getName() const;
	bool getIfGiven() const;
	char getCard() const;

	void setGiven(bool x);

	void nameCard();
};

int Card::assignValue()
{
	if (mCard == 'A') return 11;
	else if (mCard == 'T' ||
		mCard == 'J' ||
		mCard == 'Q') return 10;
	else return (mCard - '0');
}

Card::Card(char cardV, int suite)
{
	mCard = cardV;
	mValue = assignValue();
	mSuite = suite;
	given = false;
}

Card::Card(const Card& card)
{
	mCard = card.getCard();
	mValue = card.getValue();
	mSuite = card.getSuite();
	cardName = card.getName();
	given = card.getIfGiven();
}

int Card::getValue() const
{
	return mValue;
}

int Card::getSuite() const
{
	return mSuite;
}

std::string Card::getName() const
{
	return cardName;
}

bool Card::getIfGiven() const
{
	return given;
}

char Card::getCard() const
{
	return mCard;
}

void Card::setGiven(bool x)
{
	given = x;
}

void Card::nameCard()
{
	switch (mSuite)
	{
	case 0: cardName = "spades"; break;
	case 1: cardName = "clubs"; break;
	case 2: cardName = "hearts"; break;
	case 3: cardName = "diamonds";
	}
	if (mCard == 'A')
		cout << "Ace";
	else if (mCard == 'J')
		cout << "Joker";
	else if (mCard == 'Q')
		cout << "Queen";
	else 
		cout << mValue;

	cout << " of " << cardName << endl;
}