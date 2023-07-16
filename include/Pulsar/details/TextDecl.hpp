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

#ifndef PULSAR_DETAILS_TEXTDECL_HPP
#define PULSAR_DETAILS_TEXTDECL_HPP

#include "Dependencies.hpp"

#include "../Texture.hpp"

namespace pul
{
    /**
     *
     */
    class Text : public Texture
    {
    public:
        /**
         *
         */
        explicit inline Text() noexcept;

        /**
         *
         */
        explicit inline Text(std::string_view text, std::string_view fontPath,
            int pxHeight);

        /**
         *
         */
        inline void loadFont(std::string_view fontPath, int pxHeight) noexcept;

        /**
         *
         */
        inline void setText(std::string_view text, int pxHeight);

        /**
         *
         */
        inline std::string_view getText() const noexcept;

    private:
        std::string m_Text, m_FontPath;
    };
}

#endif // PULSAR_DETAILS_TEXTDECL_HPP
