#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *yomikomiFile, *kakidasiFile; // ファイルポインタの宣言
    char c; // 1文字を格納する変数

    yomikomiFile = fopen("data.txt", "r");
    kakidasiFile = fopen("count.txt", "w");

    while ((c = fgetc(yomikomiFile)) != EOF) {
        if (isalpha(c) || c == ' ' || c == '\n') {
            fputc(c, kakidasiFile);}
       	else 
	{
            fputc(' ', kakidasiFile);}}

    fclose(yomikomiFile);
    fclose(kakidasiFile);

    return 0;
}

