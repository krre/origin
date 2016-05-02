package org.gagarin.debug

import org.gagarin.screen.AbstractScreen
import org.gagarin.screen.GameScreen
import org.gagarin.screen.MainScreen
import org.gagarin.screen.SettingsScreen

object Gui {
    private var screen = Screen.GAME

    fun startScreen(): AbstractScreen {
        when (screen) {
            Screen.SETTINGS -> return SettingsScreen()
            Screen.GAME -> return GameScreen()
        }

        return MainScreen()
    }

}

enum class Screen {
    MAIN,
    SETTINGS,
    GAME
}
