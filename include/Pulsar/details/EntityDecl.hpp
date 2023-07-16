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

#ifndef PULSAR_DETAILS_ENTITYDECL_HPP
#define PULSAR_DETAILS_ENTITYDECL_HPP

#include "Dependencies.hpp"

#include "../Texture.hpp"

namespace pul
{
    class Entity
    {
    public:
        explicit constexpr Entity() noexcept;
        explicit constexpr Entity(const Texture& texture) noexcept;

        inline void render() const noexcept;

        inline void setTexture(const Texture& texture) noexcept;
        inline void setConfig(const Texture::Config& config) noexcept;
        inline void setLocation(const eqx::Point<double>& loc) noexcept;
        inline void setDrawBox(const eqx::Rectangle<double>& box) noexcept;
        inline void setAngle(double angle) noexcept;
        inline void setRotationPoint(const eqx::Point<double>& point) noexcept;
        inline void setFlip(SDL_RendererFlip flip) noexcept;
        inline void setColor(const Texture::Color& color) noexcept;

        inline Texture::Config& editConfig() noexcept;
        inline eqx::Rectangle<double>& editDrawBox() noexcept;

        inline const Texture& getTexture() const noexcept;
        inline const Texture::Config& getConfig() const noexcept;
        inline eqx::Point<double> getLocation() const noexcept;
        inline const eqx::Rectangle<double>& getDrawBox() const noexcept;
        inline double getAngle() const noexcept;
        inline const eqx::Point<double>& getRotationPoint() const noexcept;
        inline SDL_RendererFlip getFlip() const noexcept;
        inline const Texture::Color& getColor() const noexcept;

    protected:
        const Texture* m_Texture;
        Texture::Config m_Config;
    };
}

#endif // PULSAR_DETAILS_ENTITYDECL_HPP
