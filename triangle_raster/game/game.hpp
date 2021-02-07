#pragma once

namespace Game
{
    enum class State
    {
        Boot,      // Misc
        Splash,    // Hello
        Menu,      // Play, Scores, Settings, Quit
        Selected,  // Marker selection
        EnterPlay, // Prep game
        Play,      // Playing the game
        ExitPlay,  // Player died
        Continue,
        PlayAgain,
        Ranking, // Allows player to enter initials
        Scores,
        About,
        Reset,
        Exit // Exit back to 32Blit menu
    };

    enum class SceneState
    {
        OffStage,
        Enter,
        Exit,
        OnStage
    };
} // namespace Game
