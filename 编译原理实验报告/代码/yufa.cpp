//#include<bits/stdc++.h>
//using namespace std ;
//struct tree {
//    string data ;
//    vector<tree*> son ;
//    tree* addSon(string str) {
//        tree* newSon = new tree() ;
//        newSon->data = str ;
//        son.push_back(newSon) ;
//        return newSon ;
//    }
//} *root;
//FILE *inputFile ;   //输入文件
//FILE *outputFile ;  //输出文件
//char inputAddress[20] ;     //输入文件地址
//char outputAddress[20] ;    //输出文件地址
//char type[20] ;     //单词类型
//char value[40] ;    //单词值
//int line = 1 ;      //当前读到第几行
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
//        fprintf(outputFile, "`      ") ;
//    fprintf(outputFile,"%s\n",p->data.c_str()) ;
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
//    printf("第%d行  %s   %s\n", line, type, value) ;
//    line++ ;
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
//        if(strcmp("ID", type)==0 || strcmp("NUM", type)==0) {
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
//        add(current) ;
//        //检查 term
//        getNext() ;
//        flag = factor(current) ;
//        if(flag > 0)
//            return flag ;
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
//        add(current) ;
//        //检查 term
//        getNext() ;
//        flag = term(current) ;
//        if(flag > 0)
//            return flag ;
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
//        add(current) ;
//        //检查 additive_expr
//        getNext() ;
//        flag = additive_expr(current) ;
//        if(flag > 0)
//            return flag ;
//    }
//    return flag ;
//}
////表达式
//int expression(tree* father) {  // < expression >::= ID=<bool_expr>|<bool_expr>
//    tree* current = father->addSon("<expression>") ;
//    int flag = 0 ;
//    int filePlace ;     //记录当前文件位置
//    char t1[40], t2[40] ;   //临时存取数据
//    //此处进来的数据是ID
//    if(strcmp("ID", type) == 0) {   //< expression >::= ID=<bool_expr>
//        //add(current) ;
//        filePlace = ftell(inputFile) ;  //进来数据在文件中的数据
//        //检查 =
//        fscanf(inputFile, "%s%s\n", t1, t2) ;   //首先把数据存到临时的数组中
//        line++ ;
//        if(strcmp("=", t1) == 0) {    //该表达式例如 a=xxxx
//            printf("第%d行  %s   %s\n", line, t1, t2) ;
//            add(current) ;
//            current->addSon(t1) ;
//            //检查 bool_expr
//            getNext() ;   //如果进入到此处就继续往下读取数据就可以了，之后数据还是存在原来的数组中
//            flag = bool_expr(current) ;
//            if(flag > 0)
//                return flag ;
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
//    tree* current = father->addSon("<call _stat>") ;
//    add(current) ;
//    //检查 ID
//    getNext() ;
//    if(strcmp("ID", type) != 0)
//        return 6 ;
//    add(current) ;
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
//    getNext() ;
//    return 0 ;
//}
////read语句
//int read_stat(tree* father) {   //<read_stat>::=read ID;
//    tree* current = father->addSon("<read_stat>") ;
//    add(current) ;
//    //检查 ID
//    getNext() ;
//    if(strcmp("ID", type) != 0)
//        return 6 ;
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
//    //检查 (
//    getNext() ;
//    if(strcmp("(", type) != 0)
//        return 4 ;
//    add(current) ;
//    for(int i=0; i<2; i++) {
//        //检查 expr
//        getNext() ;
//        flag = expression(current) ;     //判断条件
//        if(flag > 0)
//            return flag ;
//        //检查 ;
//        if(strcmp(";", type) != 0)
//            return 3 ;
//        add(current) ;
//    }
//    //检查 expr
//    getNext() ;
//    flag = expression(current) ;     //判断条件
//    if(flag > 0)
//        return flag ;
//    //检查 )
//    if(strcmp(")", type) != 0)
//        return 5 ;
//    add(current) ;
//    //检查 statement
//    getNext() ;
//    flag = statement(current) ;    //  for中的语句
//    return flag ;           //最后一个语句，不管是否正确都直接输出即可
//}
////do_while语句
//int do_while_stat(tree* father) {    // do ‘{’ < statement > ‘}’ while ‘(‘<expr >’)’ ;
//    tree* current = father->addSon("<do_while_stat>") ;
//    add(current) ;
//    int flag = 0 ;
//    //检查 {
//    getNext() ;
//    if(strcmp("{", type) != 0)
//        return 1 ;
//    //检查执行语句
//    flag = statement(current) ; //检查完执行语句后 } 已经检查完了
//    if(flag > 0)
//        return flag ;
//    //检查 while
//    if(strcmp("while", type) != 0)
//        return 11 ;
//    add(current) ;
//    //检查判断语句
//    flag = judge(current) ;
//    if(flag > 0)
//        return flag ;
//    getNext() ;
//    return flag ;
//}
////while语句
//int while_stat(tree* father) {      //<while_stat>::= while ‘(‘<expr >’)’ < statement >
//    tree* current = father->addSon("<while_stat>") ;
//    add(current) ;
//    int flag = 0 ;
//    flag = judge(current) ;
//    if(flag > 0)
//        return flag ;
//    //检查 statement
//    getNext() ;
//    flag = statement(current) ;    //  while中的语句
//    return flag ;           //最后一个语句，不管是否正确都直接输出即可
//}
////if语句
//int if_stat(tree* father) {     // <if_stat>::= if ‘(‘<expr>’)’ <statement > [else < statement >]
//    tree* current = father->addSon("<if_stat>") ;
//    add(current) ;
//    int flag = 0 ;
//    flag = judge(current) ;     //判断条件
//    if(flag > 0)
//        return flag ;
//    //检查 statement
//    getNext() ;
//    flag = statement(current) ;    //  if中的语句
//    if(flag > 0)
//        return flag ;
//    //检查 else
//    if(strcmp("else", type) == 0) {   //当前的数据由上一步中获得了
//        add(current) ;
//        //检查 statement
//        getNext() ;
//        flag = statement(current) ;    //else中的语句
//        if(flag > 0)
//            return flag ;
//    }
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
//                strcmp("NUM", type)==0) || strcmp("ID", type)==0)
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
//        if(feof(inputFile))
//            return 2 ;
//        flag = statement(current) ;    //查看具体的语句
//        if(flag > 0)
//            return flag ;
//    }
//    add(current) ;
//    getNext() ;
//    return flag ;
//}
////声明内容
//int declaration_stat(tree* father) {        //<declaration_stat>::=int ID;
//    tree* current = father->addSon("<declaration_stat>") ;
//    add(current) ;
//    //检查 ID
//    getNext() ;
//    if(strcmp("ID", type) != 0)   //缺少标识符
//        return 6 ;
//    add(current) ;
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
//                            //<declaration_list>::={<declaration_stat>}
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
//    flag = declaration_list(current) ; //如果成功了当前的单词是语句的内容
//    if(flag > 0)
//        return flag ;
//    //检查 statement_list
//    flag = statement_list(current) ;   //一开始不用读取新的内容，成功了当前的单词应该是 }
//    return flag ;
//}
////主函数
//int main_declaration(tree* father) {    //<main_declaration>::=main’(‘ ‘ )’ < function_body>
//    tree* current = father->addSon("<main_declaration>") ;
//    add(current) ;
//    getNext() ;
//    //检查 main
//    if(strcmp("main", value) != 0)   //程序中最后的声明必须是名字为 main 的主函数
//        return 6 ;
//    add(current) ;
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
//    //检查 function_body
//    return function_body(current) ;     //检查函数体
//}
////函数声明
//int fun_declaration(tree* father) {     // <fun_declaration>::= function ID’(‘ ‘ )’< function_body>
//    tree* current = father->addSon("<fun_declaration>") ;   //当前类型
//    add(current) ;      //当前数据没问题就将其加入到树中
//    //检查 ID
//    getNext() ;
//    if(strcmp("ID", type) != 0)   //缺少标识符代表函数名
//        return 6 ;
//    add(current) ;
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
//    printf("\n\n=============语法分析结果=====================\n\n") ;
//    if(flag == 0) {
//        printf("语法分析成功\n") ;
//        printTree(root, 0) ;
//    }
//    else {
//        printf("语法分析失败\n") ;
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
//        }
//    }
//    return 0 ;
//}
//

