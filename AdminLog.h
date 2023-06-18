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


#define MAX_USERNAME_LENGTH 20                      //�û�����󳤶�
#define MAX_PASSWORD_LENGTH 20                      //������󳤶�
/**************����Ա�ṹ�嶨��********************/
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

void writeLog(const char* username, const char* status);                    //ϵͳ��¼��־
void log();                                                                 //��¼
void addUser(struct User* users, int* userCount);                           //��ӹ���Ա�˺�
void changePassword(struct User* users, int userCount);                     //�޸Ĺ���Ա����
void deleteUser();                                                          //ɾ������Ա
void displayRecentLoginLogs();                                              //��ʾ�����¼��־
void adminSelectChoice();                                                   //����Ա�˵�

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

    // ���ļ��ж�ȡ�û���������
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
        printf("��ʼ�˺�: admin ��ʼ����: 123456\n");
        printf("------------------------------------------------\n");
        printf("�������˺�: ");
        scanf("%s", input_username);
        printf("����������: ");
        scanf("%s", input_password);

        int found = 0;
        for (int i = 0; i < userCount; i++) {
            if (strcmp(input_username, users[i].username) == 0 && strcmp(input_password, users[i].password) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("��¼�ɹ���\n");
            writeLog(input_username, "success");
            return; // ��¼�ɹ�
        } else {
            system("cls");
            attempt_count++;
            printf("�˺Ż���������㻹��%d�λ��ᣬʧ�ܺ�����˳�\n", 5 - attempt_count);

            if (attempt_count >= 5) {
                printf("�������������࣬������������5����Զ��˳�\n");
                writeLog("UnkownUser","fail");
                Sleep(5000);
                exit(0);
            }

            // �����������ʱ��������������Windows��
            Beep(1000, 500); // 1000 HzƵ�ʣ�500�������ʱ��
        }
    }
}

void addUser(struct User* users, int* userCount) {
    if (*userCount == MAX_USERS) {
        printf("�û������Ѵﵽ������ƣ��޷���Ӹ����û���\n");
        printf("3����Զ������ϼ��˵�\n");
        Sleep(3000);
        return;
    }

    char new_username[MAX_USERNAME_LENGTH];
    char new_password[MAX_PASSWORD_LENGTH];

    printf("���������û���: ");
    scanf("%s", new_username);
    printf("������������: ");
    scanf("%s", new_password);

    // ���û�ƾ���ļ��Լ���û����Ƿ��Ѵ���
    FILE* file = fopen("user_credentials.txt", "r");
    if (file != NULL) {
        char existing_username[MAX_USERNAME_LENGTH];
        char existing_password[MAX_PASSWORD_LENGTH];

        // ���ж�ȡ�ļ��е��û��������룬�����бȽ�
        while (fscanf(file, "%s %s", existing_username, existing_password) == 2) {
            if (strcmp(existing_username, new_username) == 0) {
                printf("�û����Ѵ��ڣ��޷�����û���\n");
                fclose(file);
                printf("3����Զ������ϼ��˵�\n");
                Sleep(3000);
                return;
            }
        }

        fclose(file);
    }

    // �����û�д���ļ���
    file = fopen("user_credentials.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", new_username, new_password);
        fclose(file);
    }

    strcpy(users[*userCount].username, new_username);
    strcpy(users[*userCount].password, new_password);
    (*userCount)++;

    printf("�û���ӳɹ���\n");
    printf("3����Զ������ϼ��˵�\n");
    Sleep(3000);
}

void changePassword(struct User* users, int userCount) {
    char username[MAX_USERNAME_LENGTH];
    char current_password[MAX_PASSWORD_LENGTH];
    char new_password[MAX_PASSWORD_LENGTH];

    printf("�������û���: ");
    scanf("%s", username);
    printf("�����뵱ǰ����: ");
    scanf("%s", current_password);
    printf("������������: ");
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
        printf("�����޸ĳɹ���\n");
    } else {
        printf("�û�����ǰ���벻��ȷ���޷��޸����롣\n");
    }
    Sleep(5000);
    printf("5����Զ������ϼ��˵�\n");
}

void deleteUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("����������Ҫɾ�����û���\n");
    scanf("%s", username);
    printf("��������û�������\n");
    scanf("%s", password);
    int tempD = 0;
    // ���û�ƾ���ļ��Զ�ȡ�û���Ϣ
    FILE* file = fopen("user_credentials.txt", "r");
    if (file == NULL) {
        printf("�޷����û�ƾ���ļ���\n");
        return;
    }

    // ������ʱ�ļ��Ա�����º���û�ƾ����Ϣ
    FILE* tempFile = fopen("temp_user_credentials.txt", "w");
    if (tempFile == NULL) {
        printf("�޷�������ʱ�ļ���\n");
        fclose(file);
        return;
    }

    char existing_username[MAX_USERNAME_LENGTH];
    char existing_password[MAX_PASSWORD_LENGTH];

    // ���ж�ȡ�ļ��е��û��������룬�����бȽ�
    while (fscanf(file, "%s %s", existing_username, existing_password) == 2) {
        // ����û����Ƿ�ƥ��
        if (strcmp(existing_username, username) == 0 && strcmp(existing_password, password) == 0) {
            tempD = 1;
            continue; // ����Ҫɾ�����û�
        }

        // ����ɾ���û���ƾ��д����ʱ�ļ�
        fprintf(tempFile, "%s %s\n", existing_username, existing_password);
    }

    // �ر��ļ�
    fclose(file);
    fclose(tempFile);

    // ɾ��ԭ�û�ƾ���ļ�
    if (remove("user_credentials.txt") != 0) {
        printf("�޷�ɾ���û�ƾ���ļ���\n");
        printf("3����Զ������ϼ��˵�\n");
        Sleep(3000);
        return;
    }

    // ��������ʱ�ļ�Ϊ�û�ƾ���ļ�
    if (rename("temp_user_credentials.txt", "user_credentials.txt") != 0) {
        printf("�޷���������ʱ�ļ���\n");
        return;
    }
    if (tempD == 1) {
        printf("�û�ɾ���ɹ���\n");
    } else
        printf("������û�������������\n");
    printf("������������ϼ��˵�\n");
    getch();
}

void displayRecentLoginLogs() {
    system("cls");
    FILE* file = fopen("login_log.txt", "r");
    if (file == NULL) {
        printf("�޷�����־�ļ���\n");
        printf("3����Զ������ϼ��˵�\n");
        Sleep(3000);
        return;
    }

    // ��ȡ�ļ�������
    int lineCount = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }

    // ���ļ�ָ�����¶�λ���ļ���ͷ
    fseek(file, 0, SEEK_SET);

    // ������ʼ�к�
    int startLine = lineCount - 6;
    if (startLine < 0) {
        startLine = 0;
    }

    // ������ʼ��֮ǰ������
    for (int i = 0; i < startLine; i++) {
        while ((ch = fgetc(file)) != '\n' && ch != EOF);
    }

    // ���д�ӡ��־����
    printf("�����¼��־:\n");
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
    printf("������������ϼ��˵�\n");
    getch();
}
void adminSelectChoice() {

    int choice, flag1 = 0;                            /*choice ������������û�����ѡ�����֣�flag=��0/1�� ��ʾ����ʾ/�˳���ѧ���ɼ�����ϵͳ����*/
    struct User users[MAX_USERS];                   //�������Ա�û�
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
                printf("\t\t	<û�г��ִ�ѡ������������ѡ��>");
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
