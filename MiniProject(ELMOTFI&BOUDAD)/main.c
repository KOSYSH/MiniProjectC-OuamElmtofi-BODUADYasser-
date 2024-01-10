#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
/*
struct pendu {
    char word[20];
    char description[1000];
};

void printHangman(int lives) {
    printf("Lives: %d\n", lives);

    if (lives >= 1) {
        printf("------\n");
        printf("|    |\n");

        if (lives <= 6) {
            printf("|\n");
            printf("|\n");
            printf("|\n");
        }

        if (lives <= 5) {
            printf("|    O\n");
        }

        if (lives <= 4) {
            printf("|   /");
        }

        if (lives <= 3) {
            printf("|");
        }

        if (lives <= 2) {
            printf("\\\n");
        }

        if (lives <= 1) {
            printf("|\n");
        }
    }
}

void printTable(char word[], int guessed[]) {
    int i;
    for (i = 0; i < strlen(word); ++i) {
        if (guessed[i] == 1) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int guessLetter(char word[], int guessed[], char guess) {
    int correct_guess = 0;
    int i;
    for (i = 0; i < strlen(word); ++i) {
        if (word[i] == guess && guessed[i] == 1) {
            printf("You have already guessed the letter %c. Try again.\n", guess);
            correct_guess = 1;
            break;
        }

        if (word[i] == guess && guessed[i] != 1) {
            guessed[i] = 1;
            correct_guess = 1;
        }
    }

    return correct_guess;
}

void printHeart(int lives) {
    int i;
    printf("\tLives: ");
    for (i = 0; i < lives; ++i) {
        printf("* ");
    }
    printf("\n");
}

int main() {
    int admin, i;
    char password[20];
    const char *correctPassword = "shadow";
    int playagain;

    struct pendu x[100];
    int numWords = 0;
    int chosenNumber;
    int wordIndex;
    int life = 5;
    int found = 0;
    char ch;

    int guessed[20];
    memset(guessed, 0, sizeof(guessed));

    FILE *w = fopen("pendu.txt", "r");
    if (w != NULL) {
        i = 0;
        while (fscanf(w, "%s %99[^\n]\n", x[i].word, x[i].description) == 2) {
            i++;
            numWords++;
        }
        fclose(w);
    }

    printf("If you are an admin press 1, if not and want to play press 2 (enjoy the game)\n");
    scanf("%d", &admin);

    switch (admin) {
        case 1:
            printf("Enter password: ");
            i = 0;
            while (1) {
                ch = getch();

                if (ch == 13)
                    break;
                else {
                    password[i++] = ch;
                    printf("*");
                }
            }

            if (strcmp(password, correctPassword) == 0) {
                printf("\nAccess granted!\n");

                int choice;
                do {
                    printf("Admin Options:\n");
                    printf("1. Add a new word and description\n");
                    printf("2. Exit admin mode\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            w = fopen("pendu.txt", "a");
                            if (w == NULL) {
                                printf("Error opening file\n");
                            } else {
                                printf("Enter word: ");
                                scanf("%s", x[numWords].word);

                                printf("Enter description: ");
                                scanf(" %[^\n]", x[numWords].description);

                                fprintf(w, "%s %s\n", x[numWords].word, x[numWords].description);
                                printf("Word and description added successfully!\n");

                                fclose(w);
                                numWords++;
                            }
                            break;

                        case 2:
                            printf("Exiting admin mode...\n");
                            break;

                        default:
                            printf("Invalid choice\n");
                    }
                } while (choice != 2);

            } else {
                printf("\nIncorrect password!\n");
            }
            break;

        case 2:
            do {
                printf("Welcome to the Hangman game!\n");
                printf("Select a mode (1 or 2):\n1. Computer provides description, and you guess the word \n2. Two players - Player 1 provides word and description, Player 2 guesses\n");
                scanf("%d", &i);

                switch (i) {
                    case 2:
                        printf("Player 1, enter the word: ");
                        i = 0;

                        while (1) {
                            ch = getch();

                            if (ch == 13) {
                                break;
                            } else {
                                x[numWords].word[i++] = ch;
                                printf("*");
                            }
                        }

                        printf("Player 1, enter the description: ");
                        scanf(" %[^\n]", x[numWords].description);

                        w = fopen("pendu.txt", "a");
                        if (w == NULL) {
                            printf("Error opening file\n");
                        } else {
                            fprintf(w, "%s %s\n", x[numWords].word, x[numWords].description);
                            printf("Word and description added successfully!\n");

                            fclose(w);
                            numWords++;
                        }

                        printf("Player 2, guess the word letter by letter!\n");

                        memset(guessed, 0, sizeof(guessed));

                        printf("Description: %s\n", x[numWords - 1].description);
                        printTable(x[numWords - 1].word, guessed);
                        char guess;

                        while (life != 0 && found < strlen(x[numWords - 1].word)) {
                            printHangman(life);
                            printHeart(life);

                            printf("Enter a letter: ");
                            scanf(" %c", &guess);

                            int correct_guess = guessLetter(x[numWords - 1].word, guessed, guess);

                            if (correct_guess) {
                                found = 0;
                                for (i = 0; i < strlen(x[numWords - 1].word); ++i) {
                                    if (guessed[i] == 1) {
                                        found++;
                                    }
                                }
                            }

                            printTable(x[numWords - 1].word, guessed);

                            if (!correct_guess) {
                                --life;
                                printf("Incorrect! The letter is not in the word.\n");
                            }
                        }

                        if (found == strlen(x[numWords - 1].word)) {
                            printf("Congratulations! You guessed the word: %s\n", x[numWords - 1].word);
                        } else {
                            printf("Sorry, you ran out of tries. The correct word was: %s\n", x[numWords - 1].word);
                        }
                        break;

                    case 1:
                        printf("Choose a number between 1 and %d: ", numWords);
                    number:
                        scanf("%d", &chosenNumber);
                        if (chosenNumber < 1 || chosenNumber > numWords) {
                            printf("Invalid number. Please choose a number between 1 and %d.\n", numWords);
                            goto number;
                        }

                        wordIndex = chosenNumber - 1;

                        guessed[strlen(x[wordIndex].word)];
                        memset(guessed, 0, sizeof(guessed));

                        printf("Description: %s\n", x[wordIndex].description);
                        printTable(x[wordIndex].word, guessed);
                        while (life != 0 && found < strlen(x[wordIndex].word)) {
                            printHangman(life);
                            printHeart(life);

                            printf("Enter a letter: ");
                            scanf(" %c", &guess);

                            int correct_guess = guessLetter(x[wordIndex].word, guessed, guess);

                            if (correct_guess) {
                                found = 0;
                                for (i = 0; i < strlen(x[wordIndex].word); ++i) {
                                    if (guessed[i] == 1) {
                                        found++;
                                    }
                                }
                            }

                            printTable(x[wordIndex].word, guessed);

                            if (!correct_guess) {
                                --life;
                                printf("Incorrect! The letter is not in the word.\n");
                            }
                        }

                        if (found == strlen(x[wordIndex].word)) {
                            printf("Congratulations! You guessed the word: %s\n", x[wordIndex].word);
                        } else {
                            printf("Sorry, you ran out of tries. The correct word was: %s\n", x[wordIndex].word);
                        }
                        break;
                }

                play_again_label:
                printf("Do you want to play again? (1 for Yes, 0 for No): ");
                scanf("%d", &playagain);

                if (playagain == 1) {
                    // Reset game variables here
                    life = 5;
                    found = 0;
                    memset(guessed, 0, sizeof(guessed));
                } else if (playagain == 0) {
                    printf("Thank you for playing!\n");
                    break;  // Exit the loop and end the game
                } else {
                    printf("Invalid input. Please enter 1 for Yes or 0 for No.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    goto play_again_label;
                }

            } while (playagain != 0);

            break;
    }

    return 0;
}
*/


