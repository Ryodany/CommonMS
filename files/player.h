#pragma once

#include <iostream>
#include <random>

class Player {

protected:
	std::vector <std::tuple<unsigned int, unsigned int, std::string, bool>> m_achievements;

	Player& operator= (const Player& other) = delete;

	void OrderAchievements() {
		std::sort(m_achievements.begin(), m_achievements.end());
	}

public:
	~Player() {
		std::cout << "player destruct\n";
	};

	Player() {
		std::cout << "player construct\n";
	};

	Player(const Player& other) {
		std::cout << "player copy\n";
	}

	unsigned int Play(void) {
		std::cout << "Playing!\n";

		//hours
		auto timePlayed = [](void) {
			std::random_device rd;
			std::default_random_engine eng(rd());
			std::uniform_int_distribution<int> distr(0, 20);

			return distr(eng);
		};

		unsigned int hours = timePlayed();

		return hours;
	}

	void SetAchievement(unsigned int gameId, unsigned int achievementId, std::string achievementDesc) {

		std::tuple<unsigned int, unsigned int, std::string, bool> achievement;
		achievement = std::make_tuple(gameId, achievementId, achievementDesc, true);
		
		bool found = false;

		if(!m_achievements.empty()) {

			unsigned int l_gameId, l_achievementId;

			for (int i = 0; i < m_achievements.size(); i++) {

				l_gameId = std::get<0>(m_achievements[i]);

				if(l_gameId == gameId) {
					l_achievementId = std::get<1>(m_achievements[i]);

					if (l_achievementId == achievementId) {
						found = true;
						break;
					}
				}
			}
		}

		if (!found)
			m_achievements.push_back(achievement);
	}

	void DisplayAchievements(void) {
		if (m_achievements.empty())
			std::cout << "No achievements unlocked" << std::endl;
		else
		{
			OrderAchievements();

			bool accomplished = false;
			int newGame = -1, prevGame = std::get<0>(m_achievements[0]);

			for (int i = 0; i < m_achievements.size(); i++) {
				newGame = std::get<0>(m_achievements[i]);

				if (prevGame != newGame || i == 0)
				{
					prevGame = newGame;
					std::cout << "Game: " << std::get<0>(m_achievements[i]) << std::endl;
				}

				std::cout << "\tAchievement: " << std::get<1>(m_achievements[i]) << " - " << std::get<2>(m_achievements[i]) << " - ";

				accomplished = std::get<3>(m_achievements[i]);

				if (accomplished)
					std::cout << "Accomplished" << std::endl;
				else
					std::cout << "Locked" << std::endl;
			}
		}
	}
};