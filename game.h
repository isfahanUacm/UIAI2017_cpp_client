#ifndef GAME_H
#define GAME_H
#include"board.h"

#ifdef _WIN32
  /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>

#else
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */
#endif


class Game
{
    bool dooz;
    Board* board;
    int myinhandcheckernum;
    int oppinhandcheckernum;
    string msg_send, msg_recieve;
    int server_port;
    string server_address;
    int sock;
    struct sockaddr_in server;
    string teamname;
    int cycle;
public:
    Game();
    Game(string, int, string);
    ~Game();
    Board& get_board();
    bool start_client();
    void start();
    void play_round(char *);
    int get_myinhandcheckernum();
    int get_oppinhandcheckernum();
    void put(Pos p);
    void pop(Checker* c);
    void move(Checker* c,Pos newpos);
    int get_cycle();
    void check_dooz(Pos p);

};

#endif // GAME_H
