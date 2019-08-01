cmd_Release/obj.target/sound.node := g++ -shared -pthread -rdynamic -m64  -Wl,-soname=sound.node -o Release/obj.target/sound.node -Wl,--start-group Release/obj.target/sound/sound.o -Wl,--end-group 
