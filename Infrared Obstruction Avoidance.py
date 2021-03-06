# -*- coding: utf-8 -*-
"""
Created on Mon Nov 16 20:29:07 2020

@author: Yuxuan Liu
"""

#-*- coding:UTF-8 -*-
import RPi.GPIO as GPIO
import time

#红外避障引脚定义
AvoidSensorLeft = 4

#设置GPIO口为BCM编码方式
GPIO.setmode(GPIO.BCM)

#忽略警告信息
GPIO.setwarnings(False)

#电机引脚初始化为输出模式
#按键引脚初始化为输入模式
#红外避障引脚初始化为输入模式
def init():
    GPIO.setup(AvoidSensorLeft,GPIO.IN)
    
try:
    init()
    while True:
        #遇到障碍物,红外避障模块的指示灯亮,端口电平为LOW
        #未遇到障碍物,红外避障模块的指示灯灭,端口电平为HIGH
        LeftSensorValue  = GPIO.input(AvoidSensorLeft);

        if LeftSensorValue == True:
           # run()         #当两侧均未检测到障碍物时调用前进函数
           print("no object")
           time.sleep(0.002)
        elif LeftSensorValue == False:
            #spin_left()   #右边探测到有障碍物，有信号返回，原地向左转
            print("object on your way")
            time.sleep(0.002)

       
except KeyboardInterrupt:
    pass
GPIO.cleanup()