import socket

port = 1235
host = ""

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as serverSocket:
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.bind((host, port))
    serverSocket.listen()

    while True:
        conn, addr = serverSocket.accept()
        print(f"connection: {conn}\naddress: {addr}")

        while True:
            message = conn.recv(1024)
            print(f"Received from client: {message.decode()}")

            conn.send(message)
            # strMessage = message.decode()
            if message.decode()[:4] == "quit":
                print(f"Client is quitting")
                conn.close()
                break
