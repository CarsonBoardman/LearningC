//Simple console app to make a file for every user
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void registerUser();
void loginUser();
bool userInDatabase(char **);
char * readPass(FILE*);
char * concat(char *, char *);
FILE *users;
FILE *currentUser;
int main(){
    
    
    
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
    // Everything from here to the cleanup part is with the user logged into the file.

    
    // Clean up open files
    if (users == NULL){
        
        fclose(users);
        
    }
    if (currentUser == NULL){
        fclose(currentUser);
    }
    
    return 0;
}
// This function is made to register a new user and save their password 
// to file. Obviously this isn't secure but I can do that later for another
// project

// Basic structure of file is 32 bytes of the password and the rest data
// I'll figure out later
void registerUser(){
    // Creates the strings that will be the new username and password
    char * user[32];
    char * pass[32];
    printf("%s", "Username:\n");
    scanf("%s", *user);
    // I want to check if the username already exists
    // I'll add that to TODO
    /*
    if (!userInDatabase(*user)){
        printf("%s", "User already exists");
        return;
    }
    */
    printf("%s", "Password:\n");
    scanf("%s", *pass);
    // Creates a new file with the name of the user
    FILE *newFile = fopen(*user, "w");
    if (!newFile){
        printf("%s", "Failed to open file\n");
    }
    users = fopen("userfiles", "w");
    if (!users){
        printf("%s", "Failed to open file\n");
    }
    strcat(*pass, "\n\r");
    strcat(*user, "\n\r");
    fprintf(newFile, "%32s", *pass);
    fprintf(users, "%32s", *user);
    // Closes the files to clean up to login to new file
    fclose(newFile);
    fclose(users);
    return;
    
}
void loginUser(){
    fpos_t * position;
    printf("%s", "Login:\n");
    char * user[32];
    char * pass[32];
    char * passwordCheck[32];
    printf("%s", "Enter Username:\n");
    
    scanf("%s", *user);
    printf("%s", *user);
    
    /*
    if (!userInDatabase(*user)){
        printf("%s", "Name not found\n");
        return;
    }
    */
    printf("%s", "Enter Password: \n");
    
    scanf("%s", *pass);
    
    printf("%s", "No problems yet\n");
    currentUser = fopen(*user, "r");
    printf("%s", "Password is:\n");
    printf("%s", *pass);
    *passwordCheck = readPass(currentUser);
    
    if (strcmp(*pass, *passwordCheck) == 0){
        printf("%s", "youre in");
        fgetpos(currentUser, position);
        printf("%s", "file position is ");
        printf("%ld", ftell(currentUser));
        printf("%s", "\n");
        return ;
    }else {
        printf("%s", "incorrect password \n");
        fclose(currentUser);
        return;
    }

}
/*
bool userInDatabase(char ** nameToCheck){
    users = fopen("userfiles", "r");
    if (!users){
        printf("%s", "Failed to open file\n");
    }
    // TODO: check if username is in database
    return true;
    if (users != NULL){
        fclose(users);
    }
}
*/
//function to read the password to a file
char * readPass(FILE* file){
    char * pass[32];
    //make sure at the beginning of file
    rewind(file);
    fscanf(file, "%32s", *pass);
    return *pass;
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