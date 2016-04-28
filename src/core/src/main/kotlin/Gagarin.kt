package org.gagarin

import com.badlogic.gdx.Game
import com.badlogic.gdx.Screen
import org.gagarin.screen.StartScreen
import kotlin.properties.Delegates

class Gagarin() : Game() {
    override fun create() {
        instance = this
        setScreen(StartScreen())
    }

    companion object {
        var instance: Gagarin by Delegates.notNull()

        fun setScreen(screen: Screen) {
            instance.setScreen(screen)
        }
    }
}
