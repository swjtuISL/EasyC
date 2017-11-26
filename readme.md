# EasyC
`EasyC`提供了丰富的API用于简化Windows环境下C语言编程。

Windows环境下的C语言编程存在非常多的困难:
* 缺乏类似C++, Java, Python等语言所具备的容器和迭代器功能。没有字典, 可变数组, 字符串, LRU缓存, 链表等数据结构。在面临相关业务时要求程序员自己实现，增加编程难度。
* 缺乏基本的算法，没有直接提供字符串查询，排序，交集并集等功能。这同样增加了编程门槛。
* 缺乏更为方便的Windows API编程接口。若要使用Windows系统级服务，需要深入学习Windows底层原理，并且Windows API接口设计的并不算友好，直接采用原生API进行开发复杂度较高。

介于此，该工具聚合了`容器`，`算法`和`系统`等三大块的功能，全面解决了上述问题，并采用面向对象的方式组织API，直观清晰，可以更好的维护程序代码。

## 目录
- [安装与使用](doc/install.md)
- [API](doc/api.md)
	- [容器API](doc/api.md)
		- [Vector-API](doc/api.md)
		- [List-API](doc/api.md)
		- [Matrix-API](doc/api.md)
		- [String-API](doc/api.md)
		- [Stack-API](doc/api.md)
		- [Queue-API](doc/api.md)
		- [HashMap-API](doc/api.md)
		- [TreeMap-API](doc/api.md)
		- [LRU-API](doc/api.md)
	- [算法API](doc/api.md)
		- [sort-API](doc/api.md)
		- [minInVector/maxInVector-API](doc/api.md)
		- [STC-API](doc/api.md)
		- [KMP-API](doc/api.md)
	- [系统API](doc/api.md)
		- [RIO-API](doc/api.md)
		- [Process-API](doc/api.md)
		- [funWrapper-API](doc/api.md)
- [原理](doc/theory.md)
	- [容器原理](doc/theory.md)
		- [Vector原理](doc/theory.md)
		- [List原理](doc/theory.md)
		- [Matrix原理](doc/theory.md)
		- [String原理](doc/theory.md)
		- [Stack原理](doc/theory.md)
		- [Queue原理](doc/theory.md)
		- [HashMap原理](doc/theory.md)
		- [TreeMap原理](doc/theory.md)
		- [LRU原理](doc/theory.md)
	- [算法原理](doc/theory.md)
		- [sort原理](doc/theory.md)
		- [minInVector/maxInVector原理](doc/theory.md)
		- [STC原理](doc/theory.md)
		- [KMP原理](doc/theory.md)
	- [系统原理](doc/theory.md)
		- [RIO原理](doc/theory.md)
		- [Process原理](doc/theory.md)
		- [funWrapper原理](doc/theory.md)
- [致谢](doc/thanks.md)