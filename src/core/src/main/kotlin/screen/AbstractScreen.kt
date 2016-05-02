package org.gagarin.screen

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.Input
import com.badlogic.gdx.InputMultiplexer
import com.badlogic.gdx.ScreenAdapter
import com.badlogic.gdx.graphics.GL20
import com.badlogic.gdx.graphics.OrthographicCamera
import com.badlogic.gdx.graphics.Pixmap
import com.badlogic.gdx.graphics.PixmapIO
import com.badlogic.gdx.graphics.g2d.BitmapFont
import com.badlogic.gdx.graphics.g2d.TextureAtlas
import com.badlogic.gdx.graphics.g2d.freetype.FreeTypeFontGenerator
import com.badlogic.gdx.scenes.scene2d.Stage
import com.badlogic.gdx.scenes.scene2d.ui.Skin
import com.badlogic.gdx.utils.BufferUtils
import com.badlogic.gdx.utils.ScreenUtils
import com.badlogic.gdx.utils.viewport.FitViewport
import org.gagarin.event.KeyEvent
import org.gagarin.utils.Constants
import org.gagarin.utils.GameInputProcessor

open class AbstractScreen : ScreenAdapter(), KeyEvent {
    val camera = OrthographicCamera()
    val stage = Stage(FitViewport(Constants.virtualWidth, Constants.virtualHeight))
    val skin = Skin()
    var russianFont: BitmapFont
    val multiplexer = InputMultiplexer()

    init {
        Gdx.gl.glClearColor(0.4f, 0.4f, 0.4f, 1f)
        camera.setToOrtho(false, Constants.virtualWidth, Constants.virtualHeight)
        camera.update()

        multiplexer.addProcessor(GameInputProcessor(this))
        multiplexer.addProcessor(stage)

        val generator = FreeTypeFontGenerator(Gdx.files.internal("fonts/arial.ttf"))
        val parameter = FreeTypeFontGenerator.FreeTypeFontParameter()

        parameter.characters = FreeTypeFontGenerator.DEFAULT_CHARS + "абвгдеёжзийклмнопрстуфхцчшщъыьэюяAБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
        russianFont = generator.generateFont(parameter)
        generator.dispose()

        // В дефолтовый скин добавляется свой шрифт, но скин ещё не должен быть загружен,
        // поэтому создаём пустой скин, добавлям наш шрифт, а потом загружаем дефолтовый скин,
        // откуда предварительно уже был удалён дефолтовый шрифт.
        skin.add("default-font", russianFont, BitmapFont::class.java)

        val fileHandle = Gdx.files.internal("uiskin.json")
        val atlasFile = fileHandle.sibling("uiskin.atlas")
        if (atlasFile.exists()) {
            skin.addRegions(TextureAtlas(atlasFile))
        }
        skin.load(fileHandle)
    }

    override fun render(delta: Float) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT)
        stage.draw()
    }

    override fun resize(width: Int, height: Int) {
        stage.viewport.update(width, height, false)
    }

    override fun dispose() {
        stage.dispose()
    }

    override fun show() {
        Gdx.input.inputProcessor = multiplexer
    }

    override fun keyPressed(key: Int): Boolean {
        when (key) {
            Input.Keys.F1 -> println("Help")
            Input.Keys.F12 -> makeScreenshot()
            Input.Keys.ESCAPE -> escPressed()
            else -> return false
        }
        return true
    }

    open fun escPressed() {}

    fun makeScreenshot() {
        val pixels = ScreenUtils.getFrameBufferPixels(0, 0, Gdx.graphics.backBufferWidth, Gdx.graphics.backBufferHeight, true)
        val pixmap = Pixmap(Gdx.graphics.backBufferWidth, Gdx.graphics.backBufferHeight, Pixmap.Format.RGBA8888)
        BufferUtils.copy(pixels, 0, pixmap.pixels, pixels.size)
        PixmapIO.writePNG(Gdx.files.external("gagarin.png"), pixmap)
        pixmap.dispose()
        println("Save screenshot")
    }
}
