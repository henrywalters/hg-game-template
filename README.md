# HG Game Template

This template provides a minimal working setup for the HaGameEngine. It includes the 
ability to run headless as well as in the web using Emscripten.

## Installation

As this is meant to use a development version of HaGame, you must first clone the repository.

``git clone git@github.com:henrywalters/HaGameLite.git``

And then update the line in ``cmake/FindHaGame2.cmake`` with the path you cloned it to:

```cmake
set(
        FIND_HAGAME2_PATHS
        /home/dev/path-to-hagamelite
)
```

## Building

To build for desktop, it is sufficient to run:

```bash
cmake .
make
```

To build for web:

```bash
cd public
emcmake cmake .
make
```
