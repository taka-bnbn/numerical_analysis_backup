#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *inputFile, *outputFile; // ファイルポインタの宣言
    char c; // 1文字を格納する変数

    inputFile = fopen("data.txt", "r");
    outputFile = fopen("count.txt", "w");

    while ((c = fgetc(inputFile)) != EOF) {
        if (isalpha(c) || c == ' ' || c == '\n') {
            fputc(c, outputFile);
        } else {
            fputc(' ', outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

