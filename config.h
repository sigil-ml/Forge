#ifndef HEADER_CONFIG
#define HEADER_CONFIG

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

struct ForgeConfig {
    const char *PAT;
    const char *SRCFLDER;
};

static struct ForgeConfig ForgeConfig;

#endif