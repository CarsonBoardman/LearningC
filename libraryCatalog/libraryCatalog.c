#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

// Basic plan for this, each book will
// take up a certain number of bytes,
// catalog file will be oraganized in 
// chunks

// File structure as follows:
// First byte is next free id
// Each book will have 31 bytes
// of title, 31 bytes of author,
// 1 byte of inventory, and 1 
// byte of id

FILE * catalog;
void start();
void addBook();
void searchBook();
void checkout();
int choice;
bool quit;
int main(){
    // Open catalog file
    catalog = fopen("catalog", "r+");
    if (!catalog){
        printf("%s", "Failed to open catalog file\n");
        return 1;
    }
    quit = false;
    
    while (!quit){
        start();
    }
    if (catalog != NULL){
        fclose(catalog);
    }
    return 0;
}
void start(){
    
    printf("%s", "1. Search Book\n2. Add Book\n3. Checkout Book\n4. Quit\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("\033[2J\033[1;1H");
        searchBook();
        break;
    case 2:
    printf("\033[2J\033[1;1H");
        addBook();
        printf("\033[2J\033[1;1H");
        break;
    case 3:
    printf("\033[2J\033[1;1H");
        checkout();
        printf("\033[2J\033[1;1H");
        break;
    case 4:
        quit = true;
        break;
    default:
        printf("%s", "That's not a choice\n");
        break;
    }

}
void addBook(){
    char name[30];
    char author[30];
    int invintory = 0;
    int id = 0;

    printf("%s", "Enter book title\n");
    scanf("%s", name);
    printf("%s", "Enter book author\n");
    scanf("%s", author);
    printf("%s", "How many are there?\n");
    scanf("%d", &invintory);
    // Go to beginning of file
    rewind(catalog);
    // Reads the next available id
    // and writes it to id
    fscanf(catalog, "%d", &id);
    
    // Go to the end of the file
    fseek(catalog, ((id * 64) + 1), SEEK_SET); 
    // Adds the book
    fprintf(catalog, "%29s %29s %d %d", name, author, invintory, id);
    printf("%s %d %s", "book added with id ", id, "\n");
    // Incraments the next available id
    rewind(catalog);
    id = (id + 1);
    fprintf(catalog, "%d", id);
 
}
void searchBook(){
    char search[29];
    char searchValue[29];
    int  match;
    int id;
    bool found;
    fpos_t position;
    printf("%s", "Search by:\n1: Title\n2. Author\n3. id\n");
    scanf("%d", &choice);
    switch (choice){
        case 1:
        // If they search by title;
            printf("%s", "Enter search value\n");
            // 'search' is the title being searched for
            scanf("%s", search);
            
            // Postion is set to one byte into the file,
            // just after the id byte, to the first title
            fseek(catalog, 1, SEEK_SET);
            found = false;
            // Now for the loop to check every book
            int i = 0;
            while (!found){
            // Grabs the title of book in focus
            fscanf(catalog, "%29s", searchValue);
            // And the position is recorded
            fgetpos(catalog, &position);
                // If it matches the search value...
                if (strcmp(search, searchValue) == 0){
                    // The position will jump to
                    // the id of the book
                    fseek(catalog, 33, SEEK_CUR);
                    // Id is read to the match
                    fscanf(catalog, "%d", &match);
                    // found is now true to stop the loop
                    found = true;
                    }
            // Check if the end of file
            if (feof(catalog)){
                break;
            }
            i++;
            // If its not the end it will go to the next title
            fsetpos(catalog, &position);
            fseek(catalog, 29, SEEK_CUR);
            }
            printf("%s %d %s", "Match found at id ", &match, "\n");
            printf("%d %s", i, "\n");
            break;
        case 2:
        // Pretty similar but with important differences
            printf("%s", "Enter search value\n");
            // 'search' is the title being searched for
            scanf("%s", search);
            // Postion is set to 31 bytes into the file,
            // just after the first title
            fseek(catalog, 32, SEEK_SET);
            found = 0;
            // Now for the loop to check every book
            while (!found){
                
            // Grabs the title of book in focus
            fscanf(catalog, "%29s", searchValue);
            // And the position is recorded
            fgetpos(catalog, &position);
                // If it matches the search value...
                if (strcmp(search, searchValue)){
                    // The position will jump to
                    // the id of the book
                    fseek(catalog, 1, SEEK_CUR);
                    // Id is read to the match
                    fscanf(catalog, "%d", &match);
                    // found is now true to stop the loop
                    found = true;
                    }
            // Check if the end of file
            if (feof(catalog)){
                break;
            }
            // If its not the end it will go to the next title
            fsetpos(catalog, &position);
            fseek(catalog, 64, SEEK_CUR);
            }
            printf("%s %d %s", "Match found at id ", match, "\n");
        case 3:
        // If search by id
        // Much simpler, I simply check if the next available id
        // is greater than the value searched for, and then go
        // to that book
        printf("%s", "Enter search value\n");
            // 'match' is the id being searched for
            // reusing a int var not otherwise used
            // in case 3
            scanf("%d", &match);
            // Goes to beginning and get next
            // available id
            rewind(catalog);
            fscanf(catalog, "%d", &id);
            // Check if there is a book with this id
            if (match >= id){
                printf("%s", "ID doesn't exist\n");
                break;
            }
            // Seeks to the id of the book before the searched 
            // book (64 * match)
            // then forward 64 bytes to the id of the searched 
            // book, then back 38 bytes to the title
            fseek(catalog, ((64 * match) + 20), SEEK_SET);\
            // Write the title to search, once again using an
            // unused variable
            fscanf(catalog, "%29s", search);
            printf("\033[2J\033[1;1H");
            printf("%s %s %s", "Match found with title ", search, "\n");
    }
}
void checkout(){

}