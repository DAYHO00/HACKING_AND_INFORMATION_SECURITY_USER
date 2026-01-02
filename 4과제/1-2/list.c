#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_FORMAT "ls -l ./%s"
// ls -l은 현재 디렉토리에서 파일을 실행하지 않고 파일의 상세 정보를 출력
// ./은 현재 디렉토리에서 파일을 찾는다.


// This function executes the provided command line string, 'cmd'. You don't
// need to know the internals of this function.
void my_system(char* cmd);

void read_line(char* buf, int bufsize) { //char*buf는 배열을 함수에 전달하기 위한것이다.
    if (!fgets(buf, bufsize, stdin)) { //입력 스트림에서 데이터를 읽어와 버프에 저장
        exit(1); // 성공이면 ifX, 실패하면 if작동
    } // 입력에 실패하면 프로그램이 종료
    buf[strcspn(buf, "\n")] = '\0'; // Replace the trailing newline character.
    // buf에서 개행 문자의 위치를 찾는거다. so NULL문자로 교체해 문자열의 끝을 표시
}

int main(void) {
    char cmd_buf[64]; // 64바이트 크기를 가지는 배열
    char input_buf[32]; //32바이트 크기를 가지는 배열
   
    setvbuf(stdin, NULL, _IONBF, 0); // 입력 버퍼에 저장되는 시간을 줄이기 위해 입력범퍼 이용 금지

    puts("Welcome to file/directory listing service");
    puts("Input the file you want to list"); 
    puts("(Just press enter to list the current directory)");
    read_line(input_buf, sizeof(input_buf)); 
    if (strchr(input_buf, ';') != NULL) {
        //strchr은 문자열에서 특정문자를 찾는 역할을 한다.
        puts("You cannot use semicolon (;) in the input!");
        exit(1);
    }

    snprintf(cmd_buf, sizeof(cmd_buf), CMD_FORMAT, input_buf);
    // cmd_buf에 ls -l ./list.bin 문자열이 저장된다.
    my_system(cmd_buf); // cmd_buf에 저장된 명령어를 실행
    puts("Failed to execute 'ls' program!");
    exit(1);
}

// 답이 2개다.
// list.bin & cat secret.txt -> &는 백그라운드 실행을 의미
// ls -l ./list.bin은 백그라운드에서 실행된다.
// 이때  터미널은 이 명령어가 끝나길 기다리지 않는다.
//  바로 다음 명령어 at secret.txt를 실행한다.

// list.bin | cat secret.txt ->앞 명령어의 출력을 뒤 명령어의 입력으로 연결한다.
