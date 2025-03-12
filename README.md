{PROJETO SONOFF}

Separei os códigos de arduíno entre os modos STA+AP e ESP-NOW.

STA+AP: Modo Station + Access Point, nesse modo ambos os ESP-01s funcionam como AP e Client.
        Ambos os relays liberam a sua própria rede wifi configurada, se conectam à rede do outro relay e conseguem se trocar informações puxando os status de um do outro.
        Códigos: <a href="STAAP1.ino" style="display: inline-block; padding: 10px 20px; font-size: 16px; color: white; background-color: #4CAF50; text-align: center; text-decoration: none; border-radius: 5px;">STA+AP 1</a>
                 <a href="STAAP2.ino" style="display: inline-block; padding: 10px 20px; font-size: 16px; color: white; background-color: #4CAF50; text-align: center; text-decoration: none; border-radius: 5px;">STA+AP 2</a>
ESP-NOW: É um protocolo que permite os ESP-01s à se comunicarem sem utilizar um roteador no meio, de modo que eles se encontram a partir do MAC Adress de cada um e se conversam.