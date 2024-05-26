include_directories(../../ThirdParty)
include_directories(../../Libs)

add_library(Octree SHARED
    JsonStorage.cpp JsonStorage.h
    Octree.cpp Octree.h
    Substance.cpp Substance.h
    SubstanceTree.cpp SubstanceTree.h
)

target_link_libraries(Octree Core)
