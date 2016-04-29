package org.gagarin

import com.badlogic.gdx.Game
import com.badlogic.gdx.Gdx
import com.badlogic.gdx.Screen
import com.badlogic.gdx.utils.I18NBundle
import org.gagarin.screen.StartScreen
import java.util.*
import kotlin.properties.Delegates

class Gagarin() : Game() {

    override fun create() {
        instance = this
        setLocale("Default")
        setScreen(StartScreen())
    }

    companion object {
        var instance: Gagarin by Delegates.notNull()
        var guiBundle: I18NBundle by Delegates.notNull()

        fun setScreen(screen: Screen) {
            instance.setScreen(screen)
        }

        fun setLocale(lang: String) {
            val bfh = Gdx.files.internal("i18n/gui")
            when (lang) {
                "Default" -> guiBundle = I18NBundle.createBundle(bfh, Locale.getDefault())
                "English" -> guiBundle = I18NBundle.createBundle(bfh, Locale("en", "EN"))
                "Russian" -> guiBundle = I18NBundle.createBundle(bfh, Locale("ru", "RU"))
            }
        }
    }
}
