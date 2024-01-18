#include <unistd.h>

int main() {
    char *msg = "Hello!\n";
    fork();
    fork();
    fork();
    write(1, msg, 8);
    return 0;
}
