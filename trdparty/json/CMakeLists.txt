# Show in QtCreator project tree
FILE(GLOB_RECURSE json "*.*")
add_custom_target(json SOURCES ${json})
