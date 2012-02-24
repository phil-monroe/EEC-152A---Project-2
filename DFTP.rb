#!/usr/bin/env ruby

require 'socket'

# Creates a connection with host:port and 
# gets the response from sending request
def DFTP_request(hostname, port, request)
  s = TCPSocket.open(hostname, port)
  s.print(request + "\r\n\r\n")
  
  response = s.read
end

# Helper to get input
def get_request
  print "command > "
  gets.chomp
end

# Load server host, port, and acquire IP
host = ARGV.shift || "unyama.cs.ucdavis.edu"
port = ARGV.shift || 10000
ip = Socket::getaddrinfo(host, port)[0][3]
STDIN.flush

# Welcome Message
puts "Welcome to the simple DFTP client."
puts "Connecting to #{host}(#{ip}) on port #{port}."

# Main loop
request = get_request()
while(true)
  case request
  when "quit"
    puts "Goodbye."
    exit
  when "help"
    puts "help - Prints this message"
    puts "quit - Exits the program"
    puts "GET <filename> - Gets the filename from the DFTP server"
    puts "PUT <user's name> - Puts you name in a file on the DFTP server"
    puts "COMMENT <user's comment> - Puts a comment in a file on the DFTP server"
  else
    puts DFTP_request(host, port, request)
  end
  request = get_request()
end