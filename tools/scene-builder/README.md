# Scene Foundry

Scene Foundry is a browser-based scene composer for the 3DEngineCpp project. It creates a portable `3DEngineCpp.scene.v1` manifest and a runnable preview package.

## Run locally

Open `index.html` in a browser.

## Run with Docker

From this directory:

```sh
docker build -t scene-foundry .
docker run --rm -p 8080:80 scene-foundry
```

Open <http://localhost:8080>.

## Exported package

The download contains:

- `scene.json`: physics and entity data
- `index.html`: standalone browser preview
- `Dockerfile`: container configuration for the preview
- `README.md`: package-specific run instructions

The manifest is intentionally separate from the legacy renderer. The next integration step is a C++ scene loader that maps this schema to `Entity`, `PhysicsObject`, and collider instances.
