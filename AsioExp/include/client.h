//
// Created by Jakub Miros on 23/05/2022.
//

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#endif //SERVER_CLIENT_H

#include <iostream>
#include <olc_net.h>

enum class CustomMsgTypes : uint32_t{
    FireBullet,
    MovePlayer
};

int main()
{
    message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::FireBullet;

    return 0;
}
