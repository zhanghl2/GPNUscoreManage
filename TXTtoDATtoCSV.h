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


struct stuscore parseDataF(char *data);    //������������,д���ͷ
struct stuscore parseData(char *data);     //������������
void calculateAverageAndSum(struct stuscore *student);   //����ƽ��ֵ���ܳɼ�
void countAndPrintTxtFiles();                    //��ȡĿ¼��txt�ļ�
void readDataFromFile(struct stuscore* students);  //��ȡtxt�ļ�����
void readDatabase();                              //��ȡ���ݿ⣬�����ļ�

struct stuscore parseDataF(char *data) {
    data[strcspn(data, "\n")] = '\0';      // ��ȥ��ĩ����
    struct stuscore student;
    char *token;
    int i = 0;
    for (int m = 0; m <= 9; m++)
        student.course[m][0] = '\0';

    // ʹ��strtok�����ָ��ַ���
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

    data[strcspn(data, "\n")] = '\0';      // ��ȥ��ĩ����
    struct stuscore student;
    char *token;
    int i = 0;

    // ʹ��strtok�����ָ��ַ���
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

    // �򿪵�ǰĿ¼
    dir = opendir(".");

    if (dir == NULL) {
        printf("�޷���Ŀ¼��\n");
        printf("\n������������ϼ��˵�\n");
        getch();
        return;
    }

    // ����Ŀ¼�е��ļ�
    printf("��ǰĿ¼�µ� TXT �ļ��б�\n");

    while ((ent = readdir(dir)) != NULL) {
        // ����ļ����Ƿ��� ".txt" ��β
        if (strstr(ent->d_name, ".txt") != NULL) {
            printf("- %s\n", ent->d_name);
            fileCount++;
        }
    }

    closedir(dir);

    printf("�ܹ��ҵ� %d �� TXT �ļ���\n", fileCount);
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
    printf("����������Ҫ������ļ����ƣ�");
    scanf("%s", filename);

    to = filename[2] - '0';

    system("cls");
    fflush(stdin);

    if ((fp = fopen("ѧ���ɼ����ݿ�.dat", "ab +")) == NULL)					// ��׷�ӷ�ʽ�򿪻����½��ɼ������ļ�
    {
        printf("���ܴ򿪸��ļ���");
        getch();
        exit(1);
    }
    rewind(fp);

    for (count = 0; fread(&students[count], sizeof(struct stuscore), 1, fp) == 1; count++);
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    char line[256];

    // ��ȡ�ļ���ÿһ������
    while (fgets(line, sizeof(line), file) != NULL) {

        // ������ͷ��
        struct stuscore student;
        struct stuscore temp;
        if (strstr(line, "ѧ��,���,����") != NULL) {

            if (count == 0) {
                student = parseDataF(line);//    ������һ������
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

        for (int m = 0; m < temp.coursenumber; m++){   //�ɼ���ֵ
            students[count].score[m] = temp.score[m];
        }
        students[count].to = to;
        calculateAverageAndSum(&students[count]);
        fflush(stdin);
        fwrite(&students[count++], sizeof(struct stuscore), 1, fp);    // ���³ɼ�׷��д���ļ�
    }
    fclose(file);
    fclose(fp);
    printf("�����%d������,�����������������\n", count);
    getch();
}

//�����ļ�
void readDatabase() {
    system("cls");
    FILE *inputFile = fopen("ѧ���ɼ����ݿ�.dat", "rb");
    if (inputFile == NULL) {
        printf("�޷��������ļ�,������������ϼ��˵�\n");
        getchar();
        return;
    }

    FILE *outputFile = fopen("ѧ���ɼ����ݿ�.csv", "w");
    if (outputFile == NULL) {
        printf("�޷���������ļ�,������������ϼ��˵�\n");
        fclose(inputFile);
        getch();
        return;
    }
    struct stuscore temp;
    int coursenumber = temp.coursenumber;
    // д���ͷ
    if (fread(&temp, sizeof(struct stuscore), 1, inputFile) == 1){
        fprintf(outputFile, "�༶,ѧ��,");
        fprintf(outputFile, "ѧ��ѧ��,ѧ������");
        for (int i = 0; i < temp.coursenumber; i++) {
            fprintf(outputFile, ",%s", temp.course[i]);
        }
        fprintf(outputFile,",ƽ����,�ܷ�\n");
    }
    // ���ļ�ָ��ص��ļ���ͷ
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

    printf("�������,�ļ��ѱ�����-->ѧ���ɼ����ݿ�.csv��\n");
    printf("<������������ϼ��˵�>\n");
    getch();
}

#endif
