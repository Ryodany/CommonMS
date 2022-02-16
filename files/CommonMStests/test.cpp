#include "pch.h"
#include "../library.h"
#include "../player.h"
#include "../games.h"

struct LibraryTest : testing::Test {
    Library* library;

    LibraryTest() {
        library = new Library();
    }
    ~LibraryTest() {
        delete library;
    }
};

TEST_F(LibraryTest, CanAddGames) {

    FightGame game1 = FightGame("Tekken 7\0");
    FightGame game2 = FightGame("Dragon Ball FighterZ\0");
    FightGame game3 = FightGame("Mortal Kombat X\0");

    library->Push(&game1);
    library->Push(&game2);
    library->Push(&game3);

    EXPECT_EQ(3, library->Size());
};

TEST_F(LibraryTest, CanFindGameId) {

    FightGame game1 = FightGame("Tekken 7\0");
    FightGame game2 = FightGame("Dragon Ball FighterZ\0");
    FightGame game3 = FightGame("Mortal Kombat X\0");

    library->Push(&game1);
    library->Push(&game2);

    unsigned int gameId;
    bool found = library->GetGameId(&game2, gameId);
    bool found2 = library->GetGameId(&game3, gameId);

    EXPECT_EQ(true, found);
    EXPECT_EQ(false, found2);
}