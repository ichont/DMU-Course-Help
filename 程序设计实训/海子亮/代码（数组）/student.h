#ifndef STUDENT_H
#define STUDENT_H

#define M 3		// 成绩个数
#define N 10	// 学生个数

struct Student {
	char num[15];	// 学号
	char name[15];	// 姓名
	char major[10];	// 专业（computer，software，network）
	int classNo;	// 班级（1-2）
	int score[M];	// 3门课的成绩
};
typedef struct Student STU;	// 定义STU

#endif	// STUDENT_H