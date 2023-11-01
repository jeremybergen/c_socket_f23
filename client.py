import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect(("127.0.0.1", 1235))

    while True:
        message = input("Enter a message to send to server: ")
        # message = "Hello from client"
        s.sendall(message.encode())
        data = s.recv(1024)
        print(f"Received from server: {data}")
        if message == "quit":
            break