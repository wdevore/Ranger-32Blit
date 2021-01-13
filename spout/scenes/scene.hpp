#pragma once

namespace Game
{
    class Scene
    {
    protected:
        std::string name;
        uint32_t duration = 0;  // How long to stay on the stage.
        uint32_t duractionCnt = 0;

        // Dispose=true then dispose of Scene when it is finished.
        bool disposeOnExit = true;

    public:
        Scene(std::string name);

        virtual void init() = 0;
        virtual bool update(uint32_t time);
        virtual void render();

        std::string Name();
        
        bool shouldDispose();
        
        virtual std::string toString();
    };

} // namespace Game