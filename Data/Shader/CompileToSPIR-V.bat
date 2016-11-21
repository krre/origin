@ECHO OFF
set validator=%VULKAN_SDK%/bin/glslangValidator -V
%validator% Base.vert
%validator% Base-Vk.frag
%validator% Font.vert
%validator% Font.frag
%validator% Surface.frag
%validator% Surface.vert
%validator% Voxel.vert
%validator% Voxel-Vk.frag
