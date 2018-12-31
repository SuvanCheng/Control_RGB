## 2016电赛

实验器材:战舰STM32F103开发板V3版本

实验目的:学习STM32内部ADC的使用

硬件资源:
1,DS0(连接在PB5)
2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过FSMC驱动,FSMC_NE4接LCD片选/A10接RS) 
4,ADC(STM32内部ADC1,通道1,即:ADC1_CH1)

实验现象:
本实验通过STM32内部ADC1读取通道1（PA1）上面的电压，在LCD模块上面显示ADC转换值以及换算成电压后的电压值。


注意事项:
1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源适配器(推荐外接12V 1A电源).
2,本例程在LCD_Init函数里面(在ILI93xx.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!!
3,PA1默认通过跳线帽连接TPAD,读取到的电压值约为3V左右,请拔了P10跳线帽,然后给PA1提供测试电压.
4,ADC的最大输入电压是3.3V,请不要超过这个值.
5,多功能接口(P10)的ADC即连接在PA1上.
6,ADC的参考电压默认通过P5连接在VDDA上面(3.3V),所以默认参考电压是3.3V




















