package org.gagarin.screen

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.graphics.Pixmap
import com.badlogic.gdx.graphics.PixmapIO
import com.badlogic.gdx.scenes.scene2d.InputEvent
import com.badlogic.gdx.scenes.scene2d.ui.Table
import com.badlogic.gdx.scenes.scene2d.ui.TextButton
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener
import com.badlogic.gdx.utils.BufferUtils
import com.badlogic.gdx.utils.ScreenUtils
import org.gagarin.Gagarin

class StartScreen : AbstractScreen() {
    init {
        val table = Table()
        table.setFillParent(true)
        table.defaults().width(300f).height(50f).space(10f)
        stage.addActor(table)

        val playButton = TextButton(Gagarin.guiBundle.format("play"), skin)
        playButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                println("Play")
                val pixels = ScreenUtils.getFrameBufferPixels(0, 0, Gdx.graphics.getBackBufferWidth(), Gdx.graphics.getBackBufferHeight(), true)
                val pixmap = Pixmap(Gdx.graphics.getBackBufferWidth(), Gdx.graphics.getBackBufferHeight(), Pixmap.Format.RGBA8888);
                BufferUtils.copy(pixels, 0, pixmap.getPixels(), pixels.size)
                PixmapIO.writePNG(Gdx.files.external("gagarin.png"), pixmap)
                pixmap.dispose()
            }
        })
        table.add(playButton)
        table.row()

        val languageButton = TextButton(Gagarin.guiBundle.format("language"), skin)
        languageButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                println("Language")
            }
        })
        table.add(languageButton)
        table.row()

        val exitButton = TextButton(Gagarin.guiBundle.format("exit"), skin)
        exitButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                Gdx.app.exit()
            }
        })
        table.add(exitButton)
    }
}
