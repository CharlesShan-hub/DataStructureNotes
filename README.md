# DataStructureNotes
数据结构笔记  
This repository is created for revision and conclusion for data structure learning.  
这个仓库用于分享我在学习数据结构的笔记与总结的代码, 欢迎大家提出各种建议.
charles.shht@gmail.com
## 线性表
线性表包含顺序存储与链式存储. 顺序存储(顺序表)中又包含静态分配与动态存储. 

__线性表__文件夹中包含以下内容:  


|                   |顺序表|  |链式储存|
|:-|:-:|-:|-:|
|                    |静态 |动态|单链表|
|Define              |√   |√   ||
|InitList(&L)        |√   |√   ||
|Length(L)           |-   |-   ||
|IncreaseSize(&L,len)|-   |√   ||
|LocateElem(L,e)     |O(1)|O(1)||
|GetItem(L,i)        |O(n)|O(n)||
|ListInsert(&L,i,e)  |O(n)|O(n)||
|ListDelete(&L,i,&e) |O(n)|O(n)||
|Empty(L)            |-   |-   ||
|DestoryList(&L)     |-   |-   ||

__√__: 可以实现.   
__O(..)__: 可以实现, 并写出了时间复度.  
__-__: 没有对应函数, 或尚未写出该函数.  

