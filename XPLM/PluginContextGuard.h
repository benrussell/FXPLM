//
// Created by br on 14/02/26.
//

#ifndef PLUGINCONTEXTGUARD_H
#define PLUGINCONTEXTGUARD_H

class PluginContextGuard {
private:
    Plugin* plugin;

public:
    explicit PluginContextGuard(Plugin* p) : plugin(p) {
        if (plugin) {
            plugin->takeContext();
        }
    }

    ~PluginContextGuard() {
        if (plugin) {
            plugin->releaseContext();
        }
    }

    // Prevent copying
    PluginContextGuard(const PluginContextGuard&) = delete;
    PluginContextGuard& operator=(const PluginContextGuard&) = delete;

    // Allow moving (optional, but good practice)
    PluginContextGuard(PluginContextGuard&& other) noexcept
        : plugin(other.plugin) {
        other.plugin = nullptr;
    }

    PluginContextGuard& operator=(PluginContextGuard&& other) noexcept {
        if (this != &other) {
            if (plugin) plugin->releaseContext();
            plugin = other.plugin;
            other.plugin = nullptr;
        }
        return *this;
    }
};

#endif //PLUGINCONTEXTGUARD_H
