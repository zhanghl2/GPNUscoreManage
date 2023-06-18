//
// Created by 10188 on 2023/6/17.
//

#ifndef CCCCCCC_SCOREPROCESSOR_H
#define CCCCCCC_SCOREPROCESSOR_H

#include "StudentLib.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


void scoreinput(struct stuscore* p_stuscorelib);    //�ɼ�¼��
void scoremodify(struct stuscore* p_stuscorelib);   //�ɼ��޸�
void scorequery(struct stuscore* p_stuscorelib);    //�ɼ���ѯ
void scorebrowse(struct stuscore* p_stuscorelib,int count);  //�ɼ����
void selectAndBrowse(struct stuscore* p_stuscorelib);  //�ɼ������ʽ
void scoredelete(struct stuscore* p_stuscorelib);    //�ɼ�ɾ��
void printrecode(struct stuscore* p_stuscorelib, int count);  //��ʾѧ���ɼ���¼
int readscore(struct stuscore* p_stuscorelib);      //��ȡѧ���ɼ�������ѧ���ɼ���¼��
void sortBySubject(struct stuscore* students, int count, int subjectChoice); //ѧ���ɼ���������
void sortByClass(struct stuscore* students, int count, const char* targetClass); //ѧ���ɼ����༶����
void classscoresort(struct stuscore* p_stuscorelib); //�༶�ɼ�����

/*****************************�ɼ�¼��******************************/
void scoreinput(struct stuscore* p_stuscorelib)
{

    int count, i, m;
    char ch;
    system("cls");
    fflush(stdin);

    if ((fp = fopen("ѧ���ɼ����ݿ�.dat", "ab +")) == NULL)					// ��׷�ӷ�ʽ�򿪻����½��ɼ������ļ�
    {
        printf("���ܴ򿪸��ļ���");
        getch();
        exit(1);
    }
    rewind(fp);															   // �ļ�ָ��ص��ļ�����ʼλ��

    /*ͳ�Ƶ�ǰѧ���ɼ����ݿ���ѧ���ɼ���¼����*/
    for (count = 0; fread(&p_stuscorelib[count], sizeof(struct stuscore), 1, fp) == 1; count++);
    printf("��ǰѧ���ɼ����ݿ���ѧ���ɼ���¼��������%d��\n", count);
    while (1)
    {
        if (count == 0)
        {												  // ��һ������ѧ���ɼ�ʱ����Ҫ����Ա��ʾ����༶��ѧ�ڿγ�
            m = 0;
            for (i = 0; i <= 9; i++)
                p_stuscorelib[count].course[i][0] = '\0';
            printf("<����༶��ѧ�ڿγ̣�ע��γ��������Ϊ10��>\n");
            printf("--------------------------------------------\n");
            for (i = 0; i <= 9; i++)
            {
                printf("�� %d �ſγ̣����س�����������", i + 1);
                gets(p_stuscorelib[count].course[i]);
                if (p_stuscorelib[count].course[i][0] == '\0')
                    break;
                else  m++;
            }
            p_stuscorelib[count].coursenumber = m;
        }
        else
        {
            for (int i = 0; i < p_stuscorelib[0].coursenumber; i++)
                strcpy(p_stuscorelib[count].course[i], p_stuscorelib[0].course[i]);
            p_stuscorelib[count].coursenumber = p_stuscorelib[0].coursenumber;
        }

        printf("������ѧ�������� ");
        gets(p_stuscorelib[count].name);								// ��������
        printf("������ѧ��ѧ�ţ�");
        while (1) {
            scanf("%lld", &p_stuscorelib[count].number);					// ����ѧ��
            for (i = 0; i < count; i++) {
                if (p_stuscorelib[count].number == p_stuscorelib[i].number&&p_stuscorelib[i].to == p_stuscorelib[count].to) {
                    fflush(stdin);
                    printf("ѧ��������ͬѧ�غţ� ����������ѧ�ţ�");
                    break;
                }
            }
            if (i == count)break;
        }
        printf("������ѧ�ڣ�1Ϊ��һѧ�ڣ�2Ϊ�ڶ�ѧ�ڣ���");
        scanf("%d", &p_stuscorelib[count].to);

        printf("������༶��");
        scanf("%s",p_stuscorelib[count].Class);

        printf("�������ѧ���ĳɼ�\n");
        printf("------------------------\n");
        p_stuscorelib[count].sum = 0;
        for (i = 0; i < p_stuscorelib[0].coursenumber; i++) {
            fflush(stdin);
            printf("%s:", p_stuscorelib[0].course[i]);
            scanf("%lf", &p_stuscorelib[count].score[i]);
            p_stuscorelib[count].sum += p_stuscorelib[count].score[i];	// �����ܷ�
        }
        p_stuscorelib[count].average = p_stuscorelib[count].sum / p_stuscorelib[0].coursenumber;	//����ƽ����

        fflush(stdin);
        printf("------------------------\n");
        fwrite(&p_stuscorelib[count++], sizeof(struct stuscore), 1, fp);    // ���³ɼ�׷��д���ļ�
        printf("ȷ��Ҫ����������һ��ѧ���ĳɼ���y/n��");
        while (1) {
            ch = getchar();
            fflush(stdin);
            if (ch == 'y' || ch == 'Y') {
                system("cls");
                break;
            }
            if (ch == 'n' || ch == 'N') {
                system("cls");
                fclose(fp);
                return;
            }
            printf("ѡ����� ȷ��Ҫ����������һ��ѧ���ĳɼ���y/n��");
        }
    }
}


