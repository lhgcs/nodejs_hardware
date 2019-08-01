cmd_Release/obj.target/wifi.node := g++ -shared -pthread -rdynamic  -Wl,-soname=wifi.node -o Release/obj.target/wifi.node -Wl,--start-group Release/obj.target/wifi/wifi.o -Wl,--end-group 
