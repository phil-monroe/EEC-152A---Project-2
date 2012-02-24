#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Pre-declarations -----------------------------------------------------------
void init(char**, char**, int, char**);
void print_header(char*, char*);
void get_request(char**, size_t*);
void print_help_message();
void DFTP_request(char*);


// main -----------------------------------------------------------------------
int main(int argc, char* argv[]){
	// Initialize variables
	char *host, *port;
	size_t req_size = 256;
	char* request = (char*) malloc(req_size * sizeof(char));
	init(&host, &port, argc, argv);
	
	// TODO - Calculate IP
	

	print_header(host, port);
	
	while(1){
		get_request(&request, &req_size);

		if(strcmp(request, "quit") == 0){
			break;
		}else if(strcmp(request, "help") == 0){
			print_help_message();
		}else{
			DFTP_request(request);
		}
	}
	
	puts("Goodbye.");
	free(request);
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
void print_header(char* host, char* port){
	printf("Welcome to the simple DFTP client.\n");
	printf("Connecting to %s(Calc IP) on port %s.\n", host, port);
}


// get_request ----------------------------------------------------------------
void get_request(char** request, size_t* size){
	printf("command > ");
	getline(request, size, stdin);
	char* newline = strchr(*request, '\n');
	*newline = '\0';
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
void DFTP_request(char* request){
	// TODO - Connect to server
	puts(request);
}
