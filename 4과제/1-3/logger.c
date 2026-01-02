#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_FORMAT "./logs/%s.txt" // 현재 디렉토리의 logs폴더에서 secret.txt파일을 찾는다.

void read_line(char* buf, int bufsize) { //문자열이니까 포인터 변수를 이용했다.
                                         // 주소값을 이용하기 위한 것이다.
    if (!fgets(buf, bufsize, stdin)) {  // buf에 입력 문자열을 저장
        exit(1); // 입력 문자열이 있는지 없는지 확인
    }
    buf[strcspn(buf, "\n")] = '\0'; // Replace the trailing newline character.
    // 줄바꿈 문자의 위치를 찾아서 NULL문자로 바꾼다 -> 문자열의 끝을 표시
}

void write_log(char* file_path) { //문자열이니까 포인터 사용
    time_t now = time(NULL); //현재 시간을 초단위로 가져와 now에 저장한다.
    FILE* fp = fopen(file_path, "w");
    //파일이 존재할 경우 : 파일의 기존 내용은 모두 삭제되고 이후 파일에 새로 데이터를 작성할 수 있는 상태가 된다.
    //파일이 존재하지 않을 경우 :  새로운 파일이 생성되고, 그 파일에 데이터를 쓸 수 있는 상태가 된다.
    if (!fp) {
        printf("Failed to open %s\n", file_path);
        exit(1);
    }
    fprintf(fp, "Last login: %s", ctime(&now));
    //fp에 로그인 시간 정보를 저장하고, 이후 해당 정보를 터미널에 출력
    // ctime(&now)는 사람이 읽을 수 있는 문자열로 변환
    fclose(fp);
    printf("Recorded your last login time!\n");
}

void read_log(char* file_path) {
    char logbuf[64]; // 64바이트 크기의 배열
    FILE* fp = fopen(file_path, "r"); // 파일의 내용을 읽을 수 있는 상태로 연다
    if (!fp) {
        printf("Failed to open %s\n", file_path);
        exit(1);
    }
    fgets(logbuf, sizeof(logbuf), fp); // 파일에서 한 줄을 읽어 logbuf에 저장
    //한 줄을 읽는다는 것은 파일에서 개행 문자(\n)가 나올 때까지 데이터를 읽는다
    fputs(logbuf, stdout); // 로그 데이터를 터미널에 출력
    fclose(fp);
}

int main(void) {
    char file_path[64]; // 64 바이트
    char input_buf[32]; // 32 바이트

    setvbuf(stdin, NULL, _IONBF, 0); // 출력 버퍼 금지

    printf("Welcome! Please input your ID: ");
    read_line(input_buf, sizeof(input_buf)); // input_buf에 입력 문자열 저장
    snprintf(file_path, sizeof(file_path), LOG_FORMAT, input_buf);
    //file_path에 ./logs/secret.txt가 저장된다.
    write_log(file_path);
    printf("Do you want to check other user's login record? (Y/N): ");
    read_line(input_buf, sizeof(input_buf)); //input_buf에 Y를 저장
    if (strcmp("Y", input_buf) == 0) {
        printf("Input the user ID you want to check: ");
        read_line(input_buf, sizeof(input_buf)); //ex) input_buf= ../secret.txt
        snprintf(file_path, sizeof(file_path), LOG_FORMAT, input_buf);
        //file_path=./logs/../secret.txt
        // ../상위디렉토리라 이동
        // logs 디렉토리로 들어갔다가 상위 디렉토리에서 secret.txt를 찾는다.

        read_log(file_path);
    }

    return 0;
}
