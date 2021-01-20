#include "32blit.hpp"

using namespace blit;

#include "../game/parameter.hpp"
#include "island_buffer.hpp"
#include "island.hpp"

namespace Game
{
    class IsLands
    {
    private:
        std::list<IsLand> islands;

    public:
        IsLands() = default;

        void update(uint32_t time, IslandBuffer& buffer);

        void reset(int seed);

        void render();
    };

} // namespace Game