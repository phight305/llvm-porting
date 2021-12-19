#include "stdio.h"
#include <fstream>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Memory dump file does not exist!\n");
        return 1;
    }

    std::fstream file(argv[1], std::ios_base::in | std::ios_base::binary);
    if (file.fail()) {
        printf("Fail to open the file when dumping the contents of memory");
        return 1;
    }

    for (unsigned int i = 0; i < 0x20000; i++) {
        unsigned char c = 0;
        file.read((char *)&c, sizeof(char));
        if (i == 0x1234 && c != 5) {
            printf("FAIL: expect: %x, get: %x\n", 5, c);
            file.close();
            return 1;
        }
    }
    printf("SUCCESS\n");

    file.close();
}
