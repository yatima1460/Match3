#include "Rendering/TexturePointer.hpp"
#include <string>
#include <SDL_surface.h>
#include <cassert>
#include "Rendering/Graphics.hpp"

namespace TexturePointer
{

Vector2i GetSize(const TexturePointerData &texture)
{
    Vector2i size;
    assert(texture.internal != nullptr);
    SDL_QueryTexture(texture.internal, nullptr, nullptr, &size.x, &size.y);
    return size;
}

} // namespace TexturePointer
