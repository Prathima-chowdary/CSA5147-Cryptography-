#include <stdio.h>
#include <string.h>
#include <ctype.h>

char key[5][5] = {
    {'P', 'L', 'A', 'Y', 'F'},
    {'I', 'R', 'E', 'X', 'M'},
    {'B', 'C', 'D', 'G', 'H'},
    {'K', 'N', 'O', 'Q', 'S'},
    {'T', 'U', 'V', 'W', 'Z'}
};

void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (key[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decodePair(char ch1, char ch2, char *decodedPair) {
    int row1, col1, row2, col2;
    findPosition(ch1, &row1, &col1);
    findPosition(ch2, &row2, &col2);

    if (row1 == row2) {
        decodedPair[0] = key[row1][(col1 + 4) % 5];
        decodedPair[1] = key[row2][(col2 + 4) % 5];
    } else if (col1 == col2) {
        decodedPair[0] = key[(row1 + 4) % 5][col1];
        decodedPair[1] = key[(row2 + 4) % 5][col2];
    } else {
        decodedPair[0] = key[row1][col2];
        decodedPair[1] = key[row2][col1];
    }
}

void decodeMessage(const char *cipherText, char *decodedMessage) {
    int length = strlen(cipherText);
    int decodedIndex = 0;
    for (int i = 0; i < length; i += 2) {
        if (isalpha(cipherText[i]) && isalpha(cipherText[i + 1])) {
            char decodedPair[2];
            decodePair(toupper(cipherText[i]), toupper(cipherText[i + 1]), decodedPair);
            decodedMessage[decodedIndex++] = decodedPair[0];
            decodedMessage[decodedIndex++] = decodedPair[1];
        }
    }
    decodedMessage[decodedIndex] = '\0';
}

int main() {
    char cipherText[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    char decodedMessage[256];

    char cipherTextNoSpaces[256];
    int j = 0;
    for (int i = 0; i < strlen(cipherText); i++) {
        if (isalpha(cipherText[i])) {
            cipherTextNoSpaces[j++] = cipherText[i];
        }
    }
    cipherTextNoSpaces[j] = '\0';

    decodeMessage(cipherTextNoSpaces, decodedMessage);

    printf("Decoded Message: %s\n", decodedMessage);

    return 0;
}
