#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_OUTPUT 100 // ランダムに生成する文字の最大個数
#define MAX_PAIRS 10000

typedef struct {
    char pair[3];
    int frequency;
} PairFrequency;

int main() {
    char text[10000];
    int total_chars = 0;
    FILE *fp;
    PairFrequency pairs[MAX_PAIRS];
    int pair_count = 0;

    // ファイルを読み込み用に開く
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    // ファイル全体を読み込む
    char ch;
    int index = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (isalpha(ch) || ch == ' ') { // アルファベットか空白のみ
            text[index++] = tolower(ch);
        }
    }
    text[index] = '\0'; // 文字列の終端
    fclose(fp);
    total_chars = index;

    // 連続する二文字のペアをカウント
    for (int i = 0; i < total_chars - 1; i++) {
        char pair[3] = {text[i], text[i + 1], '\0'};
        int found = 0;
        for (int j = 0; j < pair_count; j++) {
            if (strcmp(pairs[j].pair, pair) == 0) {
                pairs[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(pairs[pair_count].pair, pair);
            pairs[pair_count].frequency = 1;
            pair_count++;
        }
    }

    // 累積分布を作成
    int cumulative[MAX_PAIRS];
    cumulative[0] = pairs[0].frequency;
    for (int i = 1; i < pair_count; i++) {
        cumulative[i] = cumulative[i - 1] + pairs[i].frequency;
    }

    // 全ペアの出現数
    int M = cumulative[pair_count - 1];

    // 乱数の初期化
    srand((unsigned int)time(NULL));

    // ランダムに二文字ペアを選択
    char random_text[MAX_OUTPUT + 1];
    int current_index = 0;

    // 最初のペアをランダムに選ぶ
    int k = rand() % M;
    for (int i = 0; i < pair_count; i++) {
        if (k < cumulative[i]) {
            random_text[0] = pairs[i].pair[0];
            random_text[1] = pairs[i].pair[1];
            current_index = 2;
            break;
        }
    }

    // 次の文字を繰り返し決定して文字列を生成
    while (current_index < MAX_OUTPUT) {
        char last_char = random_text[current_index - 1];

        // 次のペアを探す
        int found_pair = 0;
        for (int i = 0; i < pair_count; i++) {
            if (pairs[i].pair[0] == last_char) {
                random_text[current_index] = pairs[i].pair[1];
                current_index++;
                found_pair = 1;
                break;
            }
        }

        // ペアが見つからない場合は終了
        if (!found_pair) {
            break;
        }
    }

    random_text[current_index] = '\0'; // 終端文字

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

