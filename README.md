# DataStructureNotes
数据结构笔记  
This repository is created for revision and conclusion for data structure learning.  
这个仓库用于分享我在学习数据结构的笔记与总结的代码, 欢迎大家提出各种建议.
charles.shht@gmail.com
## 线性表

### 线性表文件夹中包含以下内容 

|                   |顺序表|  |链式储存||
|:-|:-:|-:|-:|-:|
|                    |静态 |动态|单链表-带头节点|单链表-无头节点|双链表|顺环链表|静态链表|
|Define              |√   |√   |√           |√            |
|InitList(&L)        |√   |√   |√           |√            |
|Empty(L)            |-   |-   |√           |√            |
|Length(L)           |-   |-   |O(n)        |O(n)         |
|IncreaseSize(&L,len)|-   |√   |-           |-            |
|LocateElem(L,e)     |O(1)|O(1)|O(n)        |O(n)         |
|GetItem(L,i)        |O(n)|O(n)|O(n)        |O(n)         |
|ListInsert(&L,i,e)  |O(n)|O(n)|O(n)        |O(n)         |
|InsertPoier(&L,e)   |-   |-   |O(1)        |O(1)         |
|InsertNext(&L,e)    |-   |-   |O(1)        |O(1)         |
|ListDelete(&L,i,&e) |O(n)|O(n)|O(n)        |-            |
|DeleteNode(&N)      |-   |-   |O(1)        |O(1)         |
|DestoryList(&L)     |-   |-   ||

__√__: 可以实现.   
__O(..)__: 可以实现, 并写出了时间复度.  
__-__: 没有对应函数, 或尚未写出该函数.  

### 一些小总结
1. 线性表包含顺序存储与链式存储. 顺序存储(顺序表)中又包含静态分配与动态存储. 
2. 单链表不带头节点的按位插入操作, 会比较麻烦, 一般都写带头节点的形式.
3. 单链表的前插法可以从后插法改编而成. 先后插再为原节点重新赋值, 达到与前插等效的目的.