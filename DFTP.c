#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

// Defines --------------------------------------------------------------------
#define BUF_SIZE 1024

// Pre-declarations -----------------------------------------------------------
void init(char**, char**, int, char**);
void print_header(char*, char*, char*);
void get_request(char**, size_t*);
void print_help_message();
void DFTP_request(char*, struct addrinfo*);
void get_ip(struct addrinfo*, char*);
struct addrinfo* get_addrinfo(struct addrinfo* , char* , char* );



// main -----------------------------------------------------------------------
int main(int argc, char* argv[]){
	// Initialize variables
	char *host, *port, ipstr[INET6_ADDRSTRLEN];
	size_t req_size = BUF_SIZE;
	char* request = (char*) malloc(req_size * sizeof(char));
	
	init(&host, &port, argc, argv);
	
	// Get IP from DNS
  struct addrinfo hints, *res;
	res = get_addrinfo(&hints, host, port);
	get_ip(res, ipstr);
	
	// Print Header and start console
	print_header(host, ipstr, port);
	while(1){
		get_request(&request, &req_size);

		if(strcmp(request, "quit\n") == 0){
			break;
		}else if(strcmp(request, "help\n") == 0){
			print_help_message();
		}else{
			DFTP_request(request, res);
		}
	}
	
	puts("Goodbye.");
  freeaddrinfo(res); 	// free the results list
	free(request);			// free request buffer
	return 0;
}


// init -----------------------------------------------------------------------
void init(char** host, char** port, int argc, char* argv[]){
	if(argc > 1){
		*host = argv[1];
	}else{
		*host = "unyama.cs.ucdavis.edu";
	}
	
	if(argc > 2){
		*port = argv[2];
	}else{
		*port = "10000";
	}
}


// print_header ---------------------------------------------------------------
void print_header(char* host, char* ip, char* port){
	printf("Welcome to the simple DFTP client.\n");
	printf("Connecting to %s(%s) on port %s.\n", host, ip, port);
}


// get_request ----------------------------------------------------------------
void get_request(char** request, size_t* size){
	printf("command > ");
	getline(request, size, stdin);
}


// print_help_message ---------------------------------------------------------
void print_help_message(){
	puts("help - Prints this message");
	puts("quit - Exits the program");
	puts("GET <filename> - Gets the filename from the DFTP server");
	puts("PUT <user's name> - Puts you name in a file on the DFTP server");
	puts("COMMENT <user's comment> - Puts a comment in a file on the DFTP server");
}


// DFTP_request ---------------------------------------------------------------
void DFTP_request(char* send_buf, struct addrinfo* server){
	char recv_buf[BUF_SIZE];
	int status;
	int n_bytes;

	// Create the socket
	int sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

	// Connect
	status = connect(sockfd, server->ai_addr, server->ai_addrlen);
	if(status < 0){
		fprintf(stderr, "A connection error occured.");
		return;
	}

	// SEND!
	n_bytes = send(sockfd, send_buf, strlen(send_buf), 0);

	// Keep recieving data til n_bytes recieved == 0
	while((n_bytes = recv(sockfd, recv_buf, BUF_SIZE, 0)) > 0){
		recv_buf[n_bytes]='\0'; 			// Be sure to null terminate the string
		printf("%s", recv_buf);
	}
	
	// Close socket
	close(sockfd);
}


// get_ip ---------------------------------------------------------------------
void get_ip(struct addrinfo* res, char* ipstr){
  void *addr;
  char *ipver;

  // get the pointer to the address itself,
  // different fields in IPv4 and IPv6:
  if (res->ai_family == AF_INET) { // IPv4
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
  } else { // IPv6
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
  }

  // convert the IP to a string
  inet_ntop(res->ai_family, addr, ipstr, INET6_ADDRSTRLEN);
}


// get_addrinfo ---------------------------------------------------------------
struct addrinfo* get_addrinfo(struct addrinfo* hints, char* host, char* port){
	int status;
	struct addrinfo* res;
  memset(hints, 0, sizeof(struct addrinfo));
  hints->ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
  hints->ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(host, port, hints, &res)) != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
      exit(2);
  }
	return res;
}

