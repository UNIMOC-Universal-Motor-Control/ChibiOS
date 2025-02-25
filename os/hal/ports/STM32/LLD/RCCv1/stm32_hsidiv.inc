/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    RCCv1/stm32_hsidiv.inc
 * @brief   Shared HSI with divider clock handler.
 *
 * @addtogroup STM32_HSIDIV_HANDLER
 * @{
 */

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/**
 * @brief   HSI16 clock frequency.
 */
#define STM32_HSI64CLK              64000000U

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Registry checks for robustness.*/
#if !defined(STM32_RCC_HAS_HSI)
#error "STM32_RCC_HAS_HSI not defined in stm32_registry.h"
#endif

/* Checks on configurations.*/
#if !defined(STM32_HSI_ENABLED)
#error "STM32_HSI_ENABLED not defined in mcuconf.h"
#endif

#if !defined(STM32_HSIDIV_VALUE)
#error "STM32_HSIDIV_VALUE not defined in mcuconf.h"
#endif

#if (STM32_HSIDIV_VALUE != 1) && (STM32_HSIDIV_VALUE != 2) &&               \
    (STM32_HSIDIV_VALUE != 4) && (STM32_HSIDIV_VALUE != 8)
#error "invalid STM32_HSIDIV_VALUE value"
#endif

/**
 * @brief   Divided HSI clock.
 */
#if STM32_HSI_ENABLED || defined(__DOXYGEN__)
#define STM32_HSICLK                (STM32_HSI64CLK / STM32_HSIDIV_VALUE)
#else
#define STM32_HSICLK                0
#endif

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

__STATIC_INLINE void hsi_enable(void) {

  RCC->CR |= RCC_CR_HSION;
  while ((RCC->CR & RCC_CR_HSIRDY) == 0U) {
    /* Waiting for HSI16 activation.*/
  }
}

__STATIC_INLINE void hsi_disable(void) {

  RCC->CR &= ~RCC_CR_HSION;
}

__STATIC_INLINE void hsi_reset(void) {

  /* Making sure HSI is active and ready.*/
  hsi_enable();

  /* Clocking from HSI, in case HSI was not the default source.*/
  RCC->CFGR1 = STM32_SW_HSI;
  while ((RCC->CFGR1 & STM32_SWS_MASK) != STM32_SWS_HSI) {
    /* Wait until HSI is selected.*/
  }
}

__STATIC_INLINE void hsi_init(void) {

#if STM32_HSI_ENABLED
  /* HSI activation.*/
  hsi_enable();
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/** @} */
