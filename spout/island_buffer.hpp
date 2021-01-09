#include "32blit.hpp"

//           320
//   .---------------------.
//   |                     |
//   |                     |
//   |                     |  240
//   |                     |
//   |                     |
//   .---------------------.
namespace Game
{
    using namespace blit;

    // Same size as display. 320x240
    class IslandBuffer
    {
    private:
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
    };

} // namespace Game