/*****************************�ɼ��޸�******************************/
void scoremodify(struct stuscore* p_stuscorelib)
{
    int i, j, k, m = 0, count;
    int tempterm,tempterm1 ;                                  // ѧ�ڱȽ�
    long long int tempnumber, tempnumber1;
    count = readscore(p_stuscorelib);				// ����ѧ���ɼ���������ѧ���ɼ���¼��
    if (count == 0) {
        printf("\n��û������ɼ�����������������˵���");
        getchar();
        return;
    }
    printf("������Ҫ�޸ĳɼ���¼��ѧ��ѧ�ţ�");
    scanf("%lld", &tempnumber);
    printf("������Ҫ�޸ĳɼ���¼��ѧ�ڣ�1Ϊ��һѧ�ڣ�2Ϊ�ڶ�ѧ�ڣ���");
    scanf("%d", &tempterm);
    fflush(stdin);
    for (i = 0; i < count; i++)
    {
        if (tempnumber != p_stuscorelib[i].number || tempterm != p_stuscorelib[i].to)
            continue;
        else
        {
            printf("ѧ��Ϊ%lld��ѧ����ԭʼ�ɼ���¼\n", tempnumber);
            printrecode(p_stuscorelib + i, 1);
            printf("���޸ĸ�ѧ���ɼ���Ϣ\n");
            printf("------------------------\n");
            printf("ѧ��ѧ�ţ�");
            scanf("%lld", &p_stuscorelib[i].number);
            tempnumber1 = p_stuscorelib[i].number;	 //�����������ѧ��ѧ���Ա�����º�İ༶ѧ�űȽ�
            tempterm1 = p_stuscorelib[i].to;	 //�����������ѧ��ѧ���Ա�����º�İ༶ѧ�űȽ�
            fflush(stdin);
            printf("ѧ�����֣�");
            gets(p_stuscorelib[i].name);
            printf("������ѧ�ڣ�1Ϊ��һѧ�ڣ�2Ϊ�ڶ�ѧ�ڣ���");
            scanf("%d", &p_stuscorelib[count].to);
            printf("������༶��");
            scanf("%s", p_stuscorelib[i].Class);
            fflush(stdin);
            p_stuscorelib[i].sum = 0;
            for(j=0;j<p_stuscorelib[0].coursenumber;j++)	// ѧ���ɼ�����
            {
                fflush(stdin);
                printf("%s:", p_stuscorelib[0].course[j]);
                scanf("%lf", &p_stuscorelib[i].score[j]);
                p_stuscorelib[i].sum += p_stuscorelib[i].score[j];		// �����ܷ�
            }
            p_stuscorelib[i].average = p_stuscorelib[i].sum / p_stuscorelib[0].coursenumber;
            printf("------------------------\n");
            printf("ѧ��Ϊ%d��ѧ���޸ĺ�ĳɼ���¼\n", tempnumber);
            printrecode(p_stuscorelib + i, 1);
            fp = fopen("ѧ���ɼ����ݿ�.dat", "w+b");
            for (k = 0; k < count; k++)
            {
                if (fwrite(&p_stuscorelib[k], sizeof(struct stuscore), 1, fp) != 1)
                {
                    fclose(fp);
                    printf("�޸�ʧ�ܣ���������������˵���");
                    getch();
                    system("cls");
                    return;
                }
            }
            fclose(fp);						// �ɼ��޸ĳɹ���д���ļ���ر��ļ�
            for (k = 0; k < count; k++)
                if (tempnumber1 == p_stuscorelib[k].number&&tempterm1 == p_stuscorelib[k].to) m++;                  //ѧ�ź�ѧ�ڶ���ͬ�Ļ��϶��غ���
            if (m > 1)
                printf("����Աע��----��[%d]λͬѧ��ѧ���غ��ˣ� �밴������������˵����½����޸ģ�", m);
            else
                printf("�ɼ��޸���ϣ��밴������������˵���");
            getch();
            system("cls");
            return;
        }
    }
    printf("ѧ��Ϊ%lld��ѧ�������ڣ��밴������������˵���", tempnumber);
    getch();
    system("cls");
    return;
}


