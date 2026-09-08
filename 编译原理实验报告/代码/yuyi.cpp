//#include<bits/stdc++.h>
//using namespace std ;
//enum symbolType {function, variable};   //用枚举类型方便比较类型
//struct tree {       //语法树
//    string data ;
//    vector<tree*> son ;
//    tree* addSon(string str) {
//        tree* newSon = new tree() ;
//        newSon->data = str ;
//        son.push_back(newSon) ;
//        return newSon ;
//    }
//} *root;
//struct symbol {              //符号表
//    char name[20] ;         //标识符名字
//    int address ;           //地址
//    enum symbolType kind ;  //标识符的类型 函数名或变量名
//};
//struct code {                   //中间代码
//    char operationCode[10] ;    //操作码
//    int operand ;               //操作数
//};
//
//FILE *inputFile ;   //输入文件
//FILE *outputFile ;  //输出文件
//char inputAddress[20] ;     //输入文件地址
//char outputAddress[20] ;    //输出文件地址
//char type[20] ;     //单词类型
//char value[40] ;    //单词值
//int line = 0 ;      //当前读到第几行
//int offset = 0 ;    //变量地址
//int codeLength = 0 ;    //中间代码长度
//int symbolLength = 0 ;  //符号表数据个数
//vector<symbol> symbolTable ;    //符号表
//code codes[200] ;            //中间代码
//
////存在函数之间相互调用，要先声明函数
//int parseAlanalysis() ;
//int program() ;
//int fun_declaration(tree* father) ;
//int main_declaration(tree* father) ;
//int function_body(tree* father) ;
//int declaration_list(tree* father) ;
//int declaration_stat(tree* father) ;
//int statement_list(tree* father) ;
//int statement(tree* father) ;
//int if_stat(tree* father) ;
//int while_stat(tree* father) ;
//int for_stat(tree* father) ;
//int read_stat(tree* father) ;
//int write_stat(tree* father) ;
//int compound_stat(tree* father) ;
//int call_stat(tree* father) ;
//int expression_stat(tree* father) ;
//int expression(tree* father) ;
//int bool_expr(tree* father) ;
//int additive_expr(tree* father) ;
//int term(tree* father) ;
//int factor(tree* father) ;
//int do_while_stat(tree* father) ;
//void getNext() ;
//
////将当前数据存入语法树中
//void add(tree* p) {
//    p->addSon(value) ;
//}
////输出语法树
//void printTree(tree* p, int x) {
//    for(int i=0;i<x;i++)    //每次输出之前都要先输出一定的空格实现深度
//        printf("|  ") ;
//    printf("%s\n", p->data.c_str()) ;
//	int num = p->son.size() ;
//	if(num == 0)
//        return ;
//	for(int i=0; i<num; i++)    //输出子内容
//		printTree(p->son[i],x+1);   //深度加一
//	return ;
//}
////读取下一行内容
//void getNext() {
//    fscanf(inputFile, "%s%s\n", type, value) ;
//    printf("第%d行  %s   %s\n", line, type, value) ;  //输出读取到的当前行 有错误时便于定位错误
//    line++ ;
//}
////将标识符添加到符号表中
//int insertSymbolTable(enum symbolType kind, char name[]) {
//    symbol temp ;       //临时变量，存要记录的新符号
//    //检查是否存在重复定义
//    switch (kind) {
//        case function : {   //函数
//            for(int i=0; i<symbolTable.size(); i++) {
//                if((strcmp(name, symbolTable[i].name))==0 && (symbolTable[i].kind==function))
//                    return 12 ;         //函数名重复定义
//            }
//            temp.kind = function ;      //没有重复的函数就正常赋值
//            break ;
//        }
//        case variable : {   //变量
//            for(int i=0; i<symbolTable.size(); i++) {
//                if((strcmp(name, symbolTable[i].name))==0 && (symbolTable[i].kind==variable))
//                    return 13 ;         //变量名重复定义
//            }
//            temp.kind = variable ;
//            temp.address = offset ;     //变量要有地址
//            offset++ ;
//            break ;
//        }
//    }
//    strcpy(temp.name, name) ;
//    symbolTable.push_back(temp) ;       //将新的符号添加到符号表中
//    symbolLength++ ;
//    return 0 ;
//}
////查找标识符再符号表中的位置
//int lookup(char name[], int *place) {
//    for(int i=0; i<symbolTable.size(); i++) {
//        if((strcmp(name, symbolTable[i].name)) == 0) {  //名字相同就找到
//            *place = i ;     //找到就把位置赋值然后返回
//            return 0 ;
//        }
//    }
//    return 14 ;         //没有找到说明没有定义，报错
//}
////判断条件
//int judge(tree* father) {
//    int flag = 0 ;
//    //检查 (
//    getNext() ;
//    if(strcmp("(", type) != 0)
//        return 4 ;
//    add(father) ;
//    //检查 expr
//    getNext() ;
//    flag = expression(father) ;     //判断条件
//    if(flag > 0)
//        return flag ;
//    //可能存在多重判断语句
//    while(strcmp("&&", type)==0 || strcmp("||", type)==0) {
//        add(father) ;
//        //检查 expr
//        getNext() ;
//        flag = expression(father) ;     //判断条件
//    }
//    //检查 )
//    if(strcmp(")", type) != 0)
//        return 5 ;
//    add(father) ;
//    return flag ;
//}
////运算因子
//int factor(tree* father) {     // < factor >::=‘(’ < additive_expr >‘)’|ID|NUM
//    tree* current = father->addSon("<factor>") ;
//    int flag = 0 ;
//    //括号有优先级，需要先处理其中的算术表达式
//    if(strcmp("(", type) == 0) {
//        add(current) ;
//        getNext() ;
//        flag = additive_expr(current) ;
//        if(flag > 0)
//            return flag ;
//        if(strcmp(")", type) != 0)
//            return 5 ;
//        add(current) ;
//        getNext() ;
//    }
//    else {  //因子还可能是标识符或者常数，都是最小单位了，没问题就直接返回
//        if(strcmp("ID", type)==0) {
//            int place ;
//            flag = lookup(value, &place) ;
//            if(flag > 0)
//                return flag ;
//            if(symbolTable[place].kind != variable) //运算语句中的标识符要是
//                return 17 ;
//            strcpy(codes[codeLength].operationCode, "LOAD") ;       //将变量存入
//            codes[codeLength].operand = symbolTable[place].address ;    //将要使用的变量地址存入
//            codeLength++ ;
//            add(current) ;
//            getNext() ;
//            return flag ;
//        }
//        else if(strcmp("NUM", type)==0) {
//            strcpy(codes[codeLength].operationCode, "LOADI") ;       //将变量存入
//            codes[codeLength].operand = atoi(value) ;//由于从文件读取出来的是字符串，需要把字符串类型的数字转换成整型
//            codeLength++ ;
//            add(current) ;
//            getNext() ;
//            return flag ;
//        }
//        else
//            return 7 ;
//    }
//    return flag ;
//}
////运算项
//int term(tree* father) {    //< term >::=<factor>{(*| /)< factor >}
//    tree* current = father->addSon("<term>") ;
//    int flag = 0 ;
//    //检查 term
//    flag = factor(current) ;
//    if(flag > 0)
//        return flag ;
//    //之后可能有多个运算过程所以要用循环不能用if
//    while(strcmp("*", type)==0 || strcmp("/", type)==0) {
//        char temp[20] ;     //暂时存储是什么类型的运算符，之后没有问题就根据对应的类型填写中间代码
//        strcpy(temp, type) ;
//        add(current) ;
//        //检查 term
//        getNext() ;
//        flag = factor(current) ;
//        if(flag > 0)
//            return flag ;
//        //将对应的运算符加入到中间代码中
//        if(strcmp("*", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "MULT") ;       //乘
//        else if(strcmp("/", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "DIV") ;       //除
//    }
//    return flag ;
//}
////算数表达式
//int additive_expr(tree* father) {   // < additive_expr>::=<term>{(+|-)< term >}
//    tree* current = father->addSon("<additive_expr>") ;
//    int flag = 0 ;
//    //检查 term
//    flag = term(current) ;
//    if(flag > 0)
//        return flag ;
//    //之后可能有多个运算过程所以要用循环不能用if
//    while(strcmp("+", type)==0 || strcmp("-", type)==0) {
//        char temp[20] ;     //暂时存储是什么类型的运算符，之后没有问题就根据对应的类型填写中间代码
//        strcpy(temp, type) ;
//        add(current) ;
//        //检查 term
//        getNext() ;
//        flag = term(current) ;
//        if(flag > 0)
//            return flag ;
//        //将对应的运算符加入到中间代码中
//        if(strcmp("+", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "ADD") ;       //加
//        else if(strcmp("-", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "SUB") ;       //减
//    }
//    return flag ;
//}
////布尔表达式
//int bool_expr(tree* father) {   //<bool_expr>::=<additive_expr>|<additive_expr>(>|<|>=|<=|==|!=)<additive_expr>
//                    //  <bool_expr>::=<additive_expr>{(>|<|>=|<=|==|!=)<additive_expr>}
//    tree* current = father->addSon("<bool_expr>") ;
//    int flag = 0 ;
//    //检查 additive_expr
//    flag = additive_expr(current) ;
//    if(flag > 0)
//        return flag ;
//    //之后可能有各种关系运算符，有就继续判断，没有就结束
//    if(strcmp(">", type)==0 || strcmp("<", type)==0 || strcmp(">=", type)==0 ||
//       strcmp("<=", type)==0 || strcmp("==", type)==0 || strcmp("!=", type)==0) {
//        char temp[20] ;     //暂时存储是什么类型的运算符，之后没有问题就根据对应的类型填写中间代码
//        strcpy(temp, type) ;
//        add(current) ;
//        //检查 additive_expr
//        getNext() ;
//        flag = additive_expr(current) ;
//        if(flag > 0)
//            return flag ;
//        //将对应的运算符加入到中间代码中
//        if(strcmp(">", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "GT") ;       //大于
//        else if(strcmp(">=", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "GE") ;       //大于等于
//        else if(strcmp("<", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "LES") ;      //小于
//        else if(strcmp("<=", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "LE") ;       //小于等于
//        else if(strcmp("==", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "EQ") ;       //等于
//        else if(strcmp("!=", temp) == 0)
//            strcpy(codes[codeLength++].operationCode, "NOTEQ") ;    //不等于
//    }
//    return flag ;
//}
////表达式
//int expression(tree* father) {  // < expression >::= ID=<bool_expr>|<bool_expr>
//    tree* current = father->addSon("<expression>") ;
//    int flag = 0 ;
//    int filePlace ;     //记录当前文件位置
//    int place ;
//    char t1[40], t2[40] ;   //临时存取数据
//    //此处进来的数据是ID
//    if(strcmp("ID", type) == 0) {   //< expression >::= ID=<bool_expr>
//        //add(current) ;
//        filePlace = ftell(inputFile) ;  //进来数据在文件中的数据
//        //检查 =
//        fscanf(inputFile, "%s%s\n", t1, t2) ;   //首先把数据存到临时的数组中
//        line++ ;
//        if(strcmp("=", t1) == 0) {    //该表达式例如 a=xxxx赋值
//            flag = lookup(value, &place) ;
//            if(flag > 0)
//                return flag ;
//            if(symbolTable[place].kind != variable) //赋值语句只能对变量进行
//                return 16 ;
//            printf("第%d行  %s   %s\n", line-1, t1, t2) ;
//            add(current) ;
//            current->addSon(t1) ;
//            //检查 bool_expr
//            getNext() ;   //如果进入到此处就继续往下读取数据就可以了，之后数据还是存在原来的数组中
//            flag = bool_expr(current) ;
//            if(flag > 0)
//                return flag ;
//            strcpy(codes[codeLength].operationCode, "STO") ;     //将赋值内容存入变量中
//            codes[codeLength].operand = symbolTable[place].address ;
//            codeLength++ ;
//        }
//        else {                      //该表达式例如 a>=xxxx
//            line-- ;            //多读取的行数要减掉
//            fseek(inputFile, filePlace, 0) ;  //读取数据返回到 = 前的标识符，即刚进来的ID的位置
//            flag = bool_expr(current) ;
//            if(flag > 0)
//                return flag ;
//        }
//    }
//    else        //< expression >::= <bool_expr>
//        flag = bool_expr(current) ;
//    return flag ;
//}
////表达式序列
//int expression_stat(tree* father) {     //<expression_stat>::=< expression >;|;
//    tree* current = father->addSon("<expression_stat>") ;
//    //add(current) ;
//    int flag = 0 ;
//    //检查第一个是 ;
//    if(strcmp(";", type) == 0) {
//        add(current) ;
//        getNext() ;
//        return flag ;
//    }
//    //检查expression
//    flag = expression(current) ;
//    if(flag > 0)
//        return flag ;
//    //检查末尾的 ;
//    if(strcmp(";", type) == 0) {
//        add(current) ;
//        getNext() ;
//        return 0 ;
//    }
//    else            //缺少 ;
//        return 3 ;
//}
////调用函数语句
//int call_stat(tree* father) {   // < call _stat>::= call ID‘(’ ‘)’ ;
//    int flag = 0 ;
//    int place ;
//    tree* current = father->addSon("<call _stat>") ;
//    add(current) ;
//    //检查 ID
//    getNext() ;
//
//    if(strcmp("ID", type) != 0)
//        return 6 ;
//    add(current) ;
//    flag = lookup(value, &place) ;
//    if(flag > 0)
//        return flag ;
//    if(symbolTable[place].kind != function) { //call之后不是函数名属于错误
//        flag = 15 ;
//		return flag ;
//	}
//    //检查 (
//    getNext() ;
//    if(strcmp("(", type) != 0)
//        return 4 ;
//    add(current) ;
//    getNext() ;
//    //可能带有参数
//    while(strcmp("NUM", type)==0 || strcmp("ID", type)==0) {   //call xxx(yyy,....)
//        add(current) ;
//        //检查是否存在多个参数
//        getNext() ;
//        if(strcmp(",", type) == 0) {       //有逗号说明有多个参数
//            add(current) ;
//            getNext() ;
//            if(strcmp("NUM", type)!=0 && strcmp("ID", type)!=0)  //如果逗号之后不是新的参数就出错
//                return 10 ;
//        }
//        else            //没有参数了就结束
//            break ;
//    }
//    //检查 )
//    if(strcmp(")", type) != 0)
//        return 5 ;
//    add(current) ;
//    getNext() ;
//    //检查 ;
//    if(strcmp(";", type) != 0)
//        return 3 ;
//    add(current) ;
//    strcpy(codes[codeLength].operationCode, "CAL") ;     //调用函数
//    codes[codeLength].operand = symbolTable[place].address ;     //进入函数的开始位置
//    codeLength++ ;
//    getNext() ;
//    return 0 ;  //没有问题就返回0
//}
////复合语句
//int compound_stat(tree* father) {   // <compound_stat>::=’{‘<statement_list>’}‘
//    tree* current = father->addSon("<compound_stat>") ;
//    add(current) ;
//    int flag = 0 ;
//    getNext() ;
//    flag = statement_list(current) ;
//    if(flag > 0)
//        return flag ;
//    add(current) ;
//    getNext() ;
//    return flag ;   //不管是否正确直接返回， } 在statement_list已经判断了
//}
////write语句
//int write_stat(tree* father) {  // <write_stat>::=write <expression>;
//    tree* current = father->addSon("<write_stat>") ;
//    add(current) ;
//    int flag = 0 ;
//    //检查 expression
//    getNext() ;
//    flag = expression(current) ;
//    if(flag > 0)
//        return flag ;
//    //检查 ;
//    if(strcmp(";", type) != 0)
//        return 3 ;
//    add(current) ;
//    strcpy(codes[codeLength].operationCode, "OUT") ;     //输出
//    codeLength++ ;
//    getNext() ;
//    return 0 ;
//}
////read语句
//int read_stat(tree* father) {   //<read_stat>::=read ID;
//    int place ;
//    int flag ;
//    tree* current = father->addSon("<read_stat>") ;
//    add(current) ;
//    //检查 ID
//    getNext() ;
//    if(strcmp("ID", type) != 0)
//        return 6 ;
//    flag = lookup(value, &place) ;       //在读取之前要先检查一下该变量是否被定义
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "IN") ;     //输入
//    codeLength++ ;
//    strcpy(codes[codeLength].operationCode, "STO") ;    //将输入的值存入对应变量
//    codes[codeLength].operand = symbolTable[place].address ;    //存入指定地址的变量中
//    codeLength++ ;
//    add(current) ;
//    //检查 ;
//    getNext() ;
//    if(strcmp(";", type) != 0)
//        return 3 ;
//    add(current) ;
//    getNext() ;     //读取下一个语句的内容
//    return 0 ;
//}
////for语句
//int for_stat(tree* father) {    // <for_stat>::= for’(‘<expr>;<expr>;<expr>’)’<statement>
//    tree* current = father->addSon("<for_stat>") ;
//    add(current) ;
//    int flag = 0 ;
//    int cx1, cx2, entance1, entance2 ;
//    //检查 (
//    getNext() ;
//    if(strcmp("(", type) != 0)
//        return 4 ;
//    add(current) ;
//    //检查 expr1
//    getNext() ;
//    flag = expression(current) ;     //判断条件
//    if(flag > 0)
//        return flag ;
//    //检查 ;
//    if(strcmp(";", type) != 0)
//        return 3 ;
//    add(current) ;
//    entance1 = codeLength ;         //记录下判断语句的入口，每次循环完都要回到此处
//    //检查 expr2
//    getNext() ;
//    flag = expression(current) ;     //判断条件
//    if(flag > 0)
//        return flag ;
//    //检查 ;
//    if(strcmp(";", type) != 0)
//        return 3 ;
//    add(current) ;
//    strcpy(codes[codeLength].operationCode, "BFR") ;    //判断为假就结束for
//    cx1 = codeLength ;          //暂时不知道结束位置，等待反填
//    codeLength++ ;
//    strcpy(codes[codeLength].operationCode, "BR") ;    //判断为真就进入循环语句
//    cx2 = codeLength ;          //暂时不知道语句开始位置，等待反填
//    codeLength++ ;
//    //检查 expr3
//    getNext() ;
//    entance2 = codeLength ;         //记录条件3的入口，用于语句的反填
//    flag = expression(current) ;     //判断条件
//    if(flag > 0)
//        return flag ;
//    //检查 )
//    if(strcmp(")", type) != 0)
//        return 5 ;
//    add(current) ;
//    strcpy(codes[codeLength].operationCode, "BR") ;    //执行完就进入判断
//    codes[codeLength].operand = entance1 ;      //跳转的位置是判断语句的入口
//    codeLength++ ;
//    //检查 statement
//    getNext() ;
//    codes[cx2].operand = codeLength ;       //反填判断为真的跳转入口
//    flag = statement(current) ;             //for中的语句
//    strcpy(codes[codeLength].operationCode, "BR") ;    //执行完就进入条件3
//    codes[codeLength].operand = entance2 ;             //跳转的位置是条件3的入口
//    codeLength++ ;
//    codes[cx1].operand = codeLength ;       //反填结束的跳转入口
//    return flag ;           //最后一个语句，不管是否正确都直接输出即可
//}
////do_while语句
//int do_while_stat(tree* father) {    // do ‘{’ < statement > ‘}’ while ‘(‘<expr >’)’ ;
//    tree* current = father->addSon("<do_while_stat>") ;
//    add(current) ;
//    int flag = 0 ;
//    int cx, entance ;
//    //检查 {
//    getNext() ;
//    if(strcmp("{", type) != 0)
//        return 1 ;
//    entance = codeLength ;      //执行语句的入口
//    //检查执行语句
//    flag = statement(current) ; //检查完执行语句后 } 已经检查完了
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "BF") ;    //执行完语句就进入判断语句
//    codes[codeLength].operand = codeLength + 1 ;        //判断语句就是下一句
//    codeLength++ ;
//    //检查 while
//    if(strcmp("while", type) != 0)
//        return 11 ;
//    add(current) ;
//    //检查判断语句
//    flag = judge(current) ;
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "BRF") ;    //为假就退出循环
//    cx = codeLength ;                      //暂时不知道循环退出位置，等待反填
//    codeLength++ ;
//    strcpy(codes[codeLength].operationCode, "BR") ;     //为真就返回执行语句
//    codes[codeLength].operand = entance ;           //返回执行语句入口
//    codeLength++ ;
//    codes[cx].operand = codeLength ;           //此处是循环出口，反填
//    getNext() ;
//    return flag ;
//}
////while语句
//int while_stat(tree* father) {      //<while_stat>::= while ‘(‘<expr >’)’ < statement >
//    int flag = 0 ;
//    int cx, entance ;
//    tree* current = father->addSon("<while_stat>") ;
//    add(current) ;
//    entance = codeLength ;      //每次循环都要重新判断条件，所以要记录判断条件的入口
//    flag = judge(current) ;
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "BRF") ;    //为假就退出whilie
//    cx = codeLength ;       //反填结束时的位置
//    codeLength++ ;
//    //检查 statement
//    getNext() ;
//    flag = statement(current) ;    //  while中的语句
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "BR") ;    //语句结束后要重新回到判断
//    codes[codeLength].operand = entance ;       //回到判断起点
//    codeLength++ ;
//    codes[cx].operand = codeLength ;        //反填结束跳转的位置
//    return flag ;           //最后一个语句，不管是否正确都直接输出即可
//}
////if语句
//int if_stat(tree* father) {     // <if_stat>::= if ‘(‘<expr>’)’ <statement > [else < statement >]
//    int flag = 0 ;
//    int cx1, cx2 ;
//    tree* current = father->addSon("<if_stat>") ;
//    add(current) ;
//    flag = judge(current) ;     //判断条件
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "BRF") ;    //为假就进入else
//    cx1 = codeLength ;      //记录if为假时结束跳转的地方，之后反填
//    codeLength++ ;
//    //检查 statement
//    getNext() ;
//    flag = statement(current) ;    //  if中的语句
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "BR") ;     //为真结束之后退出if
//    cx2 = codeLength ;      //记录if结束时跳转的地方，之后反填
//    codeLength++ ;
//    codes[cx1].operand = codeLength ;   //if为假要跳转到else的开始语句
//    //检查 else
//    if(strcmp("else", type) == 0) {   //当前的数据由上一步中获得了
//        add(current) ;
//        //检查 statement
//        getNext() ;
//        flag = statement(current) ;    //else中的语句
//        if(flag > 0)
//            return flag ;
//    }
//    codes[cx2].operand = codeLength ;   //if结束时跳转的地方
//    return flag ;
//}
////语句内容
//int statement(tree* father) {
///*<statement>::=<if_stat>|<while_stat>|<for_stat>|<read_stat>|<write_stat>|
//<compound_stat> |<expression_stat> | < call _stat> */
//    tree* current = father->addSon("<statement>") ;
//    int flag = 0 ;
//    //从声明中结束后得到第一个语句单词
//    if(flag==0 && strcmp("if", type)==0)
//        flag = if_stat(current) ;
//    if(flag==0 && strcmp("while", type)==0)
//        flag = while_stat(current) ;
//    if(flag==0 && strcmp("for", type)==0)
//        flag = for_stat(current) ;
//    if(flag==0 && strcmp("read", type)==0)
//        flag = read_stat(current) ;
//    if(flag==0 && strcmp("write", type)==0)
//        flag = write_stat(current) ;
//    if(flag==0 && strcmp("{", type)==0)    //复合语句要从 { 开始
//        flag = compound_stat(current) ;
//    if(flag==0 && strcmp("call", type)==0)
//        flag = call_stat(current) ;
//    if(flag==0 && (strcmp("(", type)==0 || strcmp(";", type)==0 ||
//                strcmp("NUM", type)==0 || strcmp("ID", type)==0) )
//        flag = expression_stat(current) ;
//    if(flag==0 && strcmp("do", type)==0)    //do_while语句
//        flag = do_while_stat(current) ;
//    return flag ;
//}
////语句序列
//int statement_list(tree* father) {  //<statement_list>::=<statement_list><statement>| ε
//                                    //<statement_list>::={<statement>}
//    tree* current = father->addSon("<statement_list>") ;
//    int flag = 0 ;
//    while(strcmp("}", type) != 0) { //到 } 结束
//        if(feof(inputFile))     //一直到末尾都没有 } 则出错
//            return 2 ;
//        flag = statement(current) ;    //查看具体的语句
//        if(flag > 0)
//            return flag ;
//    }
//    return flag ;
//}
////声明内容
//int declaration_stat(tree* father) {        //<declaration_stat>::=int ID;
//    int flag = 0 ;
//    tree* current = father->addSon("<declaration_stat>") ;
//    add(current) ;
//    //检查 ID
//    getNext() ;
//    if(strcmp("ID", type) != 0)   //缺少标识符
//        return 6 ;
//    add(current) ;
//    flag = insertSymbolTable(variable, value) ;    //将变量名添加到符号表中
//    if(flag > 0)
//        return flag ;
//    //检查 赋值
//    getNext() ;
//    if(strcmp("=", type) == 0) {    //变量名之后是 = 则需要赋值
//        add(current) ;
//        //检查 赋值
//        getNext() ;
//        if(strcmp("NUM", type) != 0)    //缺少赋值
//            return 7 ;
//        add(current) ;
//        //检查 ;
//        getNext() ;
//        if(strcmp(";", type) != 0)   //缺少 ;
//            return 3 ;
//        add(current) ;
//    }
//    else {  //检查 ;
//        if(strcmp(";", type) != 0)   //缺少 ;
//            return 3 ;
//        add(current) ;
//    }
//    return 0 ;              //正常就返回0
//}
////声明序列
//int declaration_list(tree* father) {    //<declaration_list>::=<declaration_list><declaration_stat> |ε
//                                        //<declaration_list>::={<declaration_stat>}
//    tree* current = father->addSon("<declaration_list>") ;
//    int flag = 0 ;
//    while(1) {
//        getNext() ;
//        if(strcmp("int", type) != 0)   //不是int说明已经没有变量声明了进入语句内容
//            break ;
//        flag = declaration_stat(current) ;     //具体的声明内容
//        if(flag > 0)
//            return flag ;
//    }
//    return flag ;
//}
////函数体
//int function_body(tree* father) {       //<function_body>::= ‘{’<declaration_list><statement_list> ‘}’ (
//    tree* current = father->addSon("<function_body>") ;
//    int flag = 0 ;
//    //检查 {
//    getNext() ;
//    if(strcmp("{", type) != 0)   //缺少 {
//        return 1 ;
//    add(current) ;
//    //检查 declaration_list
//    offset = 2 ;        //每次进入一个函数体的时候，相对地址都要重置为2
//    symbolTable[symbolLength-1].address = codeLength ;  //函数体的入口地址，上一个存在符号表中的是函数名
//    flag = declaration_list(current) ; //如果成功了当前的单词是语句的内容
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "ENTER") ;  //为函数调用开辟空间
//    codes[codeLength].operand = offset ;
//    codeLength++ ;
//    //检查 statement_list
//    flag = statement_list(current) ;   //一开始不用读取新的内容，成功了当前的单词应该是 }
//    if(flag > 0)
//        return flag ;
//    strcpy(codes[codeLength].operationCode, "RETURN") ;  //函数返回
//    codeLength++ ;
//    add(current) ;
//    getNext() ;
//    return flag ;
//}
////主函数
//int main_declaration(tree* father) {    //<main_declaration>::=main’(‘ ‘ )’ < function_body>
//    int flag = 0 ;
//    tree* current = father->addSon("<main_declaration>") ;
//    add(current) ;
//    getNext() ;
//    //检查 main
//    if(strcmp("main", value) != 0)   //程序中最后的声明必须是名字为 main 的主函数
//        return 6 ;
//    add(current) ;
//    flag = insertSymbolTable(function, value) ;    //将函数名添加到符号表中
//    if(flag > 0)
//        return flag ;
//    //检查 (
//    getNext() ;
//    if(strcmp("(", type) != 0)   //缺少 (
//        return 4 ;
//    add(current) ;
//    //检查 )
//    getNext() ;
//    if(strcmp(")", type) != 0)   //缺少 )
//        return 5 ;
//    add(current) ;
//    codes[0].operand = codeLength ;     //main函数为程序运行的起点
//    //检查 function_body
//    return function_body(current) ;     //检查函数体
//}
////函数
//int fun_declaration(tree* father) {     // <fun_declaration>::= function ID’(‘ ‘ )’< function_body>
//    int flag = 0 ;
//    tree* current = father->addSon("<fun_declaration>") ;   //当前类型
//    add(current) ;              //当前数据没问题就将其加入到树中
//    //检查 ID
//    getNext() ;
//    if(strcmp("ID", type) != 0)   //缺少标识符代表函数名
//        return 6 ;
//    add(current) ;
//    flag = insertSymbolTable(function, value) ;    //将函数名添加到符号表中
//    if(flag > 0)
//        return flag ;
//    //检查 (
//    getNext() ;
//    if(strcmp("(", type) != 0)   //缺少 (
//        return 4 ;
//    add(current) ;
//    //检查参数
//    getNext() ;
//    while(strcmp("int", type) == 0) {   //int xxx (,....)
//        add(current) ;
//        //检查 标识符
//        getNext() ;
//        if(strcmp("ID", type) != 0)
//            return 6 ;
//        add(current) ;
//        //检查是否存在多个参数
//        getNext() ;
//        if(strcmp(",", type) == 0) {       //有逗号说明有多个参数
//            add(current) ;
//            getNext() ;
//            if(strcmp("int", type) != 0)    //如果逗号之后不是新的参数就出错
//                return 10 ;
//        }
//        else            //没有参数了就结束
//            break ;
//    }
//    //检查 )
//    if(strcmp(")", type) != 0)   //缺少 )
//        return 5 ;
//    add(current) ;
//    //检查 function_body
//    return function_body(current) ;     //检查函数体
//}
////程序
//int program() {     //<program> ::={fun_declaration }<main_declaration>
//    int flag = 0 ;
//    strcpy(codes[codeLength].operationCode, "BR") ;    //程序开始先跳转到main函数
//    codeLength++ ;
//    root = new tree() ;
//    root->data = "<program>" ;
//    //检查 全局变量,可能有也可能没有
//    flag = declaration_list(root) ; //如果成功了当前的单词是语句的内容
//    if(flag > 0)
//        return flag ;
//    //检查 fun_declaration
//    while(strcmp("function", type) == 0) {   //函数声明，可能有也可能没有
//        flag = fun_declaration(root) ;     //检查函数声明
//        if(flag > 0)
//            return flag ;               //若函数有问题就返回错误类型
//    }
//    codes[0].operand = codeLength ;
//    if(strcmp("int", type) == 0) {  //主函数
//        //检查 main_declaration
//        flag = main_declaration(root) ; //检查主函数内容
//        if(flag > 0)
//            return flag ;
//    }
//    else
//        return 6 ;
//    return flag ;
//}
////语法分析
//int parseAlanalysis() {
//    //初始化，得到输入输出文件
//    printf("请输入 输入文件地址：") ;
//    scanf("%s", inputAddress) ;
//    if((inputFile=fopen(inputAddress, "r")) == NULL)     //读取输入文件
//        return 8 ;      //读取文件出错就返回对应错误类型
//    printf("请输入 输出文件地址：") ;
//    scanf("%s", outputAddress) ;
//    if((outputFile=fopen(outputAddress, "w")) == NULL)   //读取输出文件
//        return 9 ;      //读取文件出错就返回对应错误类型
//    printf("\n") ;
//    return program() ;      //文件读取成功就看看里面的内容
//}
//
//int main() {
//    int flag = 0 ;
//    flag = parseAlanalysis() ;      //递归下降语法分析
//    //处理结果
//    printf("\n\n==================================\n\n") ;
//    if(flag == 0) {
//        printf("语义分析成功\n") ;
//        //printTree(root, 0) ;        //输出语法树
//        for(int i=0; i<codeLength; i++)     //将中间代码写入文件
//            fprintf(outputFile, "%s    %d\n", codes[i].operationCode, codes[i].operand) ;
//        printf("\n符号表\n") ;
//        for(int i=0; i<symbolTable.size(); i++)
//            printf("name: %s   address:%d   kind:%d \n",
//                   symbolTable[i].name, symbolTable[i].address, symbolTable[i].kind) ;
//        printf("\n") ;
//        printf("中间代码\n") ;
//        for(int i=0; i<codeLength; i++)
//            printf("%d 操作码：%s   操作数:%d\n", i, codes[i].operationCode, codes[i].operand) ;
//    }
//    else {
//        printf("语义分析失败\n") ;
//        switch (flag) {                 //选则具体的错误类型
//            case 1 : printf("第%d行缺少 { \n", line-1) ; break ;
//            case 2 : printf("第%d行缺少 } \n", line-1) ; break ;
//            case 3 : printf("第%d行缺少 ; \n", line-1) ; break ;
//            case 4 : printf("第%d行缺少 ( \n", line-1) ; break ;
//            case 5 : printf("第%d行缺少 ) \n", line-1) ; break ;
//            case 6 : printf("第%d行缺少标识符\n", line-1) ; break ;
//            case 7 : printf("第%d行缺少操作数\n", line-1) ; break ;
//            case 8 : printf("无法打开输入文件%s\n", inputAddress);  break ;
//            case 9 : printf("无法打开输出文件%s\n", outputAddress); break ;
//            case 10 : printf("第%d行缺少参数\n", line-1);  break ;
//            case 11 : printf("第%d行缺少保留字\n", line-1);  break ;
//            case 12 : printf("第%d行函数名 %s 重复定义\n", line-1, value);  break ;
//            case 13 : printf("第%d行变量名 %s 重复定义\n", line-1, value);  break ;
//            case 14 : printf("第%d行标识符 %s 没有定义\n", line-1, value);  break ;
//            case 15 : printf("第%d行call之后的标识符 %s 不是函数名\n", line-1, value);  break ;
//            case 16 : printf("第%d行赋值语句的标识符 %s 不是变量名\n", line-1, value);  break ;
//            case 17 : printf("第%d行运算语句的标识符 %s 不是变量名\n", line-1, value);  break ;
//        }
//    }
//    return 0 ;
//}
//

