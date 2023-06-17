
// Created by ZHL on 2023/6/14.

#include "Menu.h"                                                 //显示菜单
#include "AdminLog.h"                                             //管理员登录
#include "StudentsManagerMenu.h"                                  //学生成绩管理界面

int main()
{

    showWelcomeScreen();                                          //显示欢迎界面
    log();                                                        //登录账号
    adminSelectChoice();                                          //管理员管理界面
    studentsManager();                                            //学生成绩管理界面
    showExitScreen();                                             //退出界面
    return 0;
}





