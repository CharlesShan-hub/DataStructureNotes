/**
 * 串的基本操作
 * StrAssign(&T,chars): 赋值操作
 * StrCopy(&T,S): 赋值操作
 * StrEmpty(S): 判空操作
 * StrLength(S): 求串长
 * ClearLength(&S): 清空操作
 * DestroyString(&S): 销毁串
 * Concat(&T,S1,S2): 串联接
 * Index(S,T): 定位操作
 * StrCompare(S,T): 比较操作
 */

typedef struct
{
    char *ch;
    int length;
}HString;

HString S;
S.ch = (char*)malloc(MAXLEN*sizeof(char));
S.length=0;