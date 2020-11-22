//
// Created by kookie on 20. 11. 2020..
//

#
#include "InputMonitor.h"
#include <algorithm>

std::vector<kki::InputMonitor*> kki::InputMonitor::_instances;

kki::InputMonitor::InputMonitor(const std::vector<int>& keys, Context& context) : _enabled(true) , _context(context){
    for (int key : keys) {
        _keys[key] = false;
    }
    _instances.push_back(this);
    use();
}

kki::InputMonitor::~InputMonitor() {
    _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}

bool kki::InputMonitor::keyDown(int key) {
    if (_enabled) {
        // Find iterator of the key
        auto it = _keys.find(key);
        // If the key is in the map, return its value
        return it != _keys.end() && it->second;
    }
    return false;
}

void kki::InputMonitor::setKeyDown(int key, bool down) {
    auto it = _keys.find(key);
    if (it != _keys.end()) {
        it->second = down;
    }
}

void kki::InputMonitor::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Send key event to all KeyInput instances
    for (kki::InputMonitor* keyInput : _instances) {
        keyInput->setKeyDown(key, action != GLFW_RELEASE);
    }
}

void kki::InputMonitor::addKey(int key) {
    _keys[key] = false;
}

void kki::InputMonitor::addKeys(const std::vector<int>& keys) {
    for(auto key : keys){
        addKey(key);
    }
}
