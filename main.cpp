#include "senpai.hpp"

using namespace senpai;
int main() {
    GelfConnection gelf_con{"127.0.0.1", 12211};

    GelfMessage gelf_msg{};
    gelf_msg.AppendField("short_message", "Dima hello from CPP !:)");

    gelf_con.SendMessage(gelf_msg);
}
