#include <stdio.h>
#include <Windows.h>


char* find_words(char* line, int length)
{
    printf("%s", "Search results:\n");
    char* f_words = NULL;
    f_words = (char*)malloc((strlen(line) + 1) * sizeof(char));
    int contain = 0;
    char deleminators[] = " -,.!?\t/;:\n\0";
    int cur_len = 0;
    int cursor = 0;
    for (int i = 0; i < strlen(line); ++i) {
        contain = 0;
        for (int j = 0; j < strlen(deleminators); ++j) {
            if (deleminators[j] == line[i]) {
                contain = 1;
                break;
            }
            if (j == strlen(deleminators) - 1)
                cur_len += 1;
        }
        if ((cur_len > 0) && ((contain == 1) || (i == strlen(line) - 1))) {
            if (cur_len == length) {
                if (i == strlen(line) - 1)
                    for (int j = i - cur_len ; j <= i; ++j) {
                        contain = 0;
                        for (int k = 0; k < strlen(deleminators); k++)
                        {
                            if (deleminators[k] == line[j]) {
                                contain = 1;
                                break;
                            }
                        }
                        if (contain == 0)
                        {
                            f_words[cursor] = line[j];
                            cursor += 1;
                            printf("%c", line[j]);
                        }
                    }
                else
                    for (int j = i - cur_len; j < i; ++j) {
                        f_words[cursor] = line[j];
                        cursor += 1;
                        printf("%c", line[j]);
                    }
                f_words[cursor] = ' ';
                cursor += 1;
                printf("%s", "\n");
            }
            cur_len = 0;
        }
    }
    f_words[cursor] = '\0';
    return f_words;
}


void clean_stdin()
{
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int size = -10;
    int length = -10;
    int ended = 0;
    char* line = NULL;
    printf("%s", "Enter size of the string\n");
    while (size < 1) {
        if ((scanf("%d", &size) != 1) || (size < 1)) {
            printf("%s", "Uncorrect value (size => 0)\n");
            size = -10;
        }
        clean_stdin();
    }
    line = (char*)malloc((size + 1) * sizeof(char));
    printf("%s", "Enter string\n");
    for (int i = 0; i < size + 1; i++) {
        line[i] = getchar();
        if (i == 0)
            printf("%s", "For the your size value the string will look like: ");
        if (line[i] == '\n') {
            line[i] = '\0';
            ended = 1;
            break;
        }
        else if (i == size)
            line[i] = '\0';
        else
            printf("%c", line[i]);
    }
    if (ended == 0)
        clean_stdin();
    while (length < 1) {
        printf("\nEnter length for which the words will be print\n");
        if ((scanf("%d", &length) != 1) || (length < 1)) {
            printf("%s", "Uncorrect value (lenght>0)\n");
        }
        clean_stdin();
    }
    find_words(line, length);
    free(line);
    return 0;
}
