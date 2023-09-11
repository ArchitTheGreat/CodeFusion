#include <iostream>
#include <string>
#include <fstream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

std::string read_html_file(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return content;
    } else {
        return "File not found!";
    }
}

int main() {
    io_service io;

    // Create a TCP endpoint to listen on port 8080
    tcp::endpoint endpoint(tcp::v4(), 8080);

    // Create an acceptor to listen for incoming connections
    tcp::acceptor acceptor(io, endpoint);

    std::cout << "WebWeaver is running on port 8080." << std::endl;

    while (true) {
        // Create a socket to represent the incoming connection
        tcp::socket socket(io);

        // Wait for and accept an incoming connection
        acceptor.accept(socket);

        // Read the content of the "index.html" file
        std::string html_content = read_html_file("html/index.html");

        // Generate an HTTP response with the HTML content
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Connection: close\r\n";
        response += "\r\n";
        response += html_content;

        // Send the response to the client
        boost::system::error_code ignored_error;
        write(socket, buffer(response), ignored_error);
    }

    return 0;
}
