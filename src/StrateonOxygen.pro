# MIT License
#
# Copyright (c) 2018 Theo Bessel
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

QT += widgets

#CONFIG += console

LIBS += -framework AppKit

HEADERS += \
    SyntaxicColoration/SynColoCCpp.h \
    Editor/Editor.h \
    Core/MainWindow.h \
    Core/PrincipalWidget.h \
    SyntaxicColoration/SynColoHTML.h \
    Editor/FileGestion.h \
    Core/centraltabwidget.h

SOURCES += \
    #main.cpp \
    SyntaxicColoration/SynColoCCpp.cpp \
    Editor/Editor.cpp \
    Core/PrincipalWidget.cpp \
    SyntaxicColoration/SynColoHTML.cpp \
    Editor/FileGestion.cpp \
    Core/centraltabwidget.cpp \
    Core/MainWindow.cpp \
    changetitlebarcolor.mm



OBJECTIVE_SOURCES += \
    main.mm

RESOURCES += \
    Ressouces/ressources.qrc
