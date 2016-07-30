CXX		=	g++

NAME		=	client_test

DIR_SRC		=	./

SRC		=	$(DIR_SRC)blocking_udp_echo_client.cpp \
			$(DIR_SRC)Packet.cpp
OBJ		=	$(SRC:.cpp=.o)

INCLUDE		=	-I/usr/local/boost_1_39_0/

CXXFLAGS	+=	-Wall -Wextra $(INCLUDE)

LIB		=	-L/lib/ -lboost_system-gcc43-mt-1_39 -lboost_thread-gcc43-mt

RM		=	rm -rfv


$(NAME)		:	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LIB)

all		:	$(NAME)

clean		:
			$(RM) *~ $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
