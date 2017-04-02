@ECHO OFF
set validator=%VULKAN_SDK%\bin\glslangValidator -V -t
%validator% Base.vert -o Base.vert.spv
%validator% Base.frag -o Base.frag.spv
%validator% Voxel.vert -o Voxel.vert.spv
%validator% Voxel.frag -o Voxel.frag.spv
%validator% SDF.vert -o SDF.vert.spv
%validator% SDF.frag -o SDF.frag.spv
