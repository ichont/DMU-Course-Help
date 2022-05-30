/*这是函数定义文件*/
#include"Student.h"
//菜单
void menu (){
printf("\t\t\t\tStudent Manager Sts   v1.0 by CK\n");
printf("\t\t\t  ************************************************\n");
printf("\t\t\t1.*初始信息录入                                  *\n");
printf("\t\t\t2.*读取文件中学生信息                            *\n");
printf("\t\t\t3.*显示当前缓存中的学生信息                      *\n");
printf("\t\t\t4.*读取第n个学生的信息                           *\n");
printf("\t\t\t5.*输入班级和成绩查找                            *\n");
printf("\t\t\t6.*所有学生某门课的最高分和学生姓名              *\n");
printf("\t\t\t7.*对所有学生按平均成绩从低到高排序              *\n");
printf("\t\t\t8.*对某个专业学生的某门课成绩由高到低进行排序    *\n");
printf("\t\t\t9.*储存更新后的学生信息                          *\n");
printf("\t\t\t10*对某个专业的学生某门课按成绩从高到低排序      *\n");
printf("\t\t\t0.*退出程序                                      *\n");
printf("\t\t\t  ************************************************\n");
printf("\t\t\t\t*请选择你的操作:");
}
//输入函数
void Input(STU* p) {
    system("cls");                   //清屏
    int i = 1;
    int n;
//    printf("请输入录入的学生数目 n :"); //这是下一步完善的功能
//    scanf("%d",&n);
    n = N;                                // 没有完善,暂时这样写
    while(i <= n) {                       //循环输入
    int id;
    printf("******第%d个******\n",i);
    printf("请输入学生姓名:\t");
    getchar();
    scanf("%s",p->name);
    getchar();
    printf("请输入学号(1- 20):\t");
    scanf("%s",p->num);
    printf("请选择专业:\t1.Computer\t2.Sotfware\t3.Network:\t");
    scanf("%d",&id);
    switch(id) {
       case 1: strcpy(p->major,"Computer");break;
       case 2: strcpy(p->major,"Sotfware");break;
       case 3: strcpy(p->major,"NetWork");break;
       default  : printf("输入错误,无法返回,被分到 格兰芬多学院 \n");  //一个小彩蛋
                   strcpy(p->major,"Gryffindor");break;
    }
    printf("请输入班级1 or 2:\t");
    scanf("%d",&(p->calss));
    printf("请输入大英成绩:\t");
    scanf("%d",&(p->score[0]));
    printf("请输入高数成绩:\t");
    scanf("%d",&(p->score[1]));
    printf("请输入C语言成绩: ");
    scanf("%d",&(p->score[2]));
    p++;
    i++;
      }
    printf("输入完成!!!\n");
    system("pause"); //暂停
    system("cls");    //清屏
}
//保存,每次保存会覆盖上次的数据
void Save(STU* p,int n){
 FILE* fp;
 int i = 1;
 char filename[30];
 printf("请输入保存的文件名:");       //暂时
 getchar();                           //清除回车
 gets(filename);
  if((fp = fopen(filename,"wb")) == NULL) { //没加括号之前无法保存,加了括号后问题解决 // 以写入的方式打开文件
    printf("cannot open file\n");                    //如果打不开,报错
    return;
  }
    while(i++ <= n){
    if (fwrite(p++,sizeof(STU),1,fp) != 1){         // 写入,fwrite应与fread对应使用,fprintf与fscanf对应使用,不然很麻烦
        printf("file write error\n");                // 错误提示
        return;
     }
    }
  printf("正在保存********\n");
  printf("保存成功!!!\n");
  fclose(fp);
  system("pause");
  system("cls");
}
// 输出函数
void Output(STU* p){
  if (p == NULL) return;
  printf("name:%s\t\tnum:%s\t\tmajor:%s\t\tclass:%d\t\tEnglish:%d  Math:%d  C langaug:%d  \n",p->name,p->num,p->major,p->calss,p->score[0],p->score[1],p->score[2]);
}
//读取函数
void Loadstudent(STU* p,int n) {
 system("cls");
 FILE* fp;
 char filename[30];
 printf("正在读取*******\n");
 printf("请输入打开文件名:");       //暂时
 getchar();                          //清除回车
 gets(filename);
 //strcpy(filename,"studentInit.dat"); // 没有完善,暂时
 if ((fp = fopen(filename,"rb")) == NULL) {
    printf("file cannot open !!!");
    return;
 }
 for(int i = 1;i <= n;i++)
     {
        // fscanf(fp,"name:%s\tnum:%s\tmajor:%s\tclass:%d\tEnglish:%d  Math:%d  C langaug:%d  \n",p->name,p->num,p->major,&p->calss,&p->score[0],&p->score[1],&p->score[2]);;
         fread(p++,sizeof(STU),1,fp);

     }
 fclose(fp);
 printf("读取成功!!!\n");
 system("pause");
 system("cls");
}
//查找第n个学生
void FindnStudent(){
  system("cls");
  int i;
  printf("请输入n: ");
  getchar();
  scanf("%d",&i);
  if (i > N) {          // 超过范围的提示
    printf("输入超过范围\n");
    system("pause");
    system("cls");
    return;
  }
  Output(&(Head[i-1])); //- 1操作
  system("pause");
  system("cls");
}
void Findscore(){
  system("cls");
  int Class,score,id,sum = 0; //sum 是记录输出的个数
  printf("请选择你要查询的科目 1.大英 2.高数 3.C语言: ");
  scanf("%d",&id);
  id--;
  printf("请输入班级和成绩,以空格间隔: ");
  scanf("%d %d",&Class,&score);
  printf("1.大于等于所填成绩\t2.小于所填成绩: ");
  scanf("%d",&id);
  switch(id) {   //通过id进行选择下一步操作
    case 1:      // 输出大于的成绩
          for (int i = 0;i < N;i ++) {
              if (Head[i].calss == Class)
                if (Head[i].score[id] >= score)
                     {
                      Output(&(Head[i]));
                      sum++;
                     }
          }
          break;
     case 2:      //输出小于的成绩
          for (int i = 0;i < N;i ++) {
              if (Head[i].calss == Class)
                if (Head[i].score[id] < score)
                    {
                     Output(&(Head[i]));
                     sum++;
                    }
          }
          break;

  }
  if(!sum)   // 查不到
       printf("查无此人\n");
  system("pause");
  system("cls");
}
//显示所有缓存的信息
void Show() {
 system("cls");
 for (int i = 0;i < N;i ++) {
    Output(Head+i);
  }
  system("pause");
  system("cls");
}
//比较法输出最大成绩
void Maxscore() {
  system("cls");
  int id,max = -1,n;
  printf("请选择你要查询的科目 1.大英 2.高数 3.C语言: ");
  scanf("%d",&id);
  id--;
  for(int i = 0;i < N;i++) {
    if (max < Head[i].score[id]) {
            max = Head[i].score[id];
            n = i;
      }
  }
  Output(&(Head[n]));
  system("pause");
  system("cls");
}
//选择排序
void Choosesort(){
 system("cls");
 for (int i = 0;i < N;i++) {
    for (int j = i+1;j < N;j ++) {
        if (Head[i].score[0] + Head[i].score[1] + Head[i].score[2] > Head[j].score[0] + Head[j].score[1] + Head[j].score[2])
        {
            STU tmp;
            tmp = Head[i];
            Head[i] = Head[j];
            Head[j] = tmp;
        }
    }
 }
 printf("所有学生已按照平均成绩从小到大重新排序!!!\n");
 system("pause");
 system("cls");
}
//冒泡排序
void Bubblesort(){
 system("cls");
 int id;
 printf("请选择你要查询的科目 1.大英 2.高数 3.C语言: ");
 scanf("%d",&id);
 id--;
for (int i = 0;i < N;i ++) {
    int flag = 0;
    for (int j = 0;j <N - i - 1;j ++)
        if( Head[j].score[id] < Head[j+1].score[id]) {
            STU tmp;
            tmp = Head[j];
            Head[j] = Head[j+1];
            Head[j+1] = tmp;
            flag = 1;
        }
    if (!flag) break;
}
printf("排序已完成!!!\n");
system("pause");
system("cls");

}
//插入排序
void Insertsort(){
system("cls");
int id,sum = 0,n;//sum 用来统计该专业学生数
char m[15];      //原来是用指针,不知道为什么不行,卡死.
STU Tmp[10];
printf("请选择专业:\t1.Computer\t2.Sotfware\t3.Network:\t");     //选择专业
    scanf("%d",&id);
    switch(id) {
       case 1: strcpy(m,"Computer");break;
       case 2: strcpy(m,"Sotfware");break;
       case 3: strcpy(m,"NetWork");break;
       default  : printf("格兰芬多学院 !!!\n");  //一个小彩蛋
                   strcpy(m,"Gryffindor");break;
    }
printf("请选择你要查询的科目 1.大英 2.高数 3.C语言: ");
scanf("%d",&n);
n--;
for (int i = 0;i < N;i ++) {
    if ( !strcmp(Head[i].major,m)) {
        Tmp[sum++] = Head[i];
    }
}
for (int i = 1;i < sum;i++) {
   int value = Tmp[i].score[n];
   STU tem = Tmp[i];
   int j = i - 1;
   for (;j >= 0;--j) {
    if (Tmp[j].score[n] < value) {
        Tmp[j+1] = Tmp[j];         //移动数据
    } else {
      break;
    }
   }
   Tmp[j+1] = tem;    // 插入
  }
for (int i = 0;i < sum;i ++) Output(&Tmp[i]);
system("pause");
system("cls");
}



