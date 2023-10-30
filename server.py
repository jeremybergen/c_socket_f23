import socket

port = 1235
host = "127.0.0.1"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as serverSocket:
    serverSocket.bind((host, port))
    serverSocket.listen()

    conn, addr = serverSocket.accept()
    print(f"connection: {conn}\naddress: {addr}")

    while True:
        message = conn.recv(1024)
        print(f"Received from client: {message}")

        conn.send(message)
        # strMessage = message.decode()
        if message.decode() == "quit\r\n":
            break
