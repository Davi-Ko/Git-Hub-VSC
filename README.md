# <p align="center">{PROJETO SONOFF}</p>

Separei os códigos de arduíno entre os modos STA+AP e ESP-NOW.

## STA+AP:
Modo Station + Access Point, nesse modo ambos os ESP-01s funcionam como AP e Client.<br>
Ambos os relays liberam a sua própria rede wifi configurada, se conectam à rede do outro relay e conseguem se trocar informações puxando os status de um do outro.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**CÓDIGOS:** [![STA+AP 1](https://img.shields.io/badge/STA%2BAP%201-blue)](STAAP1.ino)&nbsp;&nbsp;
             [![STA+AP 2](https://img.shields.io/badge/STA%2BAP%202-blue)](STAAP2.ino)


## ESP-NOW: 
É um protocolo que permite os ESP-01s à se comunicarem sem utilizar um roteador no meio, de modo que eles se encontram a partir do MAC Adress de cada um e se conversam.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**CÓDIGOS:** [![ESP-NOW 1](https://img.shields.io/badge/ESP--NOW%201-blue)](ESPNOW1.ino)&nbsp;&nbsp;
             [![ESP-NOW 2](https://img.shields.io/badge/ESP--NOW%202-blue)](ESPNOW2.ino)