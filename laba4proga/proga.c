#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

void capitalize_words(FILE *input, FILE *output) {
    wint_t ch;
    int is_new_word = 1;

    while ((ch = fgetwc(input)) != WEOF) {
        if (iswalpha(ch) && is_new_word) {
            fputwc(towupper(ch), output);
            is_new_word = 0;
        } else {
            fputwc(ch, output);
        }

        if (iswspace(ch)) {
            is_new_word = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc != 2) {
        fwprintf(stderr, L"используется: %s <входной_файл>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "r, ccs=UTF-8");
    if (!input) {
        perror("ошибка открытия входного файла");
        return EXIT_FAILURE;
    }

    FILE *output = fopen("output.txt", "w, ccs=UTF-8");
    if (!output) {
        perror("так называем error)) создания выходного файла");
        fclose(input);
        return EXIT_FAILURE;
    }

    capitalize_words(input, output);

    fclose(input);
    fclose(output);

    wprintf(L"обработка завершена с хайпом. все записано в 'output.txt'\n");
    return EXIT_SUCCESS;
}