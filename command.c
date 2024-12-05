#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

jmp_buf env;

void throw_error()
{
    longjmp(env, 1); // Simulate throwing an exception
}
char* run(char query[]) {
    static char result[1024];  // Static buffer to hold output

    if (setjmp(env) == 0) {
        // Try block
        FILE *fp;

        // Open a process to run the command and capture its output
        fp = popen(query, "r");
        if (fp == NULL) {
            longjmp(env, 1);  // Simulate exception if popen fails
        }

        // Read the output of the command into the result buffer
        size_t index = 0;
        while (fgets(result + index, sizeof(result) - index, fp) != NULL) {
            index += strlen(result + index);
        }

        fclose(fp);
    }
    else {
        // Catch block
        printf("Caught an exception\n");
        return NULL;
    }

    return result;
}
int main(int argc, char const *argv[])
{
    char *output = run("ls -l");  // Test with the "ls -l" command

    if (output != NULL) {
        printf("Command output:\n%s", output);  // Print the returned output
    }

    return 0;
}
