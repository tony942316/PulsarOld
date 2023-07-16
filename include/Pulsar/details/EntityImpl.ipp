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

#ifndef PULSAR_DETAILS_ENTITYIMPL_IPP
#define PULSAR_DETAILS_ENTITYIMPL_IPP

#include "EntityDecl.hpp"

namespace pul
{
    constexpr Entity::Entity() noexcept
        :
        m_Texture(nullptr),
        m_Config()
    {
    }

    constexpr Entity::Entity(const Texture& texture) noexcept
        :
        m_Texture(&texture),
        m_Config()
    {
    }

    inline void Entity::render() const noexcept
    {
        m_Texture->render(m_Config);
    }

    inline void Entity::setTexture(const Texture& texture) noexcept
    {
        m_Texture = &texture;
    }

    inline void Entity::setConfig(const Texture::Config& config) noexcept
    {
        m_Config = config;
    }

    inline void Entity::setLocation(const eqx::Point<double>& loc) noexcept
    {
        m_Config.destination.setLocation(loc);
    }

    inline void Entity::setDrawBox(const eqx::Rectangle<double>& box) noexcept
    {
        m_Config.destination = box;
    }

    inline void Entity::setAngle(double angle) noexcept
    {
        m_Config.angle = angle;
    }

    inline void Entity::setRotationPoint(const eqx::Point<double>& point)
        noexcept
    {
        m_Config.rotationPoint = point;
    }

    inline void Entity::setFlip(SDL_RendererFlip flip) noexcept
    {
        m_Config.flip = flip;
    }

    inline void Entity::setColor(const Texture::Color& color) noexcept
    {
        m_Config.color = color;
    }

    inline Texture::Config& Entity::editConfig() noexcept
    {
        return m_Config;
    }

    inline eqx::Rectangle<double>& Entity::editDrawBox() noexcept
    {
        return m_Config.destination;
    }

    inline const Texture& Entity::getTexture() const noexcept
    {
        return *m_Texture;
    }
    inline const Texture::Config& Entity::getConfig() const noexcept
    {
        return m_Config;
    }

    inline eqx::Point<double> Entity::getLocation() const noexcept
    {
        return m_Config.destination.getTopLeftPoint();
    }

    inline const eqx::Rectangle<double>& Entity::getDrawBox() const noexcept
    {
        return m_Config.destination;
    }

    inline double Entity::getAngle() const noexcept
    {
        return m_Config.angle;
    }

    inline const eqx::Point<double>& Entity::getRotationPoint() const noexcept
    {
        return m_Config.rotationPoint;
    }

    inline SDL_RendererFlip Entity::getFlip() const noexcept
    {
        return m_Config.flip;
    }

    inline const Texture::Color& Entity::getColor() const noexcept
    {
        return m_Config.color;
    }
}

#endif // PULSAR_DETAILS_ENTITYIMPL_IPP
