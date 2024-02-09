# simactivity

Simulate user activity by moving the mouse pointer back and forth a bit whenever the user has been idle for a specified amount of time.

Successfully tested with

 - macOS (macOS 10.12 (Sierra) and later required)
   - [x] macOS Sonoma 14.3 (Apple silicon)
 - Linux (X11)
   - [x] Kali Linux in UTM VM
 - Windows
   - [x] Windows 11

## Build

### Prerequisites

#### macOS

 - [Command Line Tools for Xcode](https://developer.apple.com/download/all/)
 - [CMake](https://cmake.org/)
  
#### Windows

 - [Build Tools for Visual Studio](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line)
 - Git and [CMake](https://cmake.org/):
   ```
   winget install Git.Git
   winget install Kitware.CMake
   ```

#### Linux

 - [CMake](https://cmake.org/)
 - C++ compiler, e.g. g++
 - X11 libs

### Compile

#### macOS / Linux

```
git clone https://github.com/607011/simactivity.git
cd simactivity
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```


#### Windows

Open Visual Studio Developer Console.

```
git clone https://github.com/607011/simactivity.git
cd simactivity
md build
cd build
cmake ..
cmake --build . --config Release
```

## Run

### macOS / Linux

```
./iamhere
```

### Windows

```
iamhere.exe
```
