include_directories(../../trdparty)

add_library(core SHARED
    Common.h
    Defines.h
    Object.cpp Object.h
    Signal.h
    SingleObject.h
    Utils.cpp Utils.h
)
