#pragma once

#include <stdarg.h>

#include "library.h"

#define _ACH_FirstFight		"You've fight your first fight!"
#define _ACH_LvlUp			"Level up!"

template <class T>
class DamageCalculator {
private:
	T m_exp, m_fatigue;

public:
	DamageCalculator(T exp, T fatigue) {
		m_exp = exp;
		m_fatigue = fatigue;
	}

	void DisplayDamage() {
		std::cout << "Player status: " << m_exp << " and " << m_fatigue << "." << std::endl;
		std::cout << "Punch: " << Punch() << std::endl;
		std::cout << "Kick: " << Kick() << std::endl;
		std::cout << "Combo: " << Combo() << std::endl;
		std::cout << "CoverUp: " << CoverUp() << std::endl;

	}

	T Punch() { 
		return 20*m_exp - 10*m_fatigue; 
	}
	T Kick() { 
		return 30*m_exp - 15*m_fatigue; 
	}
	T Combo() { 
		return 40*m_exp - 20*m_fatigue; 
	}
	T CoverUp() { 
		return 50*m_exp - 25*m_fatigue; 
	}
};

class FightGame : public Game {

private:
	const unsigned int m_maxPlayers = 2;
	const unsigned int m_lvlUpPoints = 100;
	unsigned int m_level = 1;

	enum Achievements
	{
		FirstFight = 0,
		LvlUp,
	};

public:
	~FightGame() override {
		std::cout << "Fight game destruct\n";
	};

	FightGame(const char* name) : Game(name) {
		std::cout << "Fight game construct\n";
		
		m_level = 1;
	};

	FightGame(const FightGame& other)
		: Game(other), m_maxPlayers(other.m_maxPlayers), m_lvlUpPoints(other.m_lvlUpPoints), m_level(other.m_level) {
		std::cout << "Fight game copy\n";
	};

	FightGame(FightGame&& other) noexcept
		: Game(other), m_maxPlayers(other.m_maxPlayers), m_lvlUpPoints(other.m_lvlUpPoints), m_level(other.m_level) {
		std::cout << "Fight game move const\n";

		other.m_level = 1;
	};

	FightGame& operator=(FightGame&& other) noexcept {
		if (this != &other) {
			std::cout << "Fight game move operator\n";
			Game::operator=(std::move(other));
			other.m_level = 1;
		}

		return *this;
	}

	virtual FightGame* Clone() const override {
		return new FightGame(*this);
	}

	void PrintInfo() const override {
		std::cout << "Fight game: " << m_name << " - hours played: " << m_hoursPlayed << std::endl;
	};

	unsigned int GetNumPlayers(void) const override {
		return m_maxPlayers;
	};

protected:

	void CheckAchievements(Player* player) override {
		
		player->SetAchievement(m_libraryId, FirstFight, _ACH_FirstFight);

		if (m_level > 2)
			player->SetAchievement(m_libraryId, LvlUp, _ACH_LvlUp);
	};

	void EvaluateExp(unsigned int level, unsigned int hours) {

		int totalDamage = 0;
		DamageCalculator<unsigned int> calc(m_level, hours);
	
		if (hours < 5)
			totalDamage = calc.Punch();
		else if (hours < 10) {
			totalDamage = calc.Kick();
			totalDamage += calc.Kick();
		}
		else if (hours < 15) {
			totalDamage = calc.Kick();
			totalDamage += calc.Combo();
			totalDamage += calc.Combo();

		}
		else {
			totalDamage = calc.Combo();
			totalDamage += calc.CoverUp();
			totalDamage += calc.Kick();
			totalDamage += calc.Punch();
		}

		if (totalDamage > m_lvlUpPoints)
			m_level++;
	}

	void Launch(Player* player1, va_list Players) override {

		Player* l_player = player1;

		unsigned short count = 0;

		while (l_player != nullptr && count < m_maxPlayers) {
			
			auto hours = l_player->Play();
			m_hoursPlayed += hours;
			EvaluateExp(m_level, hours);
			
			count++;
			CheckAchievements(l_player);

			l_player = va_arg(Players, Player*);
		}	
	}
};