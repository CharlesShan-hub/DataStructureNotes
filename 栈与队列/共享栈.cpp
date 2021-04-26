// 共享栈
/**
 * 定义
 * 初始化
 */

// 定义
#define MaxSize 10
typedef struct{
	int data[MaxSize];
	int top1;
	int top2;
}ShStack;

// 初始化
void InitShStack(ShStack &S){
	S.top1 = -1;
	S.top2 = MaxSize;
}

int main(){
	return 0;
}