//
// Created by kookie on 20. 11. 2020..
//

#ifndef PIXIES_INPUTMONITOR_H
#define PIXIES_INPUTMONITOR_H
#include <vector>
#include <map>
#include "Context.h"

namespace kki{
    class InputMonitor {
        Context& _context;
        std::map<int, bool> _keys;
        bool _enabled;

        void setKeyDown(int key, bool isDown);
        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static std::vector<InputMonitor*> _instances;

    public:
        // keys: Keys to monitor
        explicit InputMonitor(const std::vector<int>& keys, Context& context);
        void addKey(int key);
        void addKeys(const std::vector<int>& keys);
        ~InputMonitor();
        // Get key state
        bool keyDown(int key);
        inline bool operator[](int key){ return keyDown(key); }
        // See _isEnabled for details
        bool isEnabled() const { return _enabled; }
        void enable(bool value) { _enabled = value;}

        void use(){
            _context.setKeyCallback(callback);
        }
    };
}



#endif //PIXIES_INPUTMONITOR_H
