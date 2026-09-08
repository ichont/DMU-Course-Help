#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std ;

const int keywordNum = 15 ;       //保留字个数
const int singlewordNum = 9 ;     //单分界符个数
const int pureSingleNum = 6 ;     //纯单分符个数
const int doublewordNum = 6 ;     //双分界符个数

char identifier[105] ;          //记录当前的标识符
int identifierLength = 0 ;      //标识符长度
int keywordPlace ;              //保留字的位置
char numbers[105] ;             //记录当前数字大小
int numbersLength = 0 ;         //数字位数
char character[10] ;             //记录目前分界符
int characterNum = 0 ;         //分界符数
char note[2] ;                  //记录可能是注释的字符
int noteNum = 0 ;               //注释数
bool startFlag = false ;       //标记是否进入注释
char prior ;                    //上一个读取的字符
int errorSum = 0 ;              //报错数量
int line = 1 ;                  //源程序行数
char inputAddress[20] ;     //输入文件地址
char outputAddress[20] ;    //输出文件地址
FILE *inputFile ;               //输入test文件
FILE *outputFile ;              //输出结果文件

char keyword[keywordNum][20] = {"break", "call", "case", "default", "do",
            "else", "for", "function", "if", "int", "read", "switch", "then", "while", "write" } ; //保留字，按字典序排好
char pureSingleword[pureSingleNum] = {'(', ')', ',', ';', '{', '}'} ;           //纯单分符
char singleword[singlewordNum] = {'!', '&', '*', '+', '-', '<', '=', '>', '|'} ;//单分符或可能存在双分符
char doubleword[doublewordNum][5] = {"!=", "&&", "<=", "==", ">=", "||"} ;      //双分符
char errors[105][50] ;

