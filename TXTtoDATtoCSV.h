//
// Created by 10188 on 2023/6/17.
//

#ifndef CCCCCCC_TXTTODATTOCSV_H
#define CCCCCCC_TXTTODATTOCSV_H

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>

#include "StudentLib.h"


struct stuscore parseDataF(char *data);    //解析首行数据,写入表头
struct stuscore parseData(char *data);     //解析其他数据
void calculateAverageAndSum(struct stuscore *student);   //计算平均值和总成绩
void countAndPrintTxtFiles();                    //读取目录下txt文件
void readDataFromFile(struct stuscore* students);  //读取txt文件数据
void readDatabase();                              //读取数据库，导出文件

struct stuscore parseDataF(char *data) {
    data[strcspn(data, "\n")] = '\0';      // 除去行末换行
    struct stuscore student;
    char *token;
    int i = 0;
    for (int m = 0; m <= 9; m++)
        student.course[m][0] = '\0';

    // 使用strtok函数分割字符串
    token = strtok(data, ",");
    while (token != NULL) {
        switch (i) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            default:
                strcpy(student.course[i-3], token);
                break;
        }

        token = strtok(NULL, ",");
        i++;
    }
    student.coursenumber = i-3;
    return student;
}

struct stuscore parseData(char *data) {

    data[strcspn(data, "\n")] = '\0';      // 除去行末换行
    struct stuscore student;
    char *token;
    int i = 0;

    // 使用strtok函数分割字符串
    token = strtok(data, ",");
    while (token != NULL) {
        switch (i) {
            case 0:
                student.number = atoll(token);
                break;
            case 1:
                strcpy(student.Class, token);
                break;
            case 2:
                strcpy(student.name, token);
                break;
            default:
                student.score[i - 3] = atof(token);
                break;
        }

        token = strtok(NULL, ",");
        i++;
    }

    return student;
}

void calculateAverageAndSum(struct stuscore *student) {
    double sum = 0.0;
    for (int i = 0; i < student->coursenumber; i++) {
        sum += student->score[i];
    }

    student->sum = sum;
    student->average = sum / student->coursenumber;
}

void countAndPrintTxtFiles() {
    DIR *dir;
    struct dirent *ent;
    int fileCount = 0;

    // 打开当前目录
    dir = opendir(".");

    if (dir == NULL) {
        printf("无法打开目录。\n");
        printf("\n按任意键返回上级菜单\n");
        getch();
        return;
    }

    // 遍历目录中的文件
    printf("当前目录下的 TXT 文件列表：\n");

    while ((ent = readdir(dir)) != NULL) {
        // 检查文件名是否以 ".txt" 结尾
        if (strstr(ent->d_name, ".txt") != NULL) {
            printf("- %s\n", ent->d_name);
            fileCount++;
        }
    }

    closedir(dir);

    printf("总共找到 %d 个 TXT 文件。\n", fileCount);
}


void readDataFromFile(struct stuscore* students) {
    system("cls");
    int count;
    int to;
    char filename[20];
    system("cls");
    fflush(stdin);

    countAndPrintTxtFiles();
    printf("\n\n");
    printf("请输入你想要导入的文件名称：");
    scanf("%s", filename);

    to = filename[2] - '0';

    system("cls");
    fflush(stdin);

    if ((fp = fopen("学生成绩数据库.dat", "ab +")) == NULL)					// 以追加方式打开或者新建成绩数据文件
    {
        printf("不能打开该文件！");
        getch();
        exit(1);
    }
    rewind(fp);

    for (count = 0; fread(&students[count], sizeof(struct stuscore), 1, fp) == 1; count++);
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    char line[256];

    // 读取文件的每一行数据
    while (fgets(line, sizeof(line), file) != NULL) {

        // 跳过表头行
        struct stuscore student;
        struct stuscore temp;
        if (strstr(line, "学号,班别,姓名") != NULL) {

            if (count == 0) {
                student = parseDataF(line);//    解析第一行数据
                students[count] = student;
            }
            continue;
        }

        for (int j = 0; j < students[0].coursenumber; j++)
            strcpy(students[count].course[j], students[0].course[j]);
        students[count].coursenumber = students[0].coursenumber;

        temp = parseData(line);
        students[count].number = temp.number;

        strcpy(students[count].Class,temp.Class);
        strcpy(students[count].name, temp.name);
        temp.coursenumber = students[0].coursenumber;

        for (int m = 0; m < temp.coursenumber; m++){   //成绩赋值
            students[count].score[m] = temp.score[m];
        }
        students[count].to = to;
        calculateAverageAndSum(&students[count]);
        fflush(stdin);
        fwrite(&students[count++], sizeof(struct stuscore), 1, fp);    // 把新成绩追加写入文件
    }
    fclose(file);
    fclose(fp);
    printf("导入后共%d条数据,按任意键返回主界面\n", count);
    getch();
}

//导出文件
void readDatabase() {
    system("cls");
    FILE *inputFile = fopen("学生成绩数据库.dat", "rb");
    if (inputFile == NULL) {
        printf("无法打开输入文件,按任意键返回上级菜单\n");
        getchar();
        return;
    }

    FILE *outputFile = fopen("学生成绩数据库.csv", "w");
    if (outputFile == NULL) {
        printf("无法创建输出文件,按任意键返回上级菜单\n");
        fclose(inputFile);
        getch();
        return;
    }
    struct stuscore temp;
    int coursenumber = temp.coursenumber;
    // 写入表头
    if (fread(&temp, sizeof(struct stuscore), 1, inputFile) == 1){
        fprintf(outputFile, "班级,学期,");
        fprintf(outputFile, "学生学号,学生姓名");
        for (int i = 0; i < temp.coursenumber; i++) {
            fprintf(outputFile, ",%s", temp.course[i]);
        }
        fprintf(outputFile,",平均分,总分\n");
    }
    // 将文件指针回到文件开头
    fseek(inputFile, 0, SEEK_SET);


    struct stuscore student;
    while (fread(&student, sizeof(struct stuscore), 1, inputFile) == 1) {
        fprintf(outputFile, "%s,%d,", student.Class, student.to);
        fprintf(outputFile, "%lld,%s", student.number, student.name);
        for (int i = 0; i < student.coursenumber; i++) {
            fprintf(outputFile, ",%.1f", student.score[i]);
        }
        for (int i = student.coursenumber; i < coursenumber; i++) {
            fprintf(outputFile, ",");
        }
        fprintf(outputFile, ",%.1f,%.1f\n",student.average, student.sum);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("导出完成,文件已保存在-->学生成绩数据库.csv。\n");
    printf("<按任意键返回上级菜单>\n");
    getch();
}

#endif
