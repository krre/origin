package org.gagarin.screen

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.graphics.GL20

class GameScreen : AbstractScreen() {
    init {
        println("game")
    }

    override fun render(delta: Float) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT)
        stage.act()
        stage.draw()
        println(delta)
    }
}

