#include <winsock2.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

char buffer[BUFFER_SIZE];

char decode(char c)
{
    /* decode character */
	return c;
}

char* readMessage(SOCKET socket, char *header, int len)
{
    int i, header_len;
	long msg_len;
	size_t total_len;
	char *msg;
	WSABUF DataBuf;
	DWORD RecvBytes, Flags;
	WSAOVERLAPPED RecvOverlapped = {0};
	RecvOverlapped.hEvent = WSACreateEvent();
	DataBuf.len = BUFFER_SIZE;
    DataBuf.buf = buffer;

	WSARecv(socket, &DataBuf, 1, &RecvBytes, &Flags, &RecvOverlapped, NULL);
	msg_len = atol(DataBuf.buf);
	header_len = strlen(header);
	total_len = header_len;
	total_len += msg_len; /* POSSIBLE INTEGER OVERFLOW HERE */

	msg = (char*)malloc(total_len); /* USAGE OF OVERFLOWED VALUE */
	if (!msg) {
		return 0;
	}

	strcpy(msg, header);

	DataBuf.len = msg_len;
    DataBuf.buf = msg + msg_len;
	WSARecv(socket, &DataBuf, 1, &RecvBytes, &Flags, &RecvOverlapped, NULL);

	for (i = header_len; i < total_len; i++) { /* USAGE OF OVERFLOWED VALUE */
		msg[i] = decode(msg[i]); /* USAGE OF OVERFLOWED VALUE */
	}
	return msg;
}