//折半查找保留字，要使用必须先把保留字表按从小到大的顺序排好
bool binarySearch(char temp[], int left, int right) {
    if(left > right)    //遍历所有元素都找不到
        return false ;
    int mid = (left+right) / 2 ;
    if(!strcmp(temp, keyword[mid])) {       //找到和暂时存储在标识符数组相同的就是保留字
        keywordPlace = mid ;
        return true ;
    }
    else if(strcmp(temp, keyword[mid]) > 0)
        return binarySearch(temp, mid+1, right) ;
    else
        return binarySearch(temp, left, mid-1) ;
}
//判断字符是否为空字
bool isNull(char temp) {
    if(temp=='\n') {
        line++ ;            //每有一个回车就加一行
        return true ;
    }
    if(temp==' ' || temp=='\t' || temp=='\n')//空字包括空格、回车、tab
        return true ;
    else
        return false ;
}
//判断字符是否是字母
bool isLetter(char temp) {
    if(temp<='z' && temp>='a')  //小写字母
        return true ;
    if(temp<='Z' && temp>='A')  //大写字母
        return true ;
    return false ;
}
//判断字符是否是数字
bool isNumber(char temp) {
    if(temp<='9' && temp>='0')
        return true ;
    return false ;
}
//判断是否是纯单分符
bool isPureSingleword(char temp) {
    for(int i=0; i<pureSingleNum; i++) {    //查已经写好的纯单分符表有相同的就是
        if(temp == pureSingleword[i])
            return true ;
    }
    return false ;
}
//判断是否是单分符
bool isSingleword(char temp) {
    for(int i=0; i<singlewordNum; i++) {    //查已经写好的单分符表有相同的就是
        if(temp == singleword[i])
            return true ;
    }
    return false ;
}
//判断是否是单双分符
bool isDoubleword() {
    for(int i=0; i<doublewordNum; i++) {    //查已经写好的双分符表有相同的就是
        if(!strcmp(character, doubleword[i]))
            return true ;
    }
    return false ;
}
//判断是否是 '/'  用于判断是否有可能是注释的开始标志
bool isDiagonal(char temp) {
    if(temp=='/' || temp=='*')      //注释的开始标志由  /*  组成
        return true ;
    return false ;
}
//输出之前还未输出的内容
void printbefore() {
    /*各种长度不为0则说明在正在进行词法分析的字符之前有不同类型的东西没有输出
    由于这些肯定是在当前字符之前的所以应当优先输出*/
    if(identifierLength != 0) {         //之前是一个标识符或者保留字
        char temp[50] ;
        strcpy(temp, identifier) ;
        strlwr(temp) ;          //防止区分大小写，将所有大写都换成小写
        if(isNumber(identifier[0])) {             //非法标识符错误，第一位是数字
            sprintf(errors[errorSum], "第%d行:   非法标识符%s", line, identifier);
            errorSum++ ;
        }
        else if(binarySearch(temp, 0, keywordNum-1)) {  //保留字
            printf("%s      %s\n", keyword[keywordPlace], identifier) ;
            fprintf(outputFile, "%s      %s\n", keyword[keywordPlace], identifier) ;//写入输出文件中
        }
        else {                                  //标识符
            printf("ID      %s\n", identifier) ;
            fprintf(outputFile, "ID      %s\n", identifier) ;
        }
        memset(identifier, 0, sizeof(identifier)) ; //清空字符串内容
        identifierLength = 0 ;                      //清空字符串长度
    }
    if(numbersLength != 0) {               //之前是一个数字
        int num = 0 ;
        for(int i=0; i<numbersLength; i++) {    //将字符串变为整型
            num *= 10 ;
            num += (numbers[i] - '0') ;
        }
        printf("NUM     %d\n", num) ;
        fprintf(outputFile, "NUM     %d\n", num) ;
        memset(numbers, 0, sizeof(numbers)) ;   //清空字符串内容
        numbersLength = 0 ;
    }
    if(characterNum != 0) {            //之前是单分符或双分符
        if(characterNum > 2) {      //没有大于两个字符的组合，属于错误
            sprintf(errors[errorSum], "第%d行:   非法标识符%s", line, character);
            errorSum++ ;
        }
        if(characterNum == 1) {         //单分符
            printf("%c     %c\n", character[0], character[0]) ;
            fprintf(outputFile, "%c     %c\n", character[0], character[0]) ;
        }
        if(characterNum == 2) {    //双分符
            if(isDoubleword()) {    //首先要判断这两个连续的字符是不是双分符
                printf("%s     %s\n", character, character) ;
                fprintf(outputFile, "%s     %s\n", character, character) ;
            }
        }
        memset(character, 0, sizeof(character)) ;   //不管是单分符还是双分符都要清空
        characterNum = 0 ;
    }
    if(noteNum != 0) {            //之前是单分符或注释
        if(noteNum == 1) {         //单分符
            printf("%c     %c\n", note[0], note[0]) ;
            fprintf(outputFile, "%c     %c\n", note[0], note[0]) ;
            memset(note, 0, sizeof(note)) ;   //不管是单分符还是注释都要清空
            noteNum = 0 ;
        }
        else if(noteNum == 2) {    //注释
            if(!strcmp(note, "/*"))     //多行注释开始
                startFlag = true ;
            else {
                printf("%c     %c\n", note[0], note[0]) ;
                printf("%c     %c\n", note[1], note[1]) ;
                fprintf(outputFile, "%c     %c\n%c     %c\n", note[0], note[0], note[1], note[1]) ;
            }
            memset(note, 0, sizeof(note)) ;
            noteNum = 0 ;
        }
    }
}
//词法分析
void wordanalysis(char temp) {
    if(isNull(temp)) {      //遇到空字就继续看下一个字符
        printbefore() ;     //如果空字前有东西没有处理需要进行操作
        prior = temp ;      //进入到此处就不会执行后面的内容了，此处也要设置上一个字符
        return ;            //退出该函数
    }
    if(isLetter(temp) || (isLetter(prior)&&isNumber(temp))) {    //判断当前字符是不是字母
        //字母加数字的组合也可以是标识符
        if(isNumber(prior) && identifierLength==0 ) {   //但是数字加字母是非法的标识符
            //如果标识符数组中还没有任何字符，但是在第一个字母之前有任意多个数字则是非法标识符
            for(int i=0; i<numbersLength; i++) {    //将常数数组中的数组全部转移到标识符数组中
                identifier[identifierLength] = numbers[i] ;
                identifierLength++ ;
            }
            memset(numbers, 0, sizeof(numbers)) ;   //清空常数内容0
            numbersLength = 0 ;
        }
        if(!isLetter(prior) && identifierLength==0)//标识符长度为0才证明之前的数字不包含在标识符中
            printbefore() ;
        if(!startFlag) {    //可能在之前的if中判断出进入注释了就不能再继续了
            identifier[identifierLength] = temp ;   //是就将其加入到当前的标识符单词中
            identifierLength++ ;
        }
    }
    else if(isNumber(temp)) {   //判断当前字符是不是数字
        if(!isNumber(prior))    //如果前后字符类型不同就有可能要输出一些内容
            printbefore() ;
        if(!startFlag) {
            numbers[numbersLength] = temp ; //是数字就加入到数字数组中
            numbersLength++ ;
        }
    }
    else if(isPureSingleword(temp)) {           //判断当前字符是不是纯单分符
        if(!isPureSingleword(prior))
            printbefore();
        if(!startFlag) {
            printf("%c     %c\n", temp, temp) ;     //是纯单分符就直接输出
            fprintf(outputFile, "%c     %c\n", temp, temp) ;
        }
    }
    else if(!(temp=='*'&&prior=='/') && isSingleword(temp) ) {    //判断当前字符是不是单分符
        //要注意考虑注释的情况
        if(!isSingleword(prior))
            printbefore() ;
        if(!startFlag) {
            character[characterNum] = temp ;
            characterNum++ ;
        }
    }
    else if(isDiagonal(temp)) {          //判断当前字符是不是/
        if(!isDiagonal(prior))
            printbefore() ;
        if(!startFlag) {
            note[noteNum] = temp ;
            noteNum++ ;
            if(!strcmp(note, "/*")) {    //多行注释开始
                startFlag = true ;
                memset(note, 0, sizeof(note)) ;
            	noteNum = 0 ;
            }
        }
    }
    else {          //错误判断非法字符
        printbefore() ;
        if(!startFlag) {
            sprintf(errors[errorSum], "第%d行:   非法字符%c", line, temp);
            errorSum++ ;
        }
    }
    prior = temp ;              //处理完当前字符后就将其设为上一个字符
}
int main() {
    //初始化，得到输入输出文件
    printf("请输入 输入文件地址：") ;
    scanf("%s", inputAddress) ;
    if((inputFile=fopen(inputAddress, "r")) == NULL)     //读取输入文件
        printf("\nerror: 无法打开输入文件\n\n");
    printf("请输入 输出文件地址：") ;
    scanf("%s", outputAddress) ;
    if((outputFile=fopen(outputAddress, "w")) == NULL)   //读取输出文件
        printf("\nerror: 无法打开结果文件\n\n");

    while(!feof(inputFile)) {   //读取输入文件直到内容结束
        char current ;          //当前字符
        fscanf(inputFile, "%c", &current) ;    //每次读取一个字符
        if(startFlag) {         //在注释中就不进行词法分析
            if(current=='/' && prior=='*') {    //当遇到注释结束标志时修改状态
                prior = current ;
                startFlag = false ;
            }
            else {
                if(current=='\n') //注释中的行数也要考虑在内
                    line++ ;
                prior = current ;   //注释中只需要记录上一个字符是什么，为了找到结束注释做准备
            }
        }
        else                //不在注释中就要进行词法分析
            wordanalysis(current) ;
        current = ' ' ;     //每次处理完都要设为空字防止末尾字符多输出一次
    }
    if(startFlag) {       //如果注释没有结束符号，则注释之后的内容都没有了，可能会出错
        //printf("\nerror: 注释没有封闭\n\n");
        sprintf(errors[errorSum], "第%d行:   注释没有封闭", line);
        errorSum++ ;
    }
    //输出分析结果
    printf("\n\n===========================================") ;
    if(errorSum == 0)
        printf("\n词法分析成功\n") ;
    else {
        printf("\n错误数量:  %d \n", errorSum) ;
        for(int i=0; i<errorSum; i++)
            printf("%s\n", errors[i]) ;
    }
    return 0 ;
}


