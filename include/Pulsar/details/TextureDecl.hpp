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

#ifndef PULSAR_DETAILS_TEXTUREDECL_HPP
#define PULSAR_DETAILS_TEXTUREDECL_HPP

#include "Dependencies.hpp"

#include "../Window.hpp"

namespace pul
{
    /**
     *
     */
    class Texture
    {
    public:
        /**
         *
         */
        struct Color
        {
            /**
             *
             */
            explicit constexpr Color() noexcept;

            /**
             *
             */
            constexpr Color(std::uint8_t red, std::uint8_t green,
                std::uint8_t blue,
                std::uint8_t alpha = static_cast<std::uint8_t>(255)) noexcept;

            /**
             *
             */
            Color(const Color&) = default;
            Color(Color&&) = default;
            Color& operator= (const Color&) = default;
            Color& operator= (Color&&) = default;
            ~Color() = default;

            std::uint8_t r, g, b, a;
        };

        struct Config
        {
            /**
             *
             */
            explicit constexpr Config() noexcept;

            /**
             *
             */
            explicit constexpr Config(const eqx::Rectangle<double>& dest,
                double ang, const eqx::Point<double>& rotP,
                SDL_RendererFlip flp, const Color& col) noexcept;

            /**
             *
             */
            Config(const Config&) = default;
            Config(Config&&) = default;
            Config& operator= (const Config&) = default;
            Config& operator= (Config&&) = default;
            ~Config() = default;

            eqx::Rectangle<double> destination;
            double angle;
            eqx::Point<double> rotationPoint;
            SDL_RendererFlip flip;
            Color color;
        };

        /**
         *
         */
        explicit constexpr Texture() noexcept;

        /**
         *
         */
        constexpr Texture(Texture&& other) noexcept;

        /**
         *
         */
        constexpr Texture& operator= (Texture&& other) noexcept;

        /**
         *
         */
        constexpr ~Texture() noexcept;

        /**
         *
         */
        Texture(const Texture&) = delete;
        Texture& operator= (const Texture&) = delete;

        /**
         *
         */
        inline void render(const eqx::Point<double>& location) const noexcept;

        /**
         *
         */
        inline void render(const eqx::Rectangle<double>& destination)
            const noexcept;

        /**
         *
         */
        inline void render(const Config& config) const noexcept;

    protected:
        int m_Width, m_Height;

        SDL_Texture* m_SdlTexture;
        SDL_Renderer* m_Renderer;
    };
}

#endif // PULSAR_DETAILS_TEXTUREDECL_HPP
