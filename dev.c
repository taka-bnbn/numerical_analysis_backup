#include <stdio.h>
#include <ctype.h>

typedef struct {
    char letter;
    int frequency;
} LetterFrequency;

int main() {
    char kazu[1000];
    int count[26] = {0}; // アルファベットの出現回数を記録する配列
    FILE *fp, *f;
    int total_chars = 0; // 読み込んだ文字の総数

    // ファイルを読み込み用に開く
    f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    // ファイルを1行ずつ読み込む
    while (fgets(kazu, sizeof(kazu), f) != NULL && total_chars < 10000) {
        for (int i = 0; kazu[i] != '\0' && total_chars < 10000; i++) {
            if (isalpha(kazu[i])) { // アルファベットかどうかチェック
                char ch = tolower(kazu[i]); // 小文字に変換
                count[ch - 'a']++;
                total_chars++;
            }
        }
    }
    fclose(f);

    // アルファベットと頻度のペアを作成
    LetterFrequency frequencies[26];
    for (int i = 0; i < 26; i++) {
        frequencies[i].letter = 'a' + i;
        frequencies[i].frequency = count[i];
    }

    // 頻度に基づいて降順に並び替え
    for (int i = 0; i < 26 - 1; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (frequencies[i].frequency < frequencies[j].frequency) {
                LetterFrequency temp = frequencies[i];
                frequencies[i] = frequencies[j];
                frequencies[j] = temp;
            }
        }
    }

    // 結果を表示
    printf("使用頻度（降順）:\n");
    for (int i = 0; i < 26; i++) {
        if (frequencies[i].frequency > 0) { // 0回のものは表示しない
            printf("%c: %d\n", frequencies[i].letter, frequencies[i].frequency);
        }
    }

    // 結果をファイルに書き込み
    fp = fopen("count.txt", "w");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        if (frequencies[i].frequency > 0) {
            fprintf(fp, "%c: %d\n", frequencies[i].letter, frequencies[i].frequency);
        }
    }

    fclose(fp);
    return 0;
}

