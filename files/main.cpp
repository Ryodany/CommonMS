#include <iostream>
#include "library.h"
#include "games.h"

int main() {

	//A new library is created
	Library* library = new Library;

	std::cout << "-----------\n\n";

	//We have a few games available
	FightGame game1 = FightGame("Tekken 7\0");
	FightGame game2 = FightGame("Dragon Ball FighterZ\0");
	FightGame game4 = FightGame("Mortal Kombat X\0");
	
	std::cout << "-----------\n\n";

	//Let's check we can copy and move games
	FightGame game3 = game4;
	game3 = std::move(game4);

	//Let's include them in our library as copies available
	library->Push(&game1);
	library->Push(&game2);
	library->Push(&game3);

	library->PrintGames();

	std::cout << "-----------\n\n";
	
	//Some players are around
	Player* player1 = new Player();
	Player* player2 = new Player();
	player1->DisplayAchievements();

	std::cout << "-----------\n\n";

	//They start playing a game
	unsigned int gameId = 0;
	library->GetGameId(&game1, gameId);
	library->InitGame(gameId, player1, nullptr);
	library->PrintGames();
		   
	std::cout << "----------- Player 1 achievements\n";
	player1->DisplayAchievements();

	std::cout << "-----------\n\n";

	//They start playing another one
	library->GetGameId(&game2, gameId);
	library->InitGame(gameId, player1, player2, nullptr);
	library->PrintGames();

	std::cout << "----------- Player 1 achievements\n";
	player1->DisplayAchievements();
	std::cout << "----------- Player 2 achievements\n";
	player2->DisplayAchievements();

	std::cout << "-----------\n\n";
	
	//Let's check we can safely copy our library
	Library* libraryCopy = new Library(*library);
	delete library;
	libraryCopy->PrintGames();

	std::cout << "-----------\n\n";

	//Now let's check we can safely move our library
	Library libraryMove = std::move(*libraryCopy);
	delete libraryCopy;
	libraryMove.PrintGames();

	std::cout << "-----------\n\n";

	//Let's erase a game from our library
	bool found = libraryMove.GetGameId(&game2, gameId);

	if (found)
		libraryMove.Pop(gameId);

	libraryMove.PrintGames();

	std::cout << "-----------\n\n";

	std::cin.get();

	//Agregar descripción a las funciones
	//Usar algún smart pointer http://www.vishalchovatiya.com/unique_ptr-with-example-in-c/
}