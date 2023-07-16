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

#ifndef PULSAR_DETAILS_ACCENTITYDECL_HPP
#define PULSAR_DETAILS_ACCENTITYDECL_HPP

#include "Dependencies.hpp"

#include "../Entity.hpp"

namespace pul
{
    class AccEntity : public Entity
    {
    public:
        explicit constexpr AccEntity() noexcept;
        explicit constexpr AccEntity(const Texture& texture) noexcept;

        inline void update() noexcept;

        inline void setMoveTarget(const eqx::Point<double>& target) noexcept;
        inline void setMoveDirection(const eqx::Point<double>& dir) noexcept;
        inline void setMoveSpeed(double speed) noexcept;
        inline void setMoveAcceleration(double acc) noexcept;
        inline void setMaxMoveSpeed(double speed) noexcept;

        inline const eqx::Point<double>& getMoveTarget() const noexcept;
        inline const eqx::Point<double>& getMoveDirection() const noexcept;
        inline double getMoveSpeed() const noexcept;
        inline double getMoveAcceleration() const noexcept;
        inline double getMaxMoveSpeed() const noexcept;

    private:
        eqx::Point<double> m_MoveTarget, m_MoveDirection;
        double m_MoveSpeed, m_MoveAcceleration, m_MaxMoveSpeed;

        eqx::Point<int> m_MoveTargetReached;
    };
}

#endif // PULSAR_DETAILS_ACCENTITYDECL_HPP
