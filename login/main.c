//Simple console app to make a file for every user
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void registerUser();
void loginUser();
bool userInDatabase(char *);
char * concat(char *, char *);
FILE *users;
FILE *currentUser;
int main(){
    users = fopen("userfiles", "w+");
    
    {
        char *response;
        
        printf("%s", "Login or Register? l/r\n");
        scanf("%s", response);
        if (*response == 114){
        registerUser();
        }
    }
// Now for the login functionality. Users will enter a username that will
// be checked to see if its valid
    loginUser();
    
    // Clean up open files
    fclose(users);
    if (currentUser != NULL){
        printf("%s", "something's not right");
    fclose(currentUser);
    }
    return 0;
}
// This function is made to register a new user and save their password 
// to file. Obviously this isn't secure but I can do that later for another
// project
void registerUser(){
    // Creates the strings that will be the new username and password
    char *user[30];
    char *pass[30];
    printf("%s", "Username:\n");
    scanf("%s", *user);
    // I want to check if the username already exists
    // I'll add that to TODO
    if (!userInDatabase(*user)){
        printf("%s", "User already exists");
        return;
    }
    printf("%s", "Password:\n");
    scanf("%s", *pass);
    // Creates a new file with the name of the user
    FILE *newFile = fopen(*user, "w");
    strcat(*pass, "\n\r");
    strcat(*user, "\n\r");
    printf("%s", *pass);
    fprintf(newFile, "%s", *pass);
    fprintf(users, "%s", *user);
    // Closes the file to clean up to login to new file
    fclose(newFile);
    return;
    
}
void loginUser(){
    printf("%s", "Login:\n");
    char* user[30];
    char* pass[30];
    char* passwordCheck[30];
    printf("%s", "Enter Username \n");
    scanf("%s", *user);
    if (!userInDatabase(*user)){
        printf("%s", "Name not found\n");
        return;
    }
    printf("%s", "Enter Password: \n");
    scanf("%s", *pass);
    currentUser = fopen(*user, "w+");
    fscanf(currentUser, "%s", *passwordCheck);
    printf("%s", *passwordCheck);

    if (*pass == *passwordCheck){
        return ;
    }else {
        printf("%s", "incorrect password \n");
        fclose(currentUser);
        return;
    }

}
bool userInDatabase(char * nameToCheck){
    
    // TODO: check if username is in database
    return true;
}
/*
Obsolete string concatonation function, I wanted to try to make my own
but in the end I just used the normal one
might come back to this later though
char * concat(char * string1, char * string2){
    int length = sizeof(*string1) + sizeof(*string2);
    char * newString[length];
    int y = 0;
    for (int i = 0;i < sizeof(*string1);i++){
        newString[y] = &string1[i];
        y++;
    }
    for (int i = 0;i < sizeof(*string2);i++){
        newString[y] = &string2[i];
        y++;
    }
    printf("%s", *newString);
    return *newString;
}
*/