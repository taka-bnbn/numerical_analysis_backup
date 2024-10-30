#include <stdio.h>
#include <ctype.h>

int main() {
    char str[1000];
    int count[26] = {0}; // 各アルファベットの出現回数を記録する配列

    // ユーザー入力
    printf("文字列を入力してください: ");
    fgets(str, sizeof(str), stdin);

    // 文字列内の各文字について処理
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) { // アルファベットかどうかチェック
            char ch = tolower(str[i]); // 小文字に変換
            count[ch - 'a']++; // 該当する位置にカウントを加算
        }
    }

    // 結果を表示
    printf("アルファベットの使用頻度:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, count[i]);
    }

    return 0;
}






