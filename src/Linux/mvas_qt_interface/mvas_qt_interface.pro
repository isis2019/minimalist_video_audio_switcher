QT += widgets opengl

LIBS += -pthread -ldl

QMAKE_CXXFLAGS += -Wextra -Wall -w -std=c++11

SOURCES += \
    mvas_qt_main_window.cpp \
    mvas_qt_video_interface.cpp \
    ../../mvas_panel_driver.cpp \
    mvas_qt_utilities.cpp \
    ../../mvas_error.cpp \
    mvas_qt_video_preview.cpp \
    main.cpp \
    mvas_qt_audio_slice.cpp \
    mvas_qt_audio_interface.cpp \
    mvas_qt_devices_windows.cpp \
    ../include/DeckLinkAPIDispatch.cpp \
    mvas_qt_toolbar.cpp

HEADERS += \
    mvas_qt_main_window.h \
    mvas_qt_video_interface.h \
    ../../mvas_panel_driver.h \
    mvas_qt_utilities.h \
    ../../mvas_error.h \
    mvas_qt_video_preview.h \
    mvas_qt_audio_slice.h \
    mvas_qt_audio_interface.h \
    ../../mvas_macros.h \
    mvas_qt_devices_windows.h \
    mvas_qt_toolbar.h

DISTFILES += \
    stylesheets/mvas_main_window.css \
    stylesheets/mvas_video_interface.css
