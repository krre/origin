package org.gagarin

import com.badlogic.gdx.Game
import com.badlogic.gdx.Gdx

class Gagarin() : Game() {
    override fun create() {
    }
}

fun printc(message: Any) {
    Gdx.app.log("Gagarin", message.toString())
}
