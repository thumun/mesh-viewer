# mesh-viewer

Implements a simple PLY viewer

![cupofspace](https://github.com/thumun/mesh-viewer/blob/main/images/cup-noshader.png)

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ start mesh-viewer.sln
```

Your solution file should contain two projects: `mesh-viewer` and `test-ply-mesh`.
To run from the git bash command shell, 

```
mesh-viewer/build $ ../bin/Debug/test-ply-mesh.exe
mesh-viewer/build $ ../bin/Debug/mesh-viewer.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ make
```

To run each program from build, you would type

```
mesh-viewer/build $ ../bin/mesh-viewer
```

## Demo of basic features

Can cycle through the models using 'n' or 'N' (to go back). 

[insert]

Can cycle through shaders using 's' or 'S' (to go back). 

Normals shader: 

Phong-vertex shader: 

Phong-pixel shader: 

## Unique features 

Toon Shader: 

Textures: 
Can cycle through textures using 't' or 'T' (to go back). 
These textures are tiled (if the model is too big.) 

Added personal model of original character: 
