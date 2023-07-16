/*
 * Copyright (C) 2023 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PULSAR_DETAILS_SPRITEIMPL_IPP
#define PULSAR_DETAILS_SPRITEIMPL_IPP

#include "SpriteDecl.hpp"

namespace pul
{
    inline void Sprite::loadAsset(std::string_view assetPath) noexcept
    {
        m_Renderer = pul::Window::getRenderer();

        if (m_SdlTexture != nullptr)
        {
            SDL_DestroyTexture(m_SdlTexture);
        }

        SDL_Surface* surface = IMG_Load(assetPath.data());
        eqx::runtimeAssert(surface != NULL, IMG_GetError());
        m_Width = surface->w;
        m_Height = surface->h;

        m_SdlTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
        eqx::runtimeAssert(m_SdlTexture != NULL, SDL_GetError());

        SDL_FreeSurface(surface);
    }
}

#endif // PULSAR_DETAILS_SPRITEIMPL_IPP
