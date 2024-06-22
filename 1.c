#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], int k);
void decrypt(char text[], int k);

int main() {
    char text[100];
    int k;

    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 

    printf("Enter the key (1-25): ");
    scanf("%d", &k);

    if (k < 1 || k > 25) {
        printf("Invalid key! Key must be in the range 1-25.\n");
        return 1;
    }

    encrypt(text, k);
    printf("Encrypted message: %s\n", text);

    decrypt(text, k);
    printf("Decrypted message: %s\n", text);

    return 0;
}

void encrypt(char text[], int k) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + k) % 26 + base;
        }
    }
}

void decrypt(char text[], int k) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base - k + 26) % 26 + base;
        }
    }
}
