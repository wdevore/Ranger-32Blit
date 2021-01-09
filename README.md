# Ranger-32Blit

## Notes
When the game round first starts about a third of the display is pre-scrolled into view.

```

    .                                        .
    |                                        |
    |                                        |
    |                                        |
    |                                        |
    |                                        |
    |                                        |
    |         To be populated  (B)           |        Off Screen
    |                                        |
    |                                        |        "N" rows
    |         Ready for screen (A)           |
    .----------------------------------------.
    |                                        |
    |                                        |        Initially this top portion is populated.
    |                                        |
    |                                        |
    |                                        |
    |________________________________________|        <-- scroll line
    |                                        |        
    |                                        |
    |                                        |
    |                                        |        On Screen
    |                                        |
    |                                        |
    |                                        |
    .----------------------------------------.

```

## Algorithm 1
As each line enters the screen the next line is built.

Each line is a continuation of a growing shape. The shape is defined first. It is a polygon shape formed from horizontal lines. Similar to filling a triangle.

A line intersection is used to find the left and right side end points. These end points are used to fill the array.
First a bbox is created. Then a set of random points are generated. These points are the vertices of the polygon and are order ccw.

The end points are used to get the edge intersections. They are round-up for the left side and rounded-down for the right side.

## Algorithm 2
This one is simpler but produces shapes that are either more uniform or erratic.

Two random points are generated on the current line. The end points are driven by a fractal terrain algorithm. The vertical ends are left flat.

The fractal algorithm uses the subdivision method.

## Algorithm 3 (implemented)
A render-time value is randomly generated. This value is how many rows must pass before rendering of the shape begins. It basically represents a delay before the shape start appearing on the screen.

A bounding box is generated. The box represents the height of the shape and the min/max end points. As the shape is generated the bbox controls the extents. First a horizontal center point is generated, then a height and width.

A line is created for each row. A line has three points: *Left*, *Right* and *Center*. The line has a width and the values varying in size within a time range.

Most of the time the Line changes shape and position slowly, but occasionally it can accelerate. Only one of the points can change rapidly at any one time.

Each line has a width and center position on the current row. At the beginning and ending of the bbox the line shortens 50% of the time.

### Line Parameters:
--How long a parameter remains at its current value.

Rate, Duration, Gap, Range

* ShiftRate: How fast the line shifts Left or Right
* ShiftDuration: How long the line is allowed to shift. -1 = No shift
* ShiftGap: How long between and changes
* ShiftRange: How far, in either direction, shifting can go. Reletive to center.
* LeftPointRate: How fast the end point shifts
* LeftPointDuration: How long the point is allowed to shift.
* LeftGap: How long between and changes
* LeftRange: How far, in either direction = Min/Max
* RightPointRate: How fast the end point shifts
* RightPointDuration: How long the point is allowed to shift.
* RightGap: How long between and changes
* RightRange: How far, in either direction

The end points shift rarely. The line shifts a bit more often. The Gap between shifts is moderate.



# Building
If you want to build a version for the device then specify a toolchain, which in this case is **32blit.toolchain**.
```
> cmake . -D32BLIT_PATH="../../32blit-beta" -DCMAKE_TOOLCHAIN_FILE="../../32blit-beta/32blit.toolchain"
```

If you want to build a desktop version just leave off the toolchain. This will configure a **make** build system so you can compile the code.
```
> cmake . -D32BLIT_PATH="../../32blit-beta"
```
Now you can run make to compile.

```
> make
OR
> make -j4; spout
```

# Example CMakeLists.txt(s)
```
cmake_minimum_required(VERSION 3.8)
project (als)
set(32BLIT_PATH "../32blit-beta/" CACHE PATH "Path to 32blit.cmake")
include (${32BLIT_PATH}/32blit.cmake)
blit_executable (als als.cpp als.hpp)
blit_assets_yaml (als assets.yml)
blit_metadata (als metadata.yml)
```

This Doom CMakeLists.txt shows an advance usage:
https://github.com/Daft-Freak/32BlitDoom/blob/master/CMakeLists.txt


This CmakeList has interesting checks in it, include debug stuff, uses ${PROJECT_NAME}
https://github.com/Daft-Freak/32blit-mjpeg-player/blob/master/CMakeLists.txt
