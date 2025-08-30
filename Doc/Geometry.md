# Geometry - A 2-Dimensional Geometry Library

The `Geometry` library contains 2D geometry utilities based on double-precisions
floating point values. Its intent is to provide the mathematical underpinning for
a high-level 2D graphics library that can render using GPU-accelerated means.

The most important tool in the library is the ability to partition polygons into
triangles. This is done using the plane sweep algorithm as described in the book
`Computational Geometry : Algorithms and Applications by de Berg et al`. The
library implements the doubley-connected edge list (`DCEL`) data structure in
order to realise the algorithm, which has an O(n log n) complexity. The
implementation of the plane sweep algorithm handles edges cases, despite the
vagueness of the description.

In addition, the algorithm does not produce 'strict' Y-monotone polygons as it
can add horizontal edges. However, while the results may not be a set of
strictly Y-monotone polygons, they can still be partitioned into triangles
despite that.

Half of the intent of the library is to be able to process arbitrary geometry
into fillable shapes, including proper processing of holes, either explicitly
defined or degenerating from co-linear line segments. This has been
achieved by implemented the O(n log n) plane sweep line intersection algorithm
from `Computational Geometry` in addition to a polygon tracing algorithm which
operates on a set of connected line segments.

The other half of the intent is to be able to render text, one glyph at a
time, by extracting the geometry from a font definition and decomposing each
glyph into triangles. To that end, I also created the `WriteGlyphGeometry` tool.

Text output could be optimised using the Distance Field method. The algorithms
contained in the library would still be necessary in order to generate the
textures which cache glyphs ready for sampling.

`WriteGlyphGeometry` is a command line tool which takes a list of glyphs to
extract and creates a file of C++ literal data defining the outline geometry.
It uses Windows GDI for the extraction, which means it is a Windows-only process.
However, the data extracted is embedded in the unit tests for the Geometry
library. It's surprising how many edge cases glyphs expose with the partitioning
algorithm.

A CMake command, `embed_glyph_geometry()` has been created which uses
`WriteGlyphGeometry` to either extract geometry and store a backup in the source
tree on Win32 platforms, or copy the backup to the build folder on non-Win32
platforms. This will allow units test to operate on any platform.

## Future

I hope to extend the library to implement primitives for various kinds of
curves which could be useful for managing geometry for graphic rendering.