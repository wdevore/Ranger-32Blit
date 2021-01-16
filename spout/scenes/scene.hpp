#pragma once

#include "../game/game.hpp"

namespace Game
{
    class Scene
    {
    protected:
        std::string name;
        uint32_t duration = 0; // How long to stay on the stage.
        uint32_t durationCnt = 0;

        // Dispose=true then dispose of Scene when it is finished.
        bool disposeOnExit = true;

        SceneState state = {SceneState::OffStage};

    public:
        Scene(std::string name);

        virtual void update(uint32_t time) = 0;
        virtual void render();

        virtual void enterScene();
        virtual void exitScene();
        virtual std::string nextScene();

        std::string Name();

        bool shouldDispose();
        SceneState CurrentState();

        virtual std::string toString();
    };

} // namespace Game