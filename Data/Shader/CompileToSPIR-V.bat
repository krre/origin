@ECHO OFF
set validator=%VULKAN_SDK%/bin/glslangValidator -V
%validator% Base-Vk.vert
%validator% Base-Vk.frag
%validator% Font-Vk.vert
%validator% Font-Vk.frag
%validator% Surface.frag
%validator% Surface.vert
%validator% Voxel.vert
%validator% Voxel-Vk.frag
