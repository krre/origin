@ECHO OFF
set validator=%VULKAN_SDK%\bin\glslangValidator -V -t
%validator% OctreeFarm\FrontLightOctree.vert -o OctreeFarm\FrontLightOctree.vert.spv
%validator% OctreeFarm\FrontLightOctree.frag -o OctreeFarm\FrontLightOctree.frag.spv
%validator% BaseShape.vert -o BaseShape.vert.spv
%validator% BaseShape.frag -o BaseShape.frag.spv
%validator% Voxel.vert -o Voxel.vert.spv
%validator% Voxel.frag -o Voxel.frag.spv
%validator% SDF.vert -o SDF.vert.spv
%validator% SDF.frag -o SDF.frag.spv
%validator% RaycastOctree.vert -o RaycastOctree.vert.spv
%validator% RaycastOctree.frag -o RaycastOctree.frag.spv
%validator% Line.vert -o Line.vert.spv
%validator% Line.frag -o Line.frag.spv
