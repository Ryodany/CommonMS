#pragma once

#include <iostream>
#include <map>
#include <stdarg.h>

#include "player.h"

class Game {

protected:
	const char* m_name = nullptr;
	unsigned int m_hoursPlayed = 0;
	unsigned int m_libraryId = 0;

	std::vector<std::tuple<unsigned int, const char*>> m_achievements;
	Game& operator= (const Game& other) = delete;

	Game() {
	};

public:

	virtual ~Game() {
	};

	Game(const char* name) {
		std::cout << "game construct\n";

		m_libraryId = 0;
		m_hoursPlayed = 0;
	
		size_t size = strlen(name);
		m_name = new char[size + 1];
		memcpy((void*)m_name, name, size + 1);
	};

	Game(const Game& other) 
		: m_hoursPlayed(other.m_hoursPlayed), m_libraryId(other.m_libraryId) {
		std::cout << "game copy\n";

		size_t size = strlen(other.m_name);
		m_name = new char[size + 1];
		memcpy((void*)m_name, other.m_name, size + 1);
	};

	Game(Game&& other) noexcept
		: m_name(nullptr), m_hoursPlayed(other.m_hoursPlayed), m_libraryId(other.m_libraryId) {
		std::cout << "game move const\n";

		m_name = other.m_name;

		other.m_hoursPlayed = 0;
		other.m_name = nullptr;
	}

	Game& operator=(Game&& other) noexcept {
		if (this != &other) {
			std::cout << "game move operator\n";

			delete[] m_name;

			m_name = other.m_name;

			other.m_hoursPlayed = 0;
			other.m_name = nullptr;
		}

		return *this;
	}

	const char* GetName() const {
		return m_name;
	}

	unsigned int GetLibraryID() const {
		return m_libraryId;
	}

	void SetLibraryID(unsigned int id) {
		m_libraryId = id;
	}

	virtual Game* Clone() const = 0;
	virtual void PrintInfo() const = 0;
	virtual void Launch(Player* player1, va_list Players) = 0;
	virtual unsigned int GetNumPlayers(void) const = 0;

protected:
	virtual void CheckAchievements(Player* player) = 0;
};

class Library {

protected:
	std::map<unsigned int, Game*> m_games;
	Library& operator= (const Library& other) = delete;
	Library& operator= (Library&& other) = delete;

public:
	~Library() {
		std::cout << "library destruct\n";
		for (auto g : m_games) {
			g.second->~Game();
		}
	};
	Library() {
		std::cout << "library construct\n";
	};

	Library(const Library& other) {
		std::cout << "library copy construct\n";

		for (auto g : other.m_games)
			Push(g.second);
	};

	Library(Library&& other) noexcept {
		std::cout << "library move construct\n";

		for (auto g : other.m_games) {
			Game* l_game = std::move(g.second);
			Emplace(l_game);
		}
		
		other.Clear();
	};	

	void Clear() {
		m_games.clear();
	}

	void PrintGames(void) const {
		for (auto g : m_games) {
			std::cout << "Id: " << g.first << " ";
			g.second->PrintInfo();
		}
	}

	size_t Size(void) const {
		return m_games.size();
	}

	void Emplace(Game* game) {
		size_t id = m_games.size();
		m_games.insert(std::pair<unsigned int, Game*>(id, game));
	}

	void Push(Game* game) {
		size_t id = m_games.size();
		Game* newGame = game->Clone();

		newGame->SetLibraryID(id);

		m_games.insert(std::pair<unsigned int, Game*>(id, newGame));
		
	}

	void Pop(unsigned int id) {
		m_games.erase(id);
	}

	bool GetGameId(Game* game, unsigned int& id) const {
		bool found = false;
		const char* name = game->GetName();

		for (auto g : m_games) {
			const char* compName = g.second->GetName();
			if (!strcmp(name, compName)) {
				id = g.first;
				found = true; 
				break;
			}
		}

		return found;
	}

	bool InitGame(unsigned int gameId, Player* player, ...) {

		bool found = false;

		for (auto g : m_games) {
			if (g.first == gameId) {

				found = true;
				va_list playerList;
				va_start(playerList, player);
				g.second->Launch(player, playerList);
				va_end(playerList, player);

				break;
			}
		}

		return found;
	}
};