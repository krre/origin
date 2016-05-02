package org.gagarin.debug

object Common {
    var mode = Mode.DEBUG
}

enum class Mode {
    RELEASE,
    DEBUG
}