/*****************************�ɼ���ѯ******************************/
void scorequery(struct stuscore* p_stuscorelib)
{
    char* tempname;
    int choice;
    long long int tempnumber;
    int i, k, count, count2=0;
    count = readscore(p_stuscorelib);			// ����ѧ���ɼ���������ѧ���ɼ���¼��
    if (count == 0)
    {
        printf("\n��û����ɼ����밴������������˵���");
        getchar();
        return;
    }
    while (1)
    {
        system("cls");
        printf("<1.��������ѯ  2.��ѧ�Ų�ѯ  3.�������˵�>\n");
        printf("�밴���ּ�1-3��ѡ���ѯ��ʽ��");
        scanf("%d", &choice);
        fflush(stdin);
        if (choice == 1)
        {
            tempname = (char*)malloc(20 * sizeof(char));
            printf("������Ҫ���в�ѯ��ѧ������:");
            gets(tempname);
            k = 0;
            for (i = 0; i < count; i++)
            {
                if (strcmp(tempname, p_stuscorelib[i].name) != 0)     // ������������������
                    continue;
                else
                {
                    k++;
                    if (k == 1)
                        printf("==[%s]==ͬѧ�ɼ���ѯ���:\n", tempname);
                    printrecode(p_stuscorelib + i, 1);
                }
            }
            if (k > 0)
            {
                printf("��ѯ��ϣ��������������");
                free(tempname);
                getchar();
                system("cls");
            }
            else
            {
                printf("�Ҳ�����ѧ���ĳɼ����밴���������!");
                free(tempname);
                getch();
                system("cls");
            }
        }
        else if (choice == 2)
        {
            printf("������Ҫ���гɼ���ѯ��ѧ��ѧ��:");
            scanf("%lld", &tempnumber);
            fflush(stdin);
            for (i = 0; i < count; i++)
            {
                if (tempnumber != p_stuscorelib[i].number)			// ѧ�Ų�������������
                    continue;
                else
                {
                    count2++;
                    printrecode(p_stuscorelib + i, 1);
//                    printf("��ѯ��ϣ������������");
//                    getch();
//                    break;
                }
            }
            if (i == count)
            {
                if (count2 == 0) {
                    printf("û�в�ѯ����ѧ��ͬѧ�ĳɼ����밴���������!");
                    getch();
                    system("cls");
                }else{
                    printf("��ѯ��ϣ������������");
                    getch();
                    break;
                }
            }
        }
        else
        {
            system("cls");
            return;
        }
    }
}


/*****************************�ɼ����******************************/

