#pragma once
// Fake Origin.h for compability with Origin classes
#include <QtGlobal>
#ifdef Q_OS_UNIX
    #define UNIX
#elif Q_OS_WIN32
    #define WIN32
#endif
