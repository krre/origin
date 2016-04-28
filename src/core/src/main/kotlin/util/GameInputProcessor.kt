package org.gagarin.utils

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.Input
import com.badlogic.gdx.InputProcessor
import com.badlogic.gdx.graphics.Pixmap
import com.badlogic.gdx.graphics.PixmapIO
import com.badlogic.gdx.utils.BufferUtils
import com.badlogic.gdx.utils.ScreenUtils

class GameInputProcessor : InputProcessor {
    override fun keyDown (keycode: Int): Boolean {
        when (keycode) {
            Input.Keys.F1 -> println("Help")
            Input.Keys.F12 -> makeScreenshot()
        }
        return true
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
        return false;
    }

    fun makeScreenshot() {
        val pixels = ScreenUtils.getFrameBufferPixels(0, 0, Gdx.graphics.backBufferWidth, Gdx.graphics.backBufferHeight, true)
        val pixmap = Pixmap(Gdx.graphics.backBufferWidth, Gdx.graphics.backBufferHeight, Pixmap.Format.RGBA8888);
        BufferUtils.copy(pixels, 0, pixmap.pixels, pixels.size)
        PixmapIO.writePNG(Gdx.files.external("gagarin.png"), pixmap)
        pixmap.dispose()
        println("Save screenshot")
    }
}