void scorebrowse(struct stuscore* p_stuscorelib,int count)
{
    int i, j, choice;
    struct stuscore t;
    if (count == 0)
    {
        printf("\n ��û����ɼ����밴������������˵���");
        getch();
        return;
    }
    while (1)
    {
        printf("<1.��ѧ��˳�����  2.���ܳɼ��ɴ�С˳�����  3.�������˵�>\n");
        printf("�밴���ּ�1-3��ѡ�������ʽ��");
        scanf("%d", &choice);
        if (choice == 1)							// ��ѧ��˳�����
        {
            for (i = 1; i <= count - 1; i++)	    // ��ð������ѧ�Ž�����������
            {
                for (j = count - 1; j >= i; j--)
                {
                    if (p_stuscorelib[j].number < p_stuscorelib[j - 1].number)
                    {
                        t = p_stuscorelib[j];
                        p_stuscorelib[j] = p_stuscorelib[j - 1];
                        p_stuscorelib[j - 1] = t;
                    }
                }
            }
        }
        else if (choice == 2)
        {
            for (i = 1; i <= count - 1; i++)	    // ��ð������ѧ�Ž��н�������
            {
                for (j = count - 1; j >= i; j--)
                {
                    if (p_stuscorelib[j].sum > p_stuscorelib[j - 1].sum)
                    {
                        t = p_stuscorelib[j];
                        p_stuscorelib[j] = p_stuscorelib[j - 1];
                        p_stuscorelib[j - 1] = t;
                    }
                }
            }

        }
        else
        {
            system("cls");
            return;
        }
        fflush(stdin);
        printrecode(p_stuscorelib, count);
    }
}
void selectAndBrowse(struct stuscore* p_stuscorelib) {
    int semester, browseChoice;
    printf("��ѡ��ѧ�ڣ�\n");
    printf("1. ��һѧ��\n");
    printf("2. �ڶ�ѧ��\n");
    printf("��ѡ��");
    scanf("%d", &semester);
    fflush(stdin);

    if (semester != 1 && semester != 2) {
        printf("��Ч��ѡ��\n");
        getch();
        return;
    }

    printf("\n��ѡ��༶��\n");
    printf("1. �ְ༶\n");
    printf("2. ȫ�꼶\n");
    printf("��ѡ��");
    scanf("%d", &browseChoice);
    if (browseChoice != 1 && browseChoice != 2) {
        printf("��Ч��ѡ��\n");
        getch();
        return;
    }


    fflush(stdin);

    if (browseChoice == 1) {
        char className[20];
        printf("\n������༶���ƣ�");
        scanf("%s", className);

        // ����ָ���༶��ѧ����¼������ scorebrowse �����������
        int count = readscore(p_stuscorelib);
        if (count == 0) {
            printf("\n��û����ɼ����밴������������˵���");
            getch();
            return;
        }

        struct stuscore filteredRecords[count];  // �洢���˺��ѧ���ɼ���¼
        int filteredCount = 0;  // ���˺��ѧ���ɼ���¼��

        for (int i = 0; i < count; i++) {
            if (strcmp(p_stuscorelib[i].Class, className) == 0 && p_stuscorelib[i].to == semester) {
                filteredRecords[filteredCount] = p_stuscorelib[i];
                filteredCount++;
            }
        }

        if (filteredCount == 0) {
            printf("\nû���ҵ��ð༶��ѧ���ɼ���¼��\n");
            return;
        }

        scorebrowse(filteredRecords, filteredCount);
    } else if (browseChoice == 2) {
        // ����ָ��ѧ�ڵ�ѧ����¼������ scorebrowse �����������
        int count = readscore(p_stuscorelib);
        if (count == 0) {
            printf("\n��û����ɼ����밴������������˵���");
            getch();
            return;
        }

        struct stuscore filteredRecords[count];  // �洢���˺��ѧ���ɼ���¼
        int filteredCount = 0;  // ���˺��ѧ���ɼ���¼��

        for (int i = 0; i < count; i++) {
            if (p_stuscorelib[i].to == semester) {
                filteredRecords[filteredCount] = p_stuscorelib[i];
                filteredCount++;
            }
        }

        if (filteredCount == 0) {
            printf("\n��ѧ��û��ѧ���ɼ���¼��\n");
            return;
        }

        scorebrowse(filteredRecords, filteredCount);
    } else {
        printf("��Ч��ѡ��\n");
        return;
    }
}



