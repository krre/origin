package org.gagarin.voxel

import com.badlogic.gdx.graphics.GL20
import com.badlogic.gdx.graphics.Mesh
import com.badlogic.gdx.graphics.VertexAttribute
import com.badlogic.gdx.graphics.g2d.TextureRegion
import com.badlogic.gdx.graphics.g3d.Material
import com.badlogic.gdx.graphics.g3d.Renderable
import com.badlogic.gdx.graphics.g3d.RenderableProvider
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute
import com.badlogic.gdx.math.MathUtils
import com.badlogic.gdx.utils.Array
import com.badlogic.gdx.utils.Pool

class VoxelWorld(private val tiles: kotlin.Array<TextureRegion>, val chunksX: Int, val chunksY: Int, val chunksZ: Int) : RenderableProvider {

    val chunks: Array<VoxelChunk>
    val meshes: Array<Mesh>
    val materials: Array<Material>
    val dirty: BooleanArray
    val numVertices: IntArray
    var vertices: FloatArray
    var renderedChunks: Int = 0
    var numChunks = 0
    var voxelsX = 0
    var voxelsY = 0
    var voxelsZ = 0

    init {
        voxelsX = chunksX * CHUNK_SIZE_X
        voxelsY = chunksY * CHUNK_SIZE_Y
        voxelsZ = chunksZ * CHUNK_SIZE_Z
        numChunks = chunksX * chunksY * chunksZ
        chunks = Array(numChunks)
        for (y in 0..chunksY - 1) {
            for (z in 0..chunksZ - 1) {
                for (x in 0..chunksX - 1) {
                    val chunk = VoxelChunk(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z)
                    chunk.offset.set(x.toFloat() * CHUNK_SIZE_X, y.toFloat() * CHUNK_SIZE_Y, z.toFloat() * CHUNK_SIZE_Z)
                    chunks.add(chunk)
                }
            }
        }
        val len = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6 * 6 / 3
        val indices = ShortArray(len)
        var j = 0
        var i = 0
        while (i < len) {
            indices[i + 0] = (j + 0).toShort()
            indices[i + 1] = (j + 1).toShort()
            indices[i + 2] = (j + 2).toShort()
            indices[i + 3] = (j + 2).toShort()
            indices[i + 4] = (j + 3).toShort()
            indices[i + 5] = (j + 0).toShort()
            i += 6
            j += 4
        }
        meshes = Array(chunksX * chunksY * chunksZ)
        i = 0
        while (i < numChunks) {
            meshes.add(Mesh(true, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6 * 4, CHUNK_SIZE_X * CHUNK_SIZE_Y
                    * CHUNK_SIZE_Z * 36 / 3, VertexAttribute.Position(), VertexAttribute.Normal()))
            meshes[i].setIndices(indices)
            i++
        }
        this.dirty = BooleanArray(chunksX * chunksY * chunksZ)
        i = 0
        while (i < dirty.size) {
            dirty[i] = true
            i++
        }

        numVertices = IntArray(chunksX * chunksY * chunksZ)
        i = 0
        while (i < numVertices.size) {
            numVertices[i] = 0
            i++
        }

        vertices = FloatArray(VoxelChunk.VERTEX_SIZE * 6 * CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)
        materials = Array(chunksX * chunksY * chunksZ)
        i = 0
        while (i < numChunks) {
            materials.add(Material(ColorAttribute(ColorAttribute.Diffuse, MathUtils.random(0.5f, 1f), MathUtils.random(
                    0.5f, 1f), MathUtils.random(0.5f, 1f), 1f)))
            i++
        }
    }

    operator fun set(x: Float, y: Float, z: Float, voxel: Byte) {
        val ix = x.toInt()
        val iy = y.toInt()
        val iz = z.toInt()
        val chunkX = ix / CHUNK_SIZE_X
        if (chunkX < 0 || chunkX >= chunksX) return
        val chunkY = iy / CHUNK_SIZE_Y
        if (chunkY < 0 || chunkY >= chunksY) return
        val chunkZ = iz / CHUNK_SIZE_Z
        if (chunkZ < 0 || chunkZ >= chunksZ) return
        chunks[chunkX + chunkZ * chunksX + chunkY * chunksX * chunksZ].set(ix % CHUNK_SIZE_X, iy % CHUNK_SIZE_Y, iz % CHUNK_SIZE_Z,
                voxel)
    }

