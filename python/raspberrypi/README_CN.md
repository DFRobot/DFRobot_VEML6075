# DFRobot_VEML6075
- [English Version](./README.md)

VEML6075能感知UVA和UVB光线并融合光电二极管、放大器和模拟/数字电路使用CMOS工艺的单芯片。当紫外线传感器是应用时，它能够检测UVA和UVB强度提供一个信号强度的测量方法，同时支持UVI测量.<br>
VEML6075提供卓越的温度补偿在变化的情况下保持输出稳定的能力温度。VEML6075的功能很容易通过I2C的简单命令格式(兼容SMBus)接口协议。VEML6075工作电压范围从1.7 V到3.6 V。VEML6075采用无铅包装4引脚OPLGA封装，提供了最好的市场证明可靠性。<br>


![](../../resources/images/SEN0303.png)


## 产品链接(https://www.dfrobot.com.cn/goods-2007.html)

    SKU：SEN0303

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)
 
## 概述

1. 从VEML6075获取UVA, UVB和UVI数据
2. 这些数据是通过串口打印出来的
3. 使用API去配置传感器模块

## 库安装

使用此库前，请首先下载库文件，将其粘贴到树莓派的自定义目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```python
  def begin(self):
    '''!
      @brief 初始化函数
      @return  bool类型，返回初始化结果
      @retval True 初始化成功
      @retval False 初始化失败
    '''

  def set_power(self, power):
    '''!
      @brief 设置传感器的工作状态
      @param power 要设置的工作状态
    '''

  def uvi2mwpcm2(self, Uvi):
    '''!
      @brief 数据转换
      @return mW/cm2
    '''

  def get_power(self):
    '''!
      @brief 获取传感器的工作状态
      @return  工作状态
      @retval    1    power on
      @retval    0   power off
    '''

  def set_active_force_mode(self, isEnable):
    '''!
      @brief 设置active force 模式
      @param isEnable 
      @n       ACTIVE_FORCE_ENABLE    使能 active force 模式
      @n       ACTIVE_FORCE_DISABLE   关闭 active force 模式
    '''

  def get_active_force_mode(self):
    '''!
      @brief 获取传感器的active force 模式信息
      @return  模式
      @retval    ACTIVE_FORCE_ENABLE    EML6075 active force 模式开启
      @retval    ACTIVE_FORCE_DISABLE   VEML6075 active force 模式未开启
    '''

  def trig_one_measurement(self):
    '''!
      @brief  尝试一次测试
    '''

  def set_dynamic(self, dynamic):
    '''!
      @brief 设置动态环境
      @param dynamic
      @n       DYNAMIC_NORMAL    正常动态环境
      @n       DYNAMIC_HIGH      高动态环境
    '''

  def get_dynamic(self):
    '''!
      @brief 获取传感器的Dynamic设置信息
      @return  动态环境的设置信息
      @n       DYNAMIC_NORMAL    设置的正常动态环境
      @n       DYNAMIC_HIGH      设置的高动态环境
    '''

  def set_integration_time(self, t):
    '''!
      @brief 获取传感器的积分时间
      @param   t
      @n       UV_IT_50     50ms
      @n       UV_IT_100    100ms
      @n       UV_IT_200    200ms
      @n       UV_IT_400    400ms
      @n       UV_IT_800    800ms
    '''

  def get_integration_time(self):
    '''!
      @brief 获取传感器的积分时间
      @return  积分时间
      @retval    UV_IT_50     50ms
      @retval    UV_IT_100    100ms
      @retval    UV_IT_200    200ms
      @retval    UV_IT_400    400ms
      @retval    UV_IT_800    800ms
    '''

  def read_uva_raw(self):
    '''!
      @读取传感器在UVA波段收集原始数据
      @return  UVA原始数据
    '''


  def read_uvb_raw(self):
    '''!
      @brief 读取传感器在UVB波段收集原始数据
      @return  UVB 原始数据
    '''

  def read_UVcomp1_raw(self):
    '''!
      @brief 读取传感器在UvComp1中收集原始数据
      @return  UvComp1 原始数据
    '''
  
  def read_UVcomp2_raw(self):
    '''!
      @brief 读取传感器在UvComp2中收集原始数据
      @return  UvComp2 Raw
    '''

  def get_uva(self):
    '''!
      @brief 根据采集的数据计算出紫外线的UVA波段数据
      @return  UVA 数据
    '''

  def get_uvb(self):
    '''!
      @brief 根据采集的数据计算出紫外线的UVB波段数据
      @return  UVB 数据
    '''

  def get_uvi(self, Uva, Uvb):
    '''!
      @brief 根据采集到的数据计算出紫外线波段数据
      @return  UVI 数据
    '''
```

## 兼容性

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |     √     |            |          |         |
| RaspberryPi4 |           |            |    √     |         |

* Python 版本

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## 历史

- 2021/10/18 - 1.0.1 版本
- 2018/12/18 - 1.0.0 版本


## 创作者

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

