# OOP Group8

This repo is for the OOP project of Group 8.

## Group Members

- Sarper AVCI
- Utku AKKUŞOĞLU
- Emre KARABURU
- Okan Rıdvan GÜR
- Emre ÖZKENT

## Compilation Instructions

To compile the project, you need to have `qt5` along with `qmake` and `qtsvg` packages installed. This game mainly developed on Linux, so the compilation instructions are for Linux. But I'll show you how to compile it for Windows from Linux as well.

### Linux

For Linux, you can compile the project by running the following commands:

```bash
qmake
make
```

That's it! You can run the game by executing the `./build/TheChessGame` binary.

### Compile Statically for Windows via Docker Container

Feeling brave? You can compile the project for Windows from Linux by using the `mxe` Docker container. First, you need to have Docker installed on your system. Then, open a terminal in the project directory and run the following command:

```bash
docker run -it -v $(pwd):/app syping/qt5-static-mingw bash -c "cd /app && export QT_SELECT=qt5-x86_64-w64-mingw32 && qmake -qt=qt5-x86_64-w64-mingw32 && make clean && make && ls -lah build/TheChessGame.exe"
```

Example output:

```bash
sarp@IdeaPad:~/Documents/GitHub/OOP_Group8/TheChessGame$ docker run -it -v $(pwd):/app syping/qt5-static-mingw bash -c "cd /app && export QT_SELECT=qt5-x86_64-w64-mingw32 && qmake -qt=qt5-x86_64-w64-mingw32 && make clean && make && ls -lah build/TheChessGame.exe"
Info: creating stash file /app/.qmake.stash
make -f Makefile.Release clean
make[1]: Entering directory '/app'
rm -f build/rcc/qrc_resources.cpp
[...]
make[1]: Leaving directory '/app'
make -f Makefile.Release
make[1]: Entering directory '/app'
x86_64-w64-mingw32-g++ -c -pipe -fno-keep-inline-dllexport -O2 -Wall -W -Wextra -fexceptions -mthreads -DUNICODE -D_UNICODE -DWIN32 -DQT_NO_DEBUG -DQT_SVG_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_NEEDS_QMAIN -I. -Iinclude -I/opt/windev/qt64s_5.9.9/include -I/opt/windev/qt64s_5.9.9/include/QtSvg -I/opt/windev/qt64s_5.9.9/include/QtWidgets -I/opt/windev/qt64s_5.9.9/include/QtGui -I/opt/windev/qt64s_5.9.9/include/QtCore -Ibuild/moc -I/opt/windev/qt64s_5.9.9/mkspecs/win32-g++  -o build/obj/Bishop.o src/Bishop.cpp
x86_64-w64-mingw32-g++ -c -pipe -fno-keep-inline-dllexport -O2 -Wall -W -Wextra -fexceptions -mthreads -DUNICODE -D_UNICODE -DWIN32 -DQT_NO_DEBUG -DQT_SVG_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_NEEDS_QMAIN -I. -Iinclude -I/opt/windev/qt64s_5.9.9/include -I/opt/windev/qt64s_5.9.9/include/QtSvg -I/opt/windev/qt64s_5.9.9/include/QtWidgets -I/opt/windev/qt64s_5.9.9/include/QtGui -I/opt/windev/qt64s_5.9.9/include/QtCore -Ibuild/moc -I/opt/windev/qt64s_5.9.9/mkspecs/win32-g++  -o build/obj/GameBoard.o src/GameBoard.cpp
[...]
make[1]: Leaving directory '/app'
-rwxr-xr-x 1 root root 17M Dec 14 20:12 build/TheChessGame.exe
```