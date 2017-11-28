## EasyC——致力于简化Windows环境下的C语言编程
Windows环境下的C语言编程存在非常多的困难:
* 缺乏`容器`和`迭代器`功能。
	* 没有字典, 可变数组, 字符串, LRU缓存, 链表等数据结构。在面临相关业务时要求程序员自己实现，增加编程难度。
* 缺乏基本的`算法`。
	* 没有直接提供字符串查询，排序，交集并集等常用算法。
* 缺乏更为方便的`Windows API`编程接口。
	* 若要使用接口设计不算友好的Windows系统级服务，需要深入学习Windows底层原理。

本团队开发了`EasyC`工具，将容器、算法和系统三个功能聚合，全面解决了上述问题。[这里]()会有一个快速示例。

大家对于本项目的任何疑问和建议，都可以在[这里](https://github.com/swjtuISL/EasyC/issues)中提出。

## 目录
- [安装与使用](doc/install.md)
- [原理](doc/theory.md)
	- [基本模型](doc/theory.md##一、基本模型)
	- [容器原理](doc/theory.md)
	- [算法原理](doc/theory.md)
	- [系统原理](doc/theory.md)
- [API](doc/api.md)
	- [容器API](doc/api.md)
		- [Object-API](doc/api.md)
		- [String-API](doc/api.md)
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
- [致谢](doc/thanks.md)