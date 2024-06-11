# C HTTP Server

## Overview
I wanted to develop a HTTP server from scratch to gain better understanding of its operational mechanisms and to enhance my proficiency in the C programming language.

## Getting Started
### Prerequisites
If you're on a `Windows machine` you'll need to download `Windows Subsystem for Linux (WSL)` to ensure compatability, as this project is developed for Linux environments. I personally use WSL2 with Ubuntu 24.04 distribution.

To enhance your development experience in Visual Studio Code, consider installing the following extensions:
- `C/C++`: Provides IntelliSense, debugging, and code browsing capabilities for C and C++ code.
- `Code Runner`: Allows you to run code snippets or files for various programming languages directly within VS Code.

### Building the Server
To get started, you'll first need to set up your environment by installing the necessary packages. This step ensures you have all the tools needed to compile and run the program. Simply open your terminal and type:

```bash
sudo apt install build-essential
```

Next, open the project in Visual Studio Code. Navigate to the project's directory in the terminal, and run `code .`. This command opens Visual Studio Code in the current directory, where your project is located.

Now, it's time to compile the program. In the terminal, enter the following command:

```bash
gcc -o CHttpServer CHttpServer.c
```

This command compiles the C code into an executable named `CHttpServer`.

Once compiled you can run it by using

```bash
./CHttpServer
```

The server should now be up and running. You can test it by making a request to port 8080 on your local machine. Open another terminal window and try `curl http://localhost:8080` or `curl http://127.0.0.1:8080`

You should receive an HTTP response with the message `Hello World!` from your server