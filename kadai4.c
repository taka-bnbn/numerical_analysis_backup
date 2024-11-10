#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_OUTPUT 100 // ランダムに生成する文字の最大個数

typedef struct {
    char character;
    int frequency;
} CharFrequency;

int main() {
    char text[10000];
    int count[27] = {0}; // アルファベット26文字 + 空白の出現回数
    int total_chars = 0; // 有効な文字の総数
    FILE *fp;

    // ファイルを読み込み用に開く
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    // ファイルからアルファベットと空白を読み込み、出現回数をカウント
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (isalpha(ch) || ch == ' ') { // アルファベットまたは空白をチェック
            if (isalpha(ch)) {
                ch = tolower(ch); // 小文字に変換
                count[ch - 'a']++;
            } else if (ch == ' ') {
                count[26]++; // 空白のカウント
            }
            total_chars++;
        }
    }
    fclose(fp);

    // 出現頻度に基づいた文字と確率リストを作成
    CharFrequency frequencies[27];
    for (int i = 0; i < 26; i++) {
        frequencies[i].character = 'a' + i;
        frequencies[i].frequency = count[i];
    }
    frequencies[26].character = ' '; // 空白
    frequencies[26].frequency = count[26];

    // 各文字の累積頻度を計算（累積分布表を作成）
    int cumulative[27];
    cumulative[0] = frequencies[0].frequency;
    for (int i = 1; i < 27; i++) {
        cumulative[i] = cumulative[i - 1] + frequencies[i].frequency;
    }

    // 全文字の出現数（total_chars）を元に累積確率の範囲を設定
    int M = cumulative[26]; // 全ての文字の合計数

    // 乱数の初期化
    srand((unsigned int)time(NULL));

    // ランダムな文字列を生成
    char random_text[MAX_OUTPUT + 1];
    for (int i = 0; i < MAX_OUTPUT; i++) {
        int k = rand() % M; // 0からM-1の範囲で乱数を生成

        // kの値に基づいて累積分布から文字を選択
        for (int j = 0; j < 27; j++) {
            if (k < cumulative[j]) {
                random_text[i] = frequencies[j].character;
                break;
            }
        }
    }
    random_text[MAX_OUTPUT] = '\0'; // 終端文字を追加

    // 結果を count.txt に出力
    fp = fopen("count.txt", "w");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }
    fprintf(fp, "ランダムに生成された文字列:\n%s\n", random_text);
    fclose(fp);

    printf("結果が count.txt に出力されました。\n");

    return 0;
}

