main: platform.o admin.o user.o commodity.o order.o helper.o message.o
	g++ -o main platform.o admin.o user.o commodity.o order.o helper.o message.o -g
platform.o: platform.cpp
	g++ -c -o platform.o platform.cpp
admin.o: admin.cpp
	g++ -c -o admin.o admin.cpp
user.o: user.cpp
	g++ -c -o user.o user.cpp
commodity.o: commodity.cpp
	g++ -c -o commodity.o commodity.cpp
order.o: order.cpp
	g++ -c -o order.o order.cpp
helper.o: helper.cpp
	g++ -c -o helper.o helper.cpp
message.o: message.cpp
	g++ -c -o message.o message.cpp
clean:
	rm *.o main
