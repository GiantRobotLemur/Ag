# Geometry - A 2-Dimensional Geometry Library
---
The `Geometry` library contains 2D geometry utilities which use double-precisions
floating point values. Its intent is to provide the mathematical underpinning for
a high-level 2D graphics library which can render using GPU-accelerated means.

The most important tool in the library is the ability to partition polygons into
triangles. This is done using the plane sweep algorithm as described in
Computational Geometry : Algorithms and Applications by de Berg et al. The
library implements the doubley-connected edge list `DCEL` in order to realise
the algorithm, which has an O(n log n) complexity. The implementation of the
plane sweep algorithm is sound, but the polygon tracing algorithm used afterwards
still has a few kinks.

In addition, the algorithm does not produce 'strict' Y-monotone polygons as it
can add horizontal edges, the results may not be a set of strictly Y-monotone
polygons.

Half of the intent of the algorithm is to be able to render text, one glyph at a
time, by extracting the geometry from a font definition and decomposing each
glyph into triangles. To that end, I also created the `WriteGlyphGeometry` tool.

`WriteGlyphGeometry` is a command line tool which takes a list of glyphs to
extract and creates a file of C++ literal data defining the outline geometry.
It uses Windows GDI for the extraction, which means it is a Windows-only process.
However, the data extracted is embedded in the unit test for the Geometry
library. It's surprising how many edge cases glyphs expose with the partitioning
algorithm.

A CMake command, `embed_glyph_geometry()` has been created which uses
`WriteGlyphGeometry` to either extract geometry and story a backup in the source
tree on Win32 platforms, or copy the backup to the build folder on non-Windows
platforms. This will allow units test to operate on any platform.

## Future

I hope to extend the library to perform low-complexity line intersection by plane
sweep in order to implement the algorithms necessary to create a drawing context
that will record graphic commands to vertex buffers which can be rendered by GPU
commands.