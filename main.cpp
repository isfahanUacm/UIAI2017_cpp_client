#include<iostream>
#include"game.h"
#include <stdio.h>
using namespace std;
int main()
{
    Game game("127.0.0.1", 9999, "team1");
    if (game.start_client())
        game.start();
    // in each cycle update must call and also msg_send = "" and determining dooz status!

    // wait for message on socket


}
