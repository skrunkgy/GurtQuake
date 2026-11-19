# GurtQuake

GurtQuake is a research project in aims to help create a game of sorts. This is mostly done to learn more about building software, and engines. This will be my first official iteration of a game engine.

It will use OpenGL 4.6, since I found it easier to begin with and can focus more on just managing logic, even at the expense of drive overhead.

## Demo

The test scene when running this build features a scene with a triangle guy (named Bobert) with a tophat attached via parenting. There is also a point light parented to a billboard object, displaying where a light source is coming from. There is also a nice skybox for aesthetic, and a fly cam that the user can control :)
<img width="960" height="540" alt="screenshot" src="https://github.com/user-attachments/assets/b252bafe-181e-4bb8-92f3-2d5d9910cdd8" />

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
