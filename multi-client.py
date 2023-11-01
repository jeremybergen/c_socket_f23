import socket


def main():
    port = 1234
    host = "127.0.0.1"

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        while True:
            message = "Hello"
            s.send(message.encode())
            break


if __name__ == "__main__":
    main()