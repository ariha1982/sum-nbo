#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
// 리눅스의 netinet/in.h 헤더와 동일한 역할을 하는 헤더들
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) { //argv[1]부터 파일 이름 출력
    FILE *file;

    uint32_t sum = 0;
    for(int i = 1; i < argc; i++) {
        // 1. 파일 열기
        file = fopen(argv[i], "rb"); //TODO: 에러 및 예외처리

        // 2. 숫자 읽기
        unsigned char buffer[4];
        size_t file_read = fread(buffer, 1, 4, file);

        // 3. 리틀 엔디안 -> 빅 엔디안 
        uint32_t little_endian_value = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
        uint32_t big_endian_value = ntohl(little_endian_value);

        //4. 피연산자 및 연산자 출력
        printf(i == 1 ? "%d(0x%08x)" : " + %d(0x%08x)", big_endian_value, big_endian_value);

        // 5. 합계 계산
        sum += big_endian_value;

        // 6. 파일 닫기
        fclose(file);
    }

    // 7. 합계 출력
    printf(" = %d(0x%08x)\n", sum, sum);

    return 0;
}

