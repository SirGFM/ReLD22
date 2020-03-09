# ReLoneliness

Late 2013 C++ port of my Ludum Dare 22 entry... It is bad! This was
written back when I didn't know any C++, so beware...

This is only here for preservation purposes and because it's one of the few
instances when I did actually write a somewhat interesting fragment shader
(for altering the images RGB levels).

## Dependencies

* OpenGL Extension Wrangler (libglew)
* OpenGL Utility Toolkit (freeglut3-dev, maybe?)
* SDL 1.2 (libsdl1.2)

## Troubleshooting

### `Error initializing SDL: No available video device.`

If you get the error above, download a pre-compiled
[SDL 1.2 from their website](https://www.libsdl.org/download-1.2.php) and
use that version when running the game (e.g., using `LD_LIBRARY_PATH`).
