# Use zsh (macOS default)
set shell := ["zsh", "-cu"]

# Default recipe (runs if you just type `just`)
default: dev

# --------
# Configure
# --------
conf-dev:
    cmake --preset dev

conf-release:
    cmake --preset release

# ------
# Build
# ------
build-dev:
    cmake --build --preset dev

build-release:
    cmake --build --preset release

# ---
# Run
# ---
run-dev:
    ./build/dev/hello

run-release:
    ./build/release/hello

# ----------------
# Combined targets
# ----------------
dev:
    just conf-dev
    just build-dev
    just run-dev

release:
    just conf-release
    just build-release
    just run-release

# --------
# Utility
# --------
clean:
    rm -rf build