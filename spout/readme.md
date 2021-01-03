# Spout
See parent [readme.md](../readme.md) for specific *build* instructions.

Spout is a simple game where you attempt to rocket as *high* as you can in the shortest amount of time.

The ship is a simple circle with a stick for the engine. Thrust particles interact with the *walls* and *obstacles*.

# Build
```
> make; spout
```

# Tasks
* Draw ship (solid circle) and engine (line) points in opposite direction of movement.
* Fly ship around using a velocity vector.
* Gravity pulls ship to floor.

* Particle system
* Collisions
  * Particles to walls (bounces off)
  * Ship to walls (touches explodes)
  * Ship to obstacles (touches explodes)
* Ship Rotation

# Notes

