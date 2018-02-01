validator="$VULKAN_SDK/bin/glslangValidator -V -t"
$validator BaseShape.vert -o BaseShape.vert.spv
$validator BaseShape.frag -o BaseShape.frag.spv
$validator Voxel.vert -o Voxel.vert.spv
$validator Voxel.frag -o Voxel.frag.spv
$validator SDF.vert -o SDF.vert.spv
$validator SDF.frag -o SDF.frag.spv
