#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

const float english_freq[ALPHABET_SIZE] = {
    8.12, 1.49, 2.71, 4.32, 12.02, 2.30, 2.03, 5.92, 7.31, 0.10, 
    0.69, 3.98, 2.61, 6.95, 7.68, 1.82, 0.11, 6.02, 6.28, 9.10, 
    2.88, 1.11, 2.09, 0.17, 2.11, 0.07
};

typedef struct {
    char letter;
    float frequency;
} FrequencyAnalysis;

void analyze_frequency(const char* ciphertext, FrequencyAnalysis* analysis);
void sort_analysis(FrequencyAnalysis* analysis);
void generate_plaintexts(const char* ciphertext, FrequencyAnalysis* analysis, int top_n);

int main() {
    char ciphertext[1024];
    int top_n;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_n);

    FrequencyAnalysis analysis[ALPHABET_SIZE];
    analyze_frequency(ciphertext, analysis);
    sort_analysis(analysis);
    generate_plaintexts(ciphertext, analysis, top_n);

    return 0;
}

void analyze_frequency(const char* ciphertext, FrequencyAnalysis* analysis) {
    int letter_count[ALPHABET_SIZE] = {0};
    int total_letters = 0;

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            letter_count[ciphertext[i] - 'a']++;
            total_letters++;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            letter_count[ciphertext[i] - 'A']++;
            total_letters++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        analysis[i].letter = 'a' + i;
        analysis[i].frequency = (float)letter_count[i] / total_letters * 100;
    }
}

void sort_analysis(FrequencyAnalysis* analysis) {
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (analysis[j].frequency > analysis[i].frequency) {
                FrequencyAnalysis temp = analysis[i];
                analysis[i] = analysis[j];
                analysis[j] = temp;
            }
        }
    }
}

void generate_plaintexts(const char* ciphertext, FrequencyAnalysis* analysis, int top_n) {
    const char english_letters[ALPHABET_SIZE] = "etaoinshrdlcumwfgypbvkjxqz";

    for (int k = 0; k < top_n; k++) {
        char plaintext[1024];
        strcpy(plaintext, ciphertext);

        for (int i = 0; ciphertext[i] != '\0'; i++) {
            if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                for (int j = 0; j < ALPHABET_SIZE; j++) {
                    if (ciphertext[i] == analysis[j].letter) {
                        plaintext[i] = english_letters[(j + k) % ALPHABET_SIZE];
                        break;
                    }
                }
            } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                for (int j = 0; j < ALPHABET_SIZE; j++) {
                    if (ciphertext[i] == analysis[j].letter - 32) {
                        plaintext[i] = english_letters[(j + k) % ALPHABET_SIZE] - 32;
                        break;
                    }
                }
            }
        }
        printf("Possible plaintext %d: %s\n", k + 1, plaintext);
    }
}
