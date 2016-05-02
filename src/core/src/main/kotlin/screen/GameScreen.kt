package org.gagarin.screen

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.graphics.Color
import com.badlogic.gdx.graphics.GL20
import com.badlogic.gdx.graphics.PerspectiveCamera
import com.badlogic.gdx.graphics.VertexAttributes
import com.badlogic.gdx.graphics.g3d.*
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute
import com.badlogic.gdx.graphics.g3d.environment.DirectionalLight
import com.badlogic.gdx.graphics.g3d.utils.CameraInputController
import com.badlogic.gdx.graphics.g3d.utils.ModelBuilder
import org.gagarin.Gagarin

class GameScreen : AbstractScreen() {
    var camera: PerspectiveCamera
    var model: Model
    var instance: ModelInstance
    val modelBatch = ModelBatch()
    val environment = Environment()
    var controller: CameraInputController

    init {
        environment.set(ColorAttribute(ColorAttribute.AmbientLight, 0.2f, 0.2f, 0.2f, 1f))
        environment.add(DirectionalLight().set(0.8f, 0.8f, 0.8f, -1f, -0.8f, -0.2f))

        camera = PerspectiveCamera(67f, Gdx.graphics.width.toFloat(), Gdx.graphics.height.toFloat())
        camera.position.set(10f, 10f, 10f)
        camera.lookAt(0f, 0f, 0f)
        camera.near = 0.5f
        camera.far = 1000f
        camera.update()

        val modelBuilder = ModelBuilder()
        model = modelBuilder.createSphere(5f, 5f, 5f, 30, 30,
                Material(ColorAttribute.createDiffuse(Color.GREEN)),
                VertexAttributes.Usage.Position.toLong() or VertexAttributes.Usage.Normal.toLong())
        instance = ModelInstance(model)

        controller = CameraInputController(camera)
        multiplexer.addProcessor(controller)
    }

    override fun dispose() {
        super.dispose()
        modelBatch.dispose()
        model.dispose()
    }

    override fun render(delta: Float) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT or GL20.GL_DEPTH_BUFFER_BIT)

        modelBatch.begin(camera)
        modelBatch.render(instance, environment)
        modelBatch.end()
    }

    override fun escPressed() {
        Gagarin.instance.screen = Gagarin.startScreen
    }
}
