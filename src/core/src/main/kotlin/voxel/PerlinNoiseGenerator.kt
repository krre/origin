package org.gagarin.voxel

import com.badlogic.gdx.graphics.Pixmap
import com.badlogic.gdx.graphics.Pixmap.Format
import com.badlogic.gdx.math.MathUtils

/** Adapted from [http://devmag.org.za/2009/04/25/perlin-noise/](http://devmag.org.za/2009/04/25/perlin-noise/)
 * @author badlogic
 */
object PerlinNoiseGenerator {
    fun generateWhiteNoise(width: Int, height: Int): Array<FloatArray> {
        val noise = Array(width) { FloatArray(height) }
        for (y in 0..height - 1) {
            for (x in 0..width - 1) {
                noise[x][y] = MathUtils.random()
            }
        }
        return noise
    }

    fun interpolate(x0: Float, x1: Float, alpha: Float): Float {
        return x0 * (1 - alpha) + alpha * x1
    }

    fun generateSmoothNoise(baseNoise: Array<FloatArray>, octave: Int): Array<FloatArray> {
        val width = baseNoise.size
        val height = baseNoise[0].size
        val smoothNoise = Array(width) { FloatArray(height) }

        val samplePeriod = 1 shl octave // calculates 2 ^ k
        val sampleFrequency = 1.0f / samplePeriod
        for (i in 0..width - 1) {
            val sample_i0 = i / samplePeriod * samplePeriod
            val sample_i1 = (sample_i0 + samplePeriod) % width // wrap around
            val horizontal_blend = (i - sample_i0) * sampleFrequency

            for (j in 0..height - 1) {
                val sample_j0 = j / samplePeriod * samplePeriod
                val sample_j1 = (sample_j0 + samplePeriod) % height // wrap around
                val vertical_blend = (j - sample_j0) * sampleFrequency
                val top = interpolate(baseNoise[sample_i0][sample_j0], baseNoise[sample_i1][sample_j0], horizontal_blend)
                val bottom = interpolate(baseNoise[sample_i0][sample_j1], baseNoise[sample_i1][sample_j1], horizontal_blend)
                smoothNoise[i][j] = interpolate(top, bottom, vertical_blend)
            }
        }

        return smoothNoise
    }

    fun generatePerlinNoise(baseNoise: Array<FloatArray>, octaveCount: Int): Array<FloatArray> {
        val width = baseNoise.size
        val height = baseNoise[0].size
        val smoothNoise = arrayOfNulls<Array<FloatArray>>(octaveCount) // an array of 2D arrays containing
        val persistance = 0.7f

        for (i in 0..octaveCount - 1) {
            smoothNoise[i] = generateSmoothNoise(baseNoise, i)
        }

        val perlinNoise = Array(width) { FloatArray(height) } // an array of floats initialised to 0

        var amplitude = 1.0f
        var totalAmplitude = 0.0f

        for (octave in octaveCount - 1 downTo 0) {
            amplitude *= persistance
            totalAmplitude += amplitude

            for (i in 0..width - 1) {
                for (j in 0..height - 1) {
                    perlinNoise[i][j] += smoothNoise[octave]!![i][j] * amplitude
                }
            }
        }

        for (i in 0..width - 1) {
            for (j in 0..height - 1) {
                perlinNoise[i][j] /= totalAmplitude
            }
        }

        return perlinNoise
    }

    fun generatePerlinNoise(width: Int, height: Int, octaveCount: Int): Array<FloatArray> {
        val baseNoise = generateWhiteNoise(width, height)
        return generatePerlinNoise(baseNoise, octaveCount)
    }

    fun generateHeightMap(width: Int, height: Int, min: Int, max: Int, octaveCount: Int): ByteArray {
        val baseNoise = generateWhiteNoise(width, height)
        val noise = generatePerlinNoise(baseNoise, octaveCount)
        val bytes = ByteArray(baseNoise.size * baseNoise[0].size)
        var idx = 0
        val range = max - min
        for (y in 0..height - 1) {
            for (x in 0..width - 1) {
                bytes[idx++] = (noise[x][y] * range + min).toByte()
            }
        }
        return bytes
    }

    fun generatePixmap(width: Int, height: Int, min: Int, max: Int, octaveCount: Int): Pixmap {
        val bytes = generateHeightMap(width, height, min, max, octaveCount)
        val pixmap = Pixmap(width, height, Format.RGBA8888)
        var i = 0
        var idx = 0
        while (i < bytes.size) {
            val `val` = bytes[i]
            pixmap.pixels.put(idx++, `val`)
            pixmap.pixels.put(idx++, `val`)
            pixmap.pixels.put(idx++, `val`)
            pixmap.pixels.put(idx++, 255.toByte())
            i++
        }
        return pixmap
    }

    fun generateVoxels(voxelWorld: VoxelWorld, min: Int, max: Int, octaveCount: Int) {
        val heightMap = PerlinNoiseGenerator.generateHeightMap(voxelWorld.voxelsX, voxelWorld.voxelsZ, min, max, octaveCount)
        var idx = 0
        for (z in 0..voxelWorld.voxelsZ - 1) {
            for (x in 0..voxelWorld.voxelsX - 1) {
                voxelWorld.setColumn(x.toFloat(), heightMap[idx++].toFloat(), z.toFloat(), 1.toByte())
                // voxelWorld.set(x, heightMap[idx++], z, (byte)1);
            }
        }
    }
}
