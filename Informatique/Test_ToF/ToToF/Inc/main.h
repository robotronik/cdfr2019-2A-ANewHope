/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define US_TRIG_0_Pin GPIO_PIN_0
#define US_TRIG_0_GPIO_Port GPIOA
#define US_ECHO_0_Pin GPIO_PIN_1
#define US_ECHO_0_GPIO_Port GPIOA
#define US_TRIG_1_Pin GPIO_PIN_2
#define US_TRIG_1_GPIO_Port GPIOA
#define US_ECHO_1_Pin GPIO_PIN_3
#define US_ECHO_1_GPIO_Port GPIOA
#define US_TRIG_2_Pin GPIO_PIN_4
#define US_TRIG_2_GPIO_Port GPIOA
#define US_ECHO_2_Pin GPIO_PIN_5
#define US_ECHO_2_GPIO_Port GPIOA
#define US_TRIG_3_Pin GPIO_PIN_6
#define US_TRIG_3_GPIO_Port GPIOA
#define US_ECHO_3_Pin GPIO_PIN_7
#define US_ECHO_3_GPIO_Port GPIOA
#define US_OUTPUT_ENABLE_Pin GPIO_PIN_0
#define US_OUTPUT_ENABLE_GPIO_Port GPIOB
#define LED_Status_Pin GPIO_PIN_8
#define LED_Status_GPIO_Port GPIOA
#define USART1_TX_DEBUG_Pin GPIO_PIN_9
#define USART1_TX_DEBUG_GPIO_Port GPIOA
#define USART1_RX_DEBUG_Pin GPIO_PIN_10
#define USART1_RX_DEBUG_GPIO_Port GPIOA
#define I2C1_SCL_ToF_Pin GPIO_PIN_15
#define I2C1_SCL_ToF_GPIO_Port GPIOA
#define TOF_RESET_DATA_Pin GPIO_PIN_4
#define TOF_RESET_DATA_GPIO_Port GPIOB
#define TOF_RESET_SHIFT_Pin GPIO_PIN_5
#define TOF_RESET_SHIFT_GPIO_Port GPIOB
#define I2C1_SDA_ToF_Pin GPIO_PIN_7
#define I2C1_SDA_ToF_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
