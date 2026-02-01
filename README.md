# C++ Playground

A learning repository for C++ exercises and examples, organized by chapters. Features **automatic build configuration** - just create a new `cpX.cpp` file and it's ready to compile!

## Project Structure

```
cpp-playground/
├── src/
│   ├── cp1.cpp    # Chapter 1 exercises
│   ├── cp2.cpp    # Chapter 2 exercises
│   └── ...        # Add more chapters (auto-detected!)
├── docs/          # Study materials and notes
├── CMakeLists.txt # Build configuration (auto-detects cpX.cpp files)
├── justfile       # Task runner commands
└── README.md      # This file
```

## Key Features

✅ **Auto-detection**: Create `cpX.cpp` and it's automatically buildable - no config changes needed
✅ **Cross-platform**: Works seamlessly on macOS and Linux (Ubuntu)
✅ **Parametrized**: Single command works for any chapter number
✅ **Multiple build modes**: Debug (with sanitizers) and Release (optimized)

## Quick Start

### Using Just (Recommended)

```bash
# Build and run any chapter in debug mode
just cp 1
just cp 2
just cp <N>

# Release mode (optimized)
just cpr 1
just cpr 2

# See all available commands
just
```

### Using CMake Directly

```bash
# Configure
cmake --preset dev

# Build specific chapter
cmake --build --preset dev --target cp1

# Run
./build/dev/cp1
```

## Adding New Chapters

The build system automatically detects all `src/cp*.cpp` files. Just create a new file and run it:

```bash
# Step 1: Create new chapter file
touch src/cp3.cpp

# Step 2: Add your code with a main() function
cat > src/cp3.cpp << 'EOF'
#include <iostream>

int main() {
    std::cout << "Chapter 3\n";
    return 0;
}
EOF

# Step 3: Build and run - that's it!
just cp 3
```

**No configuration files need to be modified!** The CMake setup automatically:
- Detects new `cpX.cpp` files
- Creates build targets
- Makes them available to all commands

You can create `cp1.cpp`, `cp2.cpp`, `cp100.cpp` - any number works!

## Available Commands

### Most Common
```bash
just cp <N>       # Build and run chapter N (debug mode)
just cpr <N>      # Build and run chapter N (release mode)
just clean        # Clean build directory and start fresh
```

### Build Only (Don't Run)
```bash
just build <N>    # Build chapter N only (debug)
just build-r <N>  # Build chapter N only (release)
just dev          # Build all chapters (debug)
just release      # Build all chapters (release)
```

### Run Only (Must Build First)
```bash
just run <N>      # Run chapter N (debug)
just run-r <N>    # Run chapter N (release)
```

### Utilities
```bash
just              # List all available commands
just format       # Format all C++ files with clang-format
```

## Build Modes

### Debug Mode (Default)
- Uses `-fsanitize=address,undefined` for memory error detection
- Includes debug symbols for better debugging
- Slower but catches bugs early
- **Commands**: `just cp <N>`, `just build <N>`, `just dev`

### Release Mode
- Full optimizations enabled
- No sanitizers (faster execution)
- Best for performance testing
- **Commands**: `just cpr <N>`, `just build-r <N>`, `just release`

## Cross-Platform Support

Works seamlessly on both **macOS** and **Linux (Ubuntu)**:

| Platform | Linker | Notes |
|----------|--------|-------|
| **macOS** | System default | Works out of the box |
| **Linux** | mold (if available) | Faster linking, automatically detected |

The CMake presets automatically detect your platform and apply appropriate settings. The same commands work everywhere.

## Requirements

### Required
- CMake 3.26+
- C++23 compatible compiler (clang++)
- Ninja build system

### Optional
- [just](https://github.com/casey/just) - Command runner (highly recommended)
- mold linker (Linux only) - Faster linking

### Installing Just

```bash
# macOS
brew install just

# Linux
cargo install just
# or
curl --proto '=https' --tlsv1.2 -sSf https://just.systems/install.sh | bash -s -- --to ~/bin
```

## Examples

### Typical Workflow

```bash
# Working on Chapter 1 exercises
just cp 1

# Make changes to src/cp1.cpp...
# Run again
just cp 1

# Test in release mode
just cpr 1

# Start Chapter 2
touch src/cp2.cpp
# Add code...
just cp 2
```

### Creating a New Chapter

```bash
# Copy template from existing chapter
cp src/cp2.cpp src/cp5.cpp

# Edit as needed...
vim src/cp5.cpp

# Build and run
just cp 5
```

## Troubleshooting

### "Recipe not found" error
Make sure you're in the project root directory (where `justfile` is located).

### Build errors after pulling changes
Clean and rebuild:
```bash
just clean
just cp 1
```

### Sanitizer errors in debug mode
This is expected! The sanitizers catch memory errors. Fix the issues or run in release mode:
```bash
just cpr 1  # No sanitizers
```
