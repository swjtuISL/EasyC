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
- [原理](doc/theory/index.md)
	- [基本模型](doc/theory/model.md)
	- [容器原理](doc/theory/container.md)
	- [算法原理](doc/theory/algorithm.md)
	- [系统原理](doc/theory/system.md)
	- [JSON原理](doc/theory/json.md)
- [API](doc/api/index.md)
	- [容器-API](doc/api/container.md)
	- [算法-API](doc/api/algorithm.md)
	- [系统-API](doc/api/system.md)
	- [JSON-API](doc/api/json.md)
- [致谢](doc/thanks.md)