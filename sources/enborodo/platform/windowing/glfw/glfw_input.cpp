#include "glfw_input.hpp"

#include <iostream>

#include <glfw/glfw3.h>

#include <enborodo/platform/windowing/glfw/glfw_window.hpp>

namespace
{

en::key convert_keycode_to_key(const int keycode)
{
    switch (keycode)
    {
        case GLFW_KEY_SPACE: return en::key::space;
        case GLFW_KEY_APOSTROPHE: return en::key::apostrophe;
        case GLFW_KEY_COMMA: return en::key::comma;
        case GLFW_KEY_MINUS: return en::key::minus;
        case GLFW_KEY_PERIOD: return en::key::period;
        case GLFW_KEY_SLASH: return en::key::slash;
        case GLFW_KEY_0: return en::key::d0;
        case GLFW_KEY_1: return en::key::d1;
        case GLFW_KEY_2: return en::key::d2;
        case GLFW_KEY_3: return en::key::d3;
        case GLFW_KEY_4: return en::key::d4;
        case GLFW_KEY_5: return en::key::d5;
        case GLFW_KEY_6: return en::key::d6;
        case GLFW_KEY_7: return en::key::d7;
        case GLFW_KEY_8: return en::key::d8;
        case GLFW_KEY_9: return en::key::d9;
        case GLFW_KEY_SEMICOLON: return en::key::semicolon;
        case GLFW_KEY_EQUAL: return en::key::equal;
        case GLFW_KEY_A: return en::key::a;
        case GLFW_KEY_B: return en::key::b;
        case GLFW_KEY_C: return en::key::c;
        case GLFW_KEY_D: return en::key::d;
        case GLFW_KEY_E: return en::key::e;
        case GLFW_KEY_F: return en::key::f;
        case GLFW_KEY_G: return en::key::g;
        case GLFW_KEY_H: return en::key::h;
        case GLFW_KEY_I: return en::key::i;
        case GLFW_KEY_J: return en::key::j;
        case GLFW_KEY_K: return en::key::k;
        case GLFW_KEY_L: return en::key::l;
        case GLFW_KEY_M: return en::key::m;
        case GLFW_KEY_N: return en::key::n;
        case GLFW_KEY_O: return en::key::o;
        case GLFW_KEY_P: return en::key::p;
        case GLFW_KEY_Q: return en::key::q;
        case GLFW_KEY_R: return en::key::r;
        case GLFW_KEY_S: return en::key::s;
        case GLFW_KEY_T: return en::key::t;
        case GLFW_KEY_U: return en::key::u;
        case GLFW_KEY_V: return en::key::v;
        case GLFW_KEY_W: return en::key::w;
        case GLFW_KEY_X: return en::key::x;
        case GLFW_KEY_Y: return en::key::y;
        case GLFW_KEY_Z: return en::key::z;
        case GLFW_KEY_LEFT_BRACKET: return en::key::left_bracket;
        case GLFW_KEY_BACKSLASH: return en::key::backslash;
        case GLFW_KEY_RIGHT_BRACKET: return en::key::right_bracket;
        case GLFW_KEY_GRAVE_ACCENT: return en::key::grave_accent;
        case GLFW_KEY_ESCAPE: return en::key::escape;
        case GLFW_KEY_ENTER: return en::key::enter;
        case GLFW_KEY_TAB: return en::key::tab;
        case GLFW_KEY_BACKSPACE: return en::key::backspace;
        case GLFW_KEY_INSERT: return en::key::insert;
        case GLFW_KEY_DELETE: return en::key::delete_;
        case GLFW_KEY_RIGHT: return en::key::right;
        case GLFW_KEY_LEFT: return en::key::left;
        case GLFW_KEY_DOWN: return en::key::down;
        case GLFW_KEY_UP: return en::key::up;
        case GLFW_KEY_PAGE_UP: return en::key::page_up;
        case GLFW_KEY_PAGE_DOWN: return en::key::page_down;
        case GLFW_KEY_HOME: return en::key::home;
        case GLFW_KEY_END: return en::key::end;
        case GLFW_KEY_CAPS_LOCK: return en::key::caps_lock;
        case GLFW_KEY_SCROLL_LOCK: return en::key::scroll_lock;
        case GLFW_KEY_NUM_LOCK: return en::key::num_lock;
        case GLFW_KEY_PRINT_SCREEN: return en::key::print_screen;
        case GLFW_KEY_PAUSE: return en::key::pause;
        case GLFW_KEY_F1: return en::key::f1;
        case GLFW_KEY_F2: return en::key::f2;
        case GLFW_KEY_F3: return en::key::f3;
        case GLFW_KEY_F4: return en::key::f4;
        case GLFW_KEY_F5: return en::key::f5;
        case GLFW_KEY_F6: return en::key::f6;
        case GLFW_KEY_F7: return en::key::f7;
        case GLFW_KEY_F8: return en::key::f8;
        case GLFW_KEY_F9: return en::key::f9;
        case GLFW_KEY_F10: return en::key::f10;
        case GLFW_KEY_F11: return en::key::f11;
        case GLFW_KEY_F12: return en::key::f12;
        case GLFW_KEY_F13: return en::key::f13;
        case GLFW_KEY_F14: return en::key::f14;
        case GLFW_KEY_F15: return en::key::f15;
        case GLFW_KEY_F16: return en::key::f16;
        case GLFW_KEY_F17: return en::key::f17;
        case GLFW_KEY_F18: return en::key::f18;
        case GLFW_KEY_F19: return en::key::f19;
        case GLFW_KEY_F20: return en::key::f20;
        case GLFW_KEY_F21: return en::key::f21;
        case GLFW_KEY_F22: return en::key::f22;
        case GLFW_KEY_F23: return en::key::f23;
        case GLFW_KEY_F24: return en::key::f24;
        case GLFW_KEY_F25: return en::key::f25;
        case GLFW_KEY_KP_0: return en::key::kp0;
        case GLFW_KEY_KP_1: return en::key::kp1;
        case GLFW_KEY_KP_2: return en::key::kp2;
        case GLFW_KEY_KP_3: return en::key::kp3;
        case GLFW_KEY_KP_4: return en::key::kp4;
        case GLFW_KEY_KP_5: return en::key::kp5;
        case GLFW_KEY_KP_6: return en::key::kp6;
        case GLFW_KEY_KP_7: return en::key::kp7;
        case GLFW_KEY_KP_8: return en::key::kp8;
        case GLFW_KEY_KP_9: return en::key::kp9;
        case GLFW_KEY_KP_DECIMAL: return en::key::kp_decimal;
        case GLFW_KEY_KP_DIVIDE: return en::key::kp_divide;
        case GLFW_KEY_KP_MULTIPLY: return en::key::kp_multiply;
        case GLFW_KEY_KP_SUBTRACT: return en::key::kp_subtract;
        case GLFW_KEY_KP_ADD: return en::key::kp_add;
        case GLFW_KEY_KP_ENTER: return en::key::kp_enter;
        case GLFW_KEY_KP_EQUAL: return en::key::kp_equal;
        case GLFW_KEY_LEFT_SHIFT: return en::key::left_shift;
        case GLFW_KEY_LEFT_CONTROL: return en::key::left_control;
        case GLFW_KEY_LEFT_ALT: return en::key::left_alt;
        case GLFW_KEY_LEFT_SUPER: return en::key::left_super;
        case GLFW_KEY_RIGHT_SHIFT: return en::key::right_shift;
        case GLFW_KEY_RIGHT_CONTROL: return en::key::right_control;
        case GLFW_KEY_RIGHT_ALT: return en::key::right_alt;
        case GLFW_KEY_RIGHT_SUPER: return en::key::right_super;
        case GLFW_KEY_MENU: return en::key::menu;
        default: return en::key::unknown;
    }
}

en::button convert_button(const int button)
{
      switch (button)
    {
        case GLFW_MOUSE_BUTTON_LEFT: return en::button::left;
        case GLFW_MOUSE_BUTTON_RIGHT: return en::button::right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return en::button::middle;
        case GLFW_MOUSE_BUTTON_4: return en::button::b4;
        case GLFW_MOUSE_BUTTON_5: return en::button::b5;
        case GLFW_MOUSE_BUTTON_6: return en::button::b6;
        case GLFW_MOUSE_BUTTON_7: return en::button::b7;
        case GLFW_MOUSE_BUTTON_8: return en::button::b8;
        default: return en::button::unknown;
    }
}

}

