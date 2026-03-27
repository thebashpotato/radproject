# radproject 

A simple templated project for C programmers (on Linux and BSD) who are tired of using their toolchains through bloated 
blackbox build systems like CMake that make you to learn their `shitty domain specific language` just to do something
trivial like compile and link and take forever to do it.

## Contents

> This repo is only trying to provide two things, both things are meant to be as small and simple as possible whilst
> providing functionality you or your LLM would code anyway, extending it and molding it to your project is the point.

1. `build scripts` - *build.py* and the `bs/` module provide basic functions and simple data-structures so you can
    compile executables, libraries and unit tests. Uses pkg-config for system libraries.

2. `utest` - The simplest unit test header you've ever seen.
    


## Building

The project uses a custom Python build system. Requires `clang` (or `gcc`), `ar`, and `pkgconf` to be installed.

```sh
python build.py
```

This compiles all libraries and executables into the `build/` directory with release optimizations (`-O3`). A `build/compile_commands.json` is generated for editor/LSP integration.

### Options

| Flag | Description |
|---|---|
| `--debug` | Build with debug symbols (`-g3`), no optimization (`-O0`), and sanitizers (ASan, UBSan, leak) |
| `--gcc` | Use gcc for compilation instead of clang |
| `--tests` | Build and run unit tests |

### Examples

```sh
# Debug build with sanitizers
python build.py --debug

# Debug build using gcc
python build.py --debug --gcc

# Build and run tests
python build.py --tests
```

### Build output

- `build/radproject` -- main executable
- `build/libfake.a` -- fake static library
- `build/compile_commands.json` -- compilation database for LSP

The `build/` directory is fully rebuilt from scratch on each invocation.

## Adding to the build

All build configuration lives in `build.py`.

### Adding a static library

Add an entry to the `LIBRARIES` list:

```python
{
    "name": "mylib",
    "sources": ["src/mylib/foo.c", "src/mylib/bar.c"],
    "include_dirs": ["src/mylib"],
},
```

This compiles each source to an object file, then archives them into `build/libmylib.a`. The `include_dirs` are passed as `-I` flags when compiling the library itself and any target that depends on it.

### Adding an executable

Add an entry to the `TARGETS` list (or `TEST_TARGETS` for test binaries):

```python
{
    "name": "mytool",
    "sources": ["src/mytool/main.c"],
    "packages": ["libpng"],
    "ldflags": ["-lm"],
    "libs": ["mylib"],
},
```

| Field | Purpose |
|---|---|
| `name` | Output binary name (placed in `build/`) |
| `sources` | List of `.c` files to compile |
| `packages` | `pkgconf` package names -- cflags and ldflags are resolved automatically |
| `ldflags` | Additional linker flags |
| `libs` | Names of libraries from `LIBRARIES` to link against (adds include flags and archives) |

Libraries are always built before executables, so any library listed in `libs` will be available at link time.
