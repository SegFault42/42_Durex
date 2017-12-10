# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/05 00:34:51 by rabougue          #+#    #+#              #
#    Updated: 2017/11/05 01:01:57 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE = \033[34m
WHITE = \033[37m

all:
	@make -sf ./Makefile.server
	@make -sf ./Makefile.client
	@printf "$(WHITE)┌────────────────────────────────────────────────────────────────────┐\n\
	│$(BLUE)ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssssssssss$(WHITE)o++/::-----:::/++o$(BLUE)ssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssssss$(WHITE)o+::----:://///:::----:/+$(BLUE)sssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssssssssssssss$(WHITE)+/:://+oo$(BLUE)ssssssssss$(WHITE)oo+/----/o$(BLUE)ssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssss$(WHITE)o:-----------------------------------:/+/:--/+/:--------:o$(BLUE)ssssss$(WHITE)│\n\
	│$(BLUE)sssss$(WHITE)o----:::::::::::::::::::::::::::::::::/+o+:--///::----:o$(BLUE)sssssss$(WHITE)│\n\
	│$(BLUE)ssssss$(WHITE)o:--/$(BLUE)ss$(WHITE)+::/o$(BLUE)ssssssssssssssssssssssssssssss$(WHITE):--:+$(BLUE)s$(WHITE)o---/o$(BLUE)ssssssss$(WHITE)│\n\
	│$(BLUE)sssssss$(WHITE)o:--/+--:+$(BLUE)ssssssssssssssssssssssssssssssss$(WHITE)/--/o:--+$(BLUE)ssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssss$(WHITE)//+---+$(BLUE)ssssssssssssssssssssssssssssssssss$(WHITE)+++---o$(BLUE)sssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssss$(WHITE)o/--+$(BLUE)ssssssssssssssssssssssssssssssssssss$(WHITE)/--:$(BLUE)sssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssss$(WHITE)o---oo$(BLUE)sssssssssssssssssssssssssssssssss$(WHITE)o/--:o$(BLUE)sssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssss$(WHITE)+--:+:/o$(BLUE)ssssssssssssssssssssssssssssss$(WHITE)o:--/o:$(BLUE)sssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssss$(WHITE)+--:+:-:o$(BLUE)ssssssssssssssssssssssssssss$(WHITE)+--:++--$(BLUE)sssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssss$(WHITE)o:--o/---+$(BLUE)ssssssssssssssssssssssssss$(WHITE)+--:o+---$(BLUE)sssssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssssss$(WHITE)/--+o+:--+$(BLUE)sssssssssssssssssssssss$(WHITE)o/--:oo:--/$(BLUE)sssssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssssss$(WHITE)o---+$(BLUE)s$(WHITE)o:--/$(BLUE)sssssssssssssssssssss$(WHITE)o:--/$(BLUE)ss$(WHITE)/--:$(BLUE)ssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssss$(WHITE)o---+$(BLUE)ss$(WHITE)/--/o$(BLUE)ssssssssssssssssss$(WHITE)+---+$(BLUE)ss$(WHITE)/--:o$(BLUE)ssssssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssssssss$(WHITE)+---/o$(BLUE)s$(WHITE)/--:o$(BLUE)ssssssssssssssss$(WHITE)/--:+$(BLUE)s$(WHITE)o:--:o$(BLUE)sssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssss$(WHITE)o:---/s$(WHITE)+--:+$(BLUE)ssssssssssssss$(WHITE)/--:oo/---/o$(BLUE)ssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssss$(WHITE)+:---/+:--/$(BLUE)sssssssssss$(WHITE)o::/+/:---/o$(BLUE)ssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssss$(WHITE)o/--//:--/$(BLUE)sssssssss$(WHITE)o+//:---:/o$(BLUE)ssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssssssssssssssss$(WHITE)+/++/--/o+::::::-----:/o$(BLUE)sssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssssssssssss$(WHITE)+--:/+::::://+o$(BLUE)sssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssssssssssssssssssssss$(WHITE)+---/$(BLUE)ss$(WHITE)/::/o$(BLUE)sssssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssssssssssssss$(WHITE)o:--::--/o$(BLUE)ssssssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssssssssssssssssssssssss$(WHITE)o/----+$(BLUE)ssssssssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)sssssssssssssssssssssssssssssss$(WHITE)+--o$(BLUE)sssssssssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssssssssssssssssss$(WHITE)oo$(BLUE)ssssssssssssssssssssssssssssssssss$(WHITE)│\n\
	│$(BLUE)ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss$(WHITE)│\n\
	└────────────────────────────────────────────────────────────────────┘\n"

server:
	@make -sf ./Makefile.server

client:
	@make -sf Makefile.client

clean:
	@make clean -sf ./Makefile.server
	@make clean -sf ./Makefile.client

fclean:
	@make fclean -sf ./Makefile.server
	@make fclean -sf ./Makefile.client

re: clean all
