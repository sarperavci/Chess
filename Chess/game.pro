QT       += core gui svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app

DESTDIR = ./build

OBJECTS_DIR = ./build/obj

MOC_DIR = ./build/moc

RCC_DIR = ./build/rcc

UI_DIR = ./build/ui

INCLUDEPATH += include

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
           src/utils.cpp \
           src/EndGameDialog.cpp

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
            include/utils.h \
            include/EndGameDialog.h

FORMS +=

RESOURCES += resources.qrc