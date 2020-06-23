#pragma once
#include "card.h"
class Deck
{
private:
	std::vector<Card*> mDeck;

public:
	Deck();

	void fillDeck();
	void shuffle();
	Card giveCard();
};

Deck::Deck()
{
	
	fillDeck();
	shuffle();
}

void Deck::fillDeck()
{
	for (int i = 1; i <= 12; ++i)
	{
		char c;
		switch (i) {
		case 1: c = 'A'; break;
		case 2: c = '2'; break;
		case 3: c = '3'; break;
		case 4: c = '4'; break;
		case 5: c = '5'; break;
		case 6: c = '6'; break;
		case 7: c = '7'; break;
		case 8: c = '8'; break;
		case 9: c = '9'; break;
		case 10: c = 'T'; break;
		case 11: c = 'J'; break;
		case 12: c = 'Q';
		}
		for (int n = 0; n <= 3; ++n)
		{
			mDeck.push_back(new Card(c, n));
		}
	}
}

void Deck::shuffle()
{
	random_shuffle(mDeck.begin(), mDeck.end());
}

Card Deck::giveCard()
{
	for (int i = 0; i < mDeck.size(); ++i)
	{
		if (!mDeck[i]->getIfGiven())
		{
			mDeck[i]->setGiven(1);
			return (*mDeck[i]);
		}
	}
}