struct pendu {
    char word[20];
    char description[1000];
};

void printHangman(int lives) {
    printf("Vies: %d\n", lives);

    if (lives >= 1) {
        printf("------\n");
        printf("|    |\n");

        if (lives <= 6) {
            printf("|\n");
            printf("|\n");
            printf("|\n");
        }

        if (lives <= 5) {
            printf("|    O\n");
        }

        if (lives <= 4) {
            printf("|   /");
        }

        if (lives <= 3) {
            printf("|");
        }

        if (lives <= 2) {
            printf("\\\n");
        }

        if (lives <= 1) {
            printf("|\n");
        }
    }
}

void printTable(char word[], int guessed[]) {
    int i;
    for (i = 0; i < strlen(word); ++i) {
        if (guessed[i] == 1) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int guessLetter(char word[], int guessed[], char guess) {
    int correct_guess = 0;
    int i;
    for (i = 0; i < strlen(word); ++i) {
        if (word[i] == guess && guessed[i] == 1) {
            printf("Vous avez déjà deviné la lettre %c. Essayez à nouveau.\n", guess);
            correct_guess = 1;
            break;
        }

        if (word[i] == guess && guessed[i] != 1) {
            guessed[i] = 1;
            correct_guess = 1;
        }
    }

    return correct_guess;
}

void printHeart(int lives) {
    int i;
    printf("\tVies: ");
    for (i = 0; i < lives; ++i) {
        printf("* ");
    }
    printf("\n");
}

int main() {
    int admin, i;
    char password[20];
    const char *correctPassword = "shadow";
    int playagain;

    struct pendu x[100];
    int numWords = 0;
    int chosenNumber;
    int wordIndex;
    int life = 5;
    int found = 0;
    char ch;

    int guessed[20];
    memset(guessed, 0, sizeof(guessed));

    FILE *w = fopen("pendu.txt", "r");
    if (w != NULL) {
        i = 0;
        while (fscanf(w, "%s %99[^\n]\n", x[i].word, x[i].description) == 2) {
            i++;
            numWords++;
        }
        fclose(w);
    }

    printf("Si vous etes administrateur, appuyez sur 1. Sinon, si vous voulez jouer, appuyez sur 2 (profitez du jeu)\n");
    scanf("%d", &admin);

    switch (admin) {

        case 1:
            printf("Entrez le mot de passe: ");
            i = 0;
            while (1) {
                ch =
                        getch();

                if (ch == 13)
                    break;
                else {
                    password[i++] = ch;
                    printf("*");
                }
            }

            if (strcmp(password, correctPassword) == 0) {
                printf("\nAcces autorise !\n");

                int choice;
                do {
                    printf("Options administrateur:\n");
                    printf("1. Ajouter un nouveau mot et une description\n");
                    printf("2. Quitter le mode administrateur\n");
                    printf("Entrez votre choix: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            w = fopen("pendu.txt", "a");
                            if (w == NULL) {
                                printf("Erreur d'ouverture du fichier\n");
                            } else {
                                printf("Entrez le mot: ");
                                scanf("%s", x[numWords].word);

                                printf("Entrez la description: ");
                                scanf(" %[^\n]", x[numWords].description);

                                fprintf(w, "%s %s\n", x[numWords].word, x[numWords].description);
                                printf("Mot et description ajoutes avec succès !\n");

                                fclose(w);
                                numWords++;
                            }
                            break;

                        case 2:
                            printf("Sortie du mode administrateur...\n");
                            break;

                        default:
                            printf("Choix invalide\n");
                    }
                } while (choice != 2);

            } else {
                printf("\nMot de passe incorrect !\n");
            }
            break;

        case 2:
            do {
                printf("Bienvenue dans le jeu du Pendu !\n");
                printf("Selectionnez un mode (1 ou 2):\n1. L'ordinateur fournit la description, et vous devinez le mot \n2. Deux joueurs - Joueur 1 fournit le mot et la description, Joueur 2 devine\n");
                scanf("%d", &i);

                switch (i) {
                    case 2:
                        printf("Joueur 1, entrez le mot: ");
                        i = 0;

                        while (1) {
                            ch = getch();

                            if (ch == 13) {
                                break;
                            } else {
                                x[numWords].word[i++] = ch;
                                printf("*");
                            }
                        }

                        printf("Joueur 1, entrez la description: ");
                        scanf(" %[^\n]", x[numWords].description);

                        w = fopen("pendu.txt", "a");
                        if (w == NULL) {
                            printf("Erreur d'ouverture du fichier\n");
                        } else {
                            fprintf(w, "%s %s\n", x[numWords].word, x[numWords].description);
                            printf("Mot et description ajoutes avec succes !\n");

                            fclose(w);
                            numWords++;
                        }

                        printf("Joueur 2, devinez le mot lettre par lettre !\n");

                        memset(guessed, 0, sizeof(guessed));

                        printf("Description: %s\n", x[numWords - 1].description);
                        printTable(x[numWords - 1].word, guessed);
                        char guess;

                        while (life != 0 && found < strlen(x[numWords - 1].word)) {
                            printHangman(life);
                            printHeart(life);

                            printf("Entrez une lettre: ");
                            scanf(" %c", &guess);

                            int correct_guess = guessLetter(x[numWords - 1].word, guessed, guess);

                            if (correct_guess) {
                                found = 0;
                                for (i = 0; i < strlen(x[numWords - 1].word); ++i) {
                                    if (guessed[i] == 1) {
                                        found++;
                                    }
                                }
                            }

                            printTable(x[numWords - 1].word, guessed);

                            if (!correct_guess) {
                                --life;
                                printf("Incorrect ! La lettre n'est pas dans le mot.\n");
                            }
                        }

                        if (found == strlen(x[numWords - 1].word)) {
                            printf("Felicitations ! Vous avez devine le mot: %s\n", x[numWords - 1].word);
                        } else {
                            printf("Desole, vous avez epuise vos essais. Le mot correct etait: %s\n", x[numWords - 1].word);
                        }
                        break;

                    case 1:
                        printf("Choisissez un nombre entre 1 et %d: ", numWords);
                    number:
                        scanf("%d", &chosenNumber);
                        if (chosenNumber < 1 || chosenNumber > numWords) {
                            printf("Nombre invalide. Veuillez choisir un nombre entre 1 et %d.\n", numWords);
                            goto number;
                        }

                        wordIndex = chosenNumber - 1;

                        guessed[strlen(x[wordIndex].word)];
                        memset(guessed, 0, sizeof(guessed));

                        printf("Description: %s\n", x[wordIndex].description);
                        printTable(x[wordIndex].word, guessed);
                        while (life != 0 && found < strlen(x[wordIndex].word)) {
                            printHangman(life);
                            printHeart(life);

                            printf("Entrez une lettre: ");
                            scanf(" %c", &guess);

                            int correct_guess = guessLetter(x[wordIndex].word, guessed, guess);

                            if (correct_guess) {
                                found = 0;
                                for (i = 0; i < strlen(x[wordIndex].word); ++i) {
                                    if (guessed[i] == 1) {
                                        found++;
                                    }
                                }
                            }

                            printTable(x[wordIndex].word, guessed);

                            if (!correct_guess) {
                                --life;
                                printf("Incorrect ! La lettre n'est pas dans le mot.\n");
                            }
                        }

                        if (found == strlen(x[wordIndex].word)) {
                            printf("Felicitations ! Vous avez devine le mot: %s\n", x[wordIndex].word);
                        } else {
                            printf("Desole, vous avez epuisé vos essais. Le mot correct etait: %s\n", x[wordIndex].word);
                        }
                        break;
                }

                play_again_label:
                printf("Voulez-vous jouer encore ? (1 pour Oui, 0 pour Non): ");
                scanf("%d", &playagain);

                if (playagain == 1) {
                    
                    life = 5;
                    found = 0;
                    memset(guessed, 0, sizeof(guessed));
                } else if (playagain == 0) {
                    printf("Merci d'avoir joué !\n");
                    break;
                } else {
                    printf("Entrée invalide. Veuillez entrer 1 pour Oui ou 0 pour Non.\n");
                    while (getchar() != '\n');
                    goto play_again_label;
                }

            } while (playagain != 0);

            break;
    }

    return 0;
}
