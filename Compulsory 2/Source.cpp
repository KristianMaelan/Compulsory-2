#include "Header.h"

int main() {
	//Login section
	std::cout << "\t\t\t\t\t----\t Welcome to 21!\t----" << std::endl;
	logIn();
	std::cout << "You logged in as Player\nContinuing to game. Please wait..." << std::endl; //login confirmation for user
	Sleep(3000);	//Waits so user can see they logged in and clears the screen and prepares for the game
	system("cls");
	cardGen(); //Generates the cards for use in the game when you start the game. Only needs to be run once.
	game();
	return 0;
}

void game(){

	bool keepPlaying = true; //Sets the game to keep playing until user exits.
	while (keepPlaying)
	{	
		Player1.points = 0; //Resetting everything to 0
		Player1.money = 100;
		
		Dealer.points = 0;
		Dealer.money = 100;

		nowinner = true;
		carddraw = 0;
		playerbet = NULL; //Sets bet to invalid and makes user input their bet.
		while (nowinner)
		{
			blackjack();
		}//no winner yet

		std::cout << "Do you want to play again?\n1: Yes\n2: No" << std::endl;
		int play = 0;
		std::cin >> play;
			switch (play){
			case 1:
				game();
			case 2:
				std::cout << "You have chosen to stop playing. You are welcome to play again later.\nProgram will shutdown...";
				Sleep(1500);
				exit(0);
			default:
				break;
			}//Switch case keep playing
	} //KeepPlaying
}

void blackjack() {
	
	cardshuffle(); //Shuffles the order of the cards. Its here so it runs each time a new round is started.

	if (Player1.money == 0)
	{
		system("cls");
		nowinner = false;
		std::cout << "You ran out of money and lost the game.\nFeel free to try again." << std::endl;
	}
	else if (Dealer.money == 0)
	{
		system("cls");
		nowinner = false;
		std::cout << "The dealer ran out of money and you have won the game!" << std::endl;
	}
	else
	{
		int validbet = 0;
		while (validbet == 0)
		{
		system("cls");
		std::cout << "Please enter how much you want to bet" << std::endl;
		std::cout << "You have " << Player1.money << " and the dealer has " << Dealer.money << "\nPlease enter a valid bet:" << std::endl;
		std::cin >> playerbet;
		clearCin();
		Player1.points = 0;
		Dealer.points = 0;

		if ((playerbet <= Player1.money) && (playerbet <= Dealer.money) && (playerbet >= 10)) //Controls the bet, if its not a legal bet, it prints error to user.
		{
			validbet = 1;
			std::cout << "You bet " << playerbet << " this round. Payout will be " << playerbet * 2 << "." << std::endl;
			Sleep(2000);
			playerturn(); //Player goes first.
			if (Player1.points > 21) //If player gets above 21 dealer automatically win and dealer doesnt draw cards.
			{
				Player1.money = Player1.money - playerbet;
				Dealer.money = Dealer.money + playerbet;
				std::cout << "You exceeded 21 points and lost this round. Good luck next time." << std::endl;
				std::cout << "You now have " << Player1.money << " left." << std::endl;
			}
			else if (Player1.points <= 21) // if player hasnt lost, the turn goes to Dealer
			{
				dealerturn();
			}
			else if (Player1.points > Dealer.points)
			{
				std::cout << " You won this round!";
				system("break");
			}
			else if ((Dealer.points <= 21) || (Dealer.points >=Player1.points))
			{
				Player1.money = Player1.money - playerbet;
				Dealer.money = Dealer.money + playerbet;
				std::cout << "The dealer won this round!";
			}
		}
		//invalid bet, 
			else
			{
			std::cout << "\n That bet is invalid, please try again." << std::endl;
			Sleep(2500);
			}
		}
	}
}

void playerturn() { //Player1 turn, different enough from Dealer function to warrant separate functions.
	char draw = 'y';
		while (draw == 'y')
		{

			std::cout << "You drew: " << card[carddraw].cardnumber << " of " << card[carddraw].house << std::endl;

			if (card[carddraw].cardnumber == "Ace") //Lets user decide what to do when they draw an ace.
			{
				int acevalue = 0;
				std::cout << "You drew an Ace! Please choose its value:\n1: 1\n2: 10" << std::endl;
				std::cin >> acevalue;
				clearCin();
				switch (acevalue)
				{
				case 1:
					card[carddraw].cardvalue = 1;
					break;
				case 2:
					card[carddraw].cardvalue = 10;
				default:
					break;
				}
			}

			Player1.points = Player1.points + card[carddraw].cardvalue;
			std::cout << "You currently have " << Player1.points << " points.";
			if (Player1.points > 21)
			{
				std::cout << "You got over 21 points\n" << std::endl;
				system("pause");
				return;
			}
			std::cout << "\nPress \"y\" to draw another card. ";
			std::cin >> draw;
			clearCin();
			carddraw++;
			system("cls");
		}
		std::cout << "You have stopped drawing cards.\nDealers turn. " << std::endl;
		Sleep(1000);
	}

