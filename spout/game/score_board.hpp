#pragma once

#include "../game/defines.hpp"

namespace Game
{
    class ScoreBoard
    {
    private:
        GameSave gameSave;

    public:
        ScoreBoard() = default;

        void load();
        void save();

        GameScore &score(int index);

        int rankPlayer(int altitude);
        void setScore(int rank, char initials[3], int altitude, int score, int time);
        void reset();

        std::string toString();
    };

} // namespace Game