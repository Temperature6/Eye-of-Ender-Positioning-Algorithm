# 末影之眼定位算法



这是一个通过三个点坐标以及y_rotation值定位主世界末影地牢的程序

#### 文件说明

​	末影之眼定位算法.exe：编译完后的可执行文件

​	main.cpp：C++源代码文件

​	function.h：源代码文件中用到的头文件

​	末影之眼.ico：编译需要用到的图标文件

#### 使用方法

​	1、你需要抛出一颗末影之眼，用准星瞄准末影之眼最后的位置
​	2、保持不动，将此时的 X轴坐标，Z轴坐标，y_rotation值 依次输入程序
​	3、共需输入三次，第三次输入完成后程序会计算主世界末地传送门并显示

#### 注意事项

​	计算得出的位置可能有偏差，扔出的三点相隔的距离要适当

​	如果输入的数据出现问题可能导致计算结果出现错误，例如出现\"inf"

​	如果输入的数据有误，在此点输入结束后可以选择重新输入

​	计算完成后会有两个结果，如果一个误差较大可以试试另一个