namespace en
{

static void handle_key_event(GLFWwindow* handle, const int keycode, [[maybe_unused]] int scancode, const int action, [[maybe_unused]] int mods)
{
    const auto window = static_cast<glfw_window*>(glfwGetWindowUserPointer(handle));
    auto& input = dynamic_cast<glfw_input&>(window->get_input());

    const auto key = convert_keycode_to_key(keycode);
    if (key == key::unknown)
        return;

    switch (action)
    {
        case GLFW_PRESS:
            input.set_key_state(key, pressed);
            break;

        case GLFW_RELEASE:
            input.set_key_state(key, released);
            break;

        case GLFW_REPEAT:
            break;

        default:
            assert(false);
    }
}

static void handle_button_event(GLFWwindow* handle, const int glfw_button, const int action, [[maybe_unused]] int mods)
{
    const auto window = static_cast<glfw_window*>(glfwGetWindowUserPointer(handle));
    auto& input = dynamic_cast<glfw_input&>(window->get_input());

    const auto button = convert_button(glfw_button);
    if (button == button::unknown)
        return;

    switch (action)
    {
        case GLFW_PRESS:
            input.set_button_state(button, pressed);
        break;

        case GLFW_RELEASE:
            input.set_button_state(button, released);
        break;

        case GLFW_REPEAT:
            break;

        default:
            assert(false);
    }
}

static void handle_mouse_movement(GLFWwindow* handle, const double horizontal_position, const double vertical_position)
{
    const auto window = static_cast<glfw_window*>(glfwGetWindowUserPointer(handle));
    auto& input = dynamic_cast<glfw_input&>(window->get_input());

    const glm::ivec2 current_position{static_cast<int>(horizontal_position), static_cast<int>(vertical_position)};
    input.set_mouse_position(current_position);
}

glfw_input::glfw_input(glfw_window& window)
{
    m_keys.fill(up);
    m_buttons.fill(up);

    auto* handle = static_cast<GLFWwindow*>(window.get_handle());
    glfwSetKeyCallback(handle, handle_key_event);
    glfwSetMouseButtonCallback(handle, handle_button_event);
    glfwSetCursorPosCallback(handle, handle_mouse_movement);
}

void glfw_input::update()
{
    for (auto& key_state : m_keys)
    {
        if (key_state == pressed)
        {
            key_state = down;
        }
        else if (key_state == released)
        {
            key_state = up;
        }
    }

    for (auto& button_state : m_buttons)
    {
        if (button_state == pressed)
        {
            button_state = down;
        }
        else if (button_state == released)
        {
            button_state = up;
        }
    }

    m_mouse_delta = glm::vec2{0.0f};
}

bool glfw_input::is_key_pressed(const key key)
{
    return m_keys[static_cast<short>(key)] == pressed;
}

bool glfw_input::is_key_released(const key key)
{
    return m_keys[static_cast<short>(key)] == released;
}

bool glfw_input::is_key_down(const key key)
{
    const auto key_state = m_keys[static_cast<short>(key)];
    return key_state == pressed || key_state == down;
}

bool glfw_input::is_key_up(const key key)
{
    const auto key_state = m_keys[static_cast<short>(key)];
    return key_state == released || key_state == up;
}

glm::ivec2 glfw_input::get_mouse_position()
{
    return m_mouse_position;
}

glm::ivec2 glfw_input::get_mouse_delta()
{
    return m_mouse_delta;
}

float glfw_input::get_mouse_scroll()
{
    throw std::exception{"function not implemented"};
}

bool glfw_input::is_button_pressed(button button)
{
    return m_buttons[static_cast<int>(button)] == pressed;
}

bool glfw_input::is_button_released(button button)
{
    return m_buttons[static_cast<char>(button)] == released;
}

bool glfw_input::is_button_down(button button)
{
    const auto button_state = m_buttons[static_cast<char>(button)];
    return button_state == pressed || button_state == down;
}

bool glfw_input::is_button_up(button button)
{
    const auto button_state = m_buttons[static_cast<char>(button)];
    return button_state == released || button_state == up;
}

void glfw_input::set_key_state(const key key, const key_state state)
{
    m_keys[static_cast<short>(key)] = state;
}

void glfw_input::set_button_state(const button button, const key_state state)
{
    m_buttons[static_cast<char>(button)] = state;
}

void glfw_input::set_mouse_position(glm::ivec2 position)
{
    m_mouse_delta = position - m_mouse_position;
    m_mouse_position = position;
}

}
