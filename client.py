#!/usr/bin/env python3
import socket
from threading import Thread

client = socket.socket()
client.connect(("127.0.0.1", 23543))

def listen_server():
	while True:
		data = client.recv(2048)
		print(data.decode("utf-8"))


def send_server():
	listen_thread = Thread(target=listen_server)
	listen_thread.start()
	user_name = input("Enter your name/nickname: ")
	user_name += ": " 

	while True:
		client_answer = input()
		client.send(user_name.encode("utf-8"))
		client.send(client_answer.encode("utf-8"))
		if client_answer == 'q':
			client.shutdown(0)
			client.close()
			break

if __name__ == '__main__':
	send_server()