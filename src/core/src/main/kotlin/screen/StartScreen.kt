package org.gagarin.screen

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.scenes.scene2d.InputEvent
import com.badlogic.gdx.scenes.scene2d.ui.Table
import com.badlogic.gdx.scenes.scene2d.ui.TextButton
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener
import org.gagarin.printc

class StartScreen : AbstractScreen() {
    init {
        val table = Table()
        table.setFillParent(true)
        table.defaults().width(300f).height(50f).space(10f)
        stage.addActor(table)

        val playButton = TextButton("Play", skin)
        playButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                printc("Play")
            }
        })
        table.add(playButton)
        table.row()

        val languageButton = TextButton("Language", skin)
        languageButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                printc("Language")
            }
        })
        table.add(languageButton)
        table.row()

        val exitButton = TextButton("Выход", skin)
        exitButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                Gdx.app.exit()
            }
        })
        table.add(exitButton)
    }
}
