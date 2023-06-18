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


void scoreinput(struct stuscore* p_stuscorelib);    //成绩录入
void scoremodify(struct stuscore* p_stuscorelib);   //成绩修改
void scorequery(struct stuscore* p_stuscorelib);    //成绩查询
void scorebrowse(struct stuscore* p_stuscorelib,int count);  //成绩浏览
void selectAndBrowse(struct stuscore* p_stuscorelib);  //成绩浏览方式
void scoredelete(struct stuscore* p_stuscorelib);    //成绩删除
void printrecode(struct stuscore* p_stuscorelib, int count);  //显示学生成绩记录
int readscore(struct stuscore* p_stuscorelib);      //读取学生成绩并返回学生成绩记录数
void sortBySubject(struct stuscore* students, int count, int subjectChoice); //学生成绩单科排序
void sortByClass(struct stuscore* students, int count, const char* targetClass); //学生成绩单班级排序
void classscoresort(struct stuscore* p_stuscorelib); //班级成绩排序

/*****************************成绩录入******************************/
void scoreinput(struct stuscore* p_stuscorelib)
{

    int count, i, m;
    char ch;
    system("cls");
    fflush(stdin);

    if ((fp = fopen("学生成绩数据库.dat", "ab +")) == NULL)					// 以追加方式打开或者新建成绩数据文件
    {
        printf("不能打开该文件！");
        getch();
        exit(1);
    }
    rewind(fp);															   // 文件指针回到文件的起始位置

    /*统计当前学生成绩数据库中学生成绩记录总数*/
    for (count = 0; fread(&p_stuscorelib[count], sizeof(struct stuscore), 1, fp) == 1; count++);
    printf("当前学生成绩数据库中学生成绩记录总数共：%d条\n", count);
    while (1)
    {
        if (count == 0)
        {												  // 第一次输入学生成绩时，需要管理员提示输入班级本学期课程
            m = 0;
            for (i = 0; i <= 9; i++)
                p_stuscorelib[count].course[i][0] = '\0';
            printf("<输入班级本学期课程，注意课程门数最多为10门>\n");
            printf("--------------------------------------------\n");
            for (i = 0; i <= 9; i++)
            {
                printf("第 %d 门课程（按回车键结束）：", i + 1);
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

        printf("请输入学生姓名： ");
        gets(p_stuscorelib[count].name);								// 输入姓名
        printf("请输入学生学号：");
        while (1) {
            scanf("%lld", &p_stuscorelib[count].number);					// 输入学号
            for (i = 0; i < count; i++) {
                if (p_stuscorelib[count].number == p_stuscorelib[i].number&&p_stuscorelib[i].to == p_stuscorelib[count].to) {
                    fflush(stdin);
                    printf("学号与其他同学重号！ 请重新输入学号：");
                    break;
                }
            }
            if (i == count)break;
        }
        printf("请输入学期（1为第一学期，2为第二学期）：");
        scanf("%d", &p_stuscorelib[count].to);

        printf("请输入班级：");
        scanf("%s",p_stuscorelib[count].Class);

        printf("请输入该学生的成绩\n");
        printf("------------------------\n");
        p_stuscorelib[count].sum = 0;
        for (i = 0; i < p_stuscorelib[0].coursenumber; i++) {
            fflush(stdin);
            printf("%s:", p_stuscorelib[0].course[i]);
            scanf("%lf", &p_stuscorelib[count].score[i]);
            p_stuscorelib[count].sum += p_stuscorelib[count].score[i];	// 计算总分
        }
        p_stuscorelib[count].average = p_stuscorelib[count].sum / p_stuscorelib[0].coursenumber;	//计算平均分

        fflush(stdin);
        printf("------------------------\n");
        fwrite(&p_stuscorelib[count++], sizeof(struct stuscore), 1, fp);    // 把新成绩追加写入文件
        printf("确定要继续输入下一个学生的成绩吗（y/n）");
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
            printf("选择错误！ 确定要继续输入下一个学生的成绩吗（y/n）");
        }
    }
}


/*****************************成绩修改******************************/
void scoremodify(struct stuscore* p_stuscorelib)
{
    int i, j, k, m = 0, count;
    int tempterm,tempterm1 ;                                  // 学期比较
    long long int tempnumber, tempnumber1;
    count = readscore(p_stuscorelib);				// 读出学生成绩，并返回学生成绩记录数
    if (count == 0) {
        printf("\n还没有输入成绩，按任意键返回主菜单！");
        getchar();
        return;
    }
    printf("请输入要修改成绩记录的学生学号：");
    scanf("%lld", &tempnumber);
    printf("请输入要修改成绩记录的学期（1为第一学期，2为第二学期）：");
    scanf("%d", &tempterm);
    fflush(stdin);
    for (i = 0; i < count; i++)
    {
        if (tempnumber != p_stuscorelib[i].number || tempterm != p_stuscorelib[i].to)
            continue;
        else
        {
            printf("学号为%lld的学生的原始成绩记录\n", tempnumber);
            printrecode(p_stuscorelib + i, 1);
            printf("请修改该学生成绩信息\n");
            printf("------------------------\n");
            printf("学生学号：");
            scanf("%lld", &p_stuscorelib[i].number);
            tempnumber1 = p_stuscorelib[i].number;	 //保存新输入的学生学号以便与更新后的班级学号比较
            tempterm1 = p_stuscorelib[i].to;	 //保存新输入的学生学号以便与更新后的班级学号比较
            fflush(stdin);
            printf("学生名字：");
            gets(p_stuscorelib[i].name);
            printf("请输入学期（1为第一学期，2为第二学期）：");
            scanf("%d", &p_stuscorelib[count].to);
            printf("请输入班级：");
            scanf("%s", p_stuscorelib[i].Class);
            fflush(stdin);
            p_stuscorelib[i].sum = 0;
            for(j=0;j<p_stuscorelib[0].coursenumber;j++)	// 学生成绩输入
            {
                fflush(stdin);
                printf("%s:", p_stuscorelib[0].course[j]);
                scanf("%lf", &p_stuscorelib[i].score[j]);
                p_stuscorelib[i].sum += p_stuscorelib[i].score[j];		// 计算总分
            }
            p_stuscorelib[i].average = p_stuscorelib[i].sum / p_stuscorelib[0].coursenumber;
            printf("------------------------\n");
            printf("学号为%d的学生修改后的成绩记录\n", tempnumber);
            printrecode(p_stuscorelib + i, 1);
            fp = fopen("学生成绩数据库.dat", "w+b");
            for (k = 0; k < count; k++)
            {
                if (fwrite(&p_stuscorelib[k], sizeof(struct stuscore), 1, fp) != 1)
                {
                    fclose(fp);
                    printf("修改失败，按任意键返回主菜单！");
                    getch();
                    system("cls");
                    return;
                }
            }
            fclose(fp);						// 成绩修改成功，写入文件后关闭文件
            for (k = 0; k < count; k++)
                if (tempnumber1 == p_stuscorelib[k].number&&tempterm1 == p_stuscorelib[k].to) m++;                  //学号和学期都相同的话肯定重号了
            if (m > 1)
                printf("管理员注意----有[%d]位同学的学号重号了！ 请按任意键返货主菜单重新进行修改！", m);
            else
                printf("成绩修改完毕，请按任意键返回主菜单！");
            getch();
            system("cls");
            return;
        }
    }
    printf("学号为%lld的学生不存在！请按任意键返回主菜单！", tempnumber);
    getch();
    system("cls");
    return;
}


/*****************************成绩查询******************************/
void scorequery(struct stuscore* p_stuscorelib)
{
    char* tempname;
    int choice;
    long long int tempnumber;
    int i, k, count, count2=0;
    count = readscore(p_stuscorelib);			// 读出学生成绩，并返回学生成绩记录数
    if (count == 0)
    {
        printf("\n还没输入成绩，请按任意键返回主菜单！");
        getchar();
        return;
    }
    while (1)
    {
        system("cls");
        printf("<1.按姓名查询  2.按学号查询  3.返回主菜单>\n");
        printf("请按数字键1-3，选择查询方式：");
        scanf("%d", &choice);
        fflush(stdin);
        if (choice == 1)
        {
            tempname = (char*)malloc(20 * sizeof(char));
            printf("请输入要进行查询的学生姓名:");
            gets(tempname);
            k = 0;
            for (i = 0; i < count; i++)
            {
                if (strcmp(tempname, p_stuscorelib[i].name) != 0)     // 姓名不符，继续查找
                    continue;
                else
                {
                    k++;
                    if (k == 1)
                        printf("==[%s]==同学成绩查询结果:\n", tempname);
                    printrecode(p_stuscorelib + i, 1);
                }
            }
            if (k > 0)
            {
                printf("查询完毕，按任意键继续！");
                free(tempname);
                getchar();
                system("cls");
            }
            else
            {
                printf("找不到该学生的成绩，请按任意键继续!");
                free(tempname);
                getch();
                system("cls");
            }
        }
        else if (choice == 2)
        {
            printf("请输入要进行成绩查询的学生学号:");
            scanf("%lld", &tempnumber);
            fflush(stdin);
            for (i = 0; i < count; i++)
            {
                if (tempnumber != p_stuscorelib[i].number)			// 学号不符，继续查找
                    continue;
                else
                {
                    count2++;
                    printrecode(p_stuscorelib + i, 1);
//                    printf("查询完毕，按任意键继续");
//                    getch();
//                    break;
                }
            }
            if (i == count)
            {
                if (count2 == 0) {
                    printf("没有查询到该学号同学的成绩，请按任意键继续!");
                    getch();
                    system("cls");
                }else{
                    printf("查询完毕，按任意键继续");
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


/*****************************成绩浏览******************************/

void scorebrowse(struct stuscore* p_stuscorelib,int count)
{
    int i, j, choice;
    struct stuscore t;
    if (count == 0)
    {
        printf("\n 还没输入成绩，请按任意键返回主菜单！");
        getch();
        return;
    }
    while (1)
    {
        printf("<1.按学号顺序浏览  2.按总成绩由大到小顺序浏览  3.返回主菜单>\n");
        printf("请按数字键1-3，选择浏览方式：");
        scanf("%d", &choice);
        if (choice == 1)							// 按学号顺序浏览
        {
            for (i = 1; i <= count - 1; i++)	    // 用冒泡排序按学号进行升序排序
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
            for (i = 1; i <= count - 1; i++)	    // 用冒泡排序按学号进行降序排序
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
    printf("请选择学期：\n");
    printf("1. 第一学期\n");
    printf("2. 第二学期\n");
    printf("请选择：");
    scanf("%d", &semester);
    fflush(stdin);

    if (semester != 1 && semester != 2) {
        printf("无效的选择。\n");
        getch();
        return;
    }

    printf("\n请选择班级：\n");
    printf("1. 分班级\n");
    printf("2. 全年级\n");
    printf("请选择：");
    scanf("%d", &browseChoice);
    if (browseChoice != 1 && browseChoice != 2) {
        printf("无效的选择。\n");
        getch();
        return;
    }


    fflush(stdin);

    if (browseChoice == 1) {
        char className[20];
        printf("\n请输入班级名称：");
        scanf("%s", className);

        // 过滤指定班级的学生记录并调用 scorebrowse 函数进行输出
        int count = readscore(p_stuscorelib);
        if (count == 0) {
            printf("\n还没输入成绩，请按任意键返回主菜单！");
            getch();
            return;
        }

        struct stuscore filteredRecords[count];  // 存储过滤后的学生成绩记录
        int filteredCount = 0;  // 过滤后的学生成绩记录数

        for (int i = 0; i < count; i++) {
            if (strcmp(p_stuscorelib[i].Class, className) == 0 && p_stuscorelib[i].to == semester) {
                filteredRecords[filteredCount] = p_stuscorelib[i];
                filteredCount++;
            }
        }

        if (filteredCount == 0) {
            printf("\n没有找到该班级的学生成绩记录。\n");
            return;
        }

        scorebrowse(filteredRecords, filteredCount);
    } else if (browseChoice == 2) {
        // 过滤指定学期的学生记录并调用 scorebrowse 函数进行输出
        int count = readscore(p_stuscorelib);
        if (count == 0) {
            printf("\n还没输入成绩，请按任意键返回主菜单！");
            getch();
            return;
        }

        struct stuscore filteredRecords[count];  // 存储过滤后的学生成绩记录
        int filteredCount = 0;  // 过滤后的学生成绩记录数

        for (int i = 0; i < count; i++) {
            if (p_stuscorelib[i].to == semester) {
                filteredRecords[filteredCount] = p_stuscorelib[i];
                filteredCount++;
            }
        }

        if (filteredCount == 0) {
            printf("\n该学期没有学生成绩记录。\n");
            return;
        }

        scorebrowse(filteredRecords, filteredCount);
    } else {
        printf("无效的选择。\n");
        return;
    }
}



/*****************************成绩删除******************************/
void scoredelete(struct stuscore* p_stuscorelib)
{
    int i, j, count;
    long long int tempnumber;
    char ch;
    count = readscore(p_stuscorelib);		// 读取学生成绩，并返回学生成绩记录数
    if (count == 0)
    {
        printf("\n 还没输入成绩，请按任意键返回主菜单！");
        getch();
        return;
    }
    fflush(stdin);
    printrecode(p_stuscorelib, count);		// 显示当前学生成绩数据的全部记录
    printf("确定进行删除成绩的操作吗？（y/n）:");
    while (1)
    {
        ch = getchar();
        fflush(stdin);
        if (ch == 'y' || ch == 'Y')
        {
            printf("请输入要删除成绩记录的学生学号（输入无效学号返回主菜单）:");
            scanf("%lld", &tempnumber);
            fflush(stdin);
            for (i = 0; i < count; i++)
            {
                if (tempnumber != p_stuscorelib[i].number)
                    continue;
                else
                {
                    for (j = i; j < count - 1; j++)				// 找到待删除元素后，进行调位处理
                        p_stuscorelib[j] = p_stuscorelib[j + 1];
                    count--;
                    fp = fopen("学生成绩数据库.dat", "w+b");
                    for (i = 0; i < count; i++) {
                        if (fwrite(&p_stuscorelib[i], sizeof(struct stuscore), 1, fp) == 1)
                            continue;
                        else {
                            printf("删除失败，按任意键返回主菜单!");
                            fclose(fp);
                            getch();
                            system("cls");
                            return;
                        }
                    }
                    printf("删除成功，按任意键返回主菜单！");
                    fclose(fp);
                    getch();
                    system("cls");
                    return;

                }
            }
        }
        else if (ch == 'n' || ch == 'N')
        {
            printf("请按任意键返回主菜单！");
            getchar();
            system("cls");
            return;
        }
        else printf("输入错误！ 请确定要进行删除成绩的操作吗（y/n）");
    }
}



/*************************显示学生成绩记录**************************/
void printrecode(struct stuscore* p_stuscorelib, int count)		// 从指针p_styscorelib 所指的成绩记录开始，显示后面count条成绩记录
{
    int i, j, k, m[10] = { 0 }, m1,len;
    char ch,str[15];
    for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
        m[j] = strlen(p_stuscorelib[0].course[j]) + 1;
    printf("课程总数:%d", p_stuscorelib[0].coursenumber);

    // 先获取出表格中表头课程部分打印的字符数，以便后面的程序实现表格的动态输出

    for (i = 0; i < count; i++)		// 在学生成绩数据文件中找到学生成绩记录并显示出来
    {
        if ((i == 0) || (i + 1) % 9 == 0)	// 在学生成绩数据文件中找到第1条学生成绩记录或每显示完8条学生成绩且还有学生成绩未显示，就显示表头
        {
            printf("\n\t\t\t\t 学生成绩\n");
            printf("|---------------|---------------|---------------|-----------------------|");
            for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
            {
                for (k = 0; k < m[j] - 1; k++)
                    printf("-");
                printf("|");
            }
            printf("------|----|\n");
            printf("|\t学号\t|\t学期\t|\t班级\t|\t姓名\t\t");
            for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
                printf("|%s", p_stuscorelib[0].course[j]);
            printf("|平均分|总分|\n");
            printf("|---------------|---------------|---------------|-----------------------|");
            for (j = 0; j < p_stuscorelib[0].coursenumber; j++)
            {
                for (k = 0; k < m[j] - 1; k++)
                    printf("-");
                printf("|");
            }
            printf("------|----|\n");
        }

        /*动态输出学号、班级和姓名*/
        memset(str,0,15);//清空str内容

        // 输出学号
        sprintf(str,"%lld",p_stuscorelib[i].number);//将学号的类型转换为字符串并存储到str
        len=strlen(str);//看学号有多少长(多少个字节)
        printf("|");
        if(len<8)//不到一个tab的长度
            printf("\t%s\t",str);
        else if(len<16)//不到二个tab的长度    学号最多16位！！！
            printf("%s\t",str);
        else
            printf("%s",str);

        //输出学期
        sprintf(str,"%lld",p_stuscorelib[i].to);//将学号的类型转换为字符串并存储到str
        len=strlen(str);//看学期有多少字节
        printf("|");
        if(len<8)//不到一个tab的长度
            printf("\t%s\t",str);
        else if(len<16)//不到两个tab的长度    学期最多15字节长度！！！
            printf("%s\t",str);

        // 输出班级
        len=strlen(p_stuscorelib[i].Class);//看班级有多少字节
        printf("|");
        if(len<8)//不到一个tab的长度
            printf("\t%s\t",p_stuscorelib[i].Class);
        else if(len<16)//不到两个tab的长度    //班级最多15字节长度！！！
            printf("%s\t",p_stuscorelib[i].Class);

        // 输出姓名
        len=strlen(p_stuscorelib[i].name);

        printf("|");
        if(len<8)//不到一个tab的长度
            printf("\t%s\t\t",p_stuscorelib[i].name);
        else if(len<16)//不到两个tab的长度    //姓名最多5汉字或10字节！！！
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


        // 显示该班同学各门学科成绩
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

        // 每显示完8条学生成绩记录且还有学生成绩未显示，就显示提示
        if ((i + 1) % 8 == 0 && (i + 1) < count)
        {
            printf("< 要返回主菜单，请按<q>键;继续浏览则按其他建! >");
            ch = getchar();
            fflush(stdin);
            if (ch == 'q')return;
            else system("cls");
        }
    }
}



/****************读入学生成绩，并返回学生成绩记录数*****************/
int readscore(struct stuscore* p_stuscorelib)
{
    int count;
    system("cls");
    if ((fp = fopen("学生成绩数据库.dat", "rb")) == NULL)
    {
        printf("打不开学生成绩数据库文件!");
        getchar();
        return 0;
    }
    rewind(fp);				// 文件位置指针回到文件起始位置
    for (count = 0; fread(&p_stuscorelib[count], sizeof(struct stuscore), 1, fp) == 1; count++){}
    fclose(fp);
    return count;		// 把读到的成绩记录总数返回
}

/****成绩排序模块*********/

// 按单科成绩排序
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

// 按班级进行总成绩排序
void sortByClass(struct stuscore* students, int count, const char* targetClass) {
    int i, j;
    struct stuscore temp;
    struct stuscore selectedStudents[100]; // 假设最多有100个学生数据
    int selectedCount = 0;                  // 班级人数

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

    // 输出
    printf("\n   学号 \t\t\t姓名\t\t 班别\t\t总成绩\t平均分\t排名\n");
    for (i = 0; i < selectedCount; i++) {
        printf("%lld\t%20s\t%20s\t%6.2f  %6.2f   %d\n", selectedStudents[i].number, selectedStudents[i].name,
               selectedStudents[i].Class, selectedStudents[i].sum, selectedStudents[i].average, i + 1);
    }
}

//按班级排序
void classscoresort(struct stuscore* p_stuscorelib) {
    int choice, subChoice;
    int count;
    count = readscore(p_stuscorelib); // 读出学生成绩，并返回学生成绩记录数

    if (count == 0) {
        printf("\n 还没输入成绩，请按任意键返回主菜单！");
        getch();
        return;
    }

    while (1) {
        printf("<1. 上学期成绩  2. 下学期成绩  3. 返回主菜单>\n");
        printf("请按数字键1-3，选择学期：");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            printf("<1. 按单科成绩排序  2. 按班级进行总成绩排序  3. 返回上一级菜单>\n");
            printf("请按数字键1-3，选择排序方式：");
            scanf("%d", &subChoice);

            if (subChoice == 1) {
                printf("\n请选择要排序的科目:\n");
                for (int i = 0; i < p_stuscorelib[0].coursenumber; i++) {
                    printf("%d. %s\n", i + 1, p_stuscorelib[0].course[i]);
                }
                printf("请输入数字键1-%d，选择要排序的科目: ", p_stuscorelib[0].coursenumber);
                scanf("%d", &subChoice);

                sortBySubject(p_stuscorelib, count, subChoice);

                printf("\t\t\t\t第%d学期学生单科成绩\t\t\t\t\n", choice);
                printf("\n   学号 \t\t\t姓名\t\t 班别\t\t%s成绩\t\n", p_stuscorelib[0].course[subChoice - 1]);
                for (int i = 0; i < count; i++) {
                    printf("%lld\t%20s\t%20s\t%6.2f\n", p_stuscorelib[i].number, p_stuscorelib[i].name,
                           p_stuscorelib[i].Class, p_stuscorelib[i].score[subChoice - 1]);
                }
            } else if (subChoice == 2) {
                char targetClass[20];
                printf("请输入要排序的班级（xxJ计算机类X）：");
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
