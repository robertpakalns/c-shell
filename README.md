# C-Shell

A simple tool for managing processes

### Usage
```bash
# Add the binary file to the PATH environment variable on your PC to use it as "tricko"
tricko # Outputs nothing special
tricko list # Outputs all available commands
tricko killport <port> # Kills all processes using the specified port
```

### Contribution
```bash
 # Make sure CMake and a C compiler are installed
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
Target: `Windows`  
Output folder: `./dist`

by robertpakalns | [Community Server](https://discord.gg/yPjrUrvSzv) | Powered by Tricko