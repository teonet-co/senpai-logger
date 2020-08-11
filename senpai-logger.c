/**
* \file senpai-logger.c
* \author max
* Created on Thu Jul 16 20:04:10 2020
*/

#include "senpai-logger.h"

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include <json-c/json.h>

struct gelf_msg {
    json_object *json_obj;
};

#define append_msg(X, Y, Z) _Generic((Z),   \
      int : sl_msg_append_int,              \
      char* : sl_msg_append_string)         \
      ((X), (Y), (Z))

gelf_config_t *sl_gelf_config_init(const char *addr, int port) {
    const char* version = "1.1";

    gelf_config_t *config = malloc(sizeof(gelf_config_t));
    config->version = strdup(version);

    memset(&config->servaddr, 0, sizeof(config->servaddr));
    config->servaddr.sin_family = AF_INET;
    config->servaddr.sin_port = htons(port);
    inet_pton(AF_INET, addr, &config->servaddr.sin_addr);

    config->socket = socket(AF_INET, SOCK_DGRAM, 0);

    return config;
}

void sl_gelf_config_destroy(gelf_config_t *gelf_config) {
    free(gelf_config->version);
    free(gelf_config);
}


void sl_msg_append_int(gelf_msg_t *msg, const char *key, int value) {
    json_object *val_obj = json_object_new_int(value);
    json_object_get(val_obj);
    json_object_object_add(msg->json_obj, key, val_obj);
    printf("msg->json_obj.to_string()=%s\n", json_object_to_json_string(msg->json_obj));
    json_object_put(val_obj);
}

void sl_msg_append_string(gelf_msg_t *msg, const char *key, const char *value) {
    json_object *val_obj = json_object_new_string(value);
    json_object_get(val_obj);
    json_object_object_add(msg->json_obj, key, val_obj);
    printf("msg->json_obj.to_string()=%s\n", json_object_to_json_string(msg->json_obj));
    json_object_put(val_obj);
}

gelf_msg_t *sl_msg_init(gelf_config_t *gelf_config) {
    gelf_msg_t *msg = malloc(sizeof(gelf_msg_t));
    msg->json_obj = json_object_new_object();
    sl_msg_append_string(msg, "version", gelf_config->version);
    return msg;
}

void sl_msg_destroy(gelf_msg_t *msg) {
    json_object_put(msg->json_obj);
    free(msg);
}

void sl_msg_send(gelf_config_t *gelf_config, gelf_msg_t *msg) {
    const char *msg_str = json_object_to_json_string(msg->json_obj);
    sendto(gelf_config->socket, msg_str, strlen(msg_str), 0, (struct sockaddr *)&gelf_config->servaddr, sizeof(gelf_config->servaddr));
}