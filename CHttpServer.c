# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <time.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

void log_error(const char *message) {
    FILE *logFile = fopen("server.log", "a");
    if (logFile == NULL) {
        perror("Failed to open log file server.log");
        return;
    }

    time_t now;
    time(&now);
    char *timeString = ctime(&now);
    timeString[strlen(timeString) - 1] = '\0'; // Remove newline character
    
    fprintf(logFile, "[%s] %s\n", timeString, message);

    fclose(logFile);
}

void handle_error(const char *message, const char* curErr) {
    char errorMessage[256];
    snprintf(errorMessage, sizeof(errorMessage), "%s %d: %s\n", message, PORT, curErr);
    log_error(errorMessage);
    fputs(errorMessage, stderr);
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, BUFFER_SIZE - 1);
    char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server;
    socklen_t address_len = sizeof(server);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        handle_error("Failed to create socket on port", strerror(errno));
        return EXIT_FAILURE;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);
    int maxConnections = 2;

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        handle_error("Failed to bind to port", strerror(errno));
        return EXIT_FAILURE;
    }

    if (listen(server_fd, maxConnections) < 0) {
        handle_error("Failed to listen on port" , strerror(errno));
        return EXIT_FAILURE;
    }

    while (1) {
        printf("Waiting for connection...\n");
        int client_socket = accept(server_fd, (struct sockaddr *)&server, &address_len);
        if (client_socket < 0) {
            handle_error("Accept failed", strerror(errno));
            return EXIT_FAILURE;
        }
        
        handle_client(client_socket);

        close(client_socket);
    }

    return 0;
}