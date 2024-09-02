# daisy-effect-cpp

WIP: audio effect using daisy seed

## Remote flashing

If you daisy is connected to e.g. a raspi on your network you can flash it by doing

```bash
make clean; DEBUG=1 make  # remove DEBUG for release build
scp -r build pi@raspberrypi.local:/home/pi/workspace/daisy-seed-cpp/flash  # make sure the destination exists
```

then on your raspi (assuming you are using STLINKv3 connected to it and daisy seed connected to it)

```bash
ssh pi@raspberrypi.local
cd /home/pi/workspace/daisy-seed-cpp/flash  # this is the same as above yours might differ

# now flash please check if your openocd installation is in /usr/share/openocd/scripts
#  or /usr/share/local/openocd/scripts
openocd -s /usr/share/openocd/scripts -f interface/stlink.cfg -f target/stm32h7x.cfg \
                -c "program ./build/daisy-effect-cpp.elf verify reset exit"
```

Now if you did the DEBUG build and want to see the logs you can 

```bash
picocom -b 115200 /dev/ttyACM*  
```

where * is 0/1/2 depending on what you have connected, make sure you connect to the
daisy seed, semihosted logging through STLINKv3 is not supported yet
