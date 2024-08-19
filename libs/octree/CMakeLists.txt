add_library(octree SHARED
    JsonStorage.cpp JsonStorage.h
    Octree.cpp Octree.h
    Substance.cpp Substance.h
    SubstanceTree.cpp SubstanceTree.h
)

target_link_libraries(octree core)
