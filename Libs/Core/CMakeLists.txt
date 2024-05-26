include_directories(../../ThirdParty)

add_library(Core SHARED
    Common.h
    Defines.h
    Object.cpp Object.h
    Signal.h
    SingleObject.h
    Utils.cpp Utils.h
)
