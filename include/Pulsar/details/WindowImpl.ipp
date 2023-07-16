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

#ifndef PULSAR_DETAILS_WINDOWIMPL_IPP
#define PULSAR_DETAILS_WINDOWIMPL_IPP

#include "WindowDecl.hpp"

namespace pul
{
    inline void Window::createWindow() noexcept
    {
        eqx::runtimeAssert(SDL_Init(SDL_INIT_VIDEO) == 0, SDL_GetError());
        eqx::runtimeAssert(TTF_Init() == 0, TTF_GetError());

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            eqx::println("Warning: Linear Texture Filtering Not Enabled!");
        }

        s_Window = SDL_CreateWindow(s_Name->c_str(), SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, s_Width, s_Height, SDL_WINDOW_HIDDEN);
        eqx::runtimeAssert(s_Window != NULL, SDL_GetError());

        s_Renderer = SDL_CreateRenderer(s_Window, -1,
            SDL_RENDERER_ACCELERATED);
        eqx::runtimeAssert(s_Renderer != NULL, SDL_GetError());

        SDL_SetRenderDrawColor(s_Renderer, 0x00, 0x00, 0x00, 0x00);
    }

    inline void Window::init(std::string_view name, int width,
        int height)
    {
        static auto nameStorage = std::string(name);
        s_Name = &nameStorage;
        s_Width = width;
        s_Height = height;
        static auto efStore = std::function<void(const SDL_Event & e)>();
        static auto ufStore = std::function<void()>();
        static auto rfStore = std::function<void()>();
        s_EventFunction = &efStore;
        s_UpdateFunction = &ufStore;
        s_RenderFunction = &rfStore;

        createWindow();
        setEventFunction([]([[maybe_unused]] const SDL_Event& e) {  });
        setUpdateFunction([]() {});
        setRenderFunction([]() {});
        s_IsInit = true;
    }

    [[nodiscard]] inline bool Window::isInit() noexcept
    {
        return s_IsInit;
    }

    inline void Window::show()
    {
        eqx::runtimeAssert(isInit(),
            "Call pul::Window::init(...) Before Calling pul::Window::show()");

        using namespace eqx::TimeTypes;

        auto e = SDL_Event();
        auto frameTimer = eqx::StopWatch();

        SDL_ShowWindow(s_Window);
        while (true)
        {
            if (frameTimer.readTime<t_US>() <
                (1'000'000 / (s_FrameRate + 5)))
            {
                continue;
            }

            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    goto DOUBLEBREAK;
                }
                else
                {
                    Mouse::handleEvent(e);
                    std::invoke(*s_EventFunction, e);
                }
            }

            std::invoke(*s_UpdateFunction);

            SDL_RenderClear(s_Renderer);
            std::invoke(*s_RenderFunction);
            SDL_RenderPresent(s_Renderer);

            s_LastFrameTime = frameTimer.readSeconds();
            s_TotalTime += frameTimer.getSeconds();
            s_LongestFrame = std::ranges::max(s_LongestFrame, s_LastFrameTime);
            s_ShortestFrame = std::ranges::min(s_ShortestFrame, 
                s_LastFrameTime);
            s_FrameCount++;
            frameTimer.start();
        }

    DOUBLEBREAK:

        SDL_DestroyRenderer(s_Renderer);
        SDL_DestroyWindow(s_Window);

        SDL_Quit();
    }

    [[nodiscard]] inline double Window::getDeltaTime() noexcept
    {
        return s_LastFrameTime;
    }

    [[nodiscard]] inline std::string Window::getFPSInfo()
    {
        const auto avgFT = std::round((s_TotalTime /
            static_cast<double>(s_FrameCount)) * 1E6);
        const auto avgFPS = std::round(static_cast<double>(s_FrameCount) /
            s_TotalTime);
        const auto longestFrame =
            static_cast<unsigned long long>(s_LongestFrame * 1'000'000.0);
        const auto shortestFrame =
            static_cast<unsigned long long>(s_ShortestFrame * 1'000'000.0);

        s_FrameCount = 0ULL;
        s_LongestFrame = 0.0;
        s_ShortestFrame = std::numeric_limits<double>::max();
        s_TotalTime = 0.0;

        return (std::stringstream() <<
            "=========================\n" <<
            "Average Frame Time: " << avgFT << "us\n" <<
            "Average FPS: " << avgFPS << " fps\n" <<
            "Longest Frame Time: " << longestFrame << "us\n" <<
            "ShortestFrame: " << shortestFrame << "us\n" <<
            "=========================\n").str();
    }

    inline void Window::printFPSInfo(long long ms)
    {
        static auto timer = eqx::StopWatch();
        if (timer.readTime() > ms)
        {
            eqx::println(getFPSInfo());
            timer.start();
        }
    }

    inline void Window::setFrameRate(int frameRate) noexcept
    {
        s_FrameRate = frameRate;
    }

    inline void Window::setEventFunction(
        const std::function<void(const SDL_Event& e)>& func)
    {
        *s_EventFunction = func;
    }

    inline void Window::setUpdateFunction(const std::function<void()>& func)
    {
        *s_UpdateFunction = func;
    }

    inline void Window::setRenderFunction(const std::function<void()>& func)
    {
        *s_RenderFunction = func;
    }

    [[nodiscard]] inline int Window::getFrameRate() noexcept
    {
        return s_FrameRate;
    }

    [[nodiscard]] inline int Window::getWidth() noexcept
    {
        return s_Width;
    }

    [[nodiscard]] inline int Window::getHeight() noexcept
    {
        return s_Height;
    }

    [[nodiscard]] inline SDL_Renderer* Window::getRenderer() noexcept
    {
        eqx::runtimeAssert(isInit(), "pul::Window::init(...) Was Not Called");
        return s_Renderer;
    }
}

#endif // PULSAR_DETAILS_WINDOWIMPL_IPP
