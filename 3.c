#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int i, j, k = 0;
    int keyLen = strlen(key);
    int used[26] = {0};
    char processedKey[26];
    int processedKeyLen = 0;
    for (i = 0; i < keyLen; i++) {
        if (key[i] == 'j') {
            key[i] = 'i';
        }
        key[i] = toupper(key[i]);
        if (!used[key[i] - 'A'] && key[i] != 'J') {
            used[key[i] - 'A'] = 1;
            processedKey[processedKeyLen++] = key[i];
        }
    }
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (k < processedKeyLen) {
                matrix[i][j] = processedKey[k++];
            } else {
                break;
            }
        }
    }
    for (i = 0; i < 26; i++) {
        if (used[i] == 0 && 'A' + i != 'J') {
            matrix[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}

void printMatrix(char matrix[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}
void processPlaintext(char plaintext[], char processedText[]) {
    int i, j = 0;
    int len = strlen(plaintext);
    for (i = 0; i < len; i++) {
        if (plaintext[i] == 'j') {
            plaintext[i] = 'i';
        }
        plaintext[i] = toupper(plaintext[i]);
        if (isalpha(plaintext[i])) {
            processedText[j++] = plaintext[i];
        }
    }
    processedText[j] = '\0';
    for (i = 0; i < j - 1; i += 2) {
        if (processedText[i] == processedText[i + 1]) {
            memmove(processedText + i + 2, processedText + i + 1, j - i);
            processedText[i + 1] = 'X';
            j++;
        }
    }
    if (j % 2 != 0) {
        processedText[j++] = 'X';
    }
    processedText[j] = '\0';
}

void findPosition(char matrix[SIZE][SIZE], char letter, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char matrix[SIZE][SIZE], char plaintext[], char ciphertext[]) {
    int i, row1, col1, row2, col2;
    int len = strlen(plaintext);
    for (i = 0; i < len; i += 2) {
        findPosition(matrix, plaintext[i], &row1, &col1);
        findPosition(matrix, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
            // Same row
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            // Same column
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            // Rectangle
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char key[26];
    char plaintext[100];
    char processedText[100];
    char ciphertext[100];
    char matrix[SIZE][SIZE];

    printf("Enter the key: ");
    scanf("%25s", key);

    printf("Enter the plaintext: ");
    scanf("%99s", plaintext);

    createMatrix(key, matrix);
    printf("\nPlayfair Matrix:\n");
    printMatrix(matrix);

    processPlaintext(plaintext, processedText);
    printf("\nProcessed Plaintext: %s\n", processedText);

    encrypt(matrix, processedText, ciphertext);
    printf("\nCiphertext: %s\n", ciphertext);

    return 0;
}