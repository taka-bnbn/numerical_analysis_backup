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
    int total_chars = 0;


    f = fopen("data.txt", "r");

    
    while (fgets(kazu, sizeof(kazu), f) != NULL && total_chars < 10000) {
        for (int i = 0; kazu[i] != '\0' && total_chars < 10000; i++) {
            if (isalpha(kazu[i])) { 
                char ch = tolower(kazu[i]);
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

    // 並び替え
    for (int i = 0; i < 26 - 1; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (frequencies[i].frequency < frequencies[j].frequency) {
                LetterFrequency temp = frequencies[i];
                frequencies[i] = frequencies[j];
                frequencies[j] = temp;
            }
        }
    }


    fp = fopen("count.txt", "w");

    for (int i = 0; i < 26; i++) {
        fprintf(fp, "%c: %d\n", frequencies[i].letter, frequencies[i].frequency);
    }

    fclose(fp);
    return 0;
}

