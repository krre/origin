#pragma once
// Fake config.h for compability with Origin classes
#include <QtGlobal>
#ifdef Q_OS_UNIX
    #define UNIX
#endif

#ifdef Q_OS_WIN
    #ifndef WIN32
        #define WIN32
    #endif
#endif
