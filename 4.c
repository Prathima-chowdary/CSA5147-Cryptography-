#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    char *extendedKey = malloc(textLen + 1);

    for (int i = 0; i < textLen; i++) {
        extendedKey[i] = key[i % keyLen];
    }
    extendedKey[textLen] = '\0';

    for (int i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            char keyOffset = isupper(extendedKey[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - offset) + (extendedKey[i] - keyOffset)) % 26 + offset;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[textLen] = '\0';

    free(extendedKey);
}

void decrypt(char *ciphertext, char *key, char *plaintext) {
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);
    char *extendedKey = malloc(textLen + 1);

    for (int i = 0; i < textLen; i++) {
        extendedKey[i] = key[i % keyLen];
    }
    extendedKey[textLen] = '\0';

    for (int i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyOffset = isupper(extendedKey[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - offset) - (extendedKey[i] - keyOffset) + 26) % 26 + offset;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[textLen] = '\0';

    free(extendedKey);
}

int main() {
    char plaintext[256], key[256], ciphertext[256];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    char decryptedText[256];
    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}
