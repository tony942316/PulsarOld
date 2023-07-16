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

#ifndef PULSAR_DETAILS_TEXTIMPL_IPP
#define PULSAR_DETAILS_TEXTIMPL_IPP

#include "TextDecl.hpp"

namespace pul
{
    inline Text::Text() noexcept
        :
        Texture(),
        m_Text(""),
        m_FontPath("")
    {
    }

    inline Text::Text(std::string_view text, std::string_view fontPath,
        int pxHeight)
        :
        Texture(),
        m_Text(text),
        m_FontPath(fontPath)
    {
        loadFont(fontPath, pxHeight);
    }

    inline void Text::loadFont(std::string_view fontPath, int pxHeight)
        noexcept
    {
        m_Renderer = pul::Window::getRenderer();

        if (m_SdlTexture != nullptr)
        {
            SDL_DestroyTexture(m_SdlTexture);
        }

        TTF_Font* font = TTF_OpenFont(fontPath.data(), pxHeight);
        eqx::runtimeAssert(font != NULL, TTF_GetError());

        SDL_Surface* surface = TTF_RenderText_Solid(font, m_Text.c_str(),
            SDL_Color({ 255, 255, 255, 255 }));
        eqx::runtimeAssert(surface != NULL, TTF_GetError());
        m_Width = surface->w;
        m_Height = surface->h;

        m_SdlTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
        eqx::runtimeAssert(surface != NULL, SDL_GetError());

        TTF_CloseFont(font);
        SDL_FreeSurface(surface);
    }

    inline void Text::setText(std::string_view text, int pxHeight)
    {
        m_Text = text;
        loadFont(m_FontPath, pxHeight);
    }

    inline std::string_view Text::getText() const noexcept
    {
        return m_Text;
    }
}

#endif // PULSAR_DETAILS_TEXTIMPL_IPP
