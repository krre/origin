#include "VulkanManager.h"

VulkanManager::VulkanManager() {

}

bool VulkanManager::init() {
    error = std::string(initError) + "";
    return true;
}
