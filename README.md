# TinyCAN-IDS

In all the code we're using as interface `can1`. Change it to match your system. 

## Running on Raspberry 
Tested on RPi 4 with 32bit OS and PiCan 2 Duo.

Guide:
- Configure the PiCan as per [instructions](https://copperhilltech.com/blog/pican2-pican3-and-picanm-driver-installation-for-raspberry-pi/)
- Install Libraries for Tensorflow Lite (compile them by yourself, or just use [this packet](https://github.com/prepkg/tensorflow-lite-raspberrypi), probably working only on Bullseye)
- Compile the code using something like: ```gcc -o ids rpi_ids.c -ltensorflowlite_c -lm``` 
- Run it using ```./ids```

The Python code is slower and may need different libraries.