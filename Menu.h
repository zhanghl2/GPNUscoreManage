
#ifndef CCCCCCC_MENU_H
#define CCCCCCC_MENU_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void showWelcomeScreen();               //显示欢迎界面
void showAdminScreen();                 //显示管理员菜单界面
void showMenu();                        //显示学生成绩主菜单界面
void showExitScreen();                  //显示结束画面

void showWelcomeScreen() {
    /*学生管理系统欢迎界面*/
    printf("\n");
    printf("      .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.   \n");
    printf("     | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |  \n");
    printf("     | | _____  _____ | || |  _________   | || |   _____      | || |     ______   | || |     ____     | || | ____    ____ | |  \n");
    printf("     | ||_   _||_   _|| || | |_   ___  |  | || |  |_   _|     | || |   .' ___  |  | || |   .'    `.   | || ||_   \\  /   _|| |  \n");
    printf("     | |  | | /\\ | |  | || |   | |_  \\_|  | || |    | |       | || |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\/   |  | |  \n");
    printf("     | |  | |/  \\| |  | || |   |  _|  _   | || |    | |   _   | || |  | |         | || |  | |    | |  | || |  | |\\  /| |  | |  \n");
    printf("     | |  |   /\\   |  | || |  _| |___/ |  | || |   _| |__/ |  | || |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\/_| |_ | |  \n");
    printf("     | |  |__/  \\__|  | || | |_________|  | || |  |________|  | || |   `._____.'  | || |   `.____.'   | || ||_____||_____|| |  \n");
    printf("     | |              | || |              | || |              | || |              | || |              | || |              | |  \n");
    printf("     | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |  \n");
    printf("      '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'   \n");
    printf("                                           欢迎使用学生成绩管理系统，按任意键进入管理员登录界面                                                                      \n");
    printf("                                                [ version : 2.2.1 ]     by ZHL"
           "                                                                  \n");
    printf(" \n");
    getch();
    system("cls");

}

void showAdminScreen() {
    system("cls");
    printf("\n\n\n");
    printf("\t\t-------------------------------------------------\n");
    printf("\t\t||              ----------------               ||\n");
    printf("\t\t||**************管理员登录界面*****************||\n");
    printf("\t\t||              ----------------               ||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~1.添加管理员用户~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~2.修改管理员密码~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~3.删除管理员~~~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~4.显示最近6条登录日志~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~5.进入学生信息管理系统~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||*********************************************||\n");
    printf("\t\t	请按数字键1~5，进行相应操作： ");
}

void showMenu() {
    system("cls");
    printf("\n\n\n");
    printf("\t\t-------------------------------------------------\n");
    printf("\t\t||              ----------------               ||\n");
    printf("\t\t||**************学生信息管理系统***************||\n");
    printf("\t\t||              ----------------               ||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~1.录入学生信息~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~2.修改学生信息~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~3.查询学生信息~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~4.浏览学生信息~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~5.删除学生信息~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~6.排序学生信息~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~7.导入学生成绩~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~8.导出学生成绩~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||                                             ||\n");
    printf("\t\t||~~~~~~~~~~~~~~~9.退出系统~~~~~~~~~~~~~~~~~~~~||\n");
    printf("\t\t||*********************************************||\n");
    printf("\t\t	请按数字键1~8，进行相应操作： ");
}

void showExitScreen() {
    system("cls");
    printf("\n\n\n\n\n\n\n\n");
    printf("                                                                                                                          \n");
    printf("                                                                                                                               \n");
    printf("BBBBBBBBBBBBBBBBB   YYYYYYY       YYYYYYYEEEEEEEEEEEEEEEEEEEEEEBBBBBBBBBBBBBBBBB   YYYYYYY       YYYYYYYEEEEEEEEEEEEEEEEEEEEEE\n");
    printf("B::::::::::::::::B  Y:::::Y       Y:::::YE::::::::::::::::::::EB::::::::::::::::B  Y:::::Y       Y:::::YE::::::::::::::::::::E\n");
    printf("B::::::BBBBBB:::::B Y:::::Y       Y:::::YE::::::::::::::::::::EB::::::BBBBBB:::::B Y:::::Y       Y:::::YE::::::::::::::::::::E\n");
    printf("BB:::::B     B:::::BY::::::Y     Y::::::YEE::::::EEEEEEEEE::::EBB:::::B     B:::::BY::::::Y     Y::::::YEE::::::EEEEEEEEE::::E\n");
    printf("  B::::B     B:::::BYYY:::::Y   Y:::::YYY  E:::::E       EEEEEE  B::::B     B:::::BYYY:::::Y   Y:::::YYY  E:::::E       EEEEEE\n");
    printf("  B::::B     B:::::B   Y:::::Y Y:::::Y     E:::::E               B::::B     B:::::B   Y:::::Y Y:::::Y     E:::::E             \n");
    printf("  B::::BBBBBB:::::B     Y:::::Y:::::Y      E::::::EEEEEEEEEE     B::::BBBBBB:::::B     Y:::::Y:::::Y      E::::::EEEEEEEEEE   \n");
    printf("  B:::::::::::::BB       Y:::::::::Y       E:::::::::::::::E     B:::::::::::::BB       Y:::::::::Y       E:::::::::::::::E   \n");
    printf("  B::::BBBBBB:::::B       Y:::::::Y        E:::::::::::::::E     B::::BBBBBB:::::B       Y:::::::Y        E:::::::::::::::E   \n");
    printf("  B::::B     B:::::B       Y:::::Y         E::::::EEEEEEEEEE     B::::B     B:::::B       Y:::::Y         E::::::EEEEEEEEEE   \n");
    printf("  B::::B     B:::::B       Y:::::Y         E:::::E               B::::B     B:::::B       Y:::::Y         E:::::E             \n");
    printf("  B::::B     B:::::B       Y:::::Y         E:::::E       EEEEEE  B::::B     B:::::B       Y:::::Y         E:::::E       EEEEEE\n");
    printf("BB:::::BBBBBB::::::B       Y:::::Y       EE::::::EEEEEEEE:::::EBB:::::BBBBBB::::::B       Y:::::Y       EE::::::EEEEEEEE:::::E\n");
    printf("B:::::::::::::::::B     YYYY:::::YYYY    E::::::::::::::::::::EB:::::::::::::::::B     YYYY:::::YYYY    E::::::::::::::::::::E\n");
    printf("B::::::::::::::::B      Y:::::::::::Y    E::::::::::::::::::::EB::::::::::::::::B      Y:::::::::::Y    E::::::::::::::::::::E\n");
    printf("BBBBBBBBBBBBBBBBB       YYYYYYYYYYYYY    EEEEEEEEEEEEEEEEEEEEEEBBBBBBBBBBBBBBBBB       YYYYYYYYYYYYY    EEEEEEEEEEEEEEEEEEEEEE\n");
    printf("                                                                                                                               \n");
    printf("------------------------------------------------- [已退出管理系统，感谢使用] -------------------------------------------------------------\n");
    getch();
}


#endif //CCCCCCC_MENU_H
