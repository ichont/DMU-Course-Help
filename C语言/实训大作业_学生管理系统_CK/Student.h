/*这是声明头文件*/
#ifndef STUDENT_H        // 保护头文件,避免重复套用
#define STUDENT_H
#define N 10             // 宏定义输入学生数目
struct Student {         // 学生的信息
  char name[8];//名字
  char num[15];//学号
  char major[10];//专业:computer,network,software
  int calss;//班级1-2
  int score[3];//三门课成绩
};
typedef struct Student STU;
STU Head [N+1];          // 设置一个数组进行暂时存放信息,N+1是防越界
void menu();             //菜单
void Input(STU* p);      // 输入函数
void Save (STU* p,int n);  // 储存函数
void Output(STU* p);       // 输出函数
void Loadstudent(STU* p,int n); // 读取函数
void FindnStudent();         // 查询第n个学生的函数
void Findscore();                // 查询相应成绩
void Maxscore();             // 最大成绩
void Show();//显示从n到m的学生信息
void Choosesort();//选择排序
void Bubblesort();//冒泡排序
void Insertsort();//插入排序
#endif // STUDENT_H
