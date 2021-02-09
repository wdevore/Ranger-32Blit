# Triangle rasterizer
See parent [readme.md](../readme.md) for specific *build* instructions.

# Build
```
> make -j8; spout
```

## Notes
Main raster algorithm is based off of: http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html . I use the Brensenham Algorithm

More in depth on Brensenham's algorithm: http://www.sunshine2k.de/java.html#bresenham
including polygon filling and triangulation.

https://gitlab.com/-/snippets/2003119  Uses DDA algorithm.

See: [Pi Pico doc](https://docs.google.com/document/d/1cZ1SoJEQiRYRTMabbcxu4UpSiumvRVuCsX-yhIqjgek/edit)
for more links for rasterization
