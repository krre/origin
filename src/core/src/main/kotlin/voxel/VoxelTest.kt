package org.gagarin.voxel

import com.badlogic.gdx.Gdx
import com.badlogic.gdx.InputMultiplexer
import com.badlogic.gdx.graphics.GL20
import com.badlogic.gdx.graphics.PerspectiveCamera
import com.badlogic.gdx.graphics.Texture
import com.badlogic.gdx.graphics.g2d.BitmapFont
import com.badlogic.gdx.graphics.g2d.SpriteBatch
import com.badlogic.gdx.graphics.g2d.TextureRegion
import com.badlogic.gdx.graphics.g3d.Environment
import com.badlogic.gdx.graphics.g3d.ModelBatch
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute
import com.badlogic.gdx.graphics.g3d.environment.DirectionalLight
import com.badlogic.gdx.graphics.g3d.shaders.DefaultShader
import com.badlogic.gdx.graphics.g3d.utils.FirstPersonCameraController
import com.badlogic.gdx.math.MathUtils
import org.gagarin.Gagarin
import org.gagarin.screen.AbstractScreen
import org.gagarin.screen.StartScreen
import org.gagarin.utils.GameInputProcessor

class VoxelTest : AbstractScreen() {
    internal val spriteBatch = SpriteBatch()
    internal val font = BitmapFont()
    internal val modelBatch = ModelBatch()
    internal var cameraPersp: PerspectiveCamera
    internal var lights = Environment()
    internal var controller: FirstPersonCameraController
    internal var voxelWorld: VoxelWorld

    init {
        DefaultShader.defaultCullFace = GL20.GL_FRONT
        cameraPersp = PerspectiveCamera(67f, Gdx.graphics.width.toFloat(), Gdx.graphics.height.toFloat())
        cameraPersp.near = 0.5f
        cameraPersp.far = 1000f
        controller = FirstPersonCameraController(cameraPersp)

        val multiplexer = InputMultiplexer()
        multiplexer.addProcessor(GameInputProcessor(this))
        multiplexer.addProcessor(controller)
        Gdx.input.inputProcessor = multiplexer

        lights.set(ColorAttribute(ColorAttribute.AmbientLight, 0.4f, 0.4f, 0.4f, 1.0f))
        lights.add(DirectionalLight().set(1f, 1f, 1f, 0f, -1f, 0f))

        val texture = Texture(Gdx.files.internal("tiles.png"))
        val tiles = TextureRegion.split(texture, 32, 32)

        MathUtils.random.setSeed(0)
        var xx: Array<TextureRegion> = tiles[0]
        voxelWorld = VoxelWorld(xx, 20, 4, 20)
        PerlinNoiseGenerator.generateVoxels(voxelWorld, 0, 63, 10)
        val camX = voxelWorld.voxelsX / 2f
        val camZ = voxelWorld.voxelsZ / 2f
        val camY = voxelWorld.getHighest(camX, camZ) + 1.5f
        cameraPersp.position.set(camX, camY, camZ)
    }

    override fun render(delta: Float) {
        Gdx.gl.glClearColor(0.4f, 0.4f, 0.4f, 1f)
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT or GL20.GL_DEPTH_BUFFER_BIT)
        modelBatch.begin(cameraPersp)
        modelBatch.render(voxelWorld, lights)
        modelBatch.end()
        controller.update()

        spriteBatch.begin()
        font.draw(spriteBatch, "fps: " + Gdx.graphics.framesPerSecond + ", #visible chunks: " + voxelWorld.renderedChunks
                + "/" + voxelWorld.numChunks, 0f, 20f)
        spriteBatch.end()
    }

    override fun resize(width: Int, height: Int) {
        spriteBatch.projectionMatrix.setToOrtho2D(0f, 0f, width.toFloat(), height.toFloat())
        cameraPersp.viewportWidth = width.toFloat()
        cameraPersp.viewportHeight = height.toFloat()
        cameraPersp.update()
    }

    override fun escPressed() {
//        stage.dispose()
        modelBatch.dispose()
        Gagarin.setScreen(StartScreen())
    }
}
