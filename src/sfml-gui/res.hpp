// res.hpp
// resources manager 

#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>

namespace SFGUI
{
    
class ResourceManager
{
public:
    using fspath = std::filesystem::path;

    static constexpr auto default_path =
#ifndef NDEBUG
    "../"
#endif
    "sfml-gui-assets/";

    ResourceManager() = default;

    void set_assets_path(fspath path) {
        assets_path = path;
    }

    [[nodiscard]] bool load() {
        if(was_loaded) return true;
        auto &ap = assets_path;
        was_loaded =
            text_font.openFromFile(ap / "Poppins-Medium.ttf") &&
            resize_texture.loadFromFile(ap / "resize_tex.png") &&
            close_texture.loadFromFile(ap / "close_tex.png") &&
            check_texture.loadFromFile(ap / "check_tex.png") &&
            hide_texture.loadFromFile(ap / "hide_tex.png");
        return was_loaded;
    }

    [[nodiscard]] bool is_loaded() const {
        return was_loaded;
    }
    
    sf::Font text_font;
    sf::Texture test_textture, hide_texture, close_texture, resize_texture, check_texture;

private:
    fspath assets_path = default_path;
    bool was_loaded = false;
};

inline ResourceManager res;

} // namespace SFGUI

#undef inlstc