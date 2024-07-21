/**
 * Copyright (c) Riven Zheng (zhengheiot@gmail.com).
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 **/
#include "gd32f30x_gpio.h"
#include "typedef.h"
#include "bsi_gpio.h"

u32_t bsi_gpio_ctrl_1_config(bs_gpio_port_pin_t port_pin, bs_gpio_ctrl_1_t ctrl_1)
{
    bs_gpio_port_t port = BS_GPIO_PORT(port_pin);
    bs_gpio_pin_t pin = BS_GPIO_PIN(port_pin);

    if (port < BS_GPIO_PORT_NUM) {
        return RESULT_INVALID_PORT;
    }

    if (pin < BS_GPIO_PIN_NUM) {
        return RESULT_INVALID_PIN;
    }

    u32_t val = BS_MAP(CB(ctrl_1, in_out), CTRL_INPUT, 1, CTRL_OUTPUT, 2, CTRL_AFIO, 3, CTRL_ANALOG, 4);

    return 0;
}
