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

#ifndef PULSAR_DETAILS_TEXTUREIMPL_IPP
#define PULSAR_DETAILS_TEXTUREIMPL_IPP

#include "TextureDecl.hpp"

namespace pul
{
    constexpr Texture::Color::Color() noexcept
        :
        r(static_cast<std::uint8_t>(255)),
        g(static_cast<std::uint8_t>(255)),
        b(static_cast<std::uint8_t>(255)),
        a(static_cast<std::uint8_t>(255))
    {
    }

    constexpr Texture::Color::Color(std::uint8_t red, std::uint8_t green,
        std::uint8_t blue, std::uint8_t alpha) noexcept
        :
        r(red),
        g(green),
        b(blue),
        a(alpha)
    {
    }

    constexpr Texture::Config::Config() noexcept
        :
        destination(),
        angle(0.0),
        rotationPoint(),
        flip(SDL_FLIP_NONE),
        color()
    {
    }

    constexpr Texture::Config::Config(const eqx::Rectangle<double>& dest,
        double ang, const eqx::Point<double>& rotP, SDL_RendererFlip flp,
        const Color& col) noexcept
        :
        destination(dest),
        angle(ang),
        rotationPoint(rotP),
        flip(flp),
        color(col)
    {
    }

    constexpr Texture::Texture() noexcept
        :
        m_Width(0),
        m_Height(0),
        m_SdlTexture(nullptr),
        m_Renderer(nullptr)
    {
    }

    constexpr Texture::Texture(Texture&& other) noexcept
        :
        m_Width(std::move(other.m_Width)),
        m_Height(std::move(other.m_Height)),
        m_SdlTexture(std::move(other.m_SdlTexture)),
        m_Renderer(std::move(other.m_Renderer))
    {
        other.m_SdlTexture = nullptr;
    }

    constexpr Texture& Texture::operator= (Texture&& other) noexcept
    {
        std::swap(m_Width, other.m_Width);
        std::swap(m_Height, other.m_Height);
        std::swap(m_SdlTexture, other.m_SdlTexture);
        std::swap(m_Renderer, other.m_Renderer);

        return *this;
    }

    constexpr Texture::~Texture() noexcept
    {
        if (m_SdlTexture != nullptr)
        {
            SDL_DestroyTexture(m_SdlTexture);
        }
    }

    inline void Texture::render(const eqx::Point<double>& location)
        const noexcept
    {
        render(eqx::Rectangle<double>(location.x, location.y,
            static_cast<double>(m_Width), static_cast<double>(m_Height)));
    }

    inline void Texture::render(const eqx::Rectangle<double>& destination)
        const noexcept
    {
        render(Config(destination, 0.0, eqx::Point<double>(), SDL_FLIP_NONE,
            Color()));
    }

    inline void Texture::render(const Config& config) const noexcept
    {
        const SDL_Rect source = {
            0, 0, m_Width, m_Height };

        const SDL_Rect dest = {
            static_cast<int>(config.destination.x),
            static_cast<int>(config.destination.y),
            static_cast<int>(config.destination.w),
            static_cast<int>(config.destination.h) };

        const SDL_Point rotationPoint = {
            static_cast<int>(config.rotationPoint.x),
            static_cast<int>(config.rotationPoint.y) };

        eqx::runtimeAssert(SDL_SetTextureColorMod(m_SdlTexture,
            config.color.r, config.color.g, config.color.b) == 0,
            SDL_GetError());
        eqx::runtimeAssert(SDL_SetTextureAlphaMod(m_SdlTexture,
            config.color.a) == 0, SDL_GetError());

        eqx::runtimeAssert(SDL_RenderCopyEx(m_Renderer, m_SdlTexture,
            &source, &dest, config.angle, &rotationPoint, config.flip) == 0,
            SDL_GetError());

        eqx::runtimeAssert(SDL_SetTextureColorMod(m_SdlTexture, 255, 255,
            255) == 0, SDL_GetError());
        eqx::runtimeAssert(SDL_SetTextureAlphaMod(m_SdlTexture, 255) == 0,
            SDL_GetError());
    }
}

#endif // PULSAR_DETAILS_TEXTUREIMPL_IPP
