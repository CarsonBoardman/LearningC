//Simple console app to make a file for every user
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void registerUser();
void loginUser();
bool userInDatabase(char **);
char * readPass(FILE*);
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
    printf("%s", "got to here\n");
    {
        // Homemade code to print password to 
        // file, I know fprintf() exists but I'd 
        // rather figure out a solution myself
        char * passChar;
        for (int i = 0; i < 31; i++){ // Will write 32 bytes in total
            *pass[i] = *passChar;
            if (*passChar == 0){
            printf("%c", *pass[i]);
            putc(pass[i], newFile);
            } else {
                putc(0, newFile); // fill the rest of 32 bytes with null
            }
        }

    }
    {
        // Now record the username to the users file
        // Similar deal but I don't need to fill up all 32 bytes
        char * userChar;
        for (int i = 0; i < 31; i++){ // Will write 32 bytes in total
            *userChar = *user[i];
            
            putc(*user[i], users); // This inlcudes the null string terminator
            if (*userChar == 0){
                break;
            }
        }
    }
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

bool userInDatabase(char ** nameToCheck){
    users = fopen("userfiles", "r");
    if (!users){
        printf("%s", "Failed to open file\n");
    }
    // TODO: check if username is in database
    char * check;
    rewind(users);

    *check = fgetc(users);
    

    return true;
    if (users != NULL){
        fclose(users);
    }
}

//function to read the password to a file
char * readPass(FILE* file){
    char * pass[32];
    int len;
    //make sure at the beginning of file
    rewind(file);
    /*
    {
        // The password is followed by nulls to fill up space
        // I only need the password string
        for (int i = 0; i < 32; i ++){
            *pass[i] = fgetc(file);
            if (*pass[i] == 0){ // I put the check here because I need one null as a string terminator
                len = i;
                break;
            }
        }
    char * returnPass[len]; // If it breaks this is likily why, I think I should use malloc
    
    }
    */
    fscanf(file, "%32s", *pass);
    return *pass;
}


