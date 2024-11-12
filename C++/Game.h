#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <list>
#include <vector>

constexpr int PLACE_COUNT = 12;

class Player
{
public:
	Player(std::string _name)
		: name(_name) { }
		
	std::string name;
	int place = 0;
	int purse = 0;
	bool inPenaltyBox = false;

	void advance(int roll);
};

class Game
{
public:
	Game();
	bool isPlayable() const;
	void addPlayer(std::string playerName);
	int playerCount() const;
	void roll(int roll);
	bool wasCorrectlyAnswered();
	bool wrongAnswer();

private:
	std::vector <Player> players;
	std::list <std::string> popQuestions;
	std::list <std::string> scienceQuestions;
	std::list <std::string> sportsQuestions;
	std::list <std::string> rockQuestions;
	int currentPlayer = -1;
	bool isGettingOutOfPenaltyBox;

	const Player &getCurrentPlayer() const;
	Player &getCurrentPlayer();
	void askQuestion();
	std::string currentCategory();
	bool didPlayerWin();
};

#endif /* ! GAME_H_ */