void dealerturn() {
	bool dealernotwin = true; //Loops until Dealer wins OR dealer busts.
		while (dealernotwin)
		{
			carddraw++;
			system("cls");
			std::cout << "Dealer drew: " << card[carddraw].cardnumber << " of " << card[carddraw].house << std::endl;

			if (card[carddraw].cardnumber == "Ace")
			{
				if (Dealer.points < 11)
				{
					card[carddraw].cardvalue = 10;
				}

				std::cout << "Dealer drew an ace, Dealer has chosen its point value to be " << card[carddraw].cardvalue << std::endl;
			}

			Dealer.points = Dealer.points + card[carddraw].cardvalue;
			std::cout << "The dealer now has " << Dealer.points << " points." << std::endl;
			Sleep(2000);
			if ((Dealer.points <= 21) && (Dealer.points > Player1.points))
			{
				Player1.money = Player1.money - playerbet;
				Dealer.money = Dealer.money + playerbet;
				std::cout << "The dealer won this round! You lost " << playerbet << std::endl;
				dealernotwin = false;
				Sleep(2500);
			}
			else if (Dealer.points > 21)
			{
				Player1.money = Player1.money + playerbet;
				Dealer.money = Dealer.money - playerbet;
				std::cout << "The Dealer lost this round! You won " << playerbet * 2 << std::endl;
				Sleep(2500);
				return;
			}
		}
	}

void cardshuffle() { //Shuffle engine. Runs before each turn.
	std::random_device rd{};
	std::mt19937_64 g(rd());
	std::shuffle(card.begin(), card.end(), g);
}

void cardGen() { //Sets the correct values for all cards, simple blackjack using only 1 deck. 
	//Hearts 0-12
	for (int i = 0; i < 13; i++)
	{
		card[i].cardvalue = i + 1;
		card[i].house = "Hearts";
		card[i].cardnumber = std::to_string(i + 1);
	}
	//Diamonds
	for (int i = 0; i < 13; i++)
	{
		card[i + 13].cardvalue = i + 1;
		card[i + 13].house = "Diamonds";
		card[i + 13].cardnumber = std::to_string(i + 1);
	}
	//Spades
	for (int i = 0; i < 13; i++)
	{
		card[i + 26].cardvalue = i + 1;
		card[i + 26].house = "Spades";
		card[i + 26].cardnumber = std::to_string(i + 1);
	}
	//Clubs
	for (int i = 0; i < 13; i++)
	{
		card[i + 39].cardvalue = i + 1;
		card[i + 39].house = "Clubs";
		card[i + 39].cardnumber = std::to_string(i + 1);
	}
	for (int i = 0; i < 52; i++) //Looops and checks for card values higher than 10 and sets them all to 10.
	{
		if (card[i].cardvalue == 11)
		{
			card[i].cardvalue = 10;
			card[i].cardnumber = "Knight";
		}
		if (card[i].cardvalue == 12)
		{
			card[i].cardvalue = 10;
			card[i].cardnumber = "Queen";
		}
		if (card[i].cardvalue == 13)
		{
			card[i].cardvalue = 10;
			card[i].cardnumber = "King";
		}
		if (card[i].cardvalue == 1)
		{
			card[i].cardvalue = 1;
			card[i].cardnumber = "Ace";
		}
	}
}

void logIn(){
	std::string username = "Player";
	std::string usernameinput{};
	std::string userpassword = "Playerpassword123";
	std::string userpasswordinput{};
	bool notloggedin = true;
	std::cout << "\n\t\t\t\t\t    Please login to play the game: " << std::endl;
	do{
		for (int i = 0; i < 3; i++)
		{
			std::cout << "Please enter your username: " << std::endl;
			std::cin >> usernameinput;
			clearCin();
			std::cout << "Please enter your password: " << std::endl;
			std::cin >> userpasswordinput;

			if ((username == usernameinput) && (userpassword == userpasswordinput))
			{
				notloggedin = false;
				return;
			}
			else if (i < 2)
			{
				system("cls");
				std::cout << "Wrong username or password, please try again" << std::endl;;
			}
			else
			{
				std::cout << "Too many attempts... Try again later.";
				exit(0);
			}
		}
	}while (notloggedin);
}

void clearCin() {							//Function used to flush cin buffer. 
	std::cin.clear();
	std::cin.ignore(32767, '\n');
}