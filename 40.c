#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHER_LENGTH 1000

const float standard_frequencies[ALPHABET_SIZE] = {
    8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
    6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1
};

void normalize_frequencies(int freq[], int length, float normalized[]) {
    int total = 0;
    for (int i = 0; i < length; ++i) {
        total += freq[i];
    }
    for (int i = 0; i < length; ++i) {
        normalized[i] = (float)freq[i] / total * 100.0;
    }
}

void letter_frequency_attack(const char ciphertext[], char plaintext[], int top_results) {
    int cipher_freq[ALPHABET_SIZE] = {0};
    int cipher_length = strlen(ciphertext);

    for (int i = 0; i < cipher_length; ++i) {
        char ch = toupper(ciphertext[i]);
        if (isalpha(ch)) {
            cipher_freq[ch - 'A']++;
        }
    }

    float normalized_cipher_freq[ALPHABET_SIZE];
    normalize_frequencies(cipher_freq, ALPHABET_SIZE, normalized_cipher_freq);

    float freq_differences[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        freq_differences[i] = abs(normalized_cipher_freq[i] - standard_frequencies[i]);
    }

    int sorted_indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        sorted_indices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; ++i) {
        for (int j = i + 1; j < ALPHABET_SIZE; ++j) {
            if (freq_differences[sorted_indices[j]] < freq_differences[sorted_indices[i]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }

    for (int k = 0; k < top_results; ++k) {
        for (int i = 0; i < cipher_length; ++i) {
            char ch = toupper(ciphertext[i]);
            if (isalpha(ch)) {
                plaintext[i] = 'A' + (ch - 'A' + sorted_indices[k]) % ALPHABET_SIZE;
            } else {
                plaintext[i] = ch;
            }
            if (islower(ciphertext[i])) {
                plaintext[i] = tolower(plaintext[i]);
            }
        }
        plaintext[cipher_length] = '\0';
        printf("Possible plaintext (Rank %d): %s\n", k + 1, plaintext);
    }
}

int main() {
    char ciphertext[MAX_CIPHER_LENGTH];
    char plaintext[MAX_CIPHER_LENGTH];
    int top_results;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_results);

    letter_frequency_attack(ciphertext, plaintext, top_results);

    return 0;
}
