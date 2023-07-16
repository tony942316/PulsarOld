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

#ifndef PULSAR_DETAILS_ACCENTITYIMPL_IPP
#define PULSAR_DETAILS_ACCENTITYIMPL_IPP

#include "AccEntityDecl.hpp"

namespace pul
{
    constexpr AccEntity::AccEntity() noexcept
        :
        Entity(),
        m_MoveTarget(),
        m_MoveDirection(),
        m_MoveSpeed(0.0),
        m_MoveAcceleration(0.0),
        m_MaxMoveSpeed(0.0),
        m_MoveTargetReached()
    {
    }

    constexpr AccEntity::AccEntity(const Texture& texture) noexcept
        :
        Entity(texture),
        m_MoveTarget(),
        m_MoveDirection(),
        m_MoveSpeed(0.0),
        m_MoveAcceleration(0.0),
        m_MaxMoveSpeed(0.0),
        m_MoveTargetReached()
    {
    }

    inline void AccEntity::update() noexcept
    {
        const auto dt = pul::Window::getDeltaTime();
        const auto loc = getDrawBox();

        if (m_MoveTargetReached != eqx::Point<int>(1, 1))
        {
            const auto dampenedAcc =
                eqx::distance(loc.getTopLeftPoint(), m_MoveTarget) >
                m_MoveSpeed * 0.5 ?
                m_MoveAcceleration : -m_MoveAcceleration * 2;
            m_MoveSpeed = std::ranges::clamp(
                m_MoveSpeed + dampenedAcc * dt,
                m_MaxMoveSpeed * 0.2, m_MaxMoveSpeed);

            editDrawBox().x += m_MoveDirection.x * m_MoveSpeed * dt;
            if (eqx::getSign(m_MoveTarget.x - getDrawBox().x) !=
                eqx::getSign(m_MoveTarget.x - loc.x))
            {
                editDrawBox().x = m_MoveTarget.x;
                m_MoveTargetReached.x = 1;
            }

            editDrawBox().y += m_MoveDirection.y * m_MoveSpeed * dt;
            if (eqx::getSign(m_MoveTarget.y - getDrawBox().y) !=
                eqx::getSign(m_MoveTarget.y - loc.y))
            {
                editDrawBox().y = m_MoveTarget.y;
                m_MoveTargetReached.y = 1;
            }
        }
        else
        {
            m_MoveSpeed = 0.0;
        }
    }

    inline void AccEntity::setMoveTarget(const eqx::Point<double>& target)
        noexcept
    {
        m_MoveTarget = target;
        m_MoveTargetReached = eqx::Point<int>();
        setMoveDirection(target - getLocation());
    }

    inline void AccEntity::setMoveDirection(const eqx::Point<double>& dir)
        noexcept
    {
        m_MoveDirection = eqx::normalize(dir);
    }

    inline void AccEntity::setMoveSpeed(double speed) noexcept
    {
        m_MoveSpeed = speed;
    }

    inline void AccEntity::setMoveAcceleration(double acc) noexcept
    {
        m_MoveAcceleration = acc;
    }

    inline void AccEntity::setMaxMoveSpeed(double speed) noexcept
    {
        m_MaxMoveSpeed = speed;
    }

    inline const eqx::Point<double>& AccEntity::getMoveTarget() const noexcept
    {
        return m_MoveTarget;
    }

    inline const eqx::Point<double>& AccEntity::getMoveDirection()
        const noexcept
    {
        return m_MoveDirection;
    }

    inline double AccEntity::getMoveSpeed() const noexcept
    {
        return m_MoveSpeed;
    }

    inline double AccEntity::getMoveAcceleration() const noexcept
    {
        return m_MoveAcceleration;
    }

    inline double AccEntity::getMaxMoveSpeed() const noexcept
    {
        return m_MaxMoveSpeed;
    }
}

#endif // PULSAR_DETAILS_ACCENTITYIMPL_IPP
