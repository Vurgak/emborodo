#pragma once

#include <memory>

#include <glm/vec2.hpp>

namespace en
{

enum class key : short
{
    space,
    apostrophe,
    comma,
    minus,
    period,
    slash,
    d0,
    d1,
    d2,
    d3,
    d4,
    d5,
    d6,
    d7,
    d8,
    d9,
    semicolon,
    equal,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    left_bracket,
    backslash,
    right_bracket,
    grave_accent,
    escape,
    enter,
    tab,
    backspace,
    insert,
    delete_,
    right,
    left,
    down,
    up,
    page_up,
    page_down,
    home,
    end,
    caps_lock,
    scroll_lock,
    num_lock,
    print_screen,
    pause,
    f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12,
    f13,
    f14,
    f15,
    f16,
    f17,
    f18,
    f19,
    f20,
    f21,
    f22,
    f23,
    f24,
    f25,
    kp0,
    kp1,
    kp2,
    kp3,
    kp4,
    kp5,
    kp6,
    kp7,
    kp8,
    kp9,
    kp_decimal,
    kp_divide,
    kp_multiply,
    kp_subtract,
    kp_add,
    kp_enter,
    kp_equal,
    left_shift,
    left_control,
    left_alt,
    left_super,
    right_shift,
    right_control,
    right_alt,
    right_super,
    menu,

    unknown,
};

enum class button : char
{
    left,
    middle,
    right,
    b4,
    b5,
    b6,
    b7,
    b8,

    unknown,
};

enum key_state : char
{
    down,
    pressed,
    released,
    up,
};

class input
{
public:
    virtual ~input() = default;

    virtual void update() = 0;

    [[nodiscard]]
    virtual bool is_key_pressed(key key) = 0;

    [[nodiscard]]
    virtual bool is_key_released(key key) = 0;

    [[nodiscard]]
    virtual bool is_key_down(key key) = 0;

    [[nodiscard]]
    virtual bool is_key_up(key key) = 0;

    /// Gets the current mouse position in the window.
    [[nodiscard]]
    virtual glm::ivec2 get_mouse_position() = 0;

    /// Gets the offset that mouse moved since last frame.
    [[nodiscard]]
    virtual glm::ivec2 get_mouse_delta() = 0;

    [[nodiscard]]
    virtual glm::ivec2 get_scroll_movement() = 0;

    [[nodiscard]]
    virtual int get_horizontal_scroll_movement() = 0;

    [[nodiscard]]
    virtual int get_vertical_scroll_movement() = 0;

    [[nodiscard]]
    virtual bool is_button_pressed(button button) = 0;

    [[nodiscard]]
    virtual bool is_button_released(button button) = 0;

    [[nodiscard]]
    virtual bool is_button_down(button button) = 0;

    [[nodiscard]]
    virtual bool is_button_up(button button) = 0;
};

using input_ptr = std::unique_ptr<input>;

}
