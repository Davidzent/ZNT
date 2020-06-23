#pragma once
#include "Deck.h"
#include "Hand.h"
#include "node.h"
#include <fstream>
class Player
{
protected:
	Deck mDeck;
	Hand mHand;
	bool canGetCards;
	int score;
	string profile;
public:
	Player(Deck deck);
	Player(Deck deck, string);
	void plant();
	void anotherCard();
	void seeCards();

	int getScore() const;
	void setProfile(string);
	bool checkProfile();

	bool lose();
	bool win();
};

Player::Player(Deck deck)
{
	canGetCards = 1;
	mDeck = deck;
	mHand.init(deck.giveCard(), deck.giveCard());
}

void Player::plant()
{
	canGetCards = 0;
	score = mHand.getTotalVal();
}

void Player::anotherCard()
{
	if (canGetCards) mHand.addCard(mDeck.giveCard());
	else cout << "You cannot get more cards" << endl;
}

Player::Player(Deck deck, string username)
{
	this->profile = username;
	canGetCards = 1;
	mDeck = deck;
	mHand.init(deck.giveCard(), deck.giveCard());
	ofstream outfile;
	outfile.open("Profile.txt");
	outfile << username;
	outfile.close();
}

unsigned int RSHash(const std::string& str)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;

	for (std::size_t i = 0; i < str.length(); i++)
	{
		hash = hash * a + str[i];
		a = a * b;
	}

	return hash;
}


void Player::setProfile(string username)
{
	int temp;
	unsigned int hashNum;
	ifstream infile;
	infile.open("Profile.txt");
	if (infile)
	{
		char num = '0';
		int i = 0;
		Node<string> **Arr;
                Arr = new Node <string> *[10];
                
		string temp;
		while (infile >> temp) {
			hashNum = RSHash(temp) % 10;
			Arr[hashNum]->push_front(temp);

		};
		this->profile = username;
		hashNum = RSHash(username)%10;
		//cout << hashNum << endl;
			ofstream outfile;
			outfile.open("Profile.txt");
			for (int i = 0; i < 10; i++)
			{
				num = '1' + i;
				if (hashNum == i)
				{
					outfile << num + " " + username << endl;
				}
				cout << Arr[i];
				outfile << num << " " << Arr[i] << endl;
			}
			outfile << username << endl;
			outfile.close();
		
	}
	else
	{
		char num='0';
		hashNum = RSHash(username) % 10;
		//cout << hashNum<<endl ;
		ofstream outfile;
		outfile.open("Profile.txt");
		for (int i = 0; i < 10; i++)
		{
			num = '1' + i;
			if (hashNum + 1 == i)
			{
				outfile << num + " " + username << endl;
			}
			outfile << num<< endl;
		}
		outfile << username << endl;
		outfile.close();
	}
	
}

bool Player::lose()
{
	if (mHand.getTotalVal() > 21)
	{
		cout << "You went over 21. You lose" << endl;
		return true;
	}
	return false;
}

bool Player::win()
{
	return (mHand.getTotalVal() == 21 && mHand.getNumOfCards() == 2);
}

void Player::seeCards()
{
	cout << "Your cards: ";
	mHand.display();
}

int Player::getScore() const
{
	return score;
}