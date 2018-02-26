HEADERS += src/pecs/UBDesktopPecsPalette.h \
           src/pecs/UBDesktopAnnotationPecsController.h \
           src/pecs/UBCustomCapturePecsWindow.h \
           src/pecs/UBWindowPecsCapture.h \
           src/pecs/UBDesktopPecsPropertyPalette.h

SOURCES += src/pecs/UBDesktopPecsPalette.cpp \
           src/pecs/UBDesktopAnnotationPecsController.cpp \
           src/pecs/UBCustomCapturePecsWindow.cpp \
           src/pecs/UBDesktopPecsPropertyPalette.cpp

win32 { 
    HEADERS += src/pecs/UBWindowCapturePecsDelegate_win.h
    SOURCES += src/pecs/UBWindowCapturePecs_win.cpp \
               src/pecs/UBWindowCapturePecsDelegate_win.cpp
}

macx:OBJECTIVE_SOURCES += src/ecs/UBWindowPecsCapture_mac.mm

linux-g++:SOURCES += src/pecs/UBWindowCapturePecs_linux.cpp
linux-g++-32:SOURCES += src/pecs/UBWindowCapturePecs_linux.cpp
linux-g++-64:SOURCES += src/pecs/UBWindowCapturePecs_linux.cpp
