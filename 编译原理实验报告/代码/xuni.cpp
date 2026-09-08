//#include<stdio.h>
//#include<ctype.h>
//#include<stdlib.h>
//#include<string.h>
//#include<string>
//#include<map>
//using namespace std ;
//
//struct Code{        //中间代码
//	char opt[10];
//	int operand;
//};
//
//Code code[1000];//用于保存中间代码
//map<string, int> choseOpt ;     //用map集合方便switch中选择不同case，判断字符串方便
//enum opts {LOAD, LOADI, STO, ADD, SUB, MULT, DIV, BR, BRF, EQ, NOTEQ, GT, LES, GE, LE, AND,
//            OR, NOT, IN, OUT, CAL, ENTER, RETURN};  //用具体的名称代替1234使代码更易阅读
//
////初始化map，方便之后switch中选择case
//void mapInit() {
//    choseOpt["LOAD"] = LOAD ;   choseOpt["LOADI"] = LOADI ;     choseOpt["STO"] = STO ;
//    choseOpt["ADD"] = ADD ;     choseOpt["SUB"] = SUB ;     choseOpt["MULT"] = MULT ;
//    choseOpt["DIV"] = DIV ;     choseOpt["BR"] = BR ;       choseOpt["BRF"] = BRF ;
//    choseOpt["EQ"] = EQ ;       choseOpt["NOTEQ"] = NOTEQ ;     choseOpt["GT"] = GT ;
//    choseOpt["LES"] = LES ;     choseOpt["GE"] = GE ;       choseOpt["LE"] = LE ;
//    choseOpt["AND"] = AND ;     choseOpt["OR"] = OR ;       choseOpt["NOT"] = NOT ;
//    choseOpt["IN"] = IN ;       choseOpt["OUT"] = OUT ;     choseOpt["CAL"] = CAL ;
//    choseOpt["ENTER"] = ENTER ;     choseOpt["RETURN"] = RETURN ;
//}
////虚拟机
//void TESTmachine(){
//	FILE *in;
//	char codein[100];       //输入文件名
//	int codenum=0;          //指令条数
//	int top=0;				//栈顶
//	int base=0;   		 	//栈底
//	int ip=0;               //当前指令位置
//	int stack[1000];        //操作数栈
//	
//	printf("请输入目标文件名（包括路径）：");
//	scanf("%s",codein);
//	if((in=fopen(codein, "r"))==NULL){//打开输入文件
//		printf("\n打开%s错误！\n",codein);
//		exit(-1) ;      //出错就运行结束
//	}
//	while(!feof(in)){   //读取中间代码	
//		fscanf(in,"%s %d",&code[codenum].opt,&code[codenum].operand);
//		codenum++;
//	}
//	codenum-- ;     //最后一次读取会多加1
//	fclose(in);
////	for(int i=0;i<codenum;i++)
////	    printf("%s          %d\n",code[i].opt,code[i].operand);
//	stack[0]=0;
//	stack[1]=0;
//    mapInit() ;     //将map初始化
//    memset(stack, 0, sizeof(stack)) ;
//	do{        //执行指令直到执行到最后一条指令为止，最后一条指令代表主函数结束
////	while(ip < codenum){
//        Code temp = code[ip] ;  //用一个临时变量来执行操作
//        ip++ ;                  //每执行一个指令地址就往后移动一位
//	    switch(choseOpt[temp.opt]) {    //根据操作码进行选择要执行的指令
//            case LOAD : {       //LOAD D 将D中的内容加载到操作数栈
//                stack[top] = stack[temp.operand+base] ;     //找到栈中存放变量的位置
//                top++;
//                break ;
//            }
//            case LOADI : {      //LOADI a 将常量a压入操作数栈
//                stack[top]=temp.operand;
//                top++;
//                break ;
//            }
//            case STO : {        //STO D将操作数栈顶单元内容存入D
//                top--;      //先将栈顶元素减一
//                stack[temp.operand+base] = stack[top] ;
//                break ;
//            }
//            case ADD : {        //ADD 将栈顶单元与次栈顶单元出栈并相加，和置于栈顶
//                stack[top-2] += stack[top-1] ;
//                top--;
//                break ;
//            }
//            case SUB : {   		//将次栈顶单元减去栈顶单元并出栈，差置于栈顶。
//                stack[top-2] = stack[top-2]-stack[top-1];
//                top--;
//                break ;
//            }
//            case MULT : {      	//将次栈顶与栈顶单元出栈并相乘，积置于栈顶。
//                stack[top-2] = stack[top-1]*stack[top-2];
//                top--;
//                break ;
//            }
//            case DIV : {		//将次栈顶与栈顶单元出栈并相除，商置于栈顶
//                stack[top-2] = stack[top-2]/stack[top-1];
//                top--;
//                break ;
//            }
//            case BR : {         //BR lab 无条件转移到lab
//                ip = temp.operand;      //操作数记录的就是要跳转的位置
//                break ;
//            }
//            case BRF : {		//BRF 若栈顶单元逻辑值，假(0)则转移到lab
//                if(stack[top-1]==0)
//                    ip = temp.operand;  //操作数记录的就是要跳转的位置
//                top-- ;
//                break ;
//            }
//            case EQ : {		    //将栈顶两单元做相等比较，并将结果真或假(1或0)置于栈顶
//                stack[top-2] = (stack[top-2] == stack[top-1]) ;
//                top--;
//                break ;
//            }
//            case NOTEQ : {		//栈顶两单元做不等于比较，并将结果 (1或0)置于栈顶
//                stack[top-2] = (stack[top-2] != stack[top-1]) ;
//                top--;
//                break ;
//            }
//            case GT : {		    //次栈顶大于栈顶操作数，则栈顶置1，否则置0
//                stack[top-2] = (stack[top-2] > stack[top-1]) ;
//                top--;
//                break ;
//            }
//            case LES : {		//次栈顶小于栈顶操作数，则栈顶置1，否则置0
//                stack[top-2] = (stack[top-2] < stack[top-1]) ;
//                top--;
//                break ;
//            }
//            case GE : {		    //次栈顶大于等于栈顶操作数，则栈顶置1，否则置0
//    			stack[top-2] = (stack[top-2] >= stack[top-1]) ;
//                top--;
//                break ;
//            }
//            case LE : {		    //次栈顶小于等于栈顶操作数，则栈顶置1，否则置0
//                stack[top-2] = (stack[top-2] <= stack[top-1]) ;
//                top--;
//                break ;
//            }
//            case AND : {		//将栈顶两单元做逻辑与运算，并将结果 (1或0)置于栈顶
//                stack[top-2] = (stack[top-2] && stack[top-1]) ;
//                top--;
//                break ;
//            }
//            case OR : {		    //将栈顶两单元做逻辑或运算，并将结果 (1或0)置于栈顶
//                stack[top-2] = (stack[top-2] || stack[top-1]) ;
//                top--;
//                break ;
//            }
//            case NOT : {		//将栈顶的逻辑值取反
//                stack[top-1] = !stack[top-1];
//                break ;
//            }
//            case IN : {        	//从标准输入设备(键盘)读入一个整型数据，并入操作数栈
//                printf("输入数据:\n");
//                scanf("%d", &stack[top]) ;
//                top++;
//                break ;
//            }
//            case OUT : {		//将栈顶单元内容出栈，并输出到标准输出设备上(显示器)
//                printf("输出：%d\n",stack[top-1]);
//                top--;
//                break ;
//            }
//            case CAL : {        //调用函数
//                stack[top] = base ;     //记录主函数的基地址
//                stack[top+1] = ip ;     //记录函数执行完要返回主函数的位置
//                ip = temp.operand ;     //执行指令位置跳转到函数开始的位置
//                base = top ;            //进入函数后对于当前函数的基地址
//                break ;
//            }
//            case ENTER : {      //进入函数体
//                top += temp.operand ;   //为函数开辟空间
//                break ;
//            }
//            case RETURN : {             //函数返回
//                top = base ;            //释放函数开辟的空间
//                ip = stack[top+1] ;     //第二个位置存放的是返回到主函数的位置
//                base = stack[top] ;     //回到栈底就是主函数的基地址，重新赋值
//                break ;
//            }
//	    }
//    }
//    	while(ip != 0);
//}
//int main() {
//	TESTmachine();
//	return 0 ;
//}
//
//

