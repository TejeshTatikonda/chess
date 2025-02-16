#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <stdint.h>
#include <stdbool.h>

//Regular text
#define BLK printf("\e[0;30m")
#define RED printf("\e[0;31m")
#define GRN printf("\e[0;32m")
#define YEL printf("\e[0;33m")
#define BLU printf("\e[0;34m")
#define MAG printf("\e[0;35m")
#define CYN printf("\e[0;36m")
#define WHT printf("\e[0;37m")

//Regular bold text
#define BBLK printf("\e[1;30m")
#define BRED printf("\e[1;31m")
#define BGRN printf("\e[1;32m")
#define BYEL printf("\e[1;33m")
#define BBLU printf("\e[1;34m")
#define BMAG printf("\e[1;35m")
#define BCYN printf("\e[1;36m")
#define BWHT printf("\e[1;37m")

//Regular underline text
#define UBLK printf("\e[4;30m")
#define URED printf("\e[4;31m")
#define UGRN printf("\e[4;32m")
#define UYEL printf("\e[4;33m")
#define UBLU printf("\e[4;34m")
#define UMAG printf("\e[4;35m")
#define UCYN printf("\e[4;36m")
#define UWHT printf("\e[4;37m")

//Regular background
#define BLKB printf("\e[40m")
#define REDB printf("\e[41m")
#define GRNB printf("\e[42m")
#define YELB printf("\e[43m")
#define BLUB printf("\e[44m")
#define MAGB printf("\e[45m")
#define CYNB printf("\e[46m")
#define WHTB printf("\e[47m")

//High intensty background 
#define BLKHB printf("\e[0;100m")
#define REDHB printf("\e[0;101m")
#define GRNHB printf("\e[0;102m")
#define YELHB printf("\e[0;103m")
#define BLUHB printf("\e[0;104m")
#define MAGHB printf("\e[0;105m")
#define CYNHB printf("\e[0;106m")
#define WHTHB printf("\e[0;107m")

//High intensty text
#define HBLK printf("\e[0;90m")
#define HRED printf("\e[0;91m")
#define HGRN printf("\e[0;92m")
#define HYEL printf("\e[0;93m")
#define HBLU printf("\e[0;94m")
#define HMAG printf("\e[0;95m")
#define HCYN printf("\e[0;96m")
#define HWHT printf("\e[0;97m")

//Bold high intensity text
#define BHBLK printf("\e[1;90m")
#define BHRED printf("\e[1;91m")
#define BHGRN printf("\e[1;92m")
#define BHYEL printf("\e[1;93m")
#define BHBLU printf("\e[1;94m")
#define BHMAG printf("\e[1;95m")
#define BHCYN printf("\e[1;96m")
#define BHWHT printf("\e[1;97m")

//Reset
#define reset printf("\e[0m")
#define CRESET printf("\e[0m")
#define COLOR_RESET printf("\e[0m")


#define board_x 8
#define board_y 8
#define board_dimension board_x*board_y
#define players 2
#define BLACK 0
#define WHITE 1
#define pieces_per_player 16

#define white_pawn      0x81 // 1000 0001
#define white_king      0x82 // 1000 0010
#define white_queen     0x83 // 1000 0011
#define white_rook      0x84 // 1000 0100
#define white_bishop    0x85 // 1000 0101
#define white_knight    0x86 // 1000 0011

#define black_pawn      0x01 // 0000 0001
#define black_king      0x02 // 0000 0010
#define black_queen     0x03 // 0000 0011
#define black_rook      0x04 // 0000 0100
#define black_bishop    0x05 // 0000 0101
#define black_knight    0x06 // 0000 0011

#endif