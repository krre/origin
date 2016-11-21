@ECHO OFF
set validator=%VULKAN_SDK%/bin/glslangValidator -V -t
%validator% Base-Vk.vert -o Base.vert.spv
%validator% Base-Vk.frag -o Base.frag.spv
%validator% Font-Vk.vert -o Font.vert.spv
%validator% Font-Vk.frag -o Font.frag.spv
%validator% Surface.vert -o Surface.vert.spv
%validator% Surface.frag -o Surface.frag.spv
%validator% Voxel.vert -o Voxel.vert.spv
%validator% Voxel-Vk.frag -o Voxel.frag.spv
