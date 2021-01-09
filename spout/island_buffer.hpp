#include "32blit.hpp"

#include "ship.hpp"
#include "particle_node.hpp"
#include "particle_system.hpp"

namespace Game
{
    using namespace blit;

    // Same size as display. 320x240
    class IslandBuffer
    {
    private:
        //           320
        //   .---------------------.
        //   |                     |
        //   |                     |
        //   |                     |  240
        //   |                     |
        //   |                     |
        //   .---------------------.
        //
        //             col  row
        uint8_t buffer[320][240]{};
        Pen colorSet = {0, 0, 0};
        Point p;

    public:
        IslandBuffer();

        void setRow(int y, std::vector<uint8_t> &cols);
        void setPixel(int x, int y);
        void clearPixel(int x, int y);

        void scroll();
        void clear();
        void blit();

        bool collide(Ship &ship);
        bool collide(int x, int y);
        bool collide(ParticleSystem &ps);
        bool collide(std::unique_ptr<ParticleNode> &p);
    };

} // namespace Game