/*****************************�ɼ�ɾ��******************************/
void scoredelete(struct stuscore* p_stuscorelib)
{
    int i, j, count;
    long long int tempnumber;
    char ch;
    count = readscore(p_stuscorelib);		// ��ȡѧ���ɼ���������ѧ���ɼ���¼��
    if (count == 0)
    {
        printf("\n ��û����ɼ����밴������������˵���");
        getch();
        return;
    }
    fflush(stdin);
    printrecode(p_stuscorelib, count);		// ��ʾ��ǰѧ���ɼ����ݵ�ȫ����¼
    printf("ȷ������ɾ���ɼ��Ĳ����𣿣�y/n��:");
    while (1)
    {
        ch = getchar();
        fflush(stdin);
        if (ch == 'y' || ch == 'Y')
        {
            printf("������Ҫɾ���ɼ���¼��ѧ��ѧ�ţ�������Чѧ�ŷ������˵���:");
            scanf("%lld", &tempnumber);
            fflush(stdin);
            for (i = 0; i < count; i++)
            {
                if (tempnumber != p_stuscorelib[i].number)
                    continue;
                else
                {
                    for (j = i; j < count - 1; j++)				// �ҵ���ɾ��Ԫ�غ󣬽��е�λ����
                        p_stuscorelib[j] = p_stuscorelib[j + 1];
                    count--;
                    fp = fopen("ѧ���ɼ����ݿ�.dat", "w+b");
                    for (i = 0; i < count; i++) {
                        if (fwrite(&p_stuscorelib[i], sizeof(struct stuscore), 1, fp) == 1)
                            continue;
                        else {
                            printf("ɾ��ʧ�ܣ���������������˵�!");
                            fclose(fp);
                            getch();
                            system("cls");
                            return;
                        }
                    }
                    printf("ɾ���ɹ�����������������˵���");
                    fclose(fp);
                    getch();
                    system("cls");
                    return;

                }
            }
        }
        else if (ch == 'n' || ch == 'N')
        {
            printf("�밴������������˵���");
            getchar();
            system("cls");
            return;
        }
        else printf("������� ��ȷ��Ҫ����ɾ���ɼ��Ĳ�����y/n��");
    }
}



