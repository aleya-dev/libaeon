// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/platform/exception.h>
#include "sdl2_context.h"
#include "sdl2_window.h"

namespace aeon::platform
{

static auto convert_sdl_scancode(const SDL_Scancode scan_code) noexcept -> keyboard_key
{
    switch (scan_code) // NOLINT(clang-diagnostic-switch-enum)
    {
        case SDL_SCANCODE_A:
            return keyboard_key::a;
        case SDL_SCANCODE_B:
            return keyboard_key::b;
        case SDL_SCANCODE_C:
            return keyboard_key::c;
        case SDL_SCANCODE_D:
            return keyboard_key::d;
        case SDL_SCANCODE_E:
            return keyboard_key::e;
        case SDL_SCANCODE_F:
            return keyboard_key::f;
        case SDL_SCANCODE_G:
            return keyboard_key::g;
        case SDL_SCANCODE_H:
            return keyboard_key::h;
        case SDL_SCANCODE_I:
            return keyboard_key::i;
        case SDL_SCANCODE_J:
            return keyboard_key::j;
        case SDL_SCANCODE_K:
            return keyboard_key::k;
        case SDL_SCANCODE_L:
            return keyboard_key::l;
        case SDL_SCANCODE_M:
            return keyboard_key::m;
        case SDL_SCANCODE_N:
            return keyboard_key::n;
        case SDL_SCANCODE_O:
            return keyboard_key::o;
        case SDL_SCANCODE_P:
            return keyboard_key::p;
        case SDL_SCANCODE_Q:
            return keyboard_key::q;
        case SDL_SCANCODE_R:
            return keyboard_key::r;
        case SDL_SCANCODE_S:
            return keyboard_key::s;
        case SDL_SCANCODE_T:
            return keyboard_key::t;
        case SDL_SCANCODE_U:
            return keyboard_key::u;
        case SDL_SCANCODE_V:
            return keyboard_key::v;
        case SDL_SCANCODE_W:
            return keyboard_key::w;
        case SDL_SCANCODE_X:
            return keyboard_key::x;
        case SDL_SCANCODE_Y:
            return keyboard_key::y;
        case SDL_SCANCODE_Z:
            return keyboard_key::z;
        case SDL_SCANCODE_1:
            return keyboard_key::key_1;
        case SDL_SCANCODE_2:
            return keyboard_key::key_2;
        case SDL_SCANCODE_3:
            return keyboard_key::key_3;
        case SDL_SCANCODE_4:
            return keyboard_key::key_4;
        case SDL_SCANCODE_5:
            return keyboard_key::key_5;
        case SDL_SCANCODE_6:
            return keyboard_key::key_6;
        case SDL_SCANCODE_7:
            return keyboard_key::key_7;
        case SDL_SCANCODE_8:
            return keyboard_key::key_8;
        case SDL_SCANCODE_9:
            return keyboard_key::key_9;
        case SDL_SCANCODE_0:
            return keyboard_key::key_0;
        case SDL_SCANCODE_RETURN:
            return keyboard_key::enter;
        case SDL_SCANCODE_ESCAPE:
            return keyboard_key::escape;
        case SDL_SCANCODE_BACKSPACE:
            return keyboard_key::backspace;
        case SDL_SCANCODE_TAB:
            return keyboard_key::tab;
        case SDL_SCANCODE_SPACE:
            return keyboard_key::space;
        case SDL_SCANCODE_MINUS:
            return keyboard_key::minus;
        case SDL_SCANCODE_EQUALS:
            return keyboard_key::equal;
        case SDL_SCANCODE_LEFTBRACKET:
            return keyboard_key::left_bracket;
        case SDL_SCANCODE_RIGHTBRACKET:
            return keyboard_key::right_bracket;
        case SDL_SCANCODE_BACKSLASH:
            return keyboard_key::backslash;
        case SDL_SCANCODE_SEMICOLON:
            return keyboard_key::semicolon;
        case SDL_SCANCODE_APOSTROPHE:
            return keyboard_key::apostrophe;
        case SDL_SCANCODE_GRAVE:
            return keyboard_key::grave_accent;
        case SDL_SCANCODE_COMMA:
            return keyboard_key::comma;
        case SDL_SCANCODE_PERIOD:
            return keyboard_key::period;
        case SDL_SCANCODE_SLASH:
            return keyboard_key::forward_slash;
        case SDL_SCANCODE_CAPSLOCK:
            return keyboard_key::caps_lock;
        case SDL_SCANCODE_F1:
            return keyboard_key::f1;
        case SDL_SCANCODE_F2:
            return keyboard_key::f2;
        case SDL_SCANCODE_F3:
            return keyboard_key::f3;
        case SDL_SCANCODE_F4:
            return keyboard_key::f4;
        case SDL_SCANCODE_F5:
            return keyboard_key::f5;
        case SDL_SCANCODE_F6:
            return keyboard_key::f6;
        case SDL_SCANCODE_F7:
            return keyboard_key::f7;
        case SDL_SCANCODE_F8:
            return keyboard_key::f8;
        case SDL_SCANCODE_F9:
            return keyboard_key::f9;
        case SDL_SCANCODE_F10:
            return keyboard_key::f10;
        case SDL_SCANCODE_F11:
            return keyboard_key::f11;
        case SDL_SCANCODE_F12:
            return keyboard_key::f12;
        case SDL_SCANCODE_PRINTSCREEN:
            return keyboard_key::print_screen;
        case SDL_SCANCODE_SCROLLLOCK:
            return keyboard_key::scroll_lock;
        case SDL_SCANCODE_PAUSE:
            return keyboard_key::pause;
        case SDL_SCANCODE_INSERT:
            return keyboard_key::insert;
        case SDL_SCANCODE_HOME:
            return keyboard_key::home;
        case SDL_SCANCODE_PAGEUP:
            return keyboard_key::page_up;
        case SDL_SCANCODE_DELETE:
            return keyboard_key::del;
        case SDL_SCANCODE_END:
            return keyboard_key::end;
        case SDL_SCANCODE_PAGEDOWN:
            return keyboard_key::page_down;
        case SDL_SCANCODE_RIGHT:
            return keyboard_key::right;
        case SDL_SCANCODE_LEFT:
            return keyboard_key::left;
        case SDL_SCANCODE_DOWN:
            return keyboard_key::down;
        case SDL_SCANCODE_UP:
            return keyboard_key::up;
        case SDL_SCANCODE_NUMLOCKCLEAR:
            return keyboard_key::num_lock;
        case SDL_SCANCODE_KP_DIVIDE:
            return keyboard_key::kp_divide;
        case SDL_SCANCODE_KP_MULTIPLY:
            return keyboard_key::kp_multiply;
        case SDL_SCANCODE_KP_MINUS:
            return keyboard_key::kp_subtract;
        case SDL_SCANCODE_KP_PLUS:
            return keyboard_key::kp_add;
        case SDL_SCANCODE_KP_ENTER:
            return keyboard_key::kp_enter;
        case SDL_SCANCODE_KP_1:
            return keyboard_key::kp_1;
        case SDL_SCANCODE_KP_2:
            return keyboard_key::kp_2;
        case SDL_SCANCODE_KP_3:
            return keyboard_key::kp_3;
        case SDL_SCANCODE_KP_4:
            return keyboard_key::kp_4;
        case SDL_SCANCODE_KP_5:
            return keyboard_key::kp_5;
        case SDL_SCANCODE_KP_6:
            return keyboard_key::kp_6;
        case SDL_SCANCODE_KP_7:
            return keyboard_key::kp_7;
        case SDL_SCANCODE_KP_8:
            return keyboard_key::kp_8;
        case SDL_SCANCODE_KP_9:
            return keyboard_key::kp_9;
        case SDL_SCANCODE_KP_0:
            return keyboard_key::kp_0;
        case SDL_SCANCODE_KP_PERIOD:
            return keyboard_key::kp_decimal;
        case SDL_SCANCODE_KP_EQUALS:
            return keyboard_key::kp_equal;
        case SDL_SCANCODE_F13:
            return keyboard_key::f13;
        case SDL_SCANCODE_F14:
            return keyboard_key::f14;
        case SDL_SCANCODE_F15:
            return keyboard_key::f15;
        case SDL_SCANCODE_F16:
            return keyboard_key::f16;
        case SDL_SCANCODE_F17:
            return keyboard_key::f17;
        case SDL_SCANCODE_F18:
            return keyboard_key::f18;
        case SDL_SCANCODE_F19:
            return keyboard_key::f19;
        case SDL_SCANCODE_F20:
            return keyboard_key::f20;
        case SDL_SCANCODE_F21:
            return keyboard_key::f21;
        case SDL_SCANCODE_F22:
            return keyboard_key::f22;
        case SDL_SCANCODE_F23:
            return keyboard_key::f23;
        case SDL_SCANCODE_F24:
            return keyboard_key::f24;
        case SDL_SCANCODE_MENU:
            return keyboard_key::menu;
        case SDL_SCANCODE_INTERNATIONAL1:
            return keyboard_key::world_1;
        case SDL_SCANCODE_INTERNATIONAL2:
            return keyboard_key::world_2;
        case SDL_SCANCODE_LCTRL:
            return keyboard_key::left_control;
        case SDL_SCANCODE_LSHIFT:
            return keyboard_key::left_shift;
        case SDL_SCANCODE_LALT:
            return keyboard_key::left_alt;
        case SDL_SCANCODE_LGUI:
            return keyboard_key::left_super;
        case SDL_SCANCODE_RCTRL:
            return keyboard_key::right_control;
        case SDL_SCANCODE_RSHIFT:
            return keyboard_key::right_shift;
        case SDL_SCANCODE_RALT:
            return keyboard_key::right_alt;
        case SDL_SCANCODE_RGUI:
            return keyboard_key::right_super;
        default:
            return keyboard_key::unknown;
    }
}

static auto convert_sdl_mouse_button_index(const int index) noexcept -> mouse_button
{
    switch (index)
    {
        case SDL_BUTTON_LEFT:
            return mouse_button::left;
        case SDL_BUTTON_MIDDLE:
            return mouse_button::middle;
        case SDL_BUTTON_RIGHT:
            return mouse_button::right;
        case SDL_BUTTON_X1:
            return mouse_button::button4;
        case SDL_BUTTON_X2:
            return mouse_button::button5;
        case SDL_BUTTON(6):
            return mouse_button::button6;
        case SDL_BUTTON(7):
            return mouse_button::button7;
        case SDL_BUTTON(8):
            return mouse_button::button8;
        default:
            return mouse_button::unknown;
    }
}

sdl2_context::sdl2_context()
    : base_context{}
{
    if (SDL_Init(0) != 0)
        throw platform_exception{std::string{"Failed to initialize SDL2: "} + SDL_GetError()};
}

sdl2_context::~sdl2_context()
{
    SDL_Quit();
}

auto sdl2_context::create_window(const window_create_info &info) -> std::unique_ptr<window>
{
    return std::make_unique<sdl2_window>(info, *this);
}

void sdl2_context::poll_events() noexcept
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                const auto sdl_window = SDL_GetWindowFromID(event.window.windowID);

