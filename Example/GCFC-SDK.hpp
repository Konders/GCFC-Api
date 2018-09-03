#include <sstream>
#include <vector>
#include <winsock2.h>
#include "gason.hpp"
#pragma comment(lib,"ws2_32.lib")
namespace GCFC {
	struct Config_t
	{
		std::string Name; // Config name
		std::string Config; // Settings
		std::string Description; // Config Desciption
		std::string Type; // Type (Legit,Semi-rage,Rage,Other)
		std::string Owner; // Config owner
		std::string File_type; // File type(default: ini)
	};
	//Response parsing
	std::vector<Config_t> Parse(char* json)
	{
		std::vector<Config_t> configs;
		gason::JsonAllocator    allocator;
		gason::JsonValue        root;
		//parse our response
		gason::JsonParseStatus  status = gason::jsonParse(json, root, allocator);
		if (status != gason::JSON_PARSE_OK) {
			//parsing failed!
			return configs;
		}
		//fill our vector<Config_t> configs
		gason::JsonIterator it = gason::begin(root);
		while (it.isValid()) {
			configs.insert(configs.end(), Config_t{
				it->value.child("name").toString() ,
				it->value.child("config").toString(),
				it->value.child("description").toString(),
				it->value.child("type").toString(),
				it->value.child("owner").toString(),
				it->value.child("file_type").toString() });
			it++;
		}
		return configs;

	}
	//Send GET request and get response
	std::string GetResponse(std::string api, std::string user_key, std::string hostname = "api.gcfc.ru")
	{
		std::string request;
		std::string response;
		int resp_leng;
		char buffer[1024];
		struct sockaddr_in serveraddr;
		int sock;
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			printf("WSAStartup() failed\r\n");

		struct hostent *host;
		host = gethostbyname(const_cast<char*>(hostname.c_str()));

		int port = 80;
		if(api.length() == 0 && user_key.length() == 0)
			request += "GET /configs?test=true HTTP/1.0\r\n";
		else
			request += "GET /configs?api_key=" + api + "&user_key=" + user_key +" HTTP/1.0\r\n";
		request += "Host:  " + hostname + "\r\n";
		request += "User-Agent: GCFC SDK \r\n";
		request += "\r\n";

		if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
			printf("socket() failed\r\n");

		memset(&serveraddr, 0, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;

		serveraddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

		serveraddr.sin_port = htons((unsigned short)port);

		struct in_addr **addr_list;

		addr_list = (struct in_addr **) host->h_addr_list;

		response = "";

		if (connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
			printf("connect() failed\r\n");

		if (send(sock, request.c_str(), request.length(), 0) != request.length())
			printf("send() sent a different number of bytes than expected\r\n");

		resp_leng = 1024;

		while (resp_leng > 0)
		{

			resp_leng = recv(sock, (char*)&buffer, 1024, 0);

			if (resp_leng > 0)
				response += std::string(buffer).substr(0, resp_leng);
		}

		closesocket(sock);
		WSACleanup();
		//get response(without header)
		response = response.substr(response.find("\r\n\r\n") + 4);
		return response;
	}
}