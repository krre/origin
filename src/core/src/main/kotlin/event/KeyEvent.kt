package org.gagarin.event

interface KeyEvent {
    fun keyPressed(key: Int): Boolean {
        return  false
    }
}
