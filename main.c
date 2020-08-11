#include "senpai-logger.h"

int main() {
    gelf_config_t *gelf_config = sl_gelf_config_init("127.0.0.1", 12211);
    gelf_msg_t *msg = sl_msg_init(gelf_config);
    sl_msg_append_string(msg, "short_message", "Dima hello!:)");
//
//    sl_msg_send(gelf_config, msg);
    sl_msg_destroy(msg);
    sl_gelf_config_destroy(gelf_config);
}
