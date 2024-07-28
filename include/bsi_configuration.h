/**
 * Copyright (c) Riven Zheng (zhengheiot@gmail.com).
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 **/
#ifndef _BSI_CONFIGURATION_H_
#define _BSI_CONFIGURATION_H_

#include "typedef.h"
#include "gd32f30x_gpio.h"

enum {
    BS_GPIO_PORT_A = (0u),
    BS_GPIO_PORT_B,
    BS_GPIO_PORT_C,
    BS_GPIO_PORT_NUM,
};

enum {
    BS_GPIO_PIN_0 = (0u),
    BS_GPIO_PIN_1,
    BS_GPIO_PIN_2,
    BS_GPIO_PIN_3,
    BS_GPIO_PIN_4,
    BS_GPIO_PIN_5,
    BS_GPIO_PIN_6,
    BS_GPIO_PIN_7,

    BS_GPIO_PIN_8,
    BS_GPIO_PIN_9,
    BS_GPIO_PIN_10,
    BS_GPIO_PIN_11,
    BS_GPIO_PIN_12,
    BS_GPIO_PIN_13,
    BS_GPIO_PIN_14,
    BS_GPIO_PIN_15,
    BS_GPIO_PIN_NUM,
};

static inline vu32_t gpio_base_regs_addr(u8_t inst)
{
    extern vu32_t g_gpio_base_regs[];

    if (inst >= BS_GPIO_PORT_NUM) {
        return NULL;
    }
    return g_gpio_base_regs[inst];
}

#endif


