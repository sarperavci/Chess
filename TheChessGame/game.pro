QT       += core gui svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheChessGame
TEMPLATE = app

# Specify the build directory
DESTDIR = ./build

# Specify the directory for object files
OBJECTS_DIR = ./build/obj

# Specify the directory for moc files
MOC_DIR = ./build/moc

# Specify the directory for rcc files
RCC_DIR = ./build/rcc

# Specify the directory for ui files
UI_DIR = ./build/ui

# Include paths
INCLUDEPATH += include

# Get all .cpp files in the src directory
SOURCES += src/Bishop.cpp \
           src/GameBoard.cpp \
           src/Game.cpp \
           src/King.cpp \
           src/Knight.cpp \
           src/main.cpp \
           src/MainWindow.cpp \
           src/Pawn.cpp \
           src/Piece.cpp \
           src/Queen.cpp \
           src/Rook.cpp \
           src/utils.cpp

# Get all .h files in the include directory
HEADERS  += include/Bishop.h \
            include/GameBoard.h \
            include/Game.h \
            include/King.h \
            include/Knight.h \
            include/MainWindow.h \
            include/Pawn.h \
            include/Piece.h \
            include/Queen.h \
            include/Rook.h \
            include/utils.h

# Include the UI files if any
FORMS +=

# Include the resource files if any
RESOURCES += resources.qrc