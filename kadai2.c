#include <stdio.h>
#include <ctype.h>

typedef struct {
    char hitomoji;
    int hindo;
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
            }}}

    fclose(f);

    LetterFrequency frequencies[26];
    for (int i = 0; i < 26; i++) {
        frequencies[i].hitomoji = 'a' + i;
        frequencies[i].hindo = count[i];}

    for (int i = 0; i < 26 - 1; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (frequencies[i].hindo < frequencies[j].hindo) {
                LetterFrequency temp = frequencies[i];
                frequencies[i] = frequencies[j];
                frequencies[j] = temp;
            }}}
    fp = fopen("count.txt", "w");
    for (int i = 0; i < 26; i++) {
        fprintf(fp, "%c: %d\n", frequencies[i].hitomoji, frequencies[i].hindo);}
    fclose(fp);
    return 0;
}

