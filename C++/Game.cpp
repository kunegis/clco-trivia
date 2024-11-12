#include "Game.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <sstream>

void Player::advance(int roll)
{
	place += roll;
	place %= PLACE_COUNT;
}

Game::Game()
{
	for (int i = 0; i < 50; i++) {
		popQuestions.push_back("Pop Question " + std::to_string(i));
		scienceQuestions.push_back("Science Question " + std::to_string(i));
		sportsQuestions.push_back("Sports Question " + std::to_string(i));
		rockQuestions.push_back("Rock Question " + std::to_string(i));
	}
}

bool Game::isPlayable() const
{
	return playerCount() >= 2;
}

void Game::addPlayer(std::string playerName)
{
	players.emplace_back(playerName);
	std::cout << playerName << " was added" << std::endl;
	std::cout << "They are player number " << (players.size()-1) << std::endl;
	if (currentPlayer < 0) currentPlayer = 0;
}

int Game::playerCount() const
{
	return players.size();
}

void Game::roll(int roll)
{
	std::cout << players[currentPlayer].name << " is the current player" << std::endl;
	std::cout << "They have rolled a " << roll << std::endl;

	if (getCurrentPlayer().inPenaltyBox)
	{
		if (roll % 2 != 0)
		{
			isGettingOutOfPenaltyBox = true;

			std::cout << getCurrentPlayer().name << " is getting out of the penalty box" << std::endl;
			getCurrentPlayer().advance(roll);

			std::cout << getCurrentPlayer().name << "'s new location is " << getCurrentPlayer().place << std::endl;
			std::cout << "The category is " << currentCategory() << std::endl;
			askQuestion();
		}
		else
		{
			std::cout << getCurrentPlayer().name << " is not getting out of the penalty box" << std::endl;
			isGettingOutOfPenaltyBox = false;
		}
	}
	else
	{
		getCurrentPlayer().advance(roll);

		std::cout << getCurrentPlayer().name << "'s new location is " << getCurrentPlayer().place << std::endl;
		std::cout << "The category is " << currentCategory() << std::endl;
		askQuestion();
	}

}

void Game::askQuestion()
{
	if (currentCategory() == "Pop")
	{
		std::cout << popQuestions.front() << std::endl;
		popQuestions.pop_front();
	}
	if (currentCategory() == "Science")
	{
		std::cout << scienceQuestions.front() << std::endl;
		scienceQuestions.pop_front();
	}
	if (currentCategory() == "Sports")
	{
		std::cout << sportsQuestions.front() << std::endl;
		sportsQuestions.pop_front();
	}
	if (currentCategory() == "Rock")
	{
		std::cout << rockQuestions.front() << std::endl;
		rockQuestions.pop_front();
	}
}


std::string Game::currentCategory()
{
	switch (getCurrentPlayer().place) {
	case 0:     
	case 4:
	case 8:
		return "Pop";
	case 1:
	case 5:
	case 9:
		return "Science";
	case 2:
	case 6:
	case 10:
		return "Sports";
	default:
		return "Rock";
	}
}

bool Game::wasCorrectlyAnswered()
{
	if (getCurrentPlayer().inPenaltyBox)
	{
		if (isGettingOutOfPenaltyBox)
		{
			std::cout << "Answer was correct!!!!" << std::endl;
			getCurrentPlayer().purse ++;
			std::cout << getCurrentPlayer().name
				  << " now has "
				  << getCurrentPlayer().purse
				  <<  " Gold Coins." << std::endl;

			bool winner = didPlayerWin();
			currentPlayer++;
			if (currentPlayer == playerCount()) currentPlayer = 0;
			return winner;
		}
		else
		{
			currentPlayer++;
			if (currentPlayer == playerCount()) currentPlayer = 0;
			return true;
		}
	}
	else
	{
		std::cout << "Answer was corrent!!!!" << std::endl;
		getCurrentPlayer().purse++;
		std::cout << getCurrentPlayer().name
			  << " now has "
			  << getCurrentPlayer().purse
			  << " Gold Coins." << std::endl;

		bool winner = didPlayerWin();
		++currentPlayer %= players.size();
		return winner;
	}
}

bool Game::wrongAnswer()
{
	std::cout << "Question was incorrectly answered" << std::endl;
	std::cout << getCurrentPlayer().name + " was sent to the penalty box" << std::endl;
	getCurrentPlayer().inPenaltyBox = true;
	++currentPlayer %= players.size();
	return true;
}

bool Game::didPlayerWin()
{
	return !(getCurrentPlayer().purse == 6);
}

const Player &Game::getCurrentPlayer() const
{
	assert(currentPlayer >= 0 && currentPlayer < playerCount());
	return players[currentPlayer];
}

Player &Game::getCurrentPlayer()
{
	assert(currentPlayer >= 0 && currentPlayer < playerCount());
	return players[currentPlayer];
}
