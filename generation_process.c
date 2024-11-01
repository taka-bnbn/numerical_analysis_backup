#include <stdio.h>
#include <ctype.h>

int main() {
    char buffer[1000];  // 一時的にデータを読み込むバッファ
    int count[26] = {0}; // 各アルファベットの出現回数を記録する配列
    FILE *fp, *f;
    int total_chars = 0; // 読み込んだ文字の総数

    // "data.txt" を開いて入力を読み込み
    f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("data.txt を開けませんでした。\n");
        return 1;
    }

    // ファイルから複数行にわたってデータを読み込む
    while (fgets(buffer, sizeof(buffer), f) != NULL && total_chars < 10000) {
        for (int i = 0; buffer[i] != '\0' && total_chars < 10000; i++) {
            if (isalpha(buffer[i])) { // アルファベットかどうかチェック
                char ch = tolower(buffer[i]); // 小文字に変換
                count[ch - 'a']++;
                total_chars++;
            }
        }
    }
    fclose(f);

    // 結果を表示
    printf("アルファベットの使用頻度:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, count[i]);
    }

    // 結果を "count.txt" に書き込み
    fp = fopen("count.txt", "w");
    if (fp == NULL) {
        printf("count.txt を開けませんでした。\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        fprintf(fp, "%c: %d\n", 'a' + i, count[i]);
    }

    fclose(fp);
    return 0;
}

