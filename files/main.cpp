#include <iostream>
#include "library.h"
#include "games.h"

void colour_cout(const char* message) {
	std::cout << "\x1B[93m" << message << "\033[0m";
}

int main() {

	//A new library is created
	colour_cout("Let's create a library\n");
	Library* library = new Library;

	//We have a few games available
	colour_cout("\n\nLet's create some games\n");
	FightGame game1 = FightGame("Tekken 7\0");
	FightGame game2 = FightGame("Dragon Ball FighterZ\0");
	FightGame game4 = FightGame("Mortal Kombat X\0");
	
	//Let's check we can copy games
	colour_cout("\n\nLet's check we can copy a game\n");
	FightGame game3 = game4;

	//Let's see if we can move games
	colour_cout("\n\nLet's check we can move a game\n");
	game3 = std::move(game4);

	//Let's include them in our library as copies available
	colour_cout("\n\nLet's include them in our library as copies\n");
	library->Push(&game1);
	library->Push(&game2);
	library->Push(&game3);

	colour_cout("\n\nLet's see what do we have in our library\n");
	library->PrintGames();

	//Some players are around
	colour_cout("\n\nLet's create some players and check achievements\n");
	Player* player1 = new Player();
	Player* player2 = new Player();
	player1->DisplayAchievements();

	//They start playing a game
	colour_cout("\n\nLet's play a game\n");
	unsigned int gameId = 0;
	library->GetGameId(&game1, gameId);
	library->InitGame(gameId, player1, nullptr);

	colour_cout("\n\nLet's see the games' statistics\n");
	library->PrintGames();
		   
	colour_cout("\n\nNow the Player 1 achievements\n");
	player1->DisplayAchievements();

	//They start playing another one
	colour_cout("\n\nLet's play another game, a multiplayer one\n");
	library->GetGameId(&game2, gameId);
	library->InitGame(gameId, player1, player2, nullptr);

	colour_cout("\n\nLet's see the games' statistics\n");
	library->PrintGames();

	colour_cout("\n\nNow the Player 1 achievements\n");
	player1->DisplayAchievements();

	colour_cout("\n\nNow the Player 2 achievements\n");
	player2->DisplayAchievements();
	
	//Let's check we can safely copy our library
	colour_cout("\n\nLet's check we can safely copy our library\n");
	Library* libraryCopy = new Library(*library);
	delete library;

	colour_cout("\n\nWhat do we have in our copied library?\n");
	libraryCopy->PrintGames();

	//Now let's check we can safely move our library
	colour_cout("\n\nLet's check we can safely move our copied library\n");
	Library libraryMove = std::move(*libraryCopy);
	delete libraryCopy;

	colour_cout("\n\nWhat's now inside our moved library?\n");
	libraryMove.PrintGames();

	//Let's erase a game from our library
	colour_cout("\n\nLet's pop a game from our moved library\n");
	bool found = libraryMove.GetGameId(&game2, gameId);

	if (found)
		libraryMove.Pop(gameId);

	colour_cout("\n\nWhat's now inside our moved library?\n");
	libraryMove.PrintGames();

	colour_cout("\n\nEnd of the program. The remaining objects are going to be destroyed\n");

	//std::cin.get();
}