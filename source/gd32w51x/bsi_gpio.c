/**
 * Copyright (c) Riven Zheng (zhengheiot@gmail.com).
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 **/
#include "gd32f30x_gpio.h"
#include "typedef.h"
#include "bsi_gpio.h"

u32_t gpio_ctrl_1_set(gpio_num_t port_pin, gpio_ctrl_1_t setting)
{
    gpio_port_t port = BS_GPIO_PORT(port_pin);
    gpio_pin_t pin = BS_GPIO_PIN(port_pin);
    if (port < BS_GPIO_PORT_NUM) {
        return RESULT_INVALID_PORT;
    }
    if (pin < BS_GPIO_PIN_NUM) {
        return RESULT_INVALID_PIN;
    }

    gpio_regs_t *pGpioRegs = (gpio_regs_t *)gpio_base_regs_addr(port);
    u32_t ctrl = pGpioRegs->ctrl;
    u32_t pd = pGpioRegs->up_down;
    u32_t omode = pGpioRegs->out_mode;
    u32_t speed = pGpioRegs->out_speed;
    u16_t octrl = pGpioRegs->out_ctrl;
    u32_t alt_0 = pGpioRegs->alt_fun_0;
    u32_t alt_1 = pGpioRegs->alt_fun_1;

    u32_t val = BS_MAP(CB(setting, in_out),
                       CTRL_INPUT, 0u,
                       CTRL_OUTPUT, 1u,
                       CTRL_AFIO, 2u,
                       CTRL_ANALOG, 3u);
    BV_CS(ctrl, 2, pin, val);

    val = BS_MAP(CB(setting, up_down),
                 CTRL_FLOAT, 0u,
                 CTRL_PULL_UP, 1u,
                 CTRL_PULL_DOWN, 2u);
    BV_CS(pd, 2, pin, val);

    val = BS_MAP(CB(setting, out_mode),
                 CTRL_PUSH_PULL, 0u,
                 CTRL_OPEN_DRAIN, 1u);
    BV_CS(omode, 1, pin, val);

    val = BS_MAP(CB(setting, speed),
                 CTRL_SPEED_LEVEL_0, 0u,
                 CTRL_SPEED_LEVEL_1, 1u,
                 CTRL_SPEED_LEVEL_2, 2u,
                 CTRL_SPEED_LEVEL_3, 3u);
    BV_CS(speed, 2, pin, val);

    val = BS_MAP(CB(setting, out_set),
                 CTRL_LOW, 0u,
                 CTRL_HIGH, 1u);

    if (val) {
        BV_S(octrl, 1, pin, val);
    } else {
        BV_C(octrl, 1, pin);
    }

    val = BS_MAP(CB(setting, alternate),
                 CTRL_AF_FUNC_0, 0u,
                 CTRL_AF_FUNC_1, 1u,
                 CTRL_AF_FUNC_2, 2u,
                 CTRL_AF_FUNC_3, 3u,
                 CTRL_AF_FUNC_4, 4u,
                 CTRL_AF_FUNC_5, 5u,
                 CTRL_AF_FUNC_6, 6u,
                 CTRL_AF_FUNC_7, 7u,
                 CTRL_AF_FUNC_8, 8u,
                 CTRL_AF_FUNC_9, 9u,
                 CTRL_AF_FUNC_10, 10u,
                 CTRL_AF_FUNC_11, 11u,
                 CTRL_AF_FUNC_12, 12u,
                 CTRL_AF_FUNC_13, 13u,
                 CTRL_AF_FUNC_14, 14u,
                 CTRL_AF_FUNC_15, 15);

    if (pin < 8) {
        BV_CS(alt_0, 4, pin, val);
    } else {
        BV_CS(alt_1, 4, pin - 8, val);
    }

    pGpioRegs->ctrl = ctrl;
    pGpioRegs->up_down = pd;
    pGpioRegs->out_mode = omode;
    pGpioRegs->out_speed = speed;
    pGpioRegs->alt_fun_0 = alt_0;
    pGpioRegs->alt_fun_1 = alt_1;

    return 0;
}
