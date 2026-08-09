# Sdl3Tools - An SDL3 C++ wrapper library

This library provides a C++ wrapper for version 3 of the SDL library. It exposes
RAII wrappers for the finite SDL resources - windows, surfaces, the 2D renderer,
2D textures, and the SDL 3 GPU framework - so applications can use SDL from C++
without writing bespoke destructors, error checks, or type juggling.

## Namespaces

- `Ag::SDL3::*` contains the main 2D wrappers: `Window`, `Surface`,
  `LockedSurface`, `Renderer`, `Texture`, `LockedTexture`, `PropertySet`,
  `EventProcessor`, `Initialiser`, `DisplayModeSpec`, `ProgramArguments`,
  `ApiException`.
- `Ag::SDL3::GPU::*` contains the SDL 3 GPU pipeline wrappers: `Device`,
  `Swapchain`, `CommandBuffer`, `RenderPass`, `CopyPass`, `Fence`, `Sampler`,
  `Shader`, `GraphicsPipeline`, `ResourceBuffer`, `TransferBuffer`,
  `TransferMapping`, `Texture`, and the `*Builder` helpers.

Unqualified `Texture` therefore always means the 2D `SDL_Texture` wrapper.
The GPU texture is `Ag::SDL3::GPU::Texture`.

## Class summary

| Class | Wraps |
|-------|-------|
| `Window` | `SDL_Window` |
| `Surface` / `LockedSurface` | `SDL_Surface` |
| `Renderer` | `SDL_Renderer` (2D) |
| `Texture` / `LockedTexture` | `SDL_Texture` (2D) |
| `PropertySet` / `PropertySetLock` | `SDL_PropertiesID` |
| `EventProcessor` | Event pump / dispatch |
| `Initialiser` | `SDL_Init` / `SDL_Quit` |
| `ApiException` | Non-zero SDL error strings |
| `GPU::Device` | `SDL_GPUDevice` |
| `GPU::Swapchain` | Window/GPU swap chain binding |
| `GPU::CommandBuffer`, `RenderPass`, `CopyPass` | Frame command flow |
| `GPU::ResourceBuffer`, `TransferBuffer`, `TransferMapping` | GPU / CPU buffers |
| `GPU::Texture`, `Sampler`, `Shader`, `GraphicsPipeline` | Pipeline resources |
| `GPU::Fence` | GPU synchronisation primitive |

## Wrapper conventions

All wrapper classes in `Ag::SDL3::*` and `Ag::SDL3::GPU::*` follow the same
pattern so a contributor writing another wrapper knows what to produce. New
wrappers should adhere to these rules:

- **Ownership.** A wrapper owns exactly one SDL resource (plus its parent SDL
  pointer when needed to release it). Child wrappers (e.g. `Texture` on
  `SDL_Renderer`, `GPU::Fence` on `SDL_GPUDevice`) store a raw pointer to the
  parent so `release()` can be called without needing the parent wrapper.
- **Default construction.** A default-constructed wrapper is *unbound*. Its
  destructor and `release()` are safe to call.
- **Constructors from raw pointers.** Provide a constructor that takes the raw
  SDL pointer(s). Add an `owned` flag when a non-owning wrap is needed - for
  example `Window::getRenderer()` returns a `Renderer` wrapping the SDL renderer
  without taking ownership, since the window still owns it.
- **Copy semantics.** Copy construction and copy assignment are `= delete`d.
- **Move semantics.** Move construction and move assignment are `noexcept` and
  transfer ownership using `std::exchange`. Move-assign releases any previously
  bound resource first.
- **Destructor.** Calls `release()`; must be safe on an unbound wrapper.
- **`release()`.** Marked `noexcept`; only destroys the underlying SDL resource
  when the wrapper owned it, then clears every field.
- **`isBound()` / `get()`.** `isBound()` returns whether a resource is held.
  `get()` returns the raw SDL pointer (`nullptr` when unbound).
- **`verifyAccess(utf8_cptr_t operation) const`.** Private helper that returns
  the raw pointer, or throws `Ag::ObjectNotBoundException("<Class>", operation)`
  when unbound. Every public method that needs the underlying resource starts
  with `auto p = verifyAccess("...");`.
- **SDL failures.** When an SDL call returns failure, throw
  `Ag::SDL3::ApiException("SDL_FunctionName()")`. Do not swallow errors, except
  inside `release()` (which is `noexcept` and cannot throw from a destructor).
- **Companion "Locked" wrappers.** Resources that expose a locked view (e.g.
  `SDL_Surface`, streaming `SDL_Texture`) get a matching `Locked*` class that
  handles the corresponding `SDL_Unlock*` call in its destructor.

## Example: Window -> Renderer -> Texture

```cpp
#include <Ag/Sdl3Tools.hpp>

using namespace Ag::SDL3;

Initialiser init(SDL_INIT_VIDEO);

Window window;
window.create("Demo", 800, 600, 0);

Renderer renderer = window.createRenderer();

Surface bmp = Surface::loadBMP("hero.bmp");
Texture hero;
hero.createFromSurface(renderer, bmp);

renderer.setDrawColor(0, 0, 0);
renderer.clear();
renderer.drawTexture(hero, nullptr, nullptr);
renderer.present();
```

## Example: fill and blit a surface

```cpp
Surface canvas;
canvas.create(320, 240, SDL_PIXELFORMAT_RGBA32);
canvas.clear({0.1f, 0.1f, 0.15f, 1.0f});

SDL_Rect box{10, 10, 40, 40};
auto details = SDL_GetPixelFormatDetails(canvas.getFormat());
canvas.fillRect(&box, SDL_MapRGBA(details, nullptr, 255, 0, 0, 255));

canvas.blit(nullptr, window.getSurface(), nullptr);
window.updateSurface();
```

## Exceptions

- `Ag::ObjectNotBoundException` (from `Ag::Core`) - thrown by every wrapper
  method that requires a bound resource.
- `Ag::ArgumentException` - thrown for out-of-range arguments (e.g.
  `LockedSurface::getRow` with a row past the surface height).
- `Ag::OperationException` - thrown when an operation is invalid for the current
  wrapper state (e.g. `Texture::lock()` on a non-streaming texture).
- `Ag::SDL3::ApiException` - thrown when an SDL C function reports failure. The
  message names the failed function and captures `SDL_GetError()` at the time
  of the failure.

```cpp
try
{
    renderer.setLogicalPresentation(1920, 1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}
catch (const Ag::SDL3::ApiException &ex)
{
    Ag::Log::error("Renderer setup failed: {}", ex.what());
}
```

## Program arguments

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

`ProgramArguments::tryCreatePreferredRenderer(const Window &, Renderer &)`
consumes `--sdl_driver_name` and constructs an owning `Ag::SDL3::Renderer` for
the supplied window.

## Testing

The `Sdl3Tools_Tests` gtest binary uses a shared
`Ag::SDL3::SdlVideoFixture` (in `Source/Sdl3Tools/SdlVideoFixture.hpp`) that
initialises `SDL_INIT_VIDEO` once per test suite. Tests that need the video
subsystem derive from that fixture; if `SDL_InitSubSystem` fails, each such
test is skipped with `GTEST_SKIP` so headless CI runners produce no failures.
Set `SDL_VIDEO_DRIVER=dummy` before invoking the test binary on machines
without a display server.
