package org.gagarin.screen

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.graphics.GL20
import org.gagarin.Gagarin

class GameScreen : AbstractScreen() {
    init {
    }

    override fun render(delta: Float) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT)
        stage.act()
        stage.draw()
    }

    override fun escPressed() {
        Gagarin.instance.screen = Gagarin.startScreen
    }
}

