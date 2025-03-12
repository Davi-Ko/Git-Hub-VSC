<div style="text-align: center;">
  <h1>{PROJETO SONOFF}</h1>
</div>

Separei os códigos de arduíno entre os modos STA+AP e ESP-NOW.

## STA+AP:
Modo Station + Access Point, nesse modo ambos os ESP-01s funcionam como AP e Client.
        Ambos os relays liberam a sua própria rede wifi configurada, se conectam à rede do outro relay e conseguem se trocar informações puxando os status de um do outro.
        Códigos: [![STA+AP 1](https://img.shields.io/badge/STA%2BAP%201-blue)](STAAP1.ino)
                 [![STA+AP 2](https://img.shields.io/badge/STA%2BAP%202-blue)](STAAP2.ino)


## ESP-NOW: 
É um protocolo que permite os ESP-01s à se comunicarem sem utilizar um roteador no meio, de modo que eles se encontram a partir do MAC Adress de cada um e se conversam.