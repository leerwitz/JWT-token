CXX = g++
CXXFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -g -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow  -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=4 -Wswitch-default -Wundef -Werror -Wno-unused

all:  check_token authorization_server 


authorization_server: authorization_server.cpp
	$(CXX) $(CXXFLAGS) -c token/authorization_server.cpp -o authorization_server.o
	$(CXX) $(CXXFLAGS)  authorization_server.o -o authorization_server


check_token: check_token.cpp
	$(CXX) $(CXXFLAGS) -c check_token.cpp -o check_token.o
	$(CXX) $(CXXFLAGS)  check_token.o -o check_token



clean:
	rm -rf  check_token  authorization_server
	rm -rf *.o

rebuild: clean all