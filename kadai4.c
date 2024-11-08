#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_OUTPUT 100 // ランダムに生成する文字の最大個数

int main() {
    FILE *fp;
    char text[10000]; // テキストファイルから読み込むための配列
    int total_chars = 0; // テキスト内の文字数
    char random_text[MAX_OUTPUT + 1]; // 生成するランダム文字列（終端文字含む）

    // ファイルを読み込み用に開く
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    // ファイル全体を読み込み、アルファベットのみをカウント
    char ch;
    while ((ch = fgetc(fp)) != EOF && total_chars < sizeof(text) - 1) {
        // アルファベットのみを保持し、他の文字は無視
        if (isalpha(ch)) {
            text[total_chars++] = tolower(ch); // 小文字に変換して格納
        }
    }
    text[total_chars] = '\0'; // 終端文字を追加
    fclose(fp);

    // テキスト内の有効な文字数 M を表示
    printf("ファイル内の有効な文字数: %d\n", total_chars);

    // 乱数の初期化
    srand((unsigned int)time(NULL));

    // ランダムな文字列を生成
    for (int i = 0; i < MAX_OUTPUT; i++) {
        // 0から total_chars - 1 の範囲で乱数を生成
        int k = rand() % total_chars;
        random_text[i] = text[k]; // k番目の文字を取得
    }
    random_text[MAX_OUTPUT] = '\0'; // 終端文字を追加

    // 結果を表示
    printf("ランダムに生成された文字列:\n%s\n", random_text);

    // 結果を count.txt に書き込み
    fp = fopen("count.txt", "w");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    fprintf(fp, "ファイル内の有効な文字数: %d\n", total_chars);
    fprintf(fp, "ランダムに生成された文字列:\n%s\n", random_text);
    fclose(fp);

    printf("結果が count.txt に出力されました。\n");

    return 0;
}

