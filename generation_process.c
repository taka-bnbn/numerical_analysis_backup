#include <stdio.h>
#include <ctype.h>

int main() {
    char kazu[1000];  
    int count[26] = {0}; // アルファベットの出現回数を記録する配列
    FILE *fp, *f;
    int total_chars = 0; // 読み込んだ文字の総数

    
    f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("開けませんでした。\n");
        return 1;
    }

 
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

    
    printf("使用頻度:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, count[i]);
    }

    fp = fopen("count.txt", "w");
    if (fp == NULL) {
        printf("開けませんでした。\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        fprintf(fp, "%c: %d\n", 'a' + i, count[i]);
    }

    fclose(fp);
    return 0;
}

