#pragma once

namespace Game
{
    enum class State
    {
        Boot,      // Misc
        Splash,    // Hello
        Menu,      // Play, Scores, Settings, Quit
        EnterPlay, // Prep game
        Play,      // Playing the game
        ExitPlay,  // Player died
        PlayAgain,
        Exit // Exit back to 32Blit menu
    };
} // namespace Game
