# Spout
See parent [readme.md](../readme.md) for specific *build* instructions.

Spout is a simple game where you attempt to rocket as *high* as you can in the shortest amount of time.

The ship is a simple circle with a stick for the engine. Thrust particles interact with the *walls* and *obstacles*.

![Spout Gif](https://github.com/wdevore/Ranger-32Blit/blob/main/spout/spout%200.1.1.gif)


# Build
```
> make -j8; spout
```

# Tasks
* **Done** Draw ship (solid circle) and engine (line) points in opposite direction of movement.
* **Done** Fly ship around using a velocity vector.
* **Done** Gravity pulls ship to floor.
* **Done** Particle system
* **Done** Collisions. Upon death show dialog to "Play again" or "Not".
  * **Done** Particles to walls (bounces off)
  * **Done** Ship to floor (touches explodes)
  * **Done** Ship to obstacles (touches explodes)
* **Done** Ship Rotation
* Score and Altitude info bar
* Waypoint marker lines every N-pixels. A max bonus of 100 if making to waypoint under a specific time range.
* Islands
  * **1st draft** Scrolling
  * Value Targets/Mines. They are like islands in that they are added to the buffer. When collided a bonus is given to the player. The mine then explodes.
    * Starts small and swells and explodes.
    * Plain
  * (*Optional*) Simple vertical chaser appears at random.
* Menu system
  * Animation transitions
* Scenes
  * **Done** Boot
  * **Done** Splash
  * **Done** Exit
  * **In progress** Menu
  * Game scene
    * Start game. Initial islands scroll into view.
  * Score board scene
  * **Done** About scene

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

