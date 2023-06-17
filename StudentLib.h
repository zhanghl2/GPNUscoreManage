//
// Created by 10188 on 2023/6/17.
//

#ifndef CCCCCCC_STUDENTLIB_H
#define CCCCCCC_STUDENTLIB_H

#include<stdio.h>
#define MAX_STUDENTLIB_LENGTH   2000      //最大数据记录数

FILE* fp = NULL;          // 定义学生成绩数据库文件指针

// 全局结构体定义--学生成绩结构体
struct stuscore {
    char Class[20];         // 班级
    int to;                 //学期
    char course[10][20];    // 课程名称
    int coursenumber;       // 课程门数
    long long int number;   // 学生学号
    char name[30];          // 学生姓名
    double score[10];       // 学生成绩
    double average;         // 平均分
    double sum;             // 总分
};
struct  stuscore stuscorelib[MAX_STUDENTLIB_LENGTH];				// 定义学生成绩数据库数组

#endif //CCCCCCC_STUDENTLIB_H
