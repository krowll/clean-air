Firmware

## Linux

- Install platformio.

- Install (udev rules)[https://docs.platformio.org/en/latest/faq.html#platformio-udev-rules].

- Add yourself to the dialout and tty group:

```sh
sudo usermod -a -G tty $USER
sudo usermod -a -G dialout $USER
sudo usermod -a -G plugdev $USER
```

Disconnect your board, then log out and log in again for the changes to take place. 

Check if your ESP32 is connected:

```sh
ll /dev | grep ttyUSB*
```