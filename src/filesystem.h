// filesystem.h
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>

// Structure representing a file
typedef struct {
    char name[256];
    uint32_t size;
    uint32_t permissions;
    uint32_t creation_time;
} Fichier;

// Structure representing a directory
typedef struct {
    char name[256];
    uint32_t num_files;
    Fichier* files;
} Dossier;

// Function declarations
Fichier* create_file(const char* name, uint32_t size, uint32_t permissions);
void delete_file(Fichier* file);
Dossier* create_directory(const char* name);
void delete_directory(Dossier* directory);
void add_file_to_directory(Dossier* directory, Fichier* file);
void remove_file_from_directory(Dossier* directory, const char* file_name);

#endif // FILESYSTEM_H
