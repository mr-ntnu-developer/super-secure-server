# super-secure-server
To run the binary first create `/server` by running
```
sudo mkdir /server
```
Move the binary into `/server`. Then run the binary as such
```
env -i PWD="/server" SHELL="/bin/bash" SHLVL=0 ./overflow-runnable
```

## Disclaimer
No this is not a safe server. Please do NOT use this code as an example of how to make a TCP server.
