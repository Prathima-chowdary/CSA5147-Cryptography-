#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void frequency_analysis(char *ciphertext, int num_top_plaintexts);

void decrypt_and_print(char *ciphertext, int shift);

int main() {
    char ciphertext[1000]; 
    int num_top_plaintexts;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("Enter the number of top plaintexts to display: ");
    scanf("%d", &num_top_plaintexts);

    frequency_analysis(ciphertext, num_top_plaintexts);

    return 0;
}

void frequency_analysis(char *ciphertext, int num_top_plaintexts) {
    int freq[ALPHABET_SIZE] = {0};
    int i, j, max_freq, likely_shift;

    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            freq[index]++;
        }
    }

    max_freq = freq[0];
    likely_shift = 0;
    for (i = 1; i < ALPHABET_SIZE; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            likely_shift = i;
        }
    }

    int shift = (likely_shift - ('e' - 'a') + ALPHABET_SIZE) % ALPHABET_SIZE;

    printf("\nTop %d possible plaintexts:\n", num_top_plaintexts);
    for (j = 0; j < num_top_plaintexts; j++) {
        decrypt_and_print(ciphertext, (shift + j) % ALPHABET_SIZE);
    }
}

void decrypt_and_print(char *ciphertext, int shift) {
    int i;
    printf("Shift %d: ", shift);
    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char decrypted_char = ciphertext[i] - shift;
            if (islower(ciphertext[i]) && decrypted_char < 'a') {
                decrypted_char += ALPHABET_SIZE;
            } else if (isupper(ciphertext[i]) && decrypted_char < 'A') {
                decrypted_char += ALPHABET_SIZE;
            }
            printf("%c", decrypted_char);
        } else {
            printf("%c", ciphertext[i]); 
        }
    }
    printf("\n");
}
