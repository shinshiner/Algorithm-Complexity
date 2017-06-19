给定城市里几座矩形建筑的外形和位置，利用分治法求出这些建筑的(两维)轮廓，并消去隐藏线。建筑Bi通过三元组(Li，Hi，Ri)来表示。Li和Ri分别表示建筑的左右x坐标，而Hi表示建筑的高度。一个轮廓是一列x坐标以及与它们相连的高度，按照从左到右排列。要求从输入文件in.dat读入建筑数目和各个三元组，结果写入文件out.dat

示例：

in.dat

2

1 1 4

3 3 6

out.dat

1

1

3

3

6

* [lunkuowenti.cpp](https://github.com/shinshiner/Algorithm-Complexity/blob/master/Contour%20Problem/lunkuowenti.cpp) --> high complexity (origin version)
* [lkx.cpp](https://github.com/shinshiner/Algorithm-Complexity/blob/master/Contour%20Problem/lkx.cpp) --> low complexity (modified version)
