#pragma once
#include "card.h"
class Hand
{

private:
	std::vector<Card> mHand;

public:

	void init(Card, Card);
	void display();
	void displayAsDealer();
	void addCard(Card);

	int getNumOfCards();
	int getTotalVal();
};

void Hand::init(Card card1, Card card2)
{
	mHand.push_back(card1);
	mHand.push_back(card2);
}

void Hand::display()
{
	for (vector<Card>::iterator iter = mHand.begin();
		iter != mHand.end(); (++iter))
	{
		iter->nameCard();
	}
}

void Hand::displayAsDealer()
{
	mHand[0].nameCard();
}

void Hand::addCard(Card card)
{
	cout << "\nTook out: ";
	card.nameCard();

	mHand.push_back(card);
}

int Hand::getTotalVal()
{
	int sum = 0;
	for (vector<Card>::iterator iter = mHand.begin();
		iter != mHand.end(); (++iter))
	{
		sum += iter->getValue();
	}
	return sum;
}

int Hand::getNumOfCards()
{
	return mHand.size();
}