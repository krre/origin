package org.gagarin

import com.badlogic.gdx.Game
import com.badlogic.gdx.Gdx
import com.badlogic.gdx.Preferences
import com.badlogic.gdx.Screen
import com.badlogic.gdx.utils.I18NBundle
import org.gagarin.screen.GameScreen
import org.gagarin.screen.SettingsScreen
import org.gagarin.screen.MainScreen
import org.gagarin.voxel.VoxelTest
import java.util.*
import kotlin.properties.Delegates

class Gagarin() : Game() {

    override fun create() {
        instance = this
        prefs = Gdx.app.getPreferences("Gagarin")
        val lang = prefs.getString("lang", "System")
        setLocale(lang)

        startScreen = MainScreen()
        setScreen(startScreen)
    }

    companion object {
        var instance: Gagarin by Delegates.notNull()
        var guiBundle: I18NBundle by Delegates.notNull()
        var prefs: Preferences by Delegates.notNull()

        var startScreen: MainScreen? = null
        var settingsScreen: SettingsScreen? = null
        //    var gameScreen: GameScreen? = null
        var gameScreen: VoxelTest? = null

        fun setScreen(screen: Screen) {
            instance.setScreen(screen)
        }

        fun setLocale(lang: String) {
            val bfh = Gdx.files.internal("i18n/gui")
            when (lang) {
                "System" -> guiBundle = I18NBundle.createBundle(bfh, Locale.getDefault())
                "English" -> guiBundle = I18NBundle.createBundle(bfh, Locale("en", "EN"))
                "Russian" -> guiBundle = I18NBundle.createBundle(bfh, Locale("ru", "RU"))
            }
        }
    }
}
