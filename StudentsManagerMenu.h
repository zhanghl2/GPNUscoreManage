//
// Created by 10188 on 2023/6/17.
//

#ifndef CCCCCCC_STUDENTSMANAGERMENU_H
#define CCCCCCC_STUDENTSMANAGERMENU_H

#include "scoreProcessor.h"
#include "Menu.h"
#include "TXTtoDATtoCSV.h"

void studentsManager();
void studentsManager(){
    int choice ,flag = 0;							/*choice 变量用来存放用户操作选项数字，flag=（0/1） 表示（显示/退出）学生成绩管理系统界面*/
    /*学生管理系统管理界面*/
    while (1) {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: scoreinput(stuscorelib); break;                             //成绩录入
            case 2: scoremodify(stuscorelib); break;                            //成绩修改
            case 3: scorequery(stuscorelib); break;                             //成绩查询
            case 4: selectAndBrowse(stuscorelib); break;                        //成绩浏览
            case 5: scoredelete(stuscorelib); break;                            //成绩删除
            case 6: classscoresort(stuscorelib);break;                          //成绩排序
            case 7: readDataFromFile(stuscorelib);break;                           //成绩导入
            case 8: readDatabase();break;                                                    //成绩导出
            case 9: flag = 1; break;                                                         //退出系统
            default:printf("\t\t	<没有出现此选项，按任意键重新选择！>"); getch(); break;
        }
        if (flag == 1)break;
    }
}


#endif //CCCCCCC_STUDENTSMANAGERMENU_H
