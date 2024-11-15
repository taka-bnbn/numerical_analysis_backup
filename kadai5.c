#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 100000

int main() {
    char text[MAX_TEXT_SIZE];
    FILE *fp;
    int total_chars = 0;
    int M = 0;

    // ファイルを読み込み用に開く
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    // テキスト全体を読み込み
    char ch;
    int i = 0;
    while ((ch = fgetc(fp)) != EOF && i < MAX_TEXT_SIZE - 1) {
        if (isalpha(ch) || ch == ' ') { // アルファベットと空白だけを読み込む
            text[i++] = tolower(ch);  // 小文字に変換して格納
        }
    }
    text[i] = '\0'; // 終端文字を追加
    total_chars = i;

    fclose(fp);

    // 乱数の初期化
    srand((unsigned int)time(NULL));

    // ランダムに文字列を生成
    char generated[MAX_TEXT_SIZE];
    int generated_index = 0;

    // 最初のペア（k 番目と k+1 番目）を選択
    int k = rand() % (total_chars - 1); // k 番目の文字
    generated[generated_index++] = text[k];
    generated[generated_index++] = text[k + 1];

    // 乱数により次の文字を選ぶ
    for (int j = 0; generated_index < total_chars && generated_index < 100; j++) {  // 100文字まで生成
        char A = generated[generated_index - 1]; // 最後に選んだ文字 A
        int next_k = rand() % total_chars; // k′ 番目の文字

        // k′ 番目の文字から A が現れる位置を探す
        int found = 0;
        for (int i = next_k; i < total_chars - 1; i++) {
            if (text[i] == A) {
                // A の後に続く文字を選ぶ
                generated[generated_index++] = text[i + 1];
                found = 1;
                break;
            }
        }

        // 次の文字が見つからなかった場合は終了
        if (!found) {
            break;
        }
    }

    // 結果を表示
    generated[generated_index] = '\0';  // 終端文字を追加
    printf("生成された文字列: \n%s\n", generated);

    // 結果をcount.txtに出力
    fp = fopen("count.txt", "w");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    fprintf(fp, "%s", generated);
    fclose(fp);

    return 0;
}

