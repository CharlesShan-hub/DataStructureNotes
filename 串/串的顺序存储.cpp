#include<stdio.h>
#include<stdbool.h>
/*
 * 串的基本操作
 * StrAssign(&T,chars): 赋值操作
 * StrCopy(&T,S): 赋值操作
 * StrEmpty(S): 判空操作
 * StrLength(S): 求串长
 * ClearLength(&S): 清空操作
 * DestroyString(&S): 销毁串
 * Concat(&T,S1,S2): 串联接
 * Index(S,T): 定位操作 - 模式匹配
 * StrCompare(S,T): 比较操作
 * ------
 * SubString(&Sub,S,pos,len): 求子串
 */

#define MAXLEN 255
typedef struct
{
    char ch[MAXLEN];
    int length;
}SString;

void StrPrintln(SString T){
    printf("%s\n",T.ch+1);
}
void StrPrint(SString T){
    printf("%s",T.ch+1);
}
void PrintNSpace(int n){
    for(int i=0;i<n;i++)
        printf(" ");
}

bool StrAssign(SString &T,const char* chars){
    int i;
    for(i=1;i<MAXLEN&&chars[i-1]!='\0';i++){
        T.ch[i] = chars[i-1];
    }
    T.length = --i;

    return true;
}

bool SubString(SString &Sub,SString S,int pos,int len){
    /**
     * 取子串
     */

    // 判断数组越界(比较主串与子串最后一位)
    if(S.length < pos+len-1)
        return false;
    // 赋值
    for(int i=1; i<len+1; i++)
        Sub.ch[i]=S.ch[pos+i-1];
    Sub.length = len;
    return true;
}

int StrCompare(SString S,SString T){
    /**
     * 字符串比较
     */

    // 逐位比较
    for(int i=1;i<S.length+1&&i<T.length+1;i++)
        if(S.ch[i]!=T.ch[i])
            return S.ch[i] - T.ch[i];
    // 比较长度
    return S.length - T.length;

}

int Index1(SString S,SString T){
    /**
     * 朴素模式匹配算法1（用于展示）
     * 
     * 返回匹配位置，匹配失败返回0
     */

    int i=1;
    SString Sub;
    while(i<=S.length - T.length +1){
        SubString(Sub,S,i,T.length);
        PrintNSpace(i-1);
        StrPrint(Sub);           // test
        if(StrCompare(Sub,T)!=0){
            i++;
            printf("  --- x\n"); // test
        }
        else{
            printf("  --- √\n"); // test
            return i;
        }
    }
    return 0;
}

int Index2(SString S,SString T){
    /**
     * 朴素模式匹配算法2
     * 
     * 返回匹配位置，匹配失败返回0
     */
    int i=1,j=1;
    while(i<=S.length && j<=T.length){
        if(S.ch[i]==T.ch[j]){
            i++;j++; //同时后移
        }else{
            i=i-j+2; // i从下一位重新计算
            j=1;     // j也回到开头
        }
    }
    if(j>T.length)
        // 匹配成功
        return i-T.length;
    else
        // 匹配失败
        return 0;
}

int Index3(SString S,SString T){
    /**
     * KMP算法（演示版）
     * 
     * 返回匹配位置，匹配失败返回0
     */
    // 计算next数组
    int next[T.length];
    SString temp1;
    SString temp2;
    for(int i=1;i<T.length+1;i++){
        if(i==1){
            next[i]=0;
            continue;
        }else if(i==2){
            next[i]=1;
            continue;
        }
        for(int j=1;j<i;j++){
            SubString(temp1,T,1,j); // 前缀
            SubString(temp2,T,i-j,j); // 后缀
            if(StrCompare(temp1,temp2)==0){
                next[i]=j;
                break;
            }else{
                next[i]=1;
            }
        }
    }
    for(int i=1;i<T.length+1;i++){
        printf("%d ",next[i]);
    }
    printf("\n");
    // 模式匹配
    int i=1,j=1,count=1,temp=0;
    StrPrintln(T);
    while(i<=S.length && j<=T.length){
        //printf("%d(%d) %d(%d) %d\n",i,S.length,j,T.length,count);
        count++;
        if(S.ch[i]==T.ch[j]){
            //printf("√--%d:%c  %d:%c\n",i,S.ch[i],j,T.ch[j]);
            i++;j++; //同时后移
        }else{
            //printf("x--%d:%c  %d:%c\n",i,S.ch[i],j,T.ch[j]);
            temp=j; // for test
            j=next[j];
            if(j==0){
                i++;j=1;
            }
            //printf("-->%d:%c  %d:%c\n",i,S.ch[i],j,T.ch[j]);
            PrintNSpace(i-1);
            StrPrint(T);
            printf("  next[%d]:%d\n",temp,next[temp]);
        }
    }
    if(j>T.length)
        // 匹配成功
        return i-T.length;
    else
        // 匹配失败
        return 0;
}

int Index4(SString S,SString T){
    /**
     * KMP算法（演示版）
     * 
     * 返回匹配位置，匹配失败返回0
     */
    // 计算next数组
    int next[T.length];
    SString temp1;
    SString temp2;
    for(int i=1;i<T.length+1;i++){
        if(i==1){
            next[i]=0;
            continue;
        }else if(i==2){
            next[i]=1;
            continue;
        }
        for(int j=1;j<i;j++){
            SubString(temp1,T,1,j); // 前缀
            SubString(temp2,T,i-j,j); // 后缀
            if(StrCompare(temp1,temp2)==0){
                next[i]=j;
                break;
            }else{
                next[i]=1;
            }
        }
    }
    // 模式匹配
    int i=1,j=1,count=1;
    while(i<=S.length && j<=T.length){
        count++;
        if(S.ch[i]==T.ch[j]){
            i++;j++; //同时后移
        }else{
            j=next[j];
            if(j==0){
                i++;j=1;
            }
        }
    }
    if(j>T.length)
        // 匹配成功
        return i-T.length;
    else
        // 匹配失败
        return 0;
}

int main(){
    printf("用顺序串实现串的基本操作\n");
    
    SString S,T;
    StrAssign(S,"agagoagooagoog1googo1googoo");
    StrAssign(T,"googoo");
    //StrAssign(T,"ababaaababaa");
    StrPrintln(S);
    StrPrintln(T);

    printf("\n朴素模式匹配1\n");
    printf("%d\n",Index1(S,T));

    //printf("\n朴素模式匹配2\n");
    //printf("%d\n",Index2(S,T));

    StrPrintln(S);
    StrPrintln(T);

    printf("\n KMP算法\n");
    printf("%d\n",Index3(S,T));

    //printf("\n KMP算法\n");
    //printf("%d\n",Index4(S,T));

    return 0;
}