package org.gagarin.voxel

import com.badlogic.gdx.math.Vector3

class VoxelChunk(val width: Int, val height: Int, val depth: Int) {
    val voxels: ByteArray
    val offset = Vector3()
    private val widthTimesHeight: Int
    private val topOffset: Int
    private val bottomOffset: Int
    private val leftOffset: Int
    private val rightOffset: Int
    private val frontOffset: Int
    private val backOffset: Int

    init {
        this.voxels = ByteArray(width * height * depth)
        this.topOffset = width * depth
        this.bottomOffset = -width * depth
        this.leftOffset = -1
        this.rightOffset = 1
        this.frontOffset = -width
        this.backOffset = width
        this.widthTimesHeight = width * height
    }

    operator fun get(x: Int, y: Int, z: Int): Byte {
        if (x < 0 || x >= width) return 0
        if (y < 0 || y >= height) return 0
        if (z < 0 || z >= depth) return 0
        return getFast(x, y, z)
    }

    fun getFast(x: Int, y: Int, z: Int): Byte {
        return voxels[x + z * width + y * widthTimesHeight]
    }

    operator fun set(x: Int, y: Int, z: Int, voxel: Byte) {
        if (x < 0 || x >= width) return
        if (y < 0 || y >= height) return
        if (z < 0 || z >= depth) return
        setFast(x, y, z, voxel)
    }

    fun setFast(x: Int, y: Int, z: Int, voxel: Byte) {
        voxels[x + z * width + y * widthTimesHeight] = voxel
    }

    /** Creates a mesh out of the chunk, returning the number of indices produced
     * @return the number of vertices produced
     */
    fun calculateVertices(vertices: FloatArray): Int {
        var i = 0
        var vertexOffset = 0
        for (y in 0..height - 1) {
            for (z in 0..depth - 1) {
                var x = 0
                while (x < width) {
                    val voxel = voxels[i]
                    if (voxel.toInt() == 0) {
                        x++
                        i++
                        continue
                    }

                    if (y < height - 1) {
                        if (voxels[i + topOffset].toInt() == 0) vertexOffset = createTop(offset, x, y, z, vertices, vertexOffset)
                    } else {
                        vertexOffset = createTop(offset, x, y, z, vertices, vertexOffset)
                    }
                    if (y > 0) {
                        if (voxels[i + bottomOffset].toInt() == 0) vertexOffset = createBottom(offset, x, y, z, vertices, vertexOffset)
                    } else {
                        vertexOffset = createBottom(offset, x, y, z, vertices, vertexOffset)
                    }
                    if (x > 0) {
                        if (voxels[i + leftOffset].toInt() == 0) vertexOffset = createLeft(offset, x, y, z, vertices, vertexOffset)
                    } else {
                        vertexOffset = createLeft(offset, x, y, z, vertices, vertexOffset)
                    }
                    if (x < width - 1) {
                        if (voxels[i + rightOffset].toInt() == 0) vertexOffset = createRight(offset, x, y, z, vertices, vertexOffset)
                    } else {
                        vertexOffset = createRight(offset, x, y, z, vertices, vertexOffset)
                    }
                    if (z > 0) {
                        if (voxels[i + frontOffset].toInt() == 0) vertexOffset = createFront(offset, x, y, z, vertices, vertexOffset)
                    } else {
                        vertexOffset = createFront(offset, x, y, z, vertices, vertexOffset)
                    }
                    if (z < depth - 1) {
                        if (voxels[i + backOffset].toInt() == 0) vertexOffset = createBack(offset, x, y, z, vertices, vertexOffset)
                    } else {
                        vertexOffset = createBack(offset, x, y, z, vertices, vertexOffset)
                    }
                    x++
                    i++
                }
            }
        }
        return vertexOffset / VERTEX_SIZE
    }

    companion object {
        val VERTEX_SIZE = 6

        fun createTop(offset: Vector3, x: Int, y: Int, z: Int, vertices: FloatArray, vertexOffset: Int): Int {
            var vertexOffset = vertexOffset
            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 1f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 1f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 1f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 1f
            vertices[vertexOffset++] = 0f
            return vertexOffset
        }

        fun createBottom(offset: Vector3, x: Int, y: Int, z: Int, vertices: FloatArray, vertexOffset: Int): Int {
            var vertexOffset = vertexOffset
            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = -1f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = -1f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = -1f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = -1f
            vertices[vertexOffset++] = 0f
            return vertexOffset
        }

        fun createLeft(offset: Vector3, x: Int, y: Int, z: Int, vertices: FloatArray, vertexOffset: Int): Int {
            var vertexOffset = vertexOffset
            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = -1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = -1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = -1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = -1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            return vertexOffset
        }

        fun createRight(offset: Vector3, x: Int, y: Int, z: Int, vertices: FloatArray, vertexOffset: Int): Int {
            var vertexOffset = vertexOffset
            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            return vertexOffset
        }

        fun createFront(offset: Vector3, x: Int, y: Int, z: Int, vertices: FloatArray, vertexOffset: Int): Int {
            var vertexOffset = vertexOffset
            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 1f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 1f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 1f

            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 1f
            return vertexOffset
        }

        fun createBack(offset: Vector3, x: Int, y: Int, z: Int, vertices: FloatArray, vertexOffset: Int): Int {
            var vertexOffset = vertexOffset
            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = -1f

            vertices[vertexOffset++] = offset.x + x
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = -1f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y.toFloat() + 1f
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = -1f

            vertices[vertexOffset++] = offset.x + x.toFloat() + 1f
            vertices[vertexOffset++] = offset.y + y
            vertices[vertexOffset++] = offset.z + z.toFloat() + 1f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = 0f
            vertices[vertexOffset++] = -1f
            return vertexOffset
        }
    }
}
