@ECHO OFF
set validator=%VULKAN_SDK%\bin\glslangValidator -V -t
%validator% Base.vert -o Base.vert.spv
%validator% Base.frag -o Base.frag.spv
%validator% Font.vert -o Font.vert.spv
%validator% Font.frag -o Font.frag.spv
%validator% Surface.vert -o Surface.vert.spv
%validator% Surface.frag -o Surface.frag.spv
%validator% Voxel.vert -o Voxel.vert.spv
%validator% Voxel.frag -o Voxel.frag.spv
