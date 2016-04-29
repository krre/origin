package org.gagarin.screen

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.scenes.scene2d.InputEvent
import com.badlogic.gdx.scenes.scene2d.ui.Table
import com.badlogic.gdx.scenes.scene2d.ui.TextButton
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener
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
            }
        })
        table.add(playButton)
        table.row()

        val languageButton = TextButton(Gagarin.guiBundle.format("settings"), skin)
        languageButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                Gagarin.setScreen(SettingsScreen())
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
