#ifndef HEADER_FORGE
#define HEADER_FORGE

const char forge_help_string[] =
    "Usage: forge [--version] [--help]\n"
    "             <command> [<args>]\n"
    " Common commands:\n"
    "     commit	Run the commit CI pipeline and rechord changes to repo.\n"
    "     status    Run the status command to see repo and forge updates.\n";

int commit_flag = 0;

int HandleInput(char path[], int argc, char *argv[]);

int HandleCommit(int argc, char *argv[]);
int HandleInit(const char *path);
int HandleStatus(const char *path);

int Init(const char *path);

int FindTargetInDir(const char *path, const char *targetName);
int ValidateGit(const char *path);
int ValidateForge(const char *path);

int Validate(const char *path);
int ValidateDirectory(const char *path);

#endif