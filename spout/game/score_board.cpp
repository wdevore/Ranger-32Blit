#include <iostream>
#include <sstream>

#include "engine/api_private.hpp"

#include "score_board.hpp"

namespace Game
{
    using namespace blit;

    void ScoreBoard::load()
    {
        bool loaded = read_save(gameSave);
        if (loaded)
        {
            std::cout << "Loading scores from: '" << api.get_save_path() << "'" << std::endl;
            // std::cout << "ScoreBoard::load Game scores loaded" << std::endl;
        }
        else
        {
            std::cout << "No Scores present on disc. Creating defaults." << std::endl;
            reset();
        }
    }

    void ScoreBoard::save()
    {
        write_save(gameSave);
    }

    void ScoreBoard::reset()
    {
        // Setup some defaults
        //                      initials       alt|score|time
        gameSave.scores[0] = {{'t', 'n', 'k'}, 1000, 200, 10};
        gameSave.scores[1] = {{'w', 'r', 'c'}, 750, 100, 5};
        gameSave.scores[2] = {{'b', 'l', 't'}, 500, 50, 3};
        gameSave.scores[3] = {{'r', 'a', 's'}, 200, 25, 2};
        gameSave.scores[4] = {{' ', 'm', 'e'}, 100, 10, 1};

        save();
    }

    GameScore &ScoreBoard::score(int index)
    {
        return gameSave.scores[index];
    }

    int ScoreBoard::rankPlayer(int altitude)
    {
        // Scan board to see if altitude ranked.
        // To rank means altitude must exceed the one of the altitude values.
        // The incoming altitude is "walked" upwards until it either
        // reaches the top or stops.
        // The scores are always sorted.
        int rank = 0;
        int size = sizeof(gameSave.scores) / sizeof(gameSave.scores[0]);

        for (int i = 0; i < size; i++)
        {
            GameScore &gs = gameSave.scores[i];
            if (altitude > gs.altitude)
            {
                // Try next higher score
                rank++;
                continue;
            }
        }

        return rank;
    }

    void ScoreBoard::setScore(int rank, char initials[3], int altitude, int score, int time)
    {
        if (rank > 0)
        {
            int size = sizeof(gameSave.scores) / sizeof(gameSave.scores[0]);
            GameScore &gs = gameSave.scores[size - rank];
            gs.initials[0] = initials[0];
            gs.initials[1] = initials[1];
            gs.initials[2] = initials[2];
            gs.altitude = altitude;
            gs.score = score;
            gs.time = time;
        }
    }

    std::string ScoreBoard::toString()
    {
        int size = sizeof(gameSave.scores) / sizeof(gameSave.scores[0]);
        std::stringstream ss;

        for (int i = 0; i < size; i++)
        {
            GameScore &gs = gameSave.scores[i];
            ss << "'" << gs.initials[0] << gs.initials[1] << gs.initials[2] << "', " << gs.altitude << ", " << gs.score << ", " << gs.time << std::endl;
        }

        return ss.str();
    }

} // namespace Game
