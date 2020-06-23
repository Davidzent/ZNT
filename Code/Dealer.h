#pragma once
#include "Player.h"
class Dealer : public Player //The dealer IS A player
{
public:
	using Player::Player;

	void seeCard();
	void game(Player);
};

void Dealer::seeCard()
{
	cout << "Dealer's card: ";
	mHand.displayAsDealer();
	cout << endl;
}

void Dealer::game(Player play)
{
	while (mHand.getTotalVal() <= 21)
	{
		cout << "Cards: ";
		mHand.display();
		cout << endl;
		if (mHand.getTotalVal() > play.getScore() && mHand.getTotalVal() <= 21)
		{
			cout << "The dealer won because his score was greater" << endl;
			return;
		}
		if (mHand.getTotalVal() == play.getScore())
		{
			std::cout << "A tie! " << endl;
			return;
		}
		anotherCard();
	}
	if (mHand.getTotalVal() > 21)
	{
		cout << "Dealer went past 21";
		return;
	}
}

void introduction()
{
	cout << "Controls: 1 for take another card" << endl;
	cout << "2 for planting" << endl;
}