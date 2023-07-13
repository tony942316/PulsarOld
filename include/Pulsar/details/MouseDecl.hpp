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

#ifndef PULSAR_DETAILS_MOUSEDECL_HPP
#define PULSAR_DETAILS_MOUSEDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    /**
     *
     */
    class Mouse
    {
    public:
        /**
         *
         */
        enum class Button
        {
            Up,
            Down
        };

        Mouse() = delete;
        Mouse(const Mouse&) = delete;
        Mouse(Mouse&&) = delete;
        Mouse& operator= (const Mouse&) = delete;
        Mouse& operator= (Mouse&&) = delete;
        ~Mouse() = delete;

        /**
         *
         */
        static inline void handleEvent(const SDL_Event& e) noexcept;
        [[nodiscard]] static inline const eqx::Point<double>&
            getCurrentLocation() noexcept;

        /**
         *
         */
        [[nodiscard]] static inline const eqx::Point<double>&
            getLeftClickDownLocation() noexcept;

        /**
         *
         */
        [[nodiscard]] static inline const eqx::Point<double>&
            getLeftClickUpLocation() noexcept;

        /**
         *
         */
        [[nodiscard]] static inline const eqx::Point<double>&
            getRightClickDownLocation() noexcept;

        /**
         *
         */
        [[nodiscard]] static inline const eqx::Point<double>&
            getRightClickUpLocation() noexcept;

    private:
        constinit static inline auto m_CurrentLocation = eqx::Point<double>(),
            m_LeftClickDownLocation = eqx::Point<double>(),
            m_LeftClickUpLocation = eqx::Point<double>(),
            m_RightClickDownLocation = eqx::Point<double>(),
            m_RightClickUpLocation = eqx::Point<double>();
        constinit static inline auto m_LeftButtonState = Mouse::Button::Up,
            m_RightButtonState = Mouse::Button::Up;
    };
}

#endif // PULSAR_DETAILS_MOUSEDECL_HPP
