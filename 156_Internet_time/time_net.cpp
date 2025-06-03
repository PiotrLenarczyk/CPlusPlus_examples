#ifdef __GNUC__
#include <iostream>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#else 	//Windows
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctime>
#pragma comment(lib, "ws2_32.lib")
#endif


#define NTP_TIMESTAMP_DELTA 2208988800ull

// NTP packet is 48 bytes
struct NTPPacket {
	uint8_t li_vn_mode = 0x1b; // LI = 0, VN = 3, Mode = 3 (client)
	uint8_t stratum = 0;
	uint8_t poll = 0;
	uint8_t precision = 0;
	uint32_t rootDelay = 0;
	uint32_t rootDispersion = 0;
	uint32_t refId = 0;
	uint32_t refTm_s = 0;
	uint32_t refTm_f = 0;
	uint32_t origTm_s = 0;
	uint32_t origTm_f = 0;
	uint32_t rxTm_s = 0;
	uint32_t rxTm_f = 0;
	uint32_t txTm_s = 0;
	uint32_t txTm_f = 0;
};

int main() {
#ifdef __GNUC__
	const char* ntpServer = "pool.ntp.org";
	int sockfd;
	sockaddr_in serverAddr{};

	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0) {
		perror("Socket creation failed");
		return 1;
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(123); // NTP UDP port

	hostent* server = gethostbyname(ntpServer);
	if (!server) {
		std::cerr << "Failed to resolve hostname.\n";
		return 1;
	}

	std::memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);

	NTPPacket packet{};
	if (sendto(sockfd, &packet, sizeof(NTPPacket), 0,
			   (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("Send failed");
		return 1;
	}

	socklen_t serverLen = sizeof(serverAddr);
	if (recvfrom(sockfd, &packet, sizeof(NTPPacket), 0,
				 (sockaddr*)&serverAddr, &serverLen) < 0) {
		perror("Receive failed");
		return 1;
	}

	packet.txTm_s = ntohl(packet.txTm_s); // Convert NTP time to host byte order
	time_t txTime = packet.txTm_s - NTP_TIMESTAMP_DELTA;

	std::cout << "Current time (UTC): " << ctime(&txTime);

	close(sockfd);
	return 0;
#else 	//Windows

   WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed.\n";
		return 1;
	}

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Socket creation failed.\n";
		WSACleanup();
		return 1;
	}

	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(123);
	inet_pton(AF_INET, "129.6.15.28", &serverAddr.sin_addr); // time.nist.gov

	NTPPacket packet{};
	int sendResult = sendto(sock, (char*)&packet, sizeof(packet), 0,
							(sockaddr*)&serverAddr, sizeof(serverAddr));
	if (sendResult == SOCKET_ERROR) {
		std::cerr << "Sendto failed.\n";
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	int serverAddrSize = sizeof(serverAddr);
	int recvResult = recvfrom(sock, (char*)&packet, sizeof(packet), 0,
							  (sockaddr*)&serverAddr, &serverAddrSize);
	if (recvResult == SOCKET_ERROR) {
		std::cerr << "Recvfrom failed.\n";
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	packet.txTm_s = ntohl(packet.txTm_s);
	time_t txTime = packet.txTm_s - NTP_TIMESTAMP_DELTA;

	std::cout << "Current time (UTC): " << ctime(&txTime);

	closesocket(sock);
	WSACleanup();
	return 0;
#endif
}
