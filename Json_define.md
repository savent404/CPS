# Charge Pal Master-Slaver JSON Define
## TAG
* [基本模式](#Normal)
* [指纹模块](#Finger-Print)
  * [主机操作](#M002)
  * [从机操作](#S002)
  * [例子](#E002)
* [充电宝状态](#Charge-Pal)
  * [主机操作](#M003)
  * [从机操作](#S003)
  * [例子](#E003)
* [温度控制](#Temp-Control)
  * [主机操作](#M004)
  * [从机操作](#S004)
  * [例子](#E004)
* [电机控制](#Motor-Control)
  * [主机操作](#M005)
  * [从机操作](#S005)
  * [例子](#E005)
* [人体检测](#Body-Check)
  * [主机操作](#M006)
  * [从机操作](#S006)
  * [例子](#E006)
* [物体检测（充电宝是否在仓)](#Pal-Check)
  * [主机操作](#M007)
  * [从机操作](#S007)
  * [例子](#E007)
* [待机模式](#Stand-By)
  * [主机操作](#M008)
  * [从机操作](#S008)
  * [例子](#E008)

## Normal <span id="Normal"></span>
主机/从机在通讯中都会用到固定的两个参数
```json
{
    "cmd":"string",        // 提示操作的具体模块(只能是字符串)
    "arg":"strong or boll" // 提示具体的操作(字符串或者布尔量)
}
```
## Finger-Print <span id="Finger-Print"></span>
```json
{
    "cmd":"Finger-Print"
}
```

指纹部分包括
* 指纹模块使/失能
* 得到指纹特征值


### Master <span id="M002"></span>
#### 使能指纹模块
```json
"arg":"Enable"
```
#### 失能指纹模块
```json
"arg":"Disable"
```

### Slaver <span id="S002"></span>
#### 响应使能/失能模块
```json
"arg":"Ack"
```
#### 返回指纹特征值
**当开启指纹模块一段时间后从机未返回该指令，建议进行失能操作**

返回格式如下：
```json
{
    "cmd":"Finger-Print",
    "arg":"data",
    "data":"这是一个Base64格式的定长字符串"
}
```

### Example <span id="E002"></span>
首先主机发送使能请求
```json
{
    "cmd":"Finger-Print",
    "arg":"Enable"
}
```
等待从机发送响应
```json
{
    "cmd":"Finger-Print",
    "arg":"Ack"
}
```
等待从机发送指纹特征值
```json
{
    "cmd":"Finger-Print",
    "arg":"data",
    "data":"这是一个Base64格式的定长字符串"
}
```
[超时后|接收到指纹特征值后]主机发送失能信号
```json
{
    "cmd":"Finger-Print",
    "arg":"Disable"
}
```

## Charge-Pal <span id="Charge-Pal"></span>
查询多通道充电宝信息
### Master <span id="M003"></span>
#### 查询某通道充电宝状态
```json
{
    "cmd":"Charge-Pal",
    "arg":"Get-Status",
    "channel":1 //数字(1~6)
}
```
#### 开始某通道的充电
```json
{
    "cmd":"Charge-Pal",
    "arg":"Enable",
    "channel":1 //数字(1~6)
}
```
#### 结束某通道的充电
```json
{
    "cmd":"Charge-Pal",
    "arg":"Disable",
    "channel":1 //数字(1~6)
}
```
### Slaver <span id="S003"></span>
#### 响应"Enable"/"Disable"
```json
{
    "cmd":"Charge-Pal",
    "arg":"Ack",
    "channel":1 //数字(1~6)
}
```
#### 返回充电宝数据
```json
{
    "cmd":"Charge-Pal",
    "arg":"data",
    "data":{
        "channel":1,   //通道(1~6)
        "IsThere":true,//是否有充电宝在仓
        "ID":10023,    //数字ID
        "Vol":4.7,     //电压，浮点数
        "I"  :1.0,     //电流，浮点数
        "IsCharge":true, //是否在充电
    }
}
```
### Example <span id="E003"></span>
请参考指纹模块

## Temp-Control <span id="Temp-Control"></span>
温度控制模块
### Master <span id="M004"></span>
#### 查询当前温度
```json
{
    "cmd":"Temp-Control",
    "arg":"Get-Temp"
}
```
#### 设定风扇风速
```json
{
    "cmd":"Temp-Control",
    "arg":"Set-Temp",
    "speed":50 //数字0~99，0代表不转
}
```
### Slaver <span id="S004"></span>
#### 返回当前温度
```json
{
    "cmd":"Temp-Control",
    "arg":"data",
    "data":27.2 //温度值，浮点数
}
```
#### 返回风扇操作响应
```json
{
    "cmd":"Temp-Control",
    "arg":"Ack"
}
```
### Example <span id="E004"></span>
None

## Motor-Control <span id="Motor-Control"></span>
电机控制模块
### Master <span id="M005"></span>
#### 依照一个方向转动一定角度
```json
{
    "cmd":"Motor-Control",
    "arg":"Set-Angel",
    "Angel": -180.0 //可正转/反转 浮点数
}
```
### Slaver <span id="S005"></span>
#### 操作完成响应操作
```json
{
    "cmd":"Motor-Control",
    "arg":"Ack"
}
```
### Example <span id="E005"></span>

## Body-Check <span id="Body-Check"></span>
人体红外检测
### Master <span id="M006"></span>
None
### Slaver <span id="S006"></span>
```json
{
    "cmd":"Body-Control",
    "arg":"data",
    "IsThere":true //当人靠近会返回true,离开返回false
}
```
### Example <span id="E006"></span>
当人体靠近机器后从机发送：
```json
{
    "cmd":"Body-Control",
    "arg":"data",
    "IsThere":true
}
```
人保持近距离时不再返回人体检查消息

当人体离开后从机发送：
```json
{
    "cmd":"Body-Control",
    "arg":"data",
    "IsThere":false
}
```

## Pal-Check <span id="Pal-Check"></span>
充电宝拿走/归还检测
### Master <span id="M007"></span>
None
### Slaver <span id="S007"></span>
#### 返回取走/放回消息
```json
{
    "cmd":"Pal-Check",
    "arg":"data",
    "IsTake":true //拿走为真,放回为假
}
```
### Example <span id="E007"></span>
同人体红外检测

## Stand-By <span id="Stand-By"></span>
待机检测
### Master <span id="M008"></span>
None
### Slaver <span id="S008"></span>
```json
{
    "cmd":"Stand-By",
    "arg":"data",
    "go2lowPower": true //进入待机为真，退出待机为假
}
```
### Example <span id="E008"></span>
同人体红外检测
9