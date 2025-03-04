# C-Shell

A simple tool for managing processes

### Usage
```bash
# Add the binary file to the PATH environment variable on your PC to use it as "tricko"
tricko # Outputs nothing special
tricko list # Outputs all available commands
tricko killport <port> # Kills all processes using the specified port
```

Target: Windows  
Output folder: `./dist`

### Contribution
```bash
mkdir build
cd build
cmake .. # Make sure CMake and a C compiler are installed
cmake --build . --config Release
```

by robertpakalns | [Community Server](https://discord.gg/yPjrUrvSzv) | Powered by Tricko