cmd_Release/obj.target/cpu.node := g++ -shared -pthread -rdynamic  -Wl,-soname=cpu.node -o Release/obj.target/cpu.node -Wl,--start-group Release/obj.target/cpu/cpu.o -Wl,--end-group 
