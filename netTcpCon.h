#ifndef __NET_TCP_CON
#define __NET_TCP_CON

void InitNetConClient(char *ipaddress, short port);

void InitNetConServer(short port);

int nConSend(int type, char *data, int length);

int nConRecv(char *data, int length);

#endif
