QT       += core gui widgets

TARGET = Tema2
TEMPLATE = app

# Definește folderul sursă
SOURCE_DIR = src

# Specifică unde să caute fișierele .h
INCLUDEPATH += $$SOURCE_DIR

# Adaugă toate fișierele sursă folosind noul director
SOURCES += \
    $$SOURCE_DIR/main.cpp \
    $$SOURCE_DIR/mainwindow.cpp \
    $$SOURCE_DIR/labyrinth.cpp \
    $$SOURCE_DIR/labyrinthgraph.cpp \
    $$SOURCE_DIR/labyrinthrenderer.cpp \
    $$SOURCE_DIR/pathsolver.cpp

# Adaugă toate fișierele header
HEADERS += \
    $$SOURCE_DIR/mainwindow.h \
    $$SOURCE_DIR/labyrinth.h \
    $$SOURCE_DIR/labyrinthgraph.h \
    $$SOURCE_DIR/labyrinthrenderer.h \
    $$SOURCE_DIR/pathsolver.h

# Adaugă fișierul UI
FORMS += \
    $$SOURCE_DIR/mainwindow.ui