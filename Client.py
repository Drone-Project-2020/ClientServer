# -*- coding: utf-8 -*-


import socket


host, port =('localhost', 5678) # on met soit localhost ou 127.0.0.1

try:
    socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    socket.connect((host, port))
    print("Client connecté!")
    
    data = "Donnée d'envoi : commande python 1"
    data = data.encode('utf8')
    socket.sendall(data)
    
except ConnectionRefusedError:
    print("Connexion au serveur échouée!")
    
finally:
    socket.close()
    



