#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void remove_duplicates(char *str) {
    int index = 0;
    int len = strlen(str);
    int hash[256] = {0};
    
    for (int i = 0; i < len; i++) {
        if (!hash[(unsigned char)str[i]]) {
            str[index++] = str[i];
            hash[(unsigned char)str[i]] = 1;
        }
    }
    str[index] = '\0';
}

void generate_cipher_sequence(const char *keyword, char *cipher) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;
    int len = strlen(keyword);
    
    for (int i = 0; i < len; i++) {
        if (!used[toupper(keyword[i]) - 'A']) {
            cipher[index++] = toupper(keyword[i]);
            used[toupper(keyword[i]) - 'A'] = 1;
        }
    }
    
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipher[index++] = c;
        }
    }
    cipher[index] = '\0';
}

void encrypt(const char *plaintext, const char *cipher, char *ciphertext) {
    while (*plaintext) {
        if (isalpha(*plaintext)) {
            if (islower(*plaintext)) {
                *ciphertext = tolower(cipher[*plaintext - 'a']);
            } else {
                *ciphertext = cipher[*plaintext - 'A'];
            }
        } else {
            *ciphertext = *plaintext;
        }
        plaintext++;
        ciphertext++;
    }
    *ciphertext = '\0';
}

int main() {
    char keyword[100], plaintext[1000], ciphertext[1000];
    char cipher[ALPHABET_SIZE + 1];
    
    printf("Enter keyword: ");
    scanf("%s", keyword);
    
    remove_duplicates(keyword);
    
    generate_cipher_sequence(keyword, cipher);
    
    printf("Generated cipher sequence: %s\n", cipher);
    
    printf("Enter plaintext: ");
    scanf(" %[^\n]s", plaintext);
    
    encrypt(plaintext, cipher, ciphertext);
    
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}
