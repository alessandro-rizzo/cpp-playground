set shell := ["zsh", "-cu"]

default: dev

conf-dev:
    cmake --preset dev

conf-release:
    cmake --preset release

build-dev:
    cmake --build --preset dev

build-release:
    cmake --build --preset release

run-dev:
    ./build/dev/hello

run-release:
    ./build/release/hello

dev:
    just conf-dev
    just build-dev
    just run-dev

release:
    just conf-release
    just build-release
    just run-release

clean:
    rm -rf build