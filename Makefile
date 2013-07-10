GARDEN_DEBUG_OBJECTS= obj/br_cmd.o obj/conversion.o obj/clock.o \
    obj/conf_file.o obj/debug.o obj/debug_menu.o obj/x10dev.o
JAILKET_OBJECTS= obj/client_connection.o obj/client_socket.o obj/inet_port.o \
    obj/jailket_except.o obj/server_address.o obj/server_socket.o

default: garden_debug

# Meta-Targets
dnc: bin/dnc.so bin/dnc_menu.so
garden_debug: bin/garden_debug
jailket: bin/jailket.so

# Executables
bin/garden_debug: $(GARDEN_DEBUG_OBJECTS)
	g++ $(GARDEN_DEBUG_OBJECTS) -o bin/garden_debug -ldnc_menu -ldnc

# Shared Libraries
bin/dnc.so: obj/dnc.o
	g++ obj/dnc.o -o bin/libdnc.so -shared -lncurses
bin/dnc_menu.so: obj/dnc_menu.o
	g++ obj/dnc_menu.o -o bin/libdnc_menu.so -shared -lmenu -lncurses
bin/jailket.so: $(JAILKET_OBJECTS)
	g++ $(JAILKET_OBJECTS) -o bin/libjailket.so -shared

# Objects
obj/br_cmd.o: br/br_cmd.c
	g++ -c br/br_cmd.c -o obj/br_cmd.o
obj/client_connection.o: jailket/client_connection.cpp
	g++ -c jailket/client_connection.cpp -o obj/client_connection.o -fPIC
obj/client_socket.o: jailket/client_socket.cpp
	g++ -c jailket/client_socket.cpp -o obj/client_socket.o -fPIC
obj/conversion.o: conversion.cpp
	g++ -c conversion.cpp -o obj/conversion.o
obj/clock.o: clock.cpp
	g++ -c clock.cpp -o obj/clock.o
obj/conf_file.o: conf_file.cpp
	g++ -c conf_file.cpp -o obj/conf_file.o -std=c++11
obj/dnc.o: dnc/dnc.cpp
	g++ -c dnc/dnc.cpp -o obj/dnc.o -fPIC
obj/dnc_menu.o: dnc/dnc_menu.cpp
	g++ -c dnc/dnc_menu.cpp -o obj/dnc_menu.o -fPIC
obj/debug.o: debug.cpp
	g++ -c debug.cpp -o obj/debug.o
obj/debug_menu.o: debug_menu.cpp
	g++ -c debug_menu.cpp -o obj/debug_menu.o -std=c++11
obj/inet_port.o: jailket/inet_port.cpp
	g++ -c jailket/inet_port.cpp -o obj/inet_port.o -fPIC -std=c++11
obj/jailket_except.o: jailket/jailket_except.cpp
	g++ -c jailket/jailket_except.cpp -o obj/jailket_except.o -fPIC
obj/server_address.o: jailket/server_address.cpp
	g++ -c jailket/server_address.cpp -o obj/server_address.o -fPIC
obj/server_socket.o: jailket/server_socket.cpp
	g++ -c jailket/server_socket.cpp -o obj/server_socket.o -fPIC
obj/x10dev.o: x10dev.cpp
	g++ -c x10dev.cpp -o obj/x10dev.o

# Clean
clean:
	-rm -f obj/*.o
	-rm -f bin/*.so
	-rm -f bin/garden_debug

# Installations - requires root privledges
install_dnc: dnc
	cp bin/libdnc.so /usr/local/lib/libdnc.so
	cp bin/libdnc_menu.so /usr/local/lib/libdnc_menu.so
	-mkdir /usr/local/include/dnc
	cp dnc/*.h /usr/local/include/dnc/
install_jailket: jailket
	cp bin/libjailket.so /usr/local/lib/libjailket.so
	-mkdir /usr/local/include/jailket
	cp jailket/*.h /usr/local/include/jailket/

# Uninstallations - requires root privledges
uninstall_dnc:
	-rm -f /usr/local/lib/libdnc.so
	-rm -f /usr/local/include/dnc/*.h
	-rmdir /usr/local/include/dnc
uninstall_jailket:
	-rm -f /usr/local/lib/libjailket.so
	-rm -f /usr/local/include/jailket/*.h
	-rmdir /usr/local/include/jailket

