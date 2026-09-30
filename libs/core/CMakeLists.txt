add_library(core SHARED
    Common.h
    Defines.h
    Object.cpp Object.h
    Signal.h
    SingleObject.h
    Utils.cpp Utils.h
)

target_link_libraries(core PUBLIC glm::glm)
