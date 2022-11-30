//Simple console app to make a file for every user
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void registerUser();
void loginUser();
bool userInDatabase(char *);
void start();
char * readPass(FILE*);
FILE *users;
FILE *currentUser;
int main(){
    // NOTE: There must be a file called 'userfiles' with 
    // the first byte a zero to start
    
    // Typing this I realise it's my job to make
    // sure you don't have to deal with this sort of thing...
    // I'll do it later
    users = fopen("userfiles", "r+");
    bool quit = false;
    if (!users){
        printf("%s", "Failed to open file\n");
        return -1;
    }
    // While there's no user file open users 
    // can log in or register
    while (!currentUser){
    start();
    }
    // Everything from here to the cleanup part is with the user logged into the file.
    // until the user quits
    while (!quit){
        int r;
        // Here is where functionallity goes
        printf("%s", "1. quit\n");
        scanf("%d", &r);
        switch (r){
            case 1:
                quit = true;
                break;
            default:
                break;
        }
    }
    
    // Clean up open files
    if (users == NULL){   
        fclose(users);
    }
    if (currentUser == NULL){
        fclose(currentUser);
    }
    return 0;
}
// Starting screen, choice to log in or
// register     unsafe
void start(){
    printf("\033[2J\033[1;1H");
    char response;        
    printf("%s", "Login or Register? l/r\n");
    scanf("%s", &response);
    // If user typed 'r'
    if (response == 114){
    registerUser();
    }
    printf("\033[2J\033[1;1H");
    loginUser();
}
// This function is made to register a new user and save their password 
// to file. Obviously this isn't secure but I can do that later for another
// project

// Basic structure of file is 32 bytes of the password and the rest data
// I'll figure out later
void registerUser(){
    // Creates the strings that will be the new username and password
    char user[32];
    char pass[32];
    int len;
    printf("%s", "Username:\n");
    scanf("%s", user);
    // checks if user already exists, see below
    if (userInDatabase(user)){
        printf("%s", "User already exists\n");
        return;
    }
    printf("%s", "Password:\n");
    scanf("%s", pass);
    // Creates a new file with the name of the user
    FILE *newFile = fopen(user, "w");
    if (!newFile){
        printf("%s", "Failed to open file\n");
    }
    // Prints password to user file
    // as well as changes the count 
    // of users in 'userfiles'
        fprintf(newFile, "%32s", pass);
        rewind(users);
        fscanf(users, "%d", &len);
        len++;
        rewind(users);
        fprintf(users, "%d", len);
        fseek(users, 0, SEEK_END);
        fprintf(users, "%32s", user);

    // Closes the files to clean up to login to new file
    fclose(newFile);
    return;
    
}
// login function
void loginUser(){
    printf("%s", "Login:\n");
    // Sets up strings
    char user[32];
    char pass[32];
    char passwordCheck[32];
    printf("%s", "Enter Username:\n");
    scanf("%s", user);
    // checks if name exist so not to make
    // a new file
    if (!userInDatabase(user)){
        printf("%s", "Name not found\n");
        return;
    }

    printf("%s", "Enter Password: \n");
    scanf("%s", pass);
    // Opens user's file..
    currentUser = fopen(user, "r");
    // ...reads password
    fscanf(currentUser, "%s", passwordCheck);
    
    if (strcmp(pass, passwordCheck) == 0){
        fseek(currentUser, 32, SEEK_SET);
        return ;
    }else {
        // If the password is wrong it will
        // close the user's file
        printf("%s", "incorrect password \n");
        fclose(currentUser);
        return;
    }

}

// Function for testing if user exists
// Returns {true} if it does
bool userInDatabase(char* nameToCheck){
    // All strings in the app are the same length
    // this is important
    char check[32];
    int len;
    // Go to beginning of file
    rewind(users);
    // reads how many users there are
    fscanf(users, "%d", &len);
    // for each one reads if its the one
    // we're looking for
    for (int i = 0; i < len; i++){
        fscanf(users, "%31s", check);
        if (strcmp(check, nameToCheck) == 0){
            return true;
        }
    }
    return false;  
}