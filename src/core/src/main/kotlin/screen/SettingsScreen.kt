package org.gagarin.screen

import com.badlogic.gdx.scenes.scene2d.Actor
import com.badlogic.gdx.scenes.scene2d.InputEvent
import com.badlogic.gdx.scenes.scene2d.ui.Label
import com.badlogic.gdx.scenes.scene2d.ui.SelectBox
import com.badlogic.gdx.scenes.scene2d.ui.Table
import com.badlogic.gdx.scenes.scene2d.ui.TextButton
import com.badlogic.gdx.scenes.scene2d.utils.ChangeListener
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener
import org.gagarin.Gagarin

class SettingsScreen : AbstractScreen() {
    init {
        val table = Table()
        table.setFillParent(true)
        table.defaults().width(300f).height(50f).space(10f)
        stage.addActor(table)

        val languageLabel = Label(Gagarin.guiBundle.format("language") + ":", skin)
        table.add(languageLabel)

        val languageSelectBox: SelectBox<String> = SelectBox(skin)
        languageSelectBox.setItems("System", "English", "Russian")
        languageSelectBox.addListener(object: ChangeListener() {
            override fun changed(event: ChangeEvent, actor: Actor) {
                Gagarin.setLocale(languageSelectBox.selected)
                Gagarin.prefs.putString("lang", languageSelectBox.selected)
                Gagarin.prefs.flush()
            }
        })
        languageSelectBox.selected = Gagarin.prefs.getString("lang", "System")

        table.add(languageSelectBox)

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