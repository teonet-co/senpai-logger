/**
* \file senpai-logger.c
* \author max
* Created on Thu Jul 16 20:04:10 2020
*
*/

#ifndef SENPAI_LOGGER_H
#define SENPAI_LOGGER_H

#include <netdb.h>
#include <sys/socket.h>

typedef struct gelf_config {
    char *version;
    struct sockaddr_in servaddr;
    int socket;
} gelf_config_t;

typedef struct gelf_msg gelf_msg_t;

gelf_config_t*  sl_gelf_config_init(const char *addr, int port);
void            sl_gelf_config_destroy(gelf_config_t *gelf_config);

gelf_msg_t* sl_msg_init(gelf_config_t *gelf_config);
void        sl_msg_destroy(gelf_msg_t *msg);
void        sl_msg_append_int(gelf_msg_t *msg, const char *key, int value);
void        sl_msg_append_string(gelf_msg_t *msg, const char *key, const char *value);
void        sl_msg_send(gelf_config_t *gelf_config, gelf_msg_t *msg);
#endif
