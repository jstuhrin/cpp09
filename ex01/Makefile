NAME = RPN

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS = main.cpp \
			 RPN.cpp

OBJS = $(SRCS:.cpp=.o)

TYPE = long

ifeq ($(TYPE), double)
	CXXFLAGS += -DUSE_DOUBLE
endif

%.o:%.cpp RPN.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $^ -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re