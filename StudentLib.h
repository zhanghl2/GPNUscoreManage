//
// Created by 10188 on 2023/6/17.
//

#ifndef CCCCCCC_STUDENTLIB_H
#define CCCCCCC_STUDENTLIB_H

#include<stdio.h>
#define MAX_STUDENTLIB_LENGTH   2000      //������ݼ�¼��

FILE* fp = NULL;          // ����ѧ���ɼ����ݿ��ļ�ָ��

// ȫ�ֽṹ�嶨��--ѧ���ɼ��ṹ��
struct stuscore {
    char Class[20];         // �༶
    int to;                 //ѧ��
    char course[10][20];    // �γ�����
    int coursenumber;       // �γ�����
    long long int number;   // ѧ��ѧ��
    char name[30];          // ѧ������
    double score[10];       // ѧ���ɼ�
    double average;         // ƽ����
    double sum;             // �ܷ�
};
struct  stuscore stuscorelib[MAX_STUDENTLIB_LENGTH];				// ����ѧ���ɼ����ݿ�����

#endif //CCCCCCC_STUDENTLIB_H
