# Gfx2D

This library is intended to provide a high-level retained mode graphic API
inspired by the WPF `System.Windows.Media` structure. It allows callers to
define graphic artefacts and geometry and then decomposes them into base
graphic primitives compatible with GPU rendering.

The further intention is for other libraries to implement the GPU rendering
back-end, such as with OpenGL or the SDL3 GPU module. Also, there should be
a plug-in implementation for the production of font data which can also be
decomposed by this library into base primitives for rendering.

This library is a work-in-progress. It is based on the [Geometry](Geometry.md)
and and [Core](Core.md) Ag libraries, and should be agnostic of any components
which implement actual rendering.

Basic graphic rendering is defined in terms of fill styles in the form of
`Brush` instances, line styles in the form of `Pen` instances, and geometry
which can be filled and/or outlined, expressed by `Path` instances. There is an
intention to be able to animate graphics, thus `Brush` and `Pen` definitions
have an immutable 'frozen' state. Geometry primitives will need higher-level
definitions in order to implement this.

Both Brushes and Pens are underpinned by `Colour` values which represent RGB
colours with an alpha channel for transparency. 32-bit floating point values are
used to represent each channel

The expectation is that the high level primitives of a 2D scene graph will be
cloned into an immutable state for another thread to render. The rendering
thread will retain an instance of `DecompositionContext` which will manage and
re-use resources used to process, clip, combine and decompose elements of the
scene graph into collections of triangles to be encoded as vertex/index buffers for GPU rendering by a plug-in back end.