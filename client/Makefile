CXX		=	g++

NAME		=	client

DIR_SRC		=	./src/

SRC		=	$(DIR_SRC)main.cpp			\
			$(DIR_SRC)Action.cpp			\
			$(DIR_SRC)Arrows.cpp			\
			$(DIR_SRC)Cmd.cpp			\
			$(DIR_SRC)Collision.cpp			\
			$(DIR_SRC)Decor.cpp			\
			$(DIR_SRC)DynamicLib.cpp		\
			$(DIR_SRC)ExceptionLoaderLib.cpp	\
			$(DIR_SRC)FileLoader.cpp		\
			$(DIR_SRC)Input.cpp			\
			$(DIR_SRC)KeyboardInput.cpp		\
			$(DIR_SRC)Level.cpp			\
			$(DIR_SRC)Move.cpp			\
			$(DIR_SRC)NetworkClient.cpp		\
			$(DIR_SRC)Packet.cpp			\
			$(DIR_SRC)RClient.cpp			\
			$(DIR_SRC)Scenario.cpp			\
			$(DIR_SRC)ScenarioCreator.cpp		\
			$(DIR_SRC)Ship.cpp			\
			$(DIR_SRC)SpriteEntity.cpp		\
			$(DIR_SRC)SpriteFactory.cpp		\
			$(DIR_SRC)ULLoaderLib.cpp		\
			$(DIR_SRC)WindowManager.cpp		\
			$(DIR_SRC)WindowZone.cpp		\
			$(DIR_SRC)Weapon.cpp



OBJ		=	$(SRC:.cpp=.o)

INCLUDE		=	-I./header -I/usr/local/boost_1_39_0/

CXXFLAGS	+=	-Wall -Wextra $(INCLUDE)

LIB_BOOST	=	-L/lib/ -lboost_system-gcc43-mt-1_39 -lboost_thread-gcc43-mt -lboost_serialization-gcc43-mt -lboost_filesystem-gcc43-mt

LIB_SFML	=	-lsfml-system  -lsfml-audio -lsfml-window -lsfml-graphics

LIB		=	$(LIB_BOOST) $(LIB_SFML)

RM		=	rm -rfv


$(NAME)		:	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LIB) -ldl -rdynamic

all		:	$(NAME)

clean		:
			$(RM) *~ $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

libs		:
		       'cd ./libs/ && ./mklib.sh'

.PHONY		:	all clean fclean re
