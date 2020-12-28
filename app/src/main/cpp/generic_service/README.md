
# Generic Post-Quantum Key Exchange Service

## Introduction

## Building
```shell
make clean
make
```

## Setting
- IPTable.cfg: IP and port setting.
    - GatewayID: Gateway's identity.
    - Mode: Client/Server mode or Peer-2-Peer mode.
    - Role: Client or Server in Client/Server mode
    - ServerID: Server's identity set for client side.
    - PresetInitialStatus: whether or not the client sets up the internal status upon being started. If set "Yes", the server must be started before the client is starting up.
- gw_xxx_xxx.cfg: client or server side setting.

## Running
```shell
cd bin/
./KexService ../gw_xxx_xxx.cfg ../IPTable.cfg
```

  
## Modules
- DH, not available now due to some issues.
- RSA-KEM
- BIKE
- Frodo
- NewHope
- HQC
- RQC
- NTRU
- NTRU Prime
- LEDAcrypt
- LAC
- SIKE
- NTS
- ThreeBears
- Kyber
- Saber
- Rollo
- Round5
- CM

