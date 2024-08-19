package org.gagarin.utils

import com.badlogic.gdx.InputProcessor
import org.gagarin.screen.AbstractScreen

class GameInputProcessor(val screen: AbstractScreen) : InputProcessor {

    override fun keyDown (keycode: Int): Boolean {
        return screen.keyPressed(keycode)
    }

    override fun keyUp (keycode: Int): Boolean {
        return false
    }

    override fun keyTyped (character: Char): Boolean {
        return false
    }

    override fun touchDown (x: Int, y: Int, pointer: Int, button: Int): Boolean {
        return false
    }

    override fun touchUp (x: Int, y: Int, pointer: Int, button: Int): Boolean {
        return false
    }

    override fun touchDragged (x: Int, y: Int, pointer: Int): Boolean {
        return false
    }

    override fun mouseMoved (x: Int, y: Int): Boolean {
        return false
    }

    override fun scrolled (amount: Int): Boolean {
        return false
    }
}
