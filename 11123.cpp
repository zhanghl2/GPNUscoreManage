
// Created by ZHL on 2023/6/14.

#include "Menu.h"                                                 //��ʾ�˵�
#include "AdminLog.h"                                             //����Ա��¼
#include "StudentsManagerMenu.h"                                  //ѧ���ɼ��������

int main()
{

    showWelcomeScreen();                                          //��ʾ��ӭ����
    log();                                                        //��¼�˺�
    adminSelectChoice();                                          //����Ա�������
    studentsManager();                                            //ѧ���ɼ��������
    showExitScreen();                                             //�˳�����
    return 0;
}





