#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "workouts.h"

struct exercise {
    char* name;
    int weight;
};

struct workout {
    //int num_exercises;
    char* name;
    struct exercise list[10];
};

struct workout arr[10];

void
delete_n(char * str) {
    // char * ret;
    // ret = strtok(str, "\n");
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
}

void
print_workout(char* name) {
    char* garbage = malloc(1023 * sizeof(char));
    system("clear");
    int pos = -1;
    //loop through array of workouts find position of workout to print
    for(int i = 0; i < 10; i++) {
        if(strcmp(arr[i].name, name) == 0) {
            pos = i;
            break;
        }
    }

    //if workout is not there error and return to previous function
    if(pos == -1) {
        printf("There does not seem to be a workout with that name\n");
        printf("Press enter to go back\n");
        getc(stdin);
        print_workout_names();
        return;
    }

    // print workout details
    printf("Workout: %s\n", arr[pos].name);
    for(int j = 0; j < 10; j++) {
        if(strcmp(arr[pos].list[j].name, "") == 0) {
            break;
        }
        printf("%s, %d lbs.\n", arr[pos].list[j].name, arr[pos].list[j].weight);
    }

    //pauses at getc and waits for user to continue
    printf("\nPress enter to continue\n");
    fgets(garbage, 64, stdin);
    print_workout_names();
    fflush(stdin);
    return;
}

void
print_workout_names() {
    system("clear");
    //print names of all workouts
    printf("Workouts:\n");
    for(int i = 0; i < 10; i++) {
        if(strcmp(arr[i].list[0].name, "") == 0) {
            break;
        }
        printf("%d. %s\n", i + 1, arr[i].name);
    }
    printf("\nType the name of a workout to show or 'return' to return\n");
    
    //char* in = malloc(32 * sizeof(char));
    char* input = malloc(32 * sizeof(char));

    //get code
    fgets(input, 32, stdin);//takes in /n char as well, take that off and continue to line 75
    delete_n(input);

    if(strcmp(input, "return") == 0) {
        return;
    }
    print_workout(input);
    fflush(stdin);
}

int
create_workout() {
    system("clear");
    //loop through array and find empty spot
    int pos = -1;
    for(int i = 0; i < 10; i++) {
        if(strcmp(arr[i].name, "") == 0) {
            pos = i;
            break;
        }
    }

    printf("What would you like the name of the workout to be? Type exit to exit\n");
    char* input = malloc(64 * sizeof(char));
    char *int_in = malloc(16 * sizeof(char));
    int weight_input;

    fgets(input, 64, stdin);
    
    //input = strtok(in, "\n");
    delete_n(input);
    //printf("hit\n");
    if(strcmp(input, "exit") == 0) {
        return 1;
    }

    arr[pos].name = input;

    char* ex_input = malloc(64 * sizeof(char));
    for(int i = 0; i < 10; i++) {
        printf("\nwhat would you like the exercise name to be? Type exit to exit\n");

        fgets(ex_input, 64, stdin);
        delete_n(ex_input);
        
        
        if(strcmp(ex_input, "exit") == 0) {
            return 0;
        }
        strcpy(arr[pos].list[i].name, ex_input);
        //arr[pos].list[i].name = ex_input;
        
        printf("\nWhat weight would you like for the exercise? (in lbs)\n");
        fgets(int_in, 16, stdin);
        weight_input = atoi(int_in);
        
        arr[pos].list[i].weight = weight_input;
    }

    return 0;
}

int
delete_workout() {
    system("clear");
    printf("What workout would you like to delete? Type exit to exit\n\n");

    printf("Workouts:\n");
    for(int i = 0; i < 10; i++) {
        if(strcmp(arr[i].list[0].name, "") == 0) {
            break;
        }
        printf("%d. %s\n", i + 1, arr[i].name);
    }
    printf("\n");

    char* input = malloc(32 * sizeof(char));
    fgets(input, 32, stdin);
    delete_n(input);

    if(strcmp(input, "exit") == 0) {
        return 0;
    }

    int pos = -1;
    //loop through array of workouts find position of workout to print
    for(int i = 0; i < 10; i++) {
        if(strcmp(arr[i].name, input) == 0) {
            pos = i;
            break;
        }
    }

    //if workout is not there error and return to previous function
    if(pos == -1) {
        printf("There does not seem to be a workout with that name\n");
        system("sleep 1");
        delete_workout();
        return 1;
    }

    arr[pos].name = "";
    for(int i = 0; i < 10; i++) {
        arr[pos].list[i].name = "";
    }

    return 0;
}

int
main(int argc, char* argv[]) {
    char* garbage = malloc(1023 * sizeof(char));

    for(int i = 0; i < 10; i++) {
        arr[i].name = malloc(32 * sizeof(char));
        for(int j = 0; j < 10; j++) {
            arr[i].list[j].name = malloc(64 * sizeof(char));
        }
    }

    arr[0].name = "chest";
    arr[0].list[0].name = "bench press";
    arr[0].list[0].weight = 135;
    arr[0].list[1].name = "lateral fly";
    arr[0].list[1].weight = 10;

    printf("Seems like you are new here, how about we get you started with creating your first workout!\n");
    printf("Press enter to start creating!\n");
    fgets(garbage, 64, stdin);
    create_workout();

    char* input = malloc(64 * sizeof(char));
    while(strcmp(input, "exit") != 0) {
        system("clear");
        printf("What would you like to do?\n'create workout' - type to create a basic workout\n'show workouts' - type to show existing workouts\n'delete workout' - type to delete a workout\n'exit'\n\n");
        fgets(input, 64, stdin);
        delete_n(input);

        if(strcmp(input, "create workout") == 0) {
            create_workout();
        }
        else if(strcmp(input, "show workouts") == 0) {
            print_workout_names();
        }
        else if(strcmp(input, "delete workout") == 0) {
            system("clear");
            delete_workout();
        }
        else if(strcmp(input, "exit") != 0) {
            printf("Please enter a valid option, type what is shown in quotes\n\n");
            system("sleep 1");
        }
    }

    return 0;
}