#ifndef _XL9555_MACRO_H
#define _XL9555_MACRO_H

/* XL9555 各个 IO 的功能 */
#define AP_INT_IO 0x0001 /* xl9555 中断引脚 P00 */
#define QMA_INT_IO 0x0002 /* QMA6100P 中断引脚 P01 */
#define SPK_EN_IO 0x0004 /* 功放使能引脚 P02 */
#define BEEP_IO 0x0008 /* 蜂鸣器控制引脚 P03 */
#define OV_PWDN_IO 0x0010 /* 摄像头待机引脚 P04 */
#define OV_RESET_IO 0x0020 /* 摄像头复位引脚 P05 */
#define GBC_LED_IO 0x0040 /* ATK_MODULE 接口 LED 引脚 P06 */
#define GBC_KEY_IO 0x0080 /* ATK_MODULE 接口 KEY 引脚 P07 */
#define LCD_BL_IO 0x0100 /* RGB 屏背光控制引脚 P10 */
#define CT_RST_IO 0x0200 /* 触摸屏中断引脚 P11 */
#define SLCD_RST_IO 0x0400 /* SPI_LCD 复位引脚 P12 */
#define SLCD_PWR_IO 0x0800 /* SPI_LCD 控制背光引脚 P13 */
#define KEY3_IO 0x1000 /* 按键 3 引脚 P14 */
#define KEY2_IO 0x2000 /* 按键 2 引脚 P15 */
#define KEY1_IO 0x4000 /* 按键 1 引脚 P16 */
#define KEY0_IO 0x8000 /* 按键 0 引脚 P17 */

#endif