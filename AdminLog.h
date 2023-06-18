//
// Created by 10188 on 2023/6/17.
//

#ifndef CCCCCCC_ADMINLOG_H
#define CCCCCCC_ADMINLOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>


#define MAX_USERS 100


#define MAX_USERNAME_LENGTH 20                      //用户名最大长度
#define MAX_PASSWORD_LENGTH 20                      //密码最大长度
/**************管理员结构体定义********************/
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

void writeLog(const char* username, const char* status);                    //系统登录日志
void log();                                                                 //登录
void addUser(struct User* users, int* userCount);                           //添加管理员账号
void changePassword(struct User* users, int userCount);                     //修改管理员密码
void deleteUser();                                                          //删除管理员
void displayRecentLoginLogs();                                              //显示最近登录日志
void adminSelectChoice();                                                   //管理员菜单

void writeLog(const char* username, const char* status) {
    time_t now;
    time(&now);
    struct tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    FILE* file = fopen("login_log.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s - %s\n", timestamp, username, status);
        fclose(file);
    }
}

void log() {
    struct User users[MAX_USERS];
    int userCount = 0;

    // 从文件中读取用户名和密码
    FILE* file = fopen("user_credentials.txt", "r");
    if (file != NULL) {
        while (userCount < MAX_USERS && fscanf(file, "%s %s", users[userCount].username, users[userCount].password) == 2) {
            userCount++;
        }
        fclose(file);
    }

    char input_username[MAX_USERNAME_LENGTH];
    char input_password[MAX_PASSWORD_LENGTH];
    int attempt_count = 0;

    while (1) {
        printf("初始账号: admin 初始密码: 123456\n");
        printf("------------------------------------------------\n");
        printf("请输入账号: ");
        scanf("%s", input_username);
        printf("请输入密码: ");
        scanf("%s", input_password);

        int found = 0;
        for (int i = 0; i < userCount; i++) {
            if (strcmp(input_username, users[i].username) == 0 && strcmp(input_password, users[i].password) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("登录成功！\n");
            writeLog(input_username, "success");
            return; // 登录成功
        } else {
            system("cls");
            attempt_count++;
            printf("账号或密码错误！你还有%d次机会，失败后程序将退出\n", 5 - attempt_count);

            if (attempt_count >= 5) {
                printf("密码错误次数过多，程序已锁定，5秒后将自动退出\n");
                writeLog("UnkownUser","fail");
                Sleep(5000);
                exit(0);
            }

            // 输入密码错误时发出报警声音（Windows）
            Beep(1000, 500); // 1000 Hz频率，500毫秒持续时间
        }
    }
}

void addUser(struct User* users, int* userCount) {
    if (*userCount == MAX_USERS) {
        printf("用户数量已达到最大限制，无法添加更多用户。\n");
        printf("3秒后自动返回上级菜单\n");
        Sleep(3000);
        return;
    }

    char new_username[MAX_USERNAME_LENGTH];
    char new_password[MAX_PASSWORD_LENGTH];

    printf("请输入新用户名: ");
    scanf("%s", new_username);
    printf("请输入新密码: ");
    scanf("%s", new_password);

    // 打开用户凭据文件以检查用户名是否已存在
    FILE* file = fopen("user_credentials.txt", "r");
    if (file != NULL) {
        char existing_username[MAX_USERNAME_LENGTH];
        char existing_password[MAX_PASSWORD_LENGTH];

        // 逐行读取文件中的用户名和密码，并进行比较
        while (fscanf(file, "%s %s", existing_username, existing_password) == 2) {
            if (strcmp(existing_username, new_username) == 0) {
                printf("用户名已存在，无法添加用户。\n");
                fclose(file);
                printf("3秒后自动返回上级菜单\n");
                Sleep(3000);
                return;
            }
        }

        fclose(file);
    }

    // 将新用户写入文件中
    file = fopen("user_credentials.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", new_username, new_password);
        fclose(file);
    }

    strcpy(users[*userCount].username, new_username);
    strcpy(users[*userCount].password, new_password);
    (*userCount)++;

    printf("用户添加成功！\n");
    printf("3秒后自动返回上级菜单\n");
    Sleep(3000);
}

