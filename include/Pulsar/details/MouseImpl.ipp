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

#ifndef PULSAR_DETAILS_MOUSEIMPL_IPP
#define PULSAR_DETAILS_MOUSEIMPL_IPP

#include "MouseDecl.hpp"

namespace pul
{
    inline void Mouse::handleEvent(const SDL_Event& e) noexcept
    {
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            m_CurrentLocation = eqx::Point<double>(e.motion.x, e.motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                m_LeftButtonState = Mouse::Button::Down;
                m_LeftClickDownLocation = m_CurrentLocation;
            }
            else if (e.button.button == SDL_BUTTON_RIGHT)
            {
                m_RightButtonState = Mouse::Button::Down;
                m_RightClickDownLocation = m_CurrentLocation;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                m_LeftButtonState = Mouse::Button::Up;
                m_LeftClickUpLocation = m_CurrentLocation;
            }
            else if (e.button.button == SDL_BUTTON_RIGHT)
            {
                m_RightButtonState = Mouse::Button::Up;
                m_RightClickUpLocation = m_CurrentLocation;
            }
            break;
        default:
            break;
        }
    }

    [[nodiscard]] inline const eqx::Point<double>& Mouse::getCurrentLocation()
        noexcept
    {
        return m_CurrentLocation;
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getLeftClickDownLocation() noexcept
    {
        return m_LeftClickDownLocation;
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getLeftClickUpLocation() noexcept
    {
        return m_LeftClickUpLocation;
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getRightClickDownLocation() noexcept
    {
        return m_RightClickDownLocation;
    }

    [[nodiscard]] inline const eqx::Point<double>&
        Mouse::getRightClickUpLocation() noexcept
    {
        return m_RightClickUpLocation;
    }
}

#endif // PULSAR_DETAILS_MOUSEIMPL_IPP
