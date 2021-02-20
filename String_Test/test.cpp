#include "pch.h"
//#include "../Practise/Practise/Source.h"

char* find_words(char* line, int length)
{
    char* f_words = NULL;
    f_words = (char*)malloc((strlen(line) + 1) * sizeof(char));
    int contain = 0;
    char deleminators[] = " -,.!?\t/;':\n\0";
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
                    for (int j = i - cur_len; j <= i; ++j) {
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
                        }
                    }
                else
                    for (int j = i - cur_len; j < i; ++j) {
                        f_words[cursor] = line[j];
                        cursor += 1;
                    }
                f_words[cursor] = ' ';
                cursor += 1;
            }
            cur_len = 0;
        }
    }
    f_words[cursor] = '\0';
    return f_words;
}



TEST(TestFunc, Auto_Test) {
    int kol = 0;
    while (kol < 10000) {
        srand(time(NULL));
        int new_word;
        int rand_num;
        int rnd_det;
        int det_length;
        char ascii;
        char deleminators[] = " -,.!?\t/;:\n";
        char testline[1000] = { 0 };
        char waited[1000] = { 0 };
        int waited_cursor = 0;
        int testline_cursor = 0;
        int length = rand() % 10 + 1;
        for (int i = 0; i < 50; i++)
        {
            new_word = rand() % 10 + 1;
            det_length = rand() % 3 + 1;
            for (int j = 0; j < new_word; j++)
            {
                rand_num = rand() % 26 + 65;
                ascii = (char)rand_num;
                testline[testline_cursor] = ascii;
                testline_cursor += 1;
                if (new_word == length) {
                    waited[waited_cursor] = ascii;
                    waited_cursor += 1;
                }
            }
            for (int j = 0; j < det_length; j++)
            {
                rnd_det = rand() % (strlen(deleminators));
                testline[testline_cursor] = deleminators[rnd_det];
                testline_cursor += 1;
            }
            if (new_word == length) {
                waited[waited_cursor] = ' ';
                waited_cursor += 1;
            }
        }
        ASSERT_STREQ(find_words(testline, length), waited);
        kol += 1;
    }
}

TEST(TestFunc, Empty_string) {
    char testline[] = "";
    for (int i = 0; i < 5; i++)
    {
        ASSERT_STREQ(find_words(testline, i), "");
    }
}

TEST(TestFunc, words_not_found) {
    char testline[] = "qwerty qwert qwer qwe qw q";
    ASSERT_STREQ(find_words(testline, 7), ""); //в строке нет слов из 7-ми символов
}

TEST(TestFunc, different_determ) {
    char testline[] = " da dj  /daw ./ga/g.. a/s. .g e/a aw,a /wa/ ;'a' .a .g.ae d.wa'g  .es 'a.f. awd. dad' .aw daw a, .a. .. .a/. '";
    ASSERT_STREQ(find_words(testline, 1), "g a s g e a a a a g d g a f a a a "); 
}