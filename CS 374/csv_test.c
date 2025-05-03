#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LANGUAGES 5
#define MAX_LANGUAGE_LEN 21
#define MAX_TITLE_LEN 256
#define LINE_BUFFER_SIZE 1024

typedef struct movie {
    char title[MAX_TITLE_LEN];
    int year;
    char languages[MAX_LANGUAGES][MAX_LANGUAGE_LEN];
    int language_count;
    double rating;
    struct movie* next;
} Movie;

// Custom getline replacement
size_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
    if (*lineptr == NULL || *n == 0) {
        *n = 128;
        *lineptr = malloc(*n);
        if (*lineptr == NULL) return -1;
    }

    char *buf = *lineptr;
    int c = 0;
    size_t i = 0;

    while ((c = fgetc(stream)) != EOF) {
        if (i + 1 >= *n) {
            *n *= 2;
            char *newbuf = realloc(*lineptr, *n);
            if (newbuf == NULL) return -1;
            *lineptr = newbuf;
            buf = newbuf;
        }

        buf[i++] = (char)c;
        if (c == '\n') break;
    }

    if (i == 0 && c == EOF) return -1;

    buf[i] = '\0';
    return i;
}

// Create movie from a line
Movie* create_movie_from_line(const char* line) {
    Movie* m = malloc(sizeof(Movie));
    m->next = NULL;

    char* temp = strdup(line);

    char* token = strtok(temp, ",");
    strncpy(m->title, token, MAX_TITLE_LEN);

    token = strtok(NULL, ",");
    m->year = atoi(token);

    token = strtok(NULL, ",");
    m->language_count = 0;
    if (token[0] == '[') token++;
    char* end = strchr(token, ']');
    if (end) *end = '\0';
    char* lang = strtok(token, ";");
    while (lang != NULL && m->language_count < MAX_LANGUAGES) {
        strncpy(m->languages[m->language_count], lang, MAX_LANGUAGE_LEN);
        m->language_count++;
        lang = strtok(NULL, ";");
    }

    token = strtok(NULL, ",");
    m->rating = atof(token);

    free(temp);
    return m;
}

// Append to linked list
void append_movie(Movie** head_ref, Movie* new_movie) {
    if (*head_ref == NULL) {
        *head_ref = new_movie;
    } else {
        Movie* curr = *head_ref;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new_movie;
    }
}

// Read and parse movie file
Movie* processMovieFile(const char* filePath) {
    char* currLine = NULL;
    size_t len = 0;
    Movie* head = NULL;

    FILE* movieFile = fopen(filePath, "r");
    if (!movieFile) {
        perror("Error opening file");
        return NULL;
    }

    // Skip the header
    custom_getline(&currLine, &len, movieFile);

    while (custom_getline(&currLine, &len, movieFile) != -1) {
        currLine[strcspn(currLine, "\n")] = '\0';
        Movie* new_movie = create_movie_from_line(currLine);
        append_movie(&head, new_movie);
    }

    free(currLine);
    fclose(movieFile);
    printf("\nProcessed file %s\n", filePath);
    return head;
}

// Menu options
void print_movies_by_year(Movie* head, int year) {
    int found = 0;
    while (head) {
        if (head->year == year) {
            printf("%s\n", head->title);
            found = 1;
        }
        head = head->next;
    }
    if (!found)
        printf("No data about movies released in the year %d\n", year);
}

void print_highest_rated_per_year(Movie* head) {
    for (int y = 1900; y <= 2025; y++) {
        Movie* best = NULL;
        Movie* curr = head;
        while (curr) {
            if (curr->year == y && (!best || curr->rating > best->rating)) {
                best = curr;
            }
            curr = curr->next;
        }
        if (best)
            printf("%d %.1f %s\n", best->year, best->rating, best->title);
    }
}

void print_movies_by_language(Movie* head, const char* language) {
    int found = 0;
    while (head) {
        for (int i = 0; i < head->language_count; i++) {
            if (strcasecmp(head->languages[i], language) == 0) {
                printf("%d %s\n", head->year, head->title);
                found = 1;
                break;
            }
        }
        head = head->next;
    }
    if (!found)
        printf("No movies found in %s\n", language);
}

// Free memory
void free_movie_list(Movie* head) {
    while (head) {
        Movie* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }

    Movie* movie_list = processMovieFile(argv[1]);
    if (!movie_list) return EXIT_FAILURE;

    int choice;
    while (1) {
        printf("\n1. Show movies released in the specified year\n");
        printf("2. Show highest rated movie for each year\n");
        printf("3. Show the title and year of release of all movies in a specific language\n");
        printf("4. Exit from the program\n");
        printf("\nEnter a choice from 1 to 4: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int year;
            printf("Enter the year for which you want to see movies: ");
            scanf("%d", &year);
            print_movies_by_year(movie_list, year);
        } else if (choice == 2) {
            print_highest_rated_per_year(movie_list);
        } else if (choice == 3) {
            char lang[MAX_LANGUAGE_LEN];
            printf("Enter the language for which you want to see movies: ");
            scanf("%s", lang);
            print_movies_by_language(movie_list, lang);
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid choice. Please select 1–4.\n");
        }
    }

    free_movie_list(movie_list);
    return EXIT_SUCCESS;
}