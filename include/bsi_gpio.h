/**
 * Copyright (c) Riven Zheng (zhengheiot@gmail.com).
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 **/
#include "bsi_configuration.h"

/* The following table defined the At-BSI component number */
enum {
    RESULT_INVALID_PORT = 1u,
    RESULT_INVALID_PIN,
    RESULT_INVALID_IN_OUT,
};

typedef u8_t gpio_port_t;
typedef u8_t gpio_pin_t;
typedef u16_t gpio_num_t;

#define BS_GPIO_PORT(num) (gpio_port_t)(((gpio_pin_t)(num) >> 8u) & 0xFFu)
#define BS_GPIO_PIN(num)  (gpio_pin_t)((gpio_pin_t)(num) & 0xFFu)
#define BS_GPIO_NUM(port, pin) (gpio_num_t)((((gpio_port_t)(port) & 0xFFu) << 8u) | ((gpio_pin_t)(pin) & 0xFFu))

/* Start of section using anonymous unions */
#if defined(__CC_ARM)
#pragma push
#pragma anon_unions
#pragma diag_suppress 40
#elif defined(__ICCARM__)
#pragma language = extended
#elif defined(__TASKING__)
#pragma warning 586
#endif

typedef struct {
    u32_t in_out : 2;
    enum {
        CTRL_INPUT = (0u),
        CTRL_OUTPUT,
        CTRL_AFIO,
        CTRL_ANALOG,
    };

    u32_t out_mode : 1;
    enum {
        CTRL_PUSH_PULL = (0u),
        CTRL_OPEN_DRAIN,
    };

    u32_t speed : 2;
    enum {
        CTRL_SPEED_LEVEL_0 = (0u),
        CTRL_SPEED_LEVEL_1,
        CTRL_SPEED_LEVEL_2,
        CTRL_SPEED_LEVEL_3,
    };

    u32_t up_down : 2;
    enum {
        CTRL_FLOAT = (0u),
        CTRL_PULL_UP,
        CTRL_PULL_DOWN,
    };

    u32_t out_set : 1;
    enum {
        CTRL_LOW = (0u),
        CTRL_HIGH,
    };

    u32_t alternate : 4;
    enum {
        CTRL_AF_FUNC_0 = (0u),
        CTRL_AF_FUNC_1,
        CTRL_AF_FUNC_2,
        CTRL_AF_FUNC_3,
        CTRL_AF_FUNC_4,
        CTRL_AF_FUNC_5,
        CTRL_AF_FUNC_6,
        CTRL_AF_FUNC_7,

        CTRL_AF_FUNC_8,
        CTRL_AF_FUNC_9,
        CTRL_AF_FUNC_10,
        CTRL_AF_FUNC_11,
        CTRL_AF_FUNC_12,
        CTRL_AF_FUNC_13,
        CTRL_AF_FUNC_14,
        CTRL_AF_FUNC_15,
    };

    u32_t rsvd : 4;
} ctrl_1_b_t;

typedef struct {
    union {
        u32_t value;
        ctrl_1_b_t bits;
    };
} gpio_ctrl_1_t;

#define GPIO_CTRL_1_VAL(...) CM(ARGS_NUM(__VA_ARGS__))(in_out, out_mode, speed, up_down, out_set, alternate, __VA_ARGS__)

typedef struct {
    u32_t lock : 1;
    enum {
        CTRL_UNLOCK = (0u),
        CTRL_LOCK,
    };

    u32_t power : 1;
    enum {
        CTRL_POWER_ON = (0u),
        CTRL_POWER_OFF,
    };

    u32_t rsvd : 30;
} ctrl_2_b_t;

typedef struct {
    union {
        u32_t value;
        ctrl_2_b_t bits;
    };
} gpio_ctrl_2_t;

#define GPIO_CTRL_2_VAL(...) CM(ARGS_NUM(__VA_ARGS__))(lock, power, __VA_ARGS__)

#define CTRL_MSK   MASK_BIT(2)
#define CTRL_SET(n, val) val  << n

typedef struct {
    vu32_t ctrl;
    vu32_t out_mode;
    vu32_t out_speed;
    vu32_t up_down;
    vu32_t in_status;
    vu32_t out_ctrl;
    vu32_t bit_op;
    vu32_t lock;
    vu32_t alt_fun_0;
    vu32_t alt_fun_1;
    vu32_t clear;
    vu32_t toggle;
    vu32_t secure;
} gpio_regs_t;

/* End of section using anonymous unions */
#if defined(__CC_ARM)
#pragma pop
#elif defined(__TASKING__)
#pragma warning restore
#endif
