# Sdl3Tools - An SDL3 C++ wrapper library

This library provides a C++ wrapper for version 3 of the SDL library.
The library provides classes which manage finite SDL resources such as Windows
Surfaces and GPU elements. A lot of work has been put into wrapping the GPU
framework which is new to this version of the library.

The `Ag::SDL3::ProgramArguments` is a subclass of `Ag::Cli::ProgramArguments`
which implements a number of useful standard command line arguments and even a
few useful commands for enumerating the SDL 3 drivers and entities available. It
can be derived from to define command line arguments for an application which
include some useful for configuring the use of SDL. Further functions consume the
command line options in order to instantiate named devices or find specified
entities.

The SDL-specific command line arguments are:
- --sdl_list `object type`
    - Where `object type` can be one of `System`, `VideoDrivers`, `RenderDrivers`, `GPUDrivers` or `Displays`
    - The list of available object types of properties will be listed to the console.
- --sdl_display_name `display name`
    - Specifies the name of a display which the class can used to obtain an `SDL_DisplayID` value
- --sdl_display_mode `mode spec`
    - Where `mode spec` takes the form `width x height[@bpp][:refresh rate]`
    - For example: `640x480@32` for a resolution of 640 x 480 pixels at 32 bits per pixel
    - Or `1920x1080:120` for HD resolution at 120 Hz refresh rate.
    - Or `1024x768@24:75` for a resolution of 1024 x 768 pixels, 24 bits per pixel and 75 Hz refresh rate.
    - Or `1600x1200` for a resolution of 1600 x 1200 pixels, the highest colour bit depth and default refresh rate.
    - The value specified can be used to obtain an SDL_DisplayMode structure.
- --sdl_driver_name `driver name`
    - Sets the name of a driver which can be used in creating a 2D renderer or GPU pipeline.