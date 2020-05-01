#include "SFML/Network.hpp"
#include <iostream>
#include <string>
#include <vector>

#define SERVEUR_ACCESS "CONNECT"
#define SERVEUR_PORT 55000

int main()
{
	// ----- The server -----
	std::string message("");
	sf::UdpSocket socket;
	socket.bind(SERVEUR_PORT);


	int nombreClient(0);
	std::vector<unsigned short> portClients;
	std::vector<sf::IpAddress> addressClients;
	// Receive a message from anyone
	char buffer[1024];
	std::size_t received = 0;
	sf::IpAddress addressClient;
	unsigned short portClient;
	int continuer(1);
	while (continuer && message != "STOP")
	{	
		socket.receive(buffer, sizeof(buffer), received, addressClient, portClient);
		message = buffer;
		if (message == SERVEUR_ACCESS)
		{
			++nombreClient;
			portClients.push_back(portClient);
			addressClients.push_back(addressClient);
			std::cout << addressClient.toString() << " port " << portClient << " connect to the serveur!" << std::endl << "Now " << nombreClient << " connected !" << std::endl;
		}
		else if (message == "STOP")
		{
			// Déconnection du joueur
		}
		else
		{
			for (int i(0);i<nombreClient;++i)
			{
				if (portClients[i] != portClient || addressClients[i] != addressClient)
				{
					socket.send(message.c_str(), message.size() + 1, addressClients[i], portClients[i]);
				}
				else
				{
					std::cout << addressClients[i].toString() << " port " << portClients[i] << " dit: " << message << std::endl;
				}
			}
		}
	}
	system("pause");
}
