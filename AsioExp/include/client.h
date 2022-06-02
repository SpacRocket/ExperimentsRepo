//
// Created by Jakub Miros on 23/05/2022.
//

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#endif //SERVER_CLIENT_H

#include <iostream>
#include <olc_net.h>
#include <net_client.h>

enum class CustomMsgTypes : uint32_t{
    FireBullet,
    MovePlayer
};

class CustomClient : public client_interface<CustomMsgTypes>{
public:
    bool FireBullet(float x, float y)
    {
        message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::FireBullet;
        msg << x << y;
        Send(msg);
    }
};

int main()
{
    message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::FireBullet;

    return 0;
}
