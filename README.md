# 3DEngineCpp

An open-source C++ 3D engine and physics foundation inspired by the educational work of TheBennyBox. The project includes OpenGL rendering, SDL2 window/input handling, Assimp model loading, and a three-shape physics layer for spheres, planes, and AABBs.

The original work is credited to Benny Bobaganoosh. See [LICENSE](LICENSE) and [NOTICE](NOTICE) before redistributing or publishing derivative work.

## What is included

- CMake-based C++ engine build
- OpenGL, GLEW, SDL2, and Assimp integration
- Sphere, plane, and AABB collision detection
- Contact normals, penetration depth, restitution impulses, and static bodies
- RAII-owned physics objects
- Dependency-free physics unit tests
- Scene Foundry browser UI for composing and exporting scene manifests

## Prerequisites

Install CMake 3.10 or newer, a C++11-compatible compiler, GLEW, SDL2, and Assimp.

Ubuntu/Debian:

```sh
sudo apt-get update
sudo apt-get install cmake build-essential libglew-dev libsdl2-dev libassimp-dev
```

macOS with Homebrew:

```sh
brew install cmake glew sdl2 assimp
```

macOS with MacPorts:

```sh
sudo port install cmake glew libsdl2 assimp
```

## Build and run the engine

From the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target 3DEngineCpp
cd build
./3DEngineCpp
```

Run from `build/` so the engine can resolve its relative `res/` asset paths.

## Run tests

```sh
cmake --build build --target physics_unit_tests
ctest --test-dir build --output-on-failure
```

The tests cover vector math, sphere/sphere, sphere/plane, sphere/AABB, plane/AABB, AABB/AABB, collider dispatch, and dynamic/static body motion.

## Scene Foundry

Scene Foundry is a browser-based scene composer in [`tools/scene-builder`](tools/scene-builder). It lets users define gravity, timestep, ambient color, and sphere, plane, or AABB entities. It provides a live preview and downloads a runnable package containing `scene.json`, a standalone preview, Docker configuration, and instructions.

Open locally:

```sh
open tools/scene-builder/index.html
```

Or serve it with Python:

```sh
cd tools/scene-builder
python3 -m http.server 4173
```

Open <http://localhost:4173>.

Run the Scene Foundry container:

```sh
cd tools/scene-builder
docker build -t scene-foundry .
docker run --rm -p 8080:80 scene-foundry
```

Open <http://localhost:8080>.

The exported manifest uses the `3DEngineCpp.scene.v1` format. It is currently a portable scene description; native C++ scene loading is a future integration step.

## Contributing

Contributions are welcome. Please:

1. Create a feature branch.
2. Make focused changes with tests where practical.
3. Run the engine build and `ctest --test-dir build --output-on-failure`.
4. Keep existing copyright and attribution notices.
5. Clearly mark modified files when redistributing derivative work, as required by Apache 2.0 section 4.
6. Open a pull request describing the change and validation performed.

Do not remove or obscure the original Benny Bobaganoosh/TheBennyBox attribution. New contributors may add their own attribution for their modifications, but it must remain alongside the original notices.

## License

This project is distributed under the [Apache License 2.0](LICENSE). It permits anyone to use, copy, modify, publish, distribute, sublicense, and sell copies of the work, subject to the license conditions. Redistributions must include the license and retain the original copyright and attribution notices.

## Credits

- Original engine work: Benny Bobaganoosh / TheBennyBox
- CMake build setup: [mxaddict](https://github.com/mxaddict)
- Additional contributors are listed in project history and may add attribution for their own modifications.
