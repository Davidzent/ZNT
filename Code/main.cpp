#include "Deck.h"
#include "Player.h"
#include "Dealer.h"

int main()
{
	srand(time(0));
	string profile;
	Deck deck;
	Player you(deck);
	Dealer casino(deck);
	char x;
	bool bbreak = 0;

	cout << "Enter your username\n";
	cin >> profile;

	you.setProfile(profile);

	introduction();

	you.seeCards();

	casino.seeCard();

	if (you.win())
	{
		cout << "You won! " << std::endl;
	}
	else if (casino.win())
	{
		cout << "The dealer won!" << std::endl;
	}
	else
	{
		while (!you.lose())
		{
			cout << "What do you want to do: ";
			cin >> x;
			if (x == '1')
			{
				you.anotherCard();
			}
			else if (x == '2')
			{
				you.plant();
				casino.game(you);
				break;
			}
			you.seeCards();
			casino.seeCard();
		}
	}

	return 0;
}