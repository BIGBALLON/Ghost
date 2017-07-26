## 关于本项目

Ghostman is a Search Algorithm's Demo about Blind Search algorithm and Heuristic Search.


## 写在前面

- 本项目是一个关于搜索算法的演示软件，无任何商业用途
- 本项目为本人本科阶段一个大作业，未进行严格的软件测试
- 该演示软件使用Visual Studio 2013 进行开发，请注意编译器的版本
- 你可以下载该演示程序的源码，仅供学习，勿用于任何商业用途

## 界面

![](https://user-images.githubusercontent.com/7837172/46141391-5f97f300-c286-11e8-9ffd-abcc34bea477.jpeg)

## 算法

- 该算法演示程序主要演示如下几个算法
- 深度优先搜索算法（DFS）
- 广度优先搜索算法（BFS）
- A星算法（A*）
- 迭代加深的A星算法（IDA*）
- 模拟退火算法（SA）


## 软件使用

- 总的演示程序分为三块
- 迷宫寻路部分（用于演示BFS、DFS以及A star算法）
- 八数码、井字图部分（用于演示IDA start算法）
- 模拟退火部分（单独用于演示SA算法）


## 迷宫寻路部分

- 起点和终点（用于设置起点和终点）
- 直接执行（直接运行算法，幷得到路径）
- 单步执行（单步执行算法）
- 静态扩展（算法覆盖范围的静态扩展）
- 动态扩展（算法覆盖范围的动态扩展）

![](https://user-images.githubusercontent.com/7837172/46141392-5f97f300-c286-11e8-85c4-92d485923512.png)

## 八数码、井字图部分

- 只支持执行按钮
- 两个演示均采用IDA*算法
- 点击执行按钮后，将会先进行八数码的演示（左边的的拼图），然后进行井字图的演示


![](https://user-images.githubusercontent.com/7837172/46141394-60308980-c286-11e8-964e-a2dfeae9138d.png)

## 模拟退火部分

- 只支持执行按钮
- 红色方块代表火源
- 蓝色点代表最安全的位置
- 最安全的位置定义为：离火源最远的点。 （也就是和最近的那个火源的距离最大的点）
- 由于精度误差（这里演示转换为了整型变量），可能有个别点不太精确。

![](https://user-images.githubusercontent.com/7837172/46141396-60308980-c286-11e8-953d-42bc683a46d0.png)

## 演示视频

[![](http://img.youtube.com/vi/2pksJMIV1sc/0.jpg)](http://www.youtube.com/watch?v=2pksJMIV1sc&t=2s)
