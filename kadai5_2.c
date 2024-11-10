#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 100000
#define GENERATED_SIZE 10000

int main() {
    char text[MAX_TEXT_SIZE];
    FILE *fp;
    int total_chars = 0;

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
    char generated[GENERATED_SIZE];
    int generated_index = 0;

    // 最初の三ッ組（k 番目, k+1 番目, k+2 番目）を選択
    int k = rand() % (total_chars - 2); // k 番目の文字
    generated[generated_index++] = text[k];
    generated[generated_index++] = text[k + 1];
    generated[generated_index++] = text[k + 2];

    // ランダムに次の三ッ組を選ぶ
    while (generated_index < GENERATED_SIZE - 3) {  // 10,000文字未満で繰り返す
        // 最後に選んだ三ッ組の最初の文字 A を取得
        char A = generated[generated_index - 2]; 

        // 再び乱数で k' を得る
        int next_k = rand() % total_chars; 

        // k' 番目の文字から A が現れる位置を探す
        int found = 0;
        for (int i = next_k; i < total_chars - 2; i++) {
            if (text[i] == A) {
                // A の後に続く三ッ組を選ぶ
                generated[generated_index++] = text[i + 1];
                generated[generated_index++] = text[i + 2];
                found = 1;
                break;
            }
        }

        // 次の三ッ組が見つからなかった場合は終了
        if (!found) {
            break;
        }
    }

    // 結果を表示
    generated[generated_index] = '\0';  // 終端文字を追加
    printf("生成された三ッ組の文字列: \n%s\n", generated);

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

