#pragma once
#include <iostream>		//input-output
#include <Windows.h>	//sleep function
#include <algorithm>	//shuffle
#include <array>		//arrays
#include <vector>		//vectors
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>

void clearCin(); //Clears Cin buffer if needed
void logIn();	 //Login function
void cardGen();	 // Generates the cards for the game, its own function to easier edit for multiple variants.

bool nowinner = true;
int reward{};
int playerbet{};
int carddraw = 0;

struct Players {
	int points{};			//For checking if player busted
	int money{ 100 };			//Money left
	bool realplayer{};		//checks if real player or dealer
} Player1{ 0, {}, true }, Dealer{ 0, {}, false };

struct Cards {
	int cardvalue{};			//How many actual points the card gives. Gives the opportunity to give the same types multiple values.
	std::string cardnumber{};	//Card "Value" 1, 5, ace, king etc...
	std::string house{};		//Clubs, hearts, diamonds, spades
};

//Declarations for the game itself
void game();//Game function
void cardshuffle();
void blackjack();
void playerturn();
void dealerturn();

std::vector<Cards> card(52);