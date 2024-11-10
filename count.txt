#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TEXT 100000   // テキスト全体の最大長
#define MAX_PAIRS 10000   // 2文字組の最大数
#define MAX_TRIPLETS 10000 // 3文字組の最大数
#define MAX_OUTPUT 100    // ランダムに生成する文字の最大個数

typedef struct {
    char pair[3];   // 2文字のペア
    int frequency;  // 出現頻度
} PairFrequency;

typedef struct {
    char triplet[4]; // 3文字のトリプレット
    int frequency;   // 出現頻度
} TripletFrequency;

int main() {
    char *text = (char *)malloc(MAX_TEXT * sizeof(char));
    if (text == NULL) {
        printf("メモリの確保に失敗しました。\n");
        return 1;
    }

    int total_chars = 0;
    FILE *fp;
    PairFrequency pairs[MAX_PAIRS];
    TripletFrequency triplets[MAX_TRIPLETS];
    int pair_count = 0, triplet_count = 0;

    // ファイルを読み込み用に開く
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        free(text);
        return 1;
    }

    // ファイル全体を読み込み、アルファベットと空白のみを保持
    char ch;
    int index = 0;
    while ((ch = fgetc(fp)) != EOF && index < MAX_TEXT - 1) {
        if (isalpha(ch) || ch == ' ') {
            text[index++] = tolower(ch);
        }
    }
    text[index] = '\0';
    fclose(fp);
    total_chars = index;

    // 2文字ペアの出現頻度をカウント
    for (int i = 0; i < total_chars - 1; i++) {
        if (pair_count >= MAX_PAIRS) break;
        char pair[3] = {text[i], text[i + 1], '\0'};
        int found = 0;
        for (int j = 0; j < pair_count; j++) {
            if (strcmp(pairs[j].pair, pair) == 0) {
                pairs[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found && pair_count < MAX_PAIRS) {
            strcpy(pairs[pair_count].pair, pair);
            pairs[pair_count].frequency = 1;
            pair_count++;
        }
    }

    // 3文字トリプレットの出現頻度をカウント
    for (int i = 0; i < total_chars - 2; i++) {
        if (triplet_count >= MAX_TRIPLETS) break;
        char triplet[4] = {text[i], text[i + 1], text[i + 2], '\0'};
        int found = 0;
        for (int j = 0; j < triplet_count; j++) {
            if (strcmp(triplets[j].triplet, triplet) == 0) {
                triplets[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found && triplet_count < MAX_TRIPLETS) {
            strcpy(triplets[triplet_count].triplet, triplet);
            triplets[triplet_count].frequency = 1;
            triplet_count++;
        }
    }

    // 乱数の初期化
    srand((unsigned int)time(NULL));

    // ランダムに生成する文字列
    char random_text[MAX_OUTPUT + 1];
    int current_index = 0;

    // 初期トリプレットをランダムに選ぶ
    int start = rand() % triplet_count;
    strcpy(random_text, triplets[start].triplet);
    current_index = 3;

    // 次の文字を繰り返し決定して文字列を生成
    while (current_index < MAX_OUTPUT) {
        char prev1 = random_text[current_index - 2];
        char prev2 = random_text[current_index - 1];
        char next_char = '\0';

        // 次のトリプレットを探索
        int found_next = 0;
        for (int i = 0; i < triplet_count; i++) {
            if (triplets[i].triplet[0] == prev1 && triplets[i].triplet[1] == prev2) {
                // 次に続く文字を決定
                next_char = triplets[i].triplet[2];
                found_next = 1;
                break;
            }
        }

        if (found_next) {
            random_text[current_index++] = next_char;
        } else {
            // 次のトリプレットが見つからない場合はランダムに2文字のペアを選び直す
            int new_start = rand() % triplet_count;
            strcpy(random_text + current_index - 2, triplets[new_start].triplet);
            current_index = 3;
        }
    }

    random_text[current_index] = '\0'; // 終端文字

    // 結果をcount.txtに出力
    fp = fopen("count.txt", "w");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        free(text);
        return 1;
    }
    fprintf(fp, "ランダムに生成された文字列:\n%s\n", random_text);
    fclose(fp);

    printf("結果が count.txt に出力されました。\n");

    // メモリ解放
    free(text);

    return 0;
}

