# OpenCV学习笔记
**版本 OpenCV 3.2.0**


## LabWork1:
* 演示了blur，medianBlur，erode，dilate的效果
* 给出了简单的blur和medianBlur的实现样例，用于学习其原理

## LabWork2：
* 一个简单的车牌识别样例，只能够圈出车牌的位置，识别率不够高
### 用到的知识
* 把图像转化为灰度图和二值图
* Sobel算子用作边缘检测
* 利用erode和dilate把车牌的数字和汉字连通起来
* 使用findContour函数进行边缘检测，将找到的点集Vector&lt;Point>使用boundingRect转换为近似的矩形

### 备注
* 当然有一些不是车牌号的矩形会被找到，我们需要进行一些判断来确认一个矩形是不是车牌，这就是车牌识别的核心
* 如果车牌不是正的，可能需要用到自动旋转校正，这在后面一个实验会写到
* 由于间距原因，有可能车牌的汉字和数字部分会被识别为两个矩形，这时候需要将两个矩形合并，OpenCV没有提供相关的函数，需要自己编写