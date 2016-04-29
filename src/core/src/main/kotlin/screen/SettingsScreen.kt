package org.cyberhive.screen

import com.badlogic.gdx.scenes.scene2d.InputEvent
import com.badlogic.gdx.scenes.scene2d.ui.Table
import com.badlogic.gdx.scenes.scene2d.ui.TextButton
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener
import org.gagarin.Gagarin
import org.gagarin.screen.AbstractScreen
import org.gagarin.screen.StartScreen

class SettingsScreen : AbstractScreen() {
    init {
        val table = Table()
        table.setFillParent(true)
        table.defaults().width(300f).height(50f).space(10f)
        stage.addActor(table)

        val languageButton = TextButton(Gagarin.guiBundle.format("language"), skin)
        languageButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                println("Language")
            }
        })
        table.add(languageButton)
        table.row()

        val backButton = TextButton(Gagarin.guiBundle.format("back"), skin)
        backButton.addListener(object: ClickListener() {
            override fun clicked(event: InputEvent, x: Float, y: Float) {
                Gagarin.setScreen(StartScreen())
            }
        })
        table.add(backButton)
    }
}