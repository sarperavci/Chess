# Qt Chess Game

A modern, feature-rich chess implementation built with C++ and Qt, offering a polished gaming experience with an intuitive graphical interface.


![](https://github.com/user-attachments/assets/455cc454-1362-41fe-b8c2-a4ae525e00be)

## Features

- 🎮 Complete chess rules implementation including special moves (en passant, castling, pawn promotion)
- 🎯 Interactive board with move highlighting and valid move indicators
- 🎨 Customizable board themes
- ↩️ Move rewind functionality
- 🏁 Automatic detection of check, checkmate, and stalemate
- 💾 Cross-platform support (Linux & Windows)

## Demo

Watch the game in action:

https://github.com/user-attachments/assets/379a467b-24b3-4bf4-b4e7-d20c980e0b20

## Quick Start

### Pre-built Binaries

Download the latest release for your platform from our [releases page](https://github.com/sarperavci/chess/releases).

### Building from Source

#### Prerequisites

- Qt 5.x or later
- QtSVG module
- CMake 3.x or later
- C++11 compatible compiler

#### Linux Build

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt install qt5-default qtsvg5-dev

# Build
qmake
make

# Run
./build/Chess
```

#### Windows Build

##### Using Qt Creator
1. Open `game.pro` in Qt Creator
2. Configure project for your kit
3. Build and run

##### Using Command Line
```powershell
# Configure
qmake game.pro

# Build
mingw32-make

# Deploy dependencies
cd C:\Qt\6.8.0\mingw_64\bin
windeployqt.exe "path\to\Chess.exe"
```

### Docker Builds

#### Static Windows Build
```bash
docker run -it -v $(pwd):/app syping/qt5-static-mingw bash -c \
"cd /app && export QT_SELECT=qt5-x86_64-w64-mingw32 && \
qmake -qt=qt5-x86_64-w64-mingw32 && make clean && make"
```

#### Static Linux Build
```bash
docker run -it -v $(pwd):/app fishwaldo/qt-staticbuilds:5.12.4 bash -c \
"cd /app && rm -f .qmake.stash && /opt/Qt/5.12.4/bin/qmake && \
make clean && make"
```
