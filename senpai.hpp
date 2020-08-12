/**
* \file senpai.cpp
* \author max
* Created on Tue Aug 11 16:06:44 2020
*/

#ifndef SENPAI_H
#define SENPAI_H

extern "C" {
#include "senpai-logger.h"
}

#include <string>

namespace senpai {

class GelfConnection;

class GelfMessage {
public:
  GelfMessage() {
    message = sl_msg_init();
  }

  ~GelfMessage() {
    sl_msg_destroy(message);
  }

  template<typename T>
  void AppendField(const char* key, T value) {
    sl_msg_append_int(message, key, value);
  }

  friend GelfConnection;

private:
  gelf_msg_t *message;
};

template<>
void GelfMessage::AppendField<const char*>(const char* key, const char* value) {
  sl_msg_append_string(message, key, value);
}
//template<>
//void GelfMessage::AppendField<std::string>(const char* key, const std::string& value) {
//    sl_msg_append_string(message, key, value.c_str());
//}

class GelfConnection {
public:
  GelfConnection(const char* addr, int port) {
    config = sl_gelf_config_init(addr, port);
  }

  ~GelfConnection() {
    sl_gelf_config_destroy(config);
  }

  void SendMessage(const GelfMessage& message) {
    sl_msg_send(config, message.message);
  }
private:
  gelf_config_t *config;
};

}

#endif
