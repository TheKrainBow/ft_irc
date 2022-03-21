#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# include <arpa/inet.h>
# include <cstring>
# include <fcntl.h>
# include <iomanip>
# include <iostream>
# include <netdb.h>
# include <netinet/in.h>
# include <poll.h>
# include <signal.h>
# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <time.h>
# include <unistd.h>

# include "User.hpp"
# include "Channel.hpp"

# define ERR_ARG -1
# define ERR_SOCKET -2

#endif