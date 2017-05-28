#include "game.h"
#include"board.h"

#include"put_strategy.h"
#include"move_strategy.h"
#include"pop_strategy.h"
#include <windows.h>
#include<iostream>
#include <stdio.h>
#include<string>

using namespace  std;
#pragma comment(lib, "Ws2_32.lib")

int sgetline(int fd, char ** out)
{
    int buf_size = 128;
    int bytesloaded = 0;
    int ret;
    char buf;
    char *buffer = (char*)calloc(buf_size, sizeof(char));
    char * newbuf;

    if (NULL == buffer)
        return -1;

    do
    {
        // read a single byte
        ret = recv(fd, &buf, 1, 0);
        if (ret < 1)
        {
            // error or disconnect
            free(buffer);
            return -1;
        }

        buffer[bytesloaded] = buf;
        bytesloaded++;

        // has end of line been reached?
        if (buf == '\n')
            break; // yes

        // is more memory needed?
        if (bytesloaded >= buf_size)
        {
            buf_size += 128;
            newbuf = (char*)realloc(buffer, buf_size);

            if (NULL == newbuf)
            {
                free(buffer);
                return -1;
            }

            buffer = newbuf;
        }
    }while (true);

    // if the line was terminated by "\r\n", ignore the
    // "\r". the "\n" is not in the buffer
    if ((bytesloaded) && (buffer[bytesloaded-1] == '\r'))
        bytesloaded--;

    *out = buffer; // complete line
    return bytesloaded; // number of bytes in the line, not counting the line break
}

int sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1,1), &wsa_data);
#else
    return 0;
#endif
}

int sockQuit(void)
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

int sockClose(SOCKET sock)
{

    int status = 0;

#ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0) { status = closesocket(sock); }
#else
    status = shutdown(sock, SHUT_RDWR);
    if (status == 0) { status = close(sock); }
#endif

    return status;

}

Game::Game()
{
    board = new Board();
    myinhandcheckernum=12;
    msg_recieve="";
    msg_send="";
    sock = -1;
}

Game::Game(string serveraddress, int serverport, string name) : Game()
{
    server_address = serveraddress;
    server_port = serverport;
    teamname = name;
}


Game::~Game()
{
    if(board)
        delete board;
    board=nullptr;
}

Board& Game::get_board()
{
    return *board;
}

bool Game::start_client(){
    sockInit();
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        perror("Could not create socket");
    }
    //setup address structure
    if(inet_addr(server_address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;

        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( server_address.c_str() ) ) == NULL)
        {
            //gethostbyname failed

            return false;
        }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
            break;
        }
    }

    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( server_address.c_str() );
    }

    server.sin_family = AF_INET;
    server.sin_port = htons( server_port );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }


    return true;

}

void Game::start(){
    string reg = "REGISTER " + teamname + '\n';
    int l = send(sock , reg.c_str() , strlen( reg.c_str() ) , 0);    
    int flag=0;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
    if (l< 0){
        printf("ERROR!");
    };
    char* buf;
    int ret;

    while (true){
        // read a single line
        ret = sgetline(sock, &buf);
        if (ret < 0)
            break; // error/disconnect

        // is it a 0-length line?
        if (ret == 0)
        {
            printf("End of Headers detected.\n");
            free(buf);
            break;
        }

        msg_send="";
        if(strcmp("FINISH",(char*)buf)==0)
            break;
        play_round(buf);
        msg_send += "\n";
        send(sock,msg_send.c_str(),strlen(msg_send.c_str()),0);
        int flag = 0;
        setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
        free(buf);
    }
}

void Game::play_round(char *message)
{
    dooz=false;
    //message = "e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,12,12,10";
    char chboard[49];
    int m,o,round;
    sscanf(message,"%47s,%d,%d,%d", chboard, &m, &o, &round);
    string str_board(chboard);
    board->update(str_board);

    myinhandcheckernum = m;
    oppinhandcheckernum = o;
    cycle = round;

    if(myinhandcheckernum > 0)
        put_strategy(this);
    else
        move_strategy(this);
    if(dooz)
        pop_strategy(this);
}

int Game::get_myinhandcheckernum()
{
    return myinhandcheckernum;
}

int Game::get_oppinhandcheckernum()
{
    return oppinhandcheckernum;
}

void Game::update_cell_arrays()
{
    board->get_emptyCells().clear();
    board->get_myCells().clear();
    board->get_oppCells().clear();

    for(int i=0;i<8;i++)
        for(int j=0;j<3;j++)
        {
            if(board->get_cell(i,j).get_checker()==nullptr)
                board->get_emptyCells().push_back(&board->get_cell(i,j));
            else if(board->get_cell(i,j).get_checker()->isMyChecker())
                board->get_myCells().push_back(&board->get_cell(i,j));
            else
                board->get_oppCells().push_back(&board->get_cell(i,j));
        }
}

void Game::put(Pos p)
{
    msg_send = "put "+std::to_string(p.getx())+"," +std::to_string(p.gety());
    board->get_cell(p.getx(),p.gety()).set_checker(p.getx(),p.gety(),'m');
    update_cell_arrays();
    check_dooz(p);
}

void Game::pop(Checker* c)
{
    msg_send += (" " + std::to_string(c->get_pos().getx()) + ',' + std::to_string(c->get_pos().gety()));
    board->get_cell(c->get_pos()).checker=nullptr;
}

void Game::move(Checker* c,Pos newpos)
{
    msg_send = "mov "+std::to_string(c->get_pos().getx())+','+std::to_string(c->get_pos().gety())+','+std::to_string(newpos.getx())+','+std::to_string(newpos.gety());
    board->get_cell(c->get_pos()).checker=nullptr;
    board->get_cell(newpos).set_checker(newpos.getx(),newpos.gety(),'m');
    update_cell_arrays();
    check_dooz(newpos);
}

void Game::check_dooz(Pos p)
{
    bool status = true;
    for (int j = 0; j < 3; j++)
        if (board->get_cells()[p.getx()][j].get_checker() == nullptr || !board->get_cells()[p.getx()][j].get_checker()->isMyChecker())
        {
            status = false;
            break;
        }
    if (status) {
        dooz = true;
        return;
    }

    status = true;
    if (p.getx() % 2 == 0) {
        for (int i = 0; i < 3; i++)
            if (board->get_cell((p.getx() + i) % 8, p.gety()).get_checker() == nullptr || !board->get_cell((p.getx() + i) % 8, p.gety()).get_checker()->isMyChecker())
                status = false;
        if(status)
        {
            dooz = true;
            return;
        }
        status = true;
        for (int i = 0; i < 3; i++)
            if (board->get_cell((p.getx() - i + 8) % 8, p.gety()).get_checker() == nullptr || !board->get_cell((p.getx() - i + 8) % 8, p.gety()).get_checker()->isMyChecker())
                status = false;
    } else {
        for (int i = -1; i < 2; i++)
            if (board->get_cell((p.getx() + i) % 8, p.gety()).get_checker() == nullptr || !board->get_cell((p.getx() + i) % 8, p.gety()).get_checker()->isMyChecker())
            {
                status = false;
            }

    }
    if (status) {
        dooz = true;
    }
}


int Game::get_cycle()
{
    return cycle;
}
