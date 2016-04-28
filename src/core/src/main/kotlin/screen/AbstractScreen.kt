package org.gagarin.screen

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.ScreenAdapter
import com.badlogic.gdx.graphics.GL20
import com.badlogic.gdx.graphics.OrthographicCamera
import com.badlogic.gdx.graphics.g2d.BitmapFont
import com.badlogic.gdx.graphics.g2d.TextureAtlas
import com.badlogic.gdx.graphics.g2d.freetype.FreeTypeFontGenerator
import com.badlogic.gdx.scenes.scene2d.Stage
import com.badlogic.gdx.scenes.scene2d.ui.Skin
import com.badlogic.gdx.utils.viewport.FitViewport
import org.gagarin.utils.Constants

open class AbstractScreen : ScreenAdapter() {
    val camera = OrthographicCamera()
    val stage = Stage(FitViewport(Constants.virtualWidth, Constants.virtualHeight))
    val skin = Skin()
    var russianFont: BitmapFont

    init {
        Gdx.gl.glClearColor(1f, 1f, 1f, 1f)
        camera.setToOrtho(false, Constants.virtualWidth, Constants.virtualHeight)
        camera.update()
        Gdx.input.setInputProcessor(stage)

        val generator = FreeTypeFontGenerator(Gdx.files.internal("fonts/arial.ttf"))
        val parameter = FreeTypeFontGenerator.FreeTypeFontParameter()
//        parameter.size = 18

        var chars = ""
//        for(i in 32..126) chars += i as Char // цифры и весь английский
//        for(i in 1024..1103) chars += i // русские

        chars = "абвгдежзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyzАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789][_!$%#@|\\/?-+=()*&.;:,{}\"´`'<>"

//        printc(chars)

        parameter.characters = chars
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
        skin.load(fileHandle);
    }

    override fun render(delta: Float) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT)
        stage.act();
        stage.draw();
    }

    override fun resize(width: Int, height: Int) {
        stage.getViewport().update(width, height, false)
    }

    override fun dispose() {
        stage.dispose()
    }
}
