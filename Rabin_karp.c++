#include <stdio.h>
#include <string.h>
#define CHAR_RANGE 256
#define PRIME 101

void rabinKarpSearch(const char *text, const char *pattern) {
    int textLen = strlen(text);
    int patternLen = strlen(pattern);
    int patternHash = 0;
    int textHash = 0;
    int hashMultiplier = 1;
    for (int i = 0; i < patternLen - 1; i++) {
        hashMultiplier = (hashMultiplier * CHAR_RANGE) % PRIME;
    }
    for (int i = 0; i < patternLen; i++) {
        patternHash = (CHAR_RANGE * patternHash + pattern[i]) % PRIME;
        textHash = (CHAR_RANGE * textHash + text[i]) % PRIME;
    }
    for (int i = 0; i <= textLen - patternLen; i++) {
        if (patternHash == textHash) {
            int j;
            for (j = 0; j < patternLen; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == patternLen) {
                printf("Pattern found at index %d\n", i);
            }
        }
        if (i < textLen - patternLen) {
            textHash = (CHAR_RANGE * (textHash - text[i] * hashMultiplier) + text[i + patternLen]) % PRIME;
            if (textHash < 0) {
                textHash += PRIME;
            }
        }
    }
}

int main() {
    char text[100], pattern[100];
    printf("Enter the text: ");
    scanf("%99s", text);

    printf("Enter the pattern: ");
    scanf("%99s", pattern);

    rabinKarpSearch(text, pattern);
    return 0;
}