/*************************��ʾѧ���ɼ���¼**************************/
void printrecode(struct stuscore* p_stuscorelib, int count)		// ��ָ��p_styscorelib ��ָ�ĳɼ���¼��ʼ����ʾ����count���ɼ���¼
{
    int i, j, k, m[10] = { 0 }, m1,len;
    char ch,str[15];
    for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
        m[j] = strlen(p_stuscorelib[0].course[j]) + 1;
    printf("�γ�����:%d", p_stuscorelib[0].coursenumber);

    // �Ȼ�ȡ������б�ͷ�γ̲��ִ�ӡ���ַ������Ա����ĳ���ʵ�ֱ��Ķ�̬���

    for (i = 0; i < count; i++)		// ��ѧ���ɼ������ļ����ҵ�ѧ���ɼ���¼����ʾ����
    {
        if ((i == 0) || (i + 1) % 9 == 0)	// ��ѧ���ɼ������ļ����ҵ���1��ѧ���ɼ���¼��ÿ��ʾ��8��ѧ���ɼ��һ���ѧ���ɼ�δ��ʾ������ʾ��ͷ
        {
            printf("\n\t\t\t\t ѧ���ɼ�\n");
            printf("|---------------|---------------|---------------|-----------------------|");
            for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
            {
                for (k = 0; k < m[j] - 1; k++)
                    printf("-");
                printf("|");
            }
            printf("------|----|\n");
            printf("|\tѧ��\t|\tѧ��\t|\t�༶\t|\t����\t\t");
            for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
                printf("|%s", p_stuscorelib[0].course[j]);
            printf("|ƽ����|�ܷ�|\n");
            printf("|---------------|---------------|---------------|-----------------------|");
            for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
            {
                for (k = 0; k < m[j] - 1; k++)
                    printf("-");
                printf("|");
            }
            printf("------|----|\n");
        }

        /*��̬���ѧ�š��༶������*/
        memset(str,0,15);//���str����

        // ���ѧ��
        sprintf(str,"%lld",p_stuscorelib[i].number);//��ѧ�ŵ�����ת��Ϊ�ַ������洢��str
        len=strlen(str);//��ѧ���ж��ٳ�(���ٸ��ֽ�)
        printf("|");
        if(len<8)//����һ��tab�ĳ���
            printf("\t%s\t",str);
        else if(len<16)//��������tab�ĳ���    ѧ�����16λ������
            printf("%s\t",str);
        else
            printf("%s",str);

        //���ѧ��
        sprintf(str,"%lld",p_stuscorelib[i].to);//��ѧ�ŵ�����ת��Ϊ�ַ������洢��str
        len=strlen(str);//��ѧ���ж����ֽ�
        printf("|");
        if(len<8)//����һ��tab�ĳ���
            printf("\t%s\t",str);
        else if(len<16)//��������tab�ĳ���    ѧ�����15�ֽڳ��ȣ�����
            printf("%s\t",str);

        // ����༶
        len=strlen(p_stuscorelib[i].Class);//���༶�ж����ֽ�
        printf("|");
        if(len<8)//����һ��tab�ĳ���
            printf("\t%s\t",p_stuscorelib[i].Class);
        else if(len<16)//��������tab�ĳ���    //�༶���15�ֽڳ��ȣ�����
            printf("%s\t",p_stuscorelib[i].Class);

        // �������
        len=strlen(p_stuscorelib[i].name);

        printf("|");
        if(len<8)//����һ��tab�ĳ���
            printf("\t%s\t\t",p_stuscorelib[i].name);
        else if(len<16)//��������tab�ĳ���    //�������5���ֻ�10�ֽڣ�����
            printf("\t%s\t",p_stuscorelib[i].name);
        else if(len<32)
            printf("%s\t",p_stuscorelib[i].name);
        else if(len<64){
            printf("%s",p_stuscorelib[i].name);
        }
        else{
            printf("Fuck you");
        }

        //printf("|%4d|%6s", p_stuscorelib[i].number, p_stuscorelib[i].name);


        // ��ʾ�ð�ͬѧ����ѧ�Ƴɼ�
        for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
        {
            m1 = printf("|%-.0f", p_stuscorelib[i].score[j]);
            for (k = 0; k < m[j] - m1; k++)
                printf(" ");
        }
        printf("|%6.0f|%4.0f|\n", p_stuscorelib[i].average, p_stuscorelib[i].sum);
        printf("|---------------|---------------|---------------|-----------------------|");

        for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
        {
            for (k = 0; k < m[j] - 1; k++)
                printf("-");
            printf("|");
        }
        printf("------|----|\n");

        // ÿ��ʾ��8��ѧ���ɼ���¼�һ���ѧ���ɼ�δ��ʾ������ʾ��ʾ
        if ((i + 1) % 8 == 0 && (i + 1) < count)
        {
            printf("< Ҫ�������˵����밴<q>��;���������������! >");
            ch = getchar();
            fflush(stdin);
            if (ch == 'q')return;
            else system("cls");
        }
    }
}



/****************����ѧ���ɼ���������ѧ���ɼ���¼��*****************/
int readscore(struct stuscore* p_stuscorelib)
{
    int count;
    system("cls");
    if ((fp = fopen("ѧ���ɼ����ݿ�.dat", "rb")) == NULL)
    {
        printf("�򲻿�ѧ���ɼ����ݿ��ļ�!");
        getchar();
        return 0;
    }
    rewind(fp);				// �ļ�λ��ָ��ص��ļ���ʼλ��
    for (count = 0; fread(&p_stuscorelib[count], sizeof(struct stuscore), 1, fp) == 1; count++){}
    fclose(fp);
    return count;		// �Ѷ����ĳɼ���¼��������
}

/****�ɼ�����ģ��*********/

