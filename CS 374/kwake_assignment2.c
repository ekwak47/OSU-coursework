#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie {
    char* title;  // movie title
    int year;  // year value
    char languages[5][21];  // maximum languages is 5, string limit 20
    double rating;  // movie rating

    struct movie* next;  // helps initialize linked list

};

// Function to create a new movie node from a line
// source: https://www.w3schools.com/c/c_pointers.php (for general usage for pointers and structs)
struct movie* createMovie(char* cur_line) {
    struct movie* new_movie = malloc(sizeof(struct movie));  // malloc acts as dynamic memory allocation 
    char* ptr;  // pointer 


    // each of the following methods will parse and divide the generated values
    // 

    // Title
    char* token = strtok_r(cur_line, ",", &ptr);
    new_movie -> title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(new_movie->title, token);

    // Year
    token = strtok_r(NULL, ",", &ptr);
    new_movie -> year = atoi(token);

    // Languages
    token = strtok_r(NULL, ",", &ptr);
    int lang_index = 0;
    char* lang_save;
    token++; // skips over first formatting "]"
    char* langToken = strtok_r(token, ";]", &lang_save);
    while (langToken != NULL && lang_index < 5) {
        strncpy(new_movie -> languages[lang_index], langToken, 20);
        new_movie -> languages[lang_index][20] = '\0';
        lang_index++;
        langToken = strtok_r(NULL, ";]", &lang_save);
    }
    for (int i = lang_index; i < 5; i++) {
        new_movie -> languages[i][0] = '\0';
    }

    // Rating
    token = strtok_r(NULL, ",", &ptr);
    new_movie -> rating = strtof(token, NULL);

    new_movie -> next = NULL;
    return new_movie;
}

// Function to process the movie file
// copied and pasted from the assignment page
// modifications: added in parameters in order to facilitate the linked list aspects of the assignment,
// including a head node and tail node to mark the linked lists. 

struct movie* processMovieFile(char* filePath, int* movieCount) {
    char* cur_line = NULL;
    size_t len = 0;
    ssize_t nread;  // signed size type
    FILE* movie_file = fopen(filePath, "r");

    if (!movie_file) {
        printf("Could not open file %s\n", filePath);  // movie file must match to input
        exit(EXIT_FAILURE);
    }

    struct movie* head = NULL;  // points to the first movie in the file
    struct movie* tail = NULL; // points to the last movie in the file

    getline(&cur_line, &len, movie_file); // skip header line

    while ((nread = getline(&cur_line, &len, movie_file)) != -1) {
        struct movie* new_movie = createMovie(cur_line);
        if (head == NULL) {
            head = new_movie;  // if the head node is empty, reassigns the first movie to head
            tail = new_movie;  // in an empty linked list, if the head node is null, then tail node is 
                            // also empty, which is why the movie is also the tail
        } else {
            tail -> next = new_movie;  // moves up the linked list
            tail = new_movie;
        }
        (*movieCount)++;  // increments movie count
    }

    free(cur_line);
    fclose(movie_file);

    return head;
}


    // separate voids to manage each of the options 1-4 depending on user input

// Option 1: Shows movies by year
void showMoviesByYear(struct movie* head, int year) {
    int found = 0;
    struct movie* temp = head;
    while (temp != NULL) {
        if (temp -> year == year) {
            printf("%s\n", temp -> title);
            found = 1;
        }
        temp = temp -> next;
    }
    if (!found) {
        printf("No data about movies released in the year %d\n", year);
    }
}

// Option 2: shows highest rated movie each year
void showHighestRatedEachYear(struct movie* head) {
    struct movie* temp = head;

    int years[200];
    double ratings[200];
    struct movie* movies[200];
    int year_count = 0;

    while (temp != NULL) {
        int found = 0;
        for (int i = 0; i < year_count; i++) {
            if (years[i] == temp -> year) {
                found = 1;
                if (temp -> rating > ratings[i]) {
                    ratings[i] = temp -> rating;
                    movies[i] = temp;
                }
                break;
            }
        }
        if (!found) {
            years[year_count] = temp -> year;
            ratings[year_count] = temp -> rating;
            movies[year_count] = temp;
            year_count++;
        }
        temp = temp -> next;
    }

    for (int i = 0; i < year_count; i++) {
        printf("%d %.1f %s\n", years[i], ratings[i], movies[i] -> title);
    }
}

// Option 3: shows movies by language
void showMoviesByLanguage(struct movie* head, char* language) {
    int found = 0;
    struct movie* temp = head;

    while (temp != NULL) {
        for (int i = 0; i < 5; i++) {
            if (strcmp(temp -> languages[i], language) == 0) {
                printf("%d %s\n", temp -> year, temp -> title);
                found = 1;
                break;
            }
        }
        temp = temp -> next;
    }

    if (!found) {
        printf("No data about movies released in %s\n", language);
    }
}

// frees memory
void freeMovies(struct movie* head) {
    struct movie* temp;
    while (head != NULL) {
        temp = head;
        head = head -> next;
        free(temp -> title);
        free(temp);
    }
}


  // copied from project 2 notes, prompts user to enter file name in terminal and makes user run program again

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }

    int movieCount = 0;
    struct movie* movie_list = processMovieFile(argv[1], &movieCount);


    // user input

    printf("\nProcessed file %s and parsed data for %d movies\n", argv[1], movieCount);

    int user_input;
    do {
        printf("\n1. Show movies released in the specified year\n");
        printf("2. Show highest rated movie for each year\n");
        printf("3. Show the title and year of release of all movies in a specific language\n");
        printf("4. Exit from the program\n");
        printf("\nEnter a choice from 1 to 4: ");
        scanf("%d", &user_input);

        if (user_input == 1) {
            int year;
            printf("Enter the year for which you want to see movies: ");
            scanf("%d", &year);
            showMoviesByYear(movie_list, year);
        } else if (user_input == 2) {
            showHighestRatedEachYear(movie_list);
        } else if (user_input == 3) {
            char language[21];
            printf("Enter the language for which you want to see movies: ");
            scanf("%20s", language);
            showMoviesByLanguage(movie_list, language);
        } else if (user_input != 4) {
            printf("You entered an incorrect choice. Try again.\n");
        }

    } while (user_input != 4);

    freeMovies(movie_list);

    return EXIT_SUCCESS;
}
