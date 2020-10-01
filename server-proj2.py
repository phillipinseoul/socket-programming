import socket
import threading

# Define a port to run the program on.
PORT = 5050
# Put in my computer's IP address
# SERVER = "192.168.25.22"
SERVER = socket.gethostbyname(socket.gethostname())

print(SERVER)
print(socket.gethostname())
