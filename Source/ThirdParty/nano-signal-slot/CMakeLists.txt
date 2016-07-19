# Show in QtCreator project tree
FILE(GLOB_RECURSE nano "*.*")
add_custom_target(nano SOURCES ${nano})
