#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#include "forge.h"
#include "config.h"

// TODO: Todo list
/*
 *  1) Config Stuff to do
 *
 *  2) Refactoring
 *
 *  3) Clean/rename the AI-CI github repo
 */

char command[BUF_SIZE];

int main(int argc, char *argv[]) {
    
    if (argc <= 1) {
        printf("%s\n", forge_help_string);
        return 0;
    }
    
    char path[BUF_SIZE];
    if (getcwd(path, BUF_SIZE) == NULL) {
        printf("Error getting the current working directory!\n");
        return 1;
    }

    return HandleInput(path, argc, argv);
}

int HandleInput(char path[], int argc, char *argv[]) {
    while (argc > 1) {
        if (argv[1][0] == '-') {
            for (int i = 1; i < strlen(argv[1]); ++i) {
                switch (argv[1][i]) {
                    case 'h':
                        printf("%s\n", forge_help_string);
                        break;
                    default:
                        printf("Invalid Argument: -%c\n", argv[1][i]);
                        return 0;
                }
            }
            
        }
        else {
            if (!strcmp(argv[1], "commit")) {
                if (!ValidateDirectory(path)) {
                    printf("You must run 'forge init' before being able to run any other commands!\n");
                    return 1;
                }
                return HandleCommit(argc, argv);
            }
            if (!strcmp(argv[1], "init"))
                return HandleInit(path);
            if (!strcmp(argv[1], "status")) {
                if (!ValidateDirectory(path)) {
                    printf("You must run 'forge init' before being able to run any other commands!\n");
                    return 1;
                }
                return HandleStatus(path);
            }
        }
        
        ++argv;
        --argc;
    }

    return 1;
}

int HandleCommit(int argc, char *argv[]) {    
    if (argc <= 2) {
        printf("Must provide valid flag to commit!\n");
        return 0;
    }
    
    if (argv[2][0] == '-') {
        switch (argv[2][1]) {
            case 'm':
                if (argc <= 3) {
                    printf("No message added! Not committing!\n");
                    return 0;
                }

                snprintf(command, 
                    sizeof(command), 
                    "docker run -e CMT_MSG='%s' -e PAT='%s' -v `pwd`:/home/AI-CI ghcr.io/sigil-ml/commit_pipeline:latest", 
                    argv[3], ForgeConfig.PAT);
                break;
            default:
                printf("Invalid Argument: -%c\n", argv[2][1]);
                return 0;
        }
    }

    int status = system(command);

    if (status < 0) {
        printf("Docker commit failed to run!\n");
    }

    return status;
}

int HandleInit(const char *path) {
    if (!ValidateGit(path)) {
        printf("This is intended to be ran in a git repository. Are you sure you are in the right directory?\n");
        return 0;
    }
    
    if (!Init(path)) {
        printf("Init failed!\n");
        return 0;
    }
    
    printf("Initialization successful!\n");

    return 1;
}

int HandleStatus(const char *path) {
    if (!ValidateGit(path)) {
        printf("This is intended to be ran in a git repository. Are you sure you are in the right directory?\n");
        return 0;
    }
    
    snprintf(command, sizeof(command), "git status");
    
    int status = system(command);

    if (status < 0) {
      printf("Error checking forge status!\n");
    }

    return status;
}

int Init(const char *path) {
    int check;
    char* dirName = ".forge";
    
    check = mkdir(dirName, 0744);
    
    if (check < 0) {
        printf("Unable to create directory. Forge might already be initalized!\n");
        return 0;
    }

    ForgeConfig.PAT = "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";
    
    return 1;
}

int FindTargetInDir(const char *path, const char *targetName) {
    int isValid = 0;
    
    struct dirent *dp;
    DIR *dir = opendir(path);
    
    if (!dir) {
        printf("Error opening directory contents!\n");
        return isValid;
    }
    
    int found_target = 0;
    while ((dp = readdir(dir)) != NULL) {
        if (!strcmp(dp->d_name, targetName)) {
            found_target = 1;
            break;
        }
    }
    
    closedir(dir);
        
    return found_target;
}

int ValidateGit(const char *path) {
    return FindTargetInDir(path, ".git");
}

int ValidateForge(const char *path) {
    return FindTargetInDir(path, ".forge");
}

int ValidateDirectory(const char *path) {
    return ValidateForge(path) & ValidateGit(path);
}