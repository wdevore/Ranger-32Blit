#include "32blit.hpp"

using namespace blit;

#include "../game/parameter.hpp"
#include "island_buffer.hpp"
#include "../game/mine.hpp"

namespace Game
{
    class Mines
    {
    private:
        std::list<std::unique_ptr<Mine>> mines;

    public:
        Mines() = default;

        void update(uint32_t time, IslandBuffer& buffer);

        void addMine(std::unique_ptr<Mine> mine);

        void render();
    };

} // namespace Game