    operator fun get(x: Float, y: Float, z: Float): Byte {
        val ix = x.toInt()
        val iy = y.toInt()
        val iz = z.toInt()
        val chunkX = ix / CHUNK_SIZE_X
        if (chunkX < 0 || chunkX >= chunksX) return 0
        val chunkY = iy / CHUNK_SIZE_Y
        if (chunkY < 0 || chunkY >= chunksY) return 0
        val chunkZ = iz / CHUNK_SIZE_Z
        if (chunkZ < 0 || chunkZ >= chunksZ) return 0
        return chunks[chunkX + chunkZ * chunksX + chunkY * chunksX * chunksZ].get(ix % CHUNK_SIZE_X, iy % CHUNK_SIZE_Y, iz % CHUNK_SIZE_Z)
    }

    fun getHighest(x: Float, z: Float): Float {
        val ix = x.toInt()
        val iz = z.toInt()
        if (ix < 0 || ix >= voxelsX) return 0f
        if (iz < 0 || iz >= voxelsZ) return 0f
        // FIXME optimize
        for (y in voxelsY - 1 downTo 1) {
            if (get(ix.toFloat(), y.toFloat(), iz.toFloat()) > 0) return (y + 1).toFloat()
        }
        return 0f
    }

    fun setColumn(x: Float, y: Float, z: Float, voxel: Byte) {
        val ix = x.toInt()
        var iy = y.toInt()
        val iz = z.toInt()
        if (ix < 0 || ix >= voxelsX) return
        if (iy < 0 || iy >= voxelsY) return
        if (iz < 0 || iz >= voxelsZ) return
        // FIXME optimize
        while (iy > 0) {
            set(ix.toFloat(), iy.toFloat(), iz.toFloat(), voxel)
            iy--
        }
    }

    fun setCube(x: Float, y: Float, z: Float, width: Float, height: Float, depth: Float, voxel: Byte) {
        var ix = x.toInt()
        var iy = y.toInt()
        var iz = z.toInt()
        val iwidth = width.toInt()
        val iheight = height.toInt()
        val idepth = depth.toInt()
        val startX = Math.max(ix, 0)
        val endX = Math.min(voxelsX, ix + iwidth)
        val startY = Math.max(iy, 0)
        val endY = Math.min(voxelsY, iy + iheight)
        val startZ = Math.max(iz, 0)
        val endZ = Math.min(voxelsZ, iz + idepth)
        // FIXME optimize
        iy = startY
        while (iy < endY) {
            iz = startZ
            while (iz < endZ) {
                ix = startX
                while (ix < endX) {
                    set(ix.toFloat(), iy.toFloat(), iz.toFloat(), voxel)
                    ix++
                }
                iz++
            }
            iy++
        }
    }

    override fun getRenderables(renderables: Array<Renderable>, pool: Pool<Renderable>) {
        renderedChunks = 0
        for (i in 0..chunks.size - 1) {
            val chunk = chunks[i]
            val mesh = meshes[i]
            if (dirty[i]) {
                val numVerts = chunk.calculateVertices(vertices)
                numVertices[i] = numVerts / 4 * 6
                mesh.setVertices(vertices, 0, numVerts * VoxelChunk.VERTEX_SIZE)
                dirty[i] = false
            }
            if (numVertices[i] == 0) continue
            val renderable = pool.obtain()
            renderable.material = materials[i]
            renderable.meshPart.mesh = mesh
            renderable.meshPart.offset = 0
            renderable.meshPart.size = numVertices[i]
            renderable.meshPart.primitiveType = GL20.GL_TRIANGLES
            renderables.add(renderable)
            renderedChunks++
        }
    }

    companion object {
        val CHUNK_SIZE_X = 16
        val CHUNK_SIZE_Y = 16
        val CHUNK_SIZE_Z = 16
    }
}
