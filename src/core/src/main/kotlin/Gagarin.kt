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
        val bfh = Gdx.files.internal("i18n/gui")
        val locale = Locale.getDefault()
//        val locale = Locale("en", "EN")
        guiBundle = I18NBundle.createBundle(bfh, locale)

        instance = this
        setScreen(StartScreen())
    }

    companion object {
        var instance: Gagarin by Delegates.notNull()
        var guiBundle: I18NBundle by Delegates.notNull()

        fun setScreen(screen: Screen) {
            instance.setScreen(screen)
        }
    }
}
