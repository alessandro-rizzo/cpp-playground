set shell := ["zsh", "-cu"]

# Default: show available commands
default:
    @just --list

# Configure dev build
conf-dev:
    cmake --preset dev

# Configure release build
conf-release:
    cmake --preset release

# Build all targets (dev)
build-all:
    cmake --build --preset dev

# Build all targets (release)
build-all-release:
    cmake --build --preset release

# Build specific chapter (dev) - usage: just build 1
build chapter:
    cmake --build --preset dev --target cp{{chapter}}

# Build specific chapter (release)
build-r chapter:
    cmake --build --preset release --target cp{{chapter}}

# Run specific chapter (dev)
run chapter:
    ./build/dev/cp{{chapter}}

# Run specific chapter (release)
run-r chapter:
    ./build/release/cp{{chapter}}

# Build and run specific chapter (dev) - usage: just cp 1
cp chapter: conf-dev (build chapter) (run chapter)

# Build and run specific chapter (release) - usage: just cpr 2
cpr chapter: conf-release (build-r chapter) (run-r chapter)

# Build all in dev mode
dev: conf-dev build-all

# Build all in release mode
release: conf-release build-all-release

# Clean build directory
clean:
    rm -rf build

# Format all C++ files
format:
    find . -name "*.cpp" -o -name "*.hpp" -o -name "*.h" | xargs clang-format -i