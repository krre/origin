#pragma once
#include <QApplication>

class Application : public QApplication {
public:
    static constexpr auto Organization = "Origin";
    static constexpr auto Name = "AssemblyBox";
    static constexpr auto Version = "0.1.0";
    static constexpr auto Url = "https://github.com/krre/origin";
    static constexpr auto Years = "2016-2025";
    static constexpr auto Author = "Vladimir Zarypov";
    static constexpr auto BuildDate = __DATE__;
    static constexpr auto BuildTime = __TIME__;

    Application(int& argc, char* argv[]);
};