// �����Ƴɼ�����
void sortBySubject(struct stuscore* students, int count, int subjectChoice) {
    int i, j;
    struct stuscore temp;

    for (i = 1; i < count; i++) {
        for (j = count - 1; j >= i; j--) {
            if (students[j].score[subjectChoice - 1] > students[j - 1].score[subjectChoice - 1]) {
                temp = students[j];
                students[j] = students[j - 1];
                students[j - 1] = temp;
            }
        }
    }
}

// ���༶�����ܳɼ�����
void sortByClass(struct stuscore* students, int count, const char* targetClass) {
    int i, j;
    struct stuscore temp;
    struct stuscore selectedStudents[100]; // ���������100��ѧ������
    int selectedCount = 0;                  // �༶����

    for (i = 0; i < count; i++) {
        if (strcmp(students[i].Class, targetClass) == 0) {
            selectedStudents[selectedCount] = students[i];
            selectedCount++;
        }
    }

    for (i = 1; i < selectedCount; i++) {
        for (j = selectedCount - 1; j >= i; j--) {
            if (selectedStudents[j].sum > selectedStudents[j - 1].sum) {
                temp = selectedStudents[j];
                selectedStudents[j] = selectedStudents[j - 1];
                selectedStudents[j - 1] = temp;
            }
        }
    }

    // ���
    printf("\n   ѧ�� \t\t\t����\t\t ���\t\t�ܳɼ�\tƽ����\t����\n");
    for (i = 0; i < selectedCount; i++) {
        printf("%lld\t%20s\t%20s\t%6.2f  %6.2f   %d\n", selectedStudents[i].number, selectedStudents[i].name,
               selectedStudents[i].Class, selectedStudents[i].sum, selectedStudents[i].average, i + 1);
    }
}

//���༶����
void classscoresort(struct stuscore* p_stuscorelib) {
    int choice, subChoice;
    int count;
    count = readscore(p_stuscorelib); // ����ѧ���ɼ���������ѧ���ɼ���¼��

    if (count == 0) {
        printf("\n ��û����ɼ����밴������������˵���");
        getch();
        return;
    }

    while (1) {
        printf("<1. ��ѧ�ڳɼ�  2. ��ѧ�ڳɼ�  3. �������˵�>\n");
        printf("�밴���ּ�1-3��ѡ��ѧ�ڣ�");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            printf("<1. �����Ƴɼ�����  2. ���༶�����ܳɼ�����  3. ������һ���˵�>\n");
            printf("�밴���ּ�1-3��ѡ������ʽ��");
            scanf("%d", &subChoice);

            if (subChoice == 1) {
                printf("\n��ѡ��Ҫ����Ŀ�Ŀ:\n");
                for (int i = 0; i < p_stuscorelib[0].coursenumber; i++) {
                    printf("%d. %s\n", i + 1, p_stuscorelib[0].course[i]);
                }
                printf("���������ּ�1-%d��ѡ��Ҫ����Ŀ�Ŀ: ", p_stuscorelib[0].coursenumber);
                scanf("%d", &subChoice);

                sortBySubject(p_stuscorelib, count, subChoice);

                printf("\t\t\t\t��%dѧ��ѧ�����Ƴɼ�\t\t\t\t\n", choice);
                printf("\n   ѧ�� \t\t\t����\t\t ���\t\t%s�ɼ�\t\n", p_stuscorelib[0].course[subChoice - 1]);
                for (int i = 0; i < count; i++) {
                    printf("%lld\t%20s\t%20s\t%6.2f\n", p_stuscorelib[i].number, p_stuscorelib[i].name,
                           p_stuscorelib[i].Class, p_stuscorelib[i].score[subChoice - 1]);
                }
            } else if (subChoice == 2) {
                char targetClass[20];
                printf("������Ҫ����İ༶��xxJ�������X����");
                scanf("%s", targetClass);
                sortByClass(p_stuscorelib, count, targetClass);
            } else {
                system("cls");
                return;
            }
        } else {
            system("cls");
            return;
        }
    }
}
#endif //CCCCCCC_SCOREPROCESSOR_H