                if (auto *window = static_cast<sdl2_window *>(SDL_GetWindowData(sdl_window, sdl2_window::this_ptr_key)))
                    window->on_closing();

                break;
            }
            case SDL_KEYDOWN:
                handle_key(convert_sdl_scancode(event.key.keysym.scancode), event.key.keysym.scancode,
                           keyboard_key_state::pressed);
                break;
            case SDL_KEYUP:
                handle_key(convert_sdl_scancode(event.key.keysym.scancode), event.key.keysym.scancode,
                           keyboard_key_state::released);
                break;
            case SDL_MOUSEMOTION:
                handle_mouse_move({static_cast<double>(event.motion.x), static_cast<double>(event.motion.y)});
                break;
            case SDL_MOUSEBUTTONDOWN:
                handle_mouse_button(convert_sdl_mouse_button_index(event.button.button), mouse_button_state::pressed);
                break;
            case SDL_MOUSEBUTTONUP:
                handle_mouse_button(convert_sdl_mouse_button_index(event.button.button), mouse_button_state::released);
                break;
            case SDL_MOUSEWHEEL:
                handle_mouse_scroll(static_cast<double>(event.wheel.y));
                break;
            default:
                break;
        }
    }
}

void sdl2_context::handle_key(const keyboard_key key, const std::uint32_t scan_code,
                              const keyboard_key_state state) const noexcept
{
    input_listeners().invoke_each(&input_events::on_key, *this, key, scan_code, state);
}

void sdl2_context::handle_mouse_move(const math::vector2<double> position) const noexcept
{
    input_listeners().invoke_each(&input_events::on_mouse_move, *this, position);
}

void sdl2_context::handle_mouse_button(const mouse_button button, const mouse_button_state state) const noexcept
{
    input_listeners().invoke_each(&input_events::on_mouse_button, *this, button, state);
}

void sdl2_context::handle_mouse_scroll(const double delta) const noexcept
{
    input_listeners().invoke_each(&input_events::on_mouse_scroll, *this, delta);
}

} // namespace aeon::platform
