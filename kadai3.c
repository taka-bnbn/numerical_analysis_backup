#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_BI 1000
#define MAX_TRI 1000

typedef struct {
    char pair[3]; // 2文字組（バイグラム）のための配列
    int frequency;
} Bigram;

typedef struct {
    char triplet[4]; // 3文字組（トライグラム）のための配列
    int frequency;
} Trigram;

// バイグラムとトライグラムのカウント関数
void count_bigrams(char *text, Bigram bigrams[], int *bigram_count);
void count_trigrams(char *text, Trigram trigrams[], int *trigram_count);

// 頻度に基づいてソート関数
void sort_bigrams(Bigram bigrams[], int bigram_count);
void sort_trigrams(Trigram trigrams[], int trigram_count);

int main() {
    char kazu[1000];
    char text[10000] = ""; // 読み込んだ全テキスト
    FILE *fp, *f;

    // ファイルを読み込み用に開く
    f = fopen("data.txt", "r");

    // ファイルから全テキストを読み込む
    while (fgets(kazu, sizeof(kazu), f) != NULL) {
        strcat(text, kazu);
    }
    fclose(f);

    Bigram bigrams[MAX_BI];
    Trigram trigrams[MAX_TRI];
    int bigram_count = 0, trigram_count = 0;

    // バイグラムとトライグラムのカウント
    count_bigrams(text, bigrams, &bigram_count);
    count_trigrams(text, trigrams, &trigram_count);

    // ソート
    sort_bigrams(bigrams, bigram_count);
    sort_trigrams(trigrams, trigram_count);

    // 結果を表示（上位20件）
    printf("頻度の高い2文字組:\n");
    for (int i = 0; i < 20 && i < bigram_count; i++) {
        printf("%s: %d\n", bigrams[i].pair, bigrams[i].frequency);
    }

    printf("\n頻度の高い3文字組:\n");
    for (int i = 0; i < 20 && i < trigram_count; i++) {
        printf("%s: %d\n", trigrams[i].triplet, trigrams[i].frequency);
    }

    // 結果をファイルに書き込み
    fp = fopen("count.txt", "w");

    fprintf(fp, "頻度の高い2文字組:\n");
    for (int i = 0; i < 20 && i < bigram_count; i++) {
        fprintf(fp, "%s: %d\n", bigrams[i].pair, bigrams[i].frequency);
    }

    fprintf(fp, "\n頻度の高い3文字組:\n");
    for (int i = 0; i < 20 && i < trigram_count; i++) {
        fprintf(fp, "%s: %d\n", trigrams[i].triplet, trigrams[i].frequency);
    }

    fclose(fp);
    return 0;
}

// バイグラムをカウントする関数
void count_bigrams(char *text, Bigram bigrams[], int *bigram_count) {
    int len = strlen(text);
    for (int i = 0; i < len - 1; i++) {
        if (isalpha(text[i]) && isalpha(text[i + 1])) {
            char pair[3] = {tolower(text[i]), tolower(text[i + 1]), '\0'};
            
            int found = 0;
            for (int j = 0; j < *bigram_count; j++) {
                if (strcmp(bigrams[j].pair, pair) == 0) {
                    bigrams[j].frequency++;
                    found = 1;
                    break;
                }
            }
            if (!found && *bigram_count < MAX_BI) {
                strcpy(bigrams[*bigram_count].pair, pair);
                bigrams[*bigram_count].frequency = 1;
                (*bigram_count)++;
            }
        }
    }
}

// トライグラムをカウントする関数
void count_trigrams(char *text, Trigram trigrams[], int *trigram_count) {
    int len = strlen(text);
    for (int i = 0; i < len - 2; i++) {
        if (isalpha(text[i]) && isalpha(text[i + 1]) && isalpha(text[i + 2])) {
            char triplet[4] = {tolower(text[i]), tolower(text[i + 1]), tolower(text[i + 2]), '\0'};
            
            int found = 0;
            for (int j = 0; j < *trigram_count; j++) {
                if (strcmp(trigrams[j].triplet, triplet) == 0) {
                    trigrams[j].frequency++;
                    found = 1;
                    break;
                }
            }
            if (!found && *trigram_count < MAX_TRI) {
                strcpy(trigrams[*trigram_count].triplet, triplet);
                trigrams[*trigram_count].frequency = 1;
                (*trigram_count)++;
            }
        }
    }
}

// バイグラムのソート関数
void sort_bigrams(Bigram bigrams[], int bigram_count) {
    for (int i = 0; i < bigram_count - 1; i++) {
        for (int j = i + 1; j < bigram_count; j++) {
            if (bigrams[i].frequency < bigrams[j].frequency) {
                Bigram temp = bigrams[i];
                bigrams[i] = bigrams[j];
                bigrams[j] = temp;
            }
        }
    }
}

// トライグラムのソート関数
void sort_trigrams(Trigram trigrams[], int trigram_count) {
    for (int i = 0; i < trigram_count - 1; i++) {
        for (int j = i + 1; j < trigram_count; j++) {
            if (trigrams[i].frequency < trigrams[j].frequency) {
                Trigram temp = trigrams[i];
                trigrams[i] = trigrams[j];
                trigrams[j] = temp;
            }
        }
    }
}

