# A-Maze-Generating-and-Solving-Tool-based-Qt

code文件夹下为源代码

打包文件使用方法:
打开Maze.exe
1.恢复默认可读取默认迷宫
2.从文件可导入自己的迷宫
3.随机生成迷宫也可能无解
4.显示结果会出现蓝色路径
若迷宫无解，会出现提示



测试1：找到解

![image](https://github.com/PizzaDark/A-Maze-Generating-and-Solving-Tool-based-Qt/blob/main/image1.png)

测试2：无解

![image](https://github.com/PizzaDark/A-Maze-Generating-and-Solving-Tool-based-Qt/blob/main/image2.png)

注：迷宫中白色为通路，黑色为障碍，绿为起点，红为终点

若需自定义迷宫，新建一个.txt文件，格式如下：
第一行输入行数n，列数m，用空格隔开，
下面输入n行m列的01ST四种字符，中间没有空格，其中通路为0，
障碍为1，起点为S，终点为T，起终点分别有且仅有1个
