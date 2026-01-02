#include <stdio.h>
#include <stdlib.h>

// This function will print out the content of "secret.txt" file. You don't need
// to know the internals of this function.
void print_secret(void);

void menu(void) {
    printf("[SYSTEM] What is your choice?\n");
    printf("1. Send money to Alice\n");
    printf("2. Read secret file\n");
    printf("3. Quit\n");
    printf("(Enter 1~3): ");
}

int read_int(void) {
    int v;
    if (scanf("%d", &v) != 1) {
        printf("[ERROR] Invalid input format\n");
        exit(1);
    }
    return v;
}

int main(void) {
    int alice_balance = 2000; // 상대방 잔고
    int your_balance = 1000; // 내 잔고
    int choice, amount; // 번호 선택 그리고 돈
    int quit_flag = 0; // 프로그램의 종료 여부를 나타내는 변수

    setvbuf(stdin, NULL, _IONBF, 0); // 입력 버퍼를 금지 -> 이유는? 입력버퍼에 저장하는 그 짧은 시간도 줄여 입력과 출력의 흐름을 좀 더 명확하게 보기 위해서다.

    while (!quit_flag) {
        printf("=============================\n");
        printf("[SYSTEM] Your balance = %d\n", your_balance); // key point 1 : 상대방 잔고는 출력 X, 내 잔고만 출력 O. 
                                                              // 내 잔고의 변경사항은 볼 수 있지만 상대방의 잔고 상황은 알 수 없음.
        menu();
        choice = read_int();
        switch (choice) {
        case 1:
            printf("Input the amount of money you want to send: ");
            amount = read_int(); // key point 2 :  돈이 음수인지 양수인지 확인하고 있지 않다.
            if (amount > your_balance) {
                printf("[ERROR] You don't have enough balance\n");
                break;
            }
            your_balance -= amount; // key point 3 : amount가 음수이면 your_balance가 더욱 증가한다.
            alice_balance += amount;
            break;

        case 2:
            if (your_balance < 50000) {
                printf("[ERROR] Only the VIP user can read the secret file\n");
                printf("(VIP requirement: balance >= 50000)\n");
                break;
            }

            print_secret();  // key point 4
            break;

        case 3:
            quit_flag = 1;
            break;

        default:
            printf("[ERROR] Invalid choice\n");
        }
    }

    return 0;
}
