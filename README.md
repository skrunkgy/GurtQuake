# GurtQuake

GurtQuake is a research project in aims to help create a game of sorts. This is mostly done to learn more about building software, and engines. This will be my first official iteration of a game engine.

It will use OpenGL 4.6, since I found it easier to begin with and can focus more on just managing logic, even at the expense of drive overhead.

## Building

The project uses a Makefile. The project requires the following libraries:
- SDL3
- SDL3_image
- glbinding

In order to build, use GNU's `make` command. Optionally, use `bear` to generate a `compile_commands.json` for clangd, for anyone who wants to develop:
`bear -- make`
The generated file will be in `build/gquake`.

## Wayland

Wayland does not support bit streaming to the compositor (or something like that), so a .desktop file is provided in the resources folder for anyone interested.