void changePassword(struct User* users, int userCount) {
    char username[MAX_USERNAME_LENGTH];
    char current_password[MAX_PASSWORD_LENGTH];
    char new_password[MAX_PASSWORD_LENGTH];

    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入当前密码: ");
    scanf("%s", current_password);
    printf("请输入新密码: ");
    scanf("%s", new_password);

    int found = 0;
    FILE* file = fopen("user_credentials.txt", "r+");
    if (file != NULL) {
        char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2];  // +2 for username, password and space delimiter
        long int position = 0;  // to keep track of the line position

        while (fgets(line, sizeof(line), file) != NULL) {
            char stored_username[MAX_USERNAME_LENGTH];
            char stored_password[MAX_PASSWORD_LENGTH];

            // Extract username and password from the line
            if (sscanf(line, "%s %s", stored_username, stored_password) != 2) {
                continue;
            }

            // Check if the username and current password match
            if (strcmp(username, stored_username) == 0 && strcmp(current_password, stored_password) == 0) {
                found = 1;
                // Move the file pointer back to the beginning of the line
                fseek(file, position, SEEK_SET);
                // Write the new password to the file
                fprintf(file, "%s %s\n", username, new_password);
                break;
            }

            // Update the position to the next line
            position = ftell(file);
        }

        fclose(file);
    }

    if (found) {
        printf("密码修改成功！\n");
    } else {
        printf("用户名或当前密码不正确，无法修改密码。\n");
    }
    Sleep(5000);
    printf("5秒后自动返回上级菜单\n");
}

void deleteUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("请输入你想要删除的用户名\n");
    scanf("%s", username);
    printf("请输入该用户的密码\n");
    scanf("%s", password);
    int tempD = 0;
    // 打开用户凭据文件以读取用户信息
    FILE* file = fopen("user_credentials.txt", "r");
    if (file == NULL) {
        printf("无法打开用户凭据文件。\n");
        return;
    }

    // 创建临时文件以保存更新后的用户凭据信息
    FILE* tempFile = fopen("temp_user_credentials.txt", "w");
    if (tempFile == NULL) {
        printf("无法创建临时文件。\n");
        fclose(file);
        return;
    }

    char existing_username[MAX_USERNAME_LENGTH];
    char existing_password[MAX_PASSWORD_LENGTH];

    // 逐行读取文件中的用户名和密码，并进行比较
    while (fscanf(file, "%s %s", existing_username, existing_password) == 2) {
        // 检查用户名是否匹配
        if (strcmp(existing_username, username) == 0 && strcmp(existing_password, password) == 0) {
            tempD = 1;
            continue; // 跳过要删除的用户
        }

        // 将非删除用户的凭据写入临时文件
        fprintf(tempFile, "%s %s\n", existing_username, existing_password);
    }

    // 关闭文件
    fclose(file);
    fclose(tempFile);

    // 删除原用户凭据文件
    if (remove("user_credentials.txt") != 0) {
        printf("无法删除用户凭据文件。\n");
        printf("3秒后自动返回上级菜单\n");
        Sleep(3000);
        return;
    }

    // 重命名临时文件为用户凭据文件
    if (rename("temp_user_credentials.txt", "user_credentials.txt") != 0) {
        printf("无法重命名临时文件。\n");
        return;
    }
    if (tempD == 1) {
        printf("用户删除成功！\n");
    } else
        printf("输入的用户名或密码有误！\n");
    printf("按任意键返回上级菜单\n");
    getch();
}

void displayRecentLoginLogs() {
    system("cls");
    FILE* file = fopen("login_log.txt", "r");
    if (file == NULL) {
        printf("无法打开日志文件。\n");
        printf("3秒后自动返回上级菜单\n");
        Sleep(3000);
        return;
    }

    // 获取文件总行数
    int lineCount = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }

    // 将文件指针重新定位到文件开头
    fseek(file, 0, SEEK_SET);

    // 计算起始行号
    int startLine = lineCount - 6;
    if (startLine < 0) {
        startLine = 0;
    }

    // 跳过起始行之前的内容
    for (int i = 0; i < startLine; i++) {
        while ((ch = fgetc(file)) != '\n' && ch != EOF);
    }

    // 逐行打印日志内容
    printf("最近登录日志:\n");
    printf("------------------------------------------------\n");
    int lineNo = startLine + 1;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
        if (ch == '\n') {
            lineNo++;
        }
    }

    fclose(file);
    printf("------------------------------------------------\n");
    printf("按任意键返回上级菜单\n");
    getch();
}
void adminSelectChoice() {

    int choice, flag1 = 0;                            /*choice 变量用来存放用户操作选项数字，flag=（0/1） 表示（显示/退出）学生成绩管理系统界面*/
    struct User users[MAX_USERS];                   //定义管理员用户
    int userCount = 0;
    while (1) {
        showAdminScreen();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addUser(users, &userCount);
                break;
            case 2:
                changePassword(users, userCount);
                break;
            case 3:
                deleteUser();
                break;
            case 4:
                displayRecentLoginLogs();
                break;
            case 5:
                flag1 = 1;
                break;
            default:
                printf("\t\t	<没有出现此选项，按任意键重新选择！>");
                getch();
                break;
        }
        if (flag1 == 1) {
            system("cls");
            break;
        }
    }
}


#endif //CCCCCCC_ADMINLOG_H
