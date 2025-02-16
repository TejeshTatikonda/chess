#include <stdio.h>
#include <stdint.h>
#include "includes/constants.h"
#include <string.h>

#define IS_LOWER(a) ((a>='a') && (a<='z'))
#define IS_UPPER(a) ((a>='A') && (a<='Z'))
#define IS_NUM(a) ((a>='0') && (a<='9'))

char board_position[100];

typedef struct positioner
{
    char row8[9];
    char row7[9];
    char row6[9];
    char row5[9];
    char row4[9];
    char row3[9];
    char row2[9];
    char row1[9];
}POSITIONER;

typedef struct fen
{
    char position[100];
    char player_turn[10];
    char castling[4];
    char enpasant[10];
    char half_move[10];
    char full_move[10];
}FEN;

typedef struct piece
{
    uint8_t power;
    uint8_t piece_num;
    char piece_name[20];
    char short_name;
}PIECE;

/// @brief takes piece number as input and finds its info like color, piece name and creates an object for it.
/// @param piece_num 
PIECE creat_piece(const char piece);

/// @brief takes fen format of any board position and seperates all the fields in it.
/// @param fen 
/// @param seperator 
/// @return FEN structure which contains all the fields.
FEN seperator(const char *fen, const char seperator);
POSITIONER position_seperator(const char *pieces_pos);
void fill_board(POSITIONER positions, uint8_t board[][8]);
void square_status(const char status, uint8_t board[][8], uint8_t row, uint8_t *row_cnt);

/// @brief takes board (2D array) as input and prints the position of all the pieces to the console.
/// @param board 
void print_board(uint8_t board[][8]);

/// @brief selects a square on board and finds what piece is there and finds its possible moves.
/// @param square 
/// @param board 
void select_square(const char *square, uint8_t board[][8]);

uint8_t find_piece_in_square(const char *square, uint8_t board[][8]);

void highlight_possible_moves(const uint8_t board[][8], const uint32_t possible_cnt, uint8_t *possible_x, uint8_t *possible_y);

void knight_moves(uint8_t knight_info, const uint8_t position_x, const uint8_t position_y, uint8_t *possible_x, uint8_t *possible_y, uint32_t *possible_cnt);

void rook_possible_moves(uint8_t rook_info, const uint8_t position_x, const uint8_t position_y, const uint8_t board[][8], uint8_t *possible_x, uint8_t *possible_y, uint32_t *possible_cnt);

void bishop_moves(uint8_t bishop_info, const uint8_t position_x, const uint8_t position_y, const uint8_t board[][8], uint8_t *possible_x, uint8_t *possible_y, uint32_t *possible_cnt);

void pawn_possible_moves(const uint8_t position_x, const uint8_t position_y, const uint8_t board[][8], uint8_t *possible_x, uint8_t *possible_y, uint32_t *possible_cnt);

void king_possible_moves(const uint8_t position_x, const uint8_t position_y, const uint8_t board[][8], uint8_t *possible_x,  uint8_t *possible_y, uint32_t *possible_cnt); 

int main()
{
    uint8_t board[8][8] = {0};

    // PIECE knight1 = creat_piece(black_queen);
    // for(int i = 1; i < 9; i ++)
    // {
    //     for(int j = 'a'; j < ('a'+8); j++)
    //     {
    //         reset;
    //         printf("\n\n");
    //         // print_board(j, i, 'K');
    //         print_board(j, i, knight1.short_name);
    //     }
    // }

    printf("\n");

    // char fen_pos[100] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    // char fen_pos[100] = "8/5k2/3p4/1p1Pp2p/pP2Pp1P/P4P1K/8/8 b - - 99 50";
    // char fen_pos[100] = "rnbqkb1r/pp1pppp1/4n3/2p2P2/3P3p/1N6/PPP1P1PP/R1BQKBNR w KQkq - 0 1";
    // char fen_pos[100] = "rnbqkbn1/ppppp1pp/5p2/8/2B5/8/P4PPP/R1BQK1NR w KQq - 0 1";
    char fen_pos[100] = "rnbqk1n1/pKp1pb1p/1p1p1p2/8/2BB4/1p4b1/P4PPP/R2QK1NR w KQq - 0 1";
    
    FEN position;
    memset(position.position, '\0', 100);
    memset(position.castling, '\0', 4);
    memset(position.enpasant, '\0', 10);
    memset(position.full_move, '\0', 10);
    memset(position.half_move, '\0', 10);
    memset(position.player_turn, '\0', 10);
    position = seperator(fen_pos, ' ');

    printf("\n\npositions : %s, %s, %s, %s, %s, %s\n\n", position.position, position.player_turn, position.castling, position.enpasant, position.half_move,position.full_move);
    
    POSITIONER board_state;
    memset(board_state.row1, '\0', 9);
    memset(board_state.row2, '\0', 9);
    memset(board_state.row3, '\0', 9);
    memset(board_state.row4, '\0', 9);
    memset(board_state.row5, '\0', 9);
    memset(board_state.row6, '\0', 9);
    memset(board_state.row7, '\0', 9);
    memset(board_state.row8, '\0', 9);
    board_state = position_seperator(position.position);

    printf("\n\n%s, %s, %s, %s, %s, %s, %s, %s\n\n", board_state.row8, board_state.row7, board_state.row6, board_state.row5, board_state.row4, board_state.row3, board_state.row2, board_state.row1);

    // printf("actual board :\n");
    fill_board(board_state, board);

    GRNB;
    printf("\nGiven board position :\n");
    reset;

    print_board(board);

    while(1)
    {
        char in[10];
        printf("\nselect a square : ");
        scanf("%s", in);
        if(in[0] == 'z')
        {
            break;
        }
        select_square(in, board);
    }

    return 0;
}

void print_board(uint8_t board[][8])
{
    uint8_t cnt = 0;
    int i = 0, j = 0;

    bool light_square = true;
    // for x-axis coordinates
    printf("  ");
    for(int i = 0; i < 8; i++)
    printf("\e[4;37m %c ", i+'a');
    for(i = 8; i > 0; i--)
    {
        reset;
        light_square = (i%2 == 0);
        
        printf("\n%d", (i)); // for y-axis coordinates
        for(j = 0; j < 8; j++)
        {
            light_square ? ((j%2 == 0) ? MAGHB : BLKB) : ((j%2 == 0) ? BLKB : MAGHB);

            uint8_t piece = board[i-1][j];
            char piece_to_place = ' ';
            if(piece != 0)
            {
                piece_to_place = piece;
            }
            printf("|\e[4;37m%c ", piece_to_place);
            if(j == 7)
            {
                printf("|");
            }
            cnt++;
        }
    }
    reset;
}

PIECE creat_piece(const char piece)
{
    if (IS_LOWER(piece))
    {
        switch (piece)
        {
            case 'r':
            {
                PIECE BLACK_ROOK;
                BLACK_ROOK.power = 4;
                char dummy[20] = "black_rook";
                strcpy(BLACK_ROOK.piece_name,dummy);
                BLACK_ROOK.piece_num = black_rook;
                BLACK_ROOK.short_name = piece;
                return BLACK_ROOK;
            }
            break;
            case 'n':
            {
                PIECE BLACK_KNIGHT;
                BLACK_KNIGHT.power = 2;
                char dummy[20] = "black_knight";
                strcpy(BLACK_KNIGHT.piece_name,dummy);
                BLACK_KNIGHT.piece_num = black_knight;
                BLACK_KNIGHT.short_name = piece;
                return BLACK_KNIGHT;
            }
            break;
            case 'b':
            {
                PIECE BLACK_BISHOP;
                BLACK_BISHOP.power = 3;
                char dummy[20] = "black_bishop";
                strcpy(BLACK_BISHOP.piece_name,dummy);
                BLACK_BISHOP.piece_num = black_bishop;
                BLACK_BISHOP.short_name = piece;
                return BLACK_BISHOP;
            }
            break;
            case 'k':
            {
                PIECE BLACK_KING;
                BLACK_KING.power = 10;
                char dummy[20] = "black_king";
                strcpy(BLACK_KING.piece_name,dummy);
                BLACK_KING.piece_num = black_king;
                BLACK_KING.short_name = piece;
                return BLACK_KING;
            }
            break;
            case 'q':
            {
                PIECE BLACK_QUEEN;
                BLACK_QUEEN.power = 6;
                char dummy[20] = "black_queen";
                strcpy(BLACK_QUEEN.piece_name,dummy);
                BLACK_QUEEN.piece_num = black_queen;
                BLACK_QUEEN.short_name = piece;
                return BLACK_QUEEN;
            }
            break;
            case 'p':
            {
                PIECE BLACK_PAWN;
                BLACK_PAWN.power = 1;
                char dummy[20] = "black_pawn";
                strcpy(BLACK_PAWN.piece_name,dummy);
                BLACK_PAWN.piece_num = black_pawn;
                BLACK_PAWN.short_name = piece;
                return BLACK_PAWN;
            }
            break;

            default:
            {
                REDB;
                printf("Invalid piece to create %c ", piece);
                reset;
            }
            break;
        }
    }
    else if (IS_UPPER(piece))
    {
        switch (piece)
        {
            case 'R':
            {
                PIECE WHITE_ROOK;
                WHITE_ROOK.power = 4;
                char dummy[20] = "white_rook";
                strcpy(WHITE_ROOK.piece_name,dummy);
                WHITE_ROOK.piece_num = white_rook;
                WHITE_ROOK.short_name = piece;
                return WHITE_ROOK;
            }
            break;
            case 'N':
            {
                PIECE WHITE_KNIGHT;
                WHITE_KNIGHT.power = 2;
                char dummy[20] = "white_knight";
                strcpy(WHITE_KNIGHT.piece_name,dummy);
                WHITE_KNIGHT.piece_num = white_knight;
                WHITE_KNIGHT.short_name = piece;
                return WHITE_KNIGHT;
            }
            break;
            case 'B':
            {
                PIECE WHITE_BISHOP;
                WHITE_BISHOP.power = 3;
                char dummy[20] = "white_bishop";
                strcpy(WHITE_BISHOP.piece_name,dummy);
                WHITE_BISHOP.piece_num = white_bishop;
                WHITE_BISHOP.short_name = piece;
                return WHITE_BISHOP;
            }
            break;
            case 'K':
            {
                PIECE WHITE_KING;
                WHITE_KING.power = 10;
                char dummy[20] = "white_king";
                strcpy(WHITE_KING.piece_name,dummy);
                WHITE_KING.piece_num = white_king;
                WHITE_KING.short_name = piece;
                return WHITE_KING;
            }
            break;
            case 'Q':
            {
                PIECE WHITE_QUEEN;
                WHITE_QUEEN.power = 6;
                char dummy[20] = "white_queen";
                strcpy(WHITE_QUEEN.piece_name,dummy);
                WHITE_QUEEN.piece_num = white_queen;
                WHITE_QUEEN.short_name = piece;
                return WHITE_QUEEN;
            }
            break;
            case 'P':
            {
                PIECE WHITE_PAWN;
                WHITE_PAWN.power = 1;
                char dummy[20] = "white_pawn";
                strcpy(WHITE_PAWN.piece_name,dummy);
                WHITE_PAWN.piece_num = white_pawn;
                WHITE_PAWN.short_name = piece;
                return WHITE_PAWN;
            }
            break;

            default:
            {
                REDB;
                printf("Invalid piece to create %c ", piece);
                reset;
            }
            break;
        }
    

}
    else
    {
        REDB;
        printf("Invalid piece to create %c ",piece);
        reset;
    }
}

FEN seperator(const char *fen, const char seperator)
{
    char s[100];
    int idx = 0;
    uint32_t s_len = 0;

    FEN pos;

    for(int i = 0; i < strlen(fen); i++)
    {
        // printf("fen[%d] = %c\n", i, fen[i]);
        if(fen[i]!=seperator)
        {
            s[s_len++] = fen[i];
        }
        if(fen[i] == seperator || i+1 == strlen(fen))
        {
            idx++;
            printf("s_len = %d ", s_len);

            if(idx == 1) // pieces positions
            {
                memset(pos.position, '\0', 100);
                for(int k = 0; k < s_len; k++)
                {
                    pos.position[k] = s[k];
                }
                pos.position[s_len] = '\0';
                printf("position = %s\n", pos.position);
            }
            else if(idx == 2) // player turn
            {
                memset(pos.player_turn, '\0', 10);
                for(int k = 0; k < s_len; k++)
                {
                    pos.player_turn[k] = s[k];
                }
                pos.player_turn[s_len] = '\0';
                printf("player turn = %s\n", pos.player_turn);
            }
            else if(idx == 3) // castling status
            {
                memset(pos.castling, '\0', 4);
                for(int k = 0; k < s_len; k++)
                {
                    pos.castling[k] = s[k];
                }
                pos.castling[s_len] = '\0';
                printf("castling = %s\n", pos.castling);
            }
            else if(idx == 4) // enpasant status of squares
            {
                memset(pos.enpasant, '\0', 10);
                for(int k = 0; k < s_len; k++)
                {
                    pos.enpasant[k] = s[k];
                }
                pos.enpasant[s_len] = '\0';
                printf("enpasant = %s\n", pos.enpasant);
            }
            else if(idx == 5) // half move
            {
                memset(pos.half_move, '\0', 10);
                for(int k = 0; k < s_len; k++)
                {
                    pos.half_move[k] = s[k];
                }
                pos.half_move[s_len] = '\0';
                printf("half move = %s\n", pos.half_move);
            }
            else if(idx == 6) // full move
            {
                memset(pos.full_move, '\0', 10);
                for(int k = 0; k < s_len; k++)
                {
                    pos.full_move[k] = s[k];
                }
                pos.full_move[s_len] = '\0';
                printf("full move = %s\n", pos.full_move);
            }

            // printf("idx = %d ", idx);
            s_len = 0;
        }
    }

    // printf("%s, %s, %s, %s, %s, %s", pos.position, pos.player_turn, pos.castling, pos.castling, pos.half_move,pos.full_move);
    return pos;
}

POSITIONER position_seperator(const char *pieces_pos)
{
    char s[100];
    int idx = 0;
    uint32_t s_len = 0;

    POSITIONER pos;

    for(int i = 0; i < strlen(pieces_pos); i++)
    {
        // printf("pieces_pos[%d] = %c\n", i, pieces_pos[i]);
        if(pieces_pos[i]!='/')
        {
            s[s_len++] = pieces_pos[i];
        }
        if(pieces_pos[i] == '/' || i+1 == strlen(pieces_pos))
        {
            idx++;
            printf("s_len = %d ", s_len);

            if(idx == 1)
            {
                memset(pos.row8, '\0', 8);
                for(int k = 0; k < s_len; k++)
                {
                    pos.row8[k] = s[k];
                }
                pos.row8[s_len] = '\0';
                printf("row8 = %s\n", pos.row8);
            }
            else if(idx == 2)
            {
                memset(pos.row7, '\0', 8);
                for(int k = 0; k < s_len; k++)
                {
                    pos.row7[k] = s[k];
                }
                pos.row7[s_len] = '\0';
                printf("row7 = %s\n", pos.row7);
            }
            else if(idx == 3)
            {
                memset(pos.row6, '\0', 8);
                for(int k = 0; k < s_len; k++)
                {
                    pos.row6[k] = s[k];
                }
                pos.row6[s_len] = '\0';
                printf("row6 = %s\n", pos.row6);
            }
            else if(idx == 4)
            {
                memset(pos.row5, '\0', 8);
                for(int k = 0; k < s_len; k++)
                {
                    pos.row5[k] = s[k];
                }
                pos.row5[s_len] = '\0';
                printf("row5 = %s\n", pos.row5);
            }
            else if(idx == 5)
            {
                memset(pos.row4, '\0', 8);
                for(int k = 0; k < s_len; k++)
                {
                    pos.row4[k] = s[k];
                }
                pos.row4[s_len] = '\0';
                printf("row4 = %s\n", pos.row4);
            }
            else if(idx == 6)
            {
                memset(pos.row3, '\0', 8);
                for(int k = 0; k < s_len; k++)
                {
                    pos.row3[k] = s[k];
                }
                pos.row3[s_len] = '\0';
                printf("row3 = %s\n", pos.row3);
            }
            else if(idx == 7)
            {
                memset(pos.row2, '\0', 8);
                for(int k = 0; k < s_len; k++)
                {
                    pos.row2[k] = s[k];
                }
                pos.row2[s_len] = '\0';
                printf("row2 = %s\n", pos.row2);
            }
            else if(idx == 8)
            {
                memset(pos.row1, '\0', 8);
                for(int k = 0; k < s_len; k++)
                {
                    pos.row1[k] = s[k];
                }
                pos.row1[s_len] = '\0';
                printf("row1 = %s\n", pos.row1);
            }

            // printf("idx = %d ", idx);
            s_len = 0;
        }
    }

    return pos;
}

void fill_board(POSITIONER positions, uint8_t board[][8])
{
    uint8_t row8_cnt = 0; // tells how many cols were filled in row 6.
    uint8_t row = 7; // actual row = 8.
    for(int i = 0; i < strlen(positions.row8); i++)
    {
        square_status(positions.row8[i], board, row, &row8_cnt);
    }
    // printf("\n");
    // for(int l = 0; l < row8_cnt; l++)
    // {
    //     printf("%c, ", board[row][l]);
    // }

    uint8_t row7_cnt = 0; // tells how many cols were filled in row 6.
    row = 6; // actual row = 7.
    for(int i = 0; i < strlen(positions.row7); i++)
    {
        square_status(positions.row7[i], board, row, &row7_cnt);
    }
    // printf("\n");
    // for(int l = 0; l < row7_cnt; l++)
    // {
    //     printf("%c, ", board[row][l]);
    // }

    uint8_t row6_cnt = 0; // tells how many cols were filled in row 6.
    row = 5; // actual row = 6.
    for(int i = 0; i < strlen(positions.row6); i++)
    {
        square_status(positions.row6[i], board, row, &row6_cnt);
    }
    // printf("\n");
    // for(int l = 0; l < row6_cnt; l++)
    // {
    //     printf("%c, ", board[row][l]);
    // }

    uint8_t row5_cnt = 0; // tells how many cols were filled in row 6.
    row = 4; // actual row = 5.
    for(int i = 0; i < strlen(positions.row5); i++)
    {
        square_status(positions.row5[i], board, row, &row5_cnt);
    }
    // printf("\n");
    // for(int l = 0; l < row5_cnt; l++)
    // {
    //     printf("%c, ", board[row][l]);
    // }

    uint8_t row4_cnt = 0; // tells how many cols were filled in row 6.
    row = 3; // actual row = 4.
    for(int i = 0; i < strlen(positions.row4); i++)
    {
        square_status(positions.row4[i], board, row, &row4_cnt);
    }
    // printf("\n");
    // for(int l = 0; l < row4_cnt; l++)
    // {
    //     printf("%c, ", board[row][l]);
    // }

    uint8_t row3_cnt = 0; // tells how many cols were filled in row 6.
    row = 2; // actual row = 3.
    for(int i = 0; i < strlen(positions.row3); i++)
    {
        square_status(positions.row3[i], board, row, &row3_cnt);
    }
    // printf("\n");
    // for(int l = 0; l < row3_cnt; l++)
    // {
    //     printf("%c, ", board[row][l]);
    // }

    uint8_t row2_cnt = 0; // tells how many cols were filled in row 6.
    row = 1; // actual row = 2.
    for(int i = 0; i < strlen(positions.row2); i++)
    {
        square_status(positions.row2[i], board, row, &row2_cnt);
    }
    // printf("\n");
    // for(int l = 0; l < row2_cnt; l++)
    // {
    //     printf("%c, ", board[row][l]);
    // }

    uint8_t row1_cnt = 0; // tells how many cols were filled in row 6.
    row = 0; // actual row = 1.
    for(int i = 0; i < strlen(positions.row1); i++)
    {
        square_status(positions.row1[i], board, row, &row1_cnt);
    }
    // printf("\n");
    // for(int l = 0; l < row1_cnt; l++)
    // {
    //     printf("%c, ", board[row][l]);
    // }
}

void square_status(const char status, uint8_t board[][8], uint8_t row, uint8_t *row_cnt)
{
    if(IS_NUM(status)) // empty squares.
    {
        uint8_t empty_spaces = status - '0';
        for(int k = 0; k < empty_spaces; k++)
        {
            board[row][(*row_cnt)++] = 0;
        }
    }
    else if(IS_LOWER(status)) // black piece.
    {
        uint8_t piece = status;
        switch(piece)
        {
            case 'r':
            {
                // PIECE BLACK_ROOK = creat_piece(black_rook); // for display purpose.
                board[row][(*row_cnt)++] = 'r';
            }
            break;
            case 'n':
            {
                // PIECE BLACK_KNIGHT = creat_piece(black_knight); // for display purpose.
                board[row][(*row_cnt)++] = 'n';
            }
            break;
            case 'b':
            {
                // PIECE BLACK_BISHOP = creat_piece(black_bishop); // for display purpose.
                board[row][(*row_cnt)++] = 'b';
            }
            break;
            case 'k':
            {
                // PIECE BLACK_KING = creat_piece(black_king); // for display purpose.
                board[row][(*row_cnt)++] = 'k';
            }
            break;
            case 'q':
            {
                // PIECE BLACK_QUEEN = creat_piece(black_queen); // for display purpose.
                board[row][(*row_cnt)++] = 'q';
            }
            break;
            case 'p':
            {
                // PIECE BLACK_PAWN = creat_piece(black_pawn); // for display purpose.
                board[row][(*row_cnt)++] = 'p';
            }
            break;
            default:
            {
                REDB;
                printf("\nshould not enter this case ..!\ninvalid piece found : %c", status);
                reset;
            }
        }
    }
    else if(IS_UPPER(status)) // white piece.
    {
        uint8_t piece = status;
        switch(piece)
        {
            case 'R':
            {
                // PIECE WHITE_ROOK = creat_piece(white_rook); // for display purpose.
                board[row][(*row_cnt)++] = 'R';
            }
            break;
            case 'N':
            {
                // PIECE WHITE_KNIGHT = creat_piece(white_knight); // for display purpose.
                board[row][(*row_cnt)++] = 'N';
            }
            break;
            case 'B':
            {
                // PIECE WHITE_BISHOP = creat_piece(white_bishop); // for display purpose.
                board[row][(*row_cnt)++] = 'B';
            }
            break;
            case 'K':
            {
                // PIECE WHITE_KING = creat_piece(white_king); // for display purpose.
                board[row][(*row_cnt)++] = 'K';
            }
            break;
            case 'Q':
            {
                // PIECE WHITE_QUEEN = creat_piece(white_queen); // for display purpose.
                board[row][(*row_cnt)++] = 'Q';
            }
            break;
            case 'P':
            {
                // PIECE WHITE_PAWN = creat_piece(white_pawn); // for display purpose.
                board[row][(*row_cnt)++] = 'P';
            }
            break;
            default:
            {
                REDB;
                printf("\nshould not enter this case ..!\ninvalid piece found : %c", status);
                reset;
            }
        }
    }
    else
    {
        REDB;
        printf("\nunknown piece detected..!\n");
        reset;
    }
}

void select_square(const char *square, uint8_t board[][8])
{
    uint8_t len = strlen(square);
    if(len != 2)
    {
        REDB;
        printf("\n[%s][%d]:Invalid square selected..!\n", __FILE__, __LINE__);
        reset;
        return;
    }

    if(square[0] < 'a' || square[0] > 'h')
    {
        REDB;
        printf("\n[%s][%d]:Invalid x coordinate %c selected..!\n", __FILE__, __LINE__, square[0]);
        reset;
        return;
    }
    if(square[1] < '1' || square[1] > '8')
    {
        REDB;
        printf("\n[%s][%d]:Invalid y coordinate %c selected..!\n", __FILE__, __LINE__, square[1]);
        reset;
        return;
    }

    uint8_t y = (square[0] - 'a');
    uint8_t x = (square[1] - '1');

    BLUB;
    printf("\nx : %d, y : %d\n", x, y);
    printf("\npiece on square %s : %c\n", square,  board[x][y]);
    reset;

    if(board[x][y] == 'n' || board[x][y] == 'N')
    {
        uint8_t x_out[100], y_out[100];
        uint32_t posibility_cnt = 0;
        knight_moves(black_knight, x, y, x_out, y_out, &posibility_cnt);

        if(IS_LOWER(board[x][y])) // if selected square has black player
        {
            for(int i = 0; i < posibility_cnt; i++)
            {
                char square[3];
                square[0] = y_out[i] + 'a';
                square[1] = x_out[i] + '1';
                square[2] = '\0';
                uint8_t piece = 0;
                piece = find_piece_in_square(square, board);
                if(IS_LOWER(piece)) // if there is same player's piece at possible move
                {
                    y_out[i] = 0xff;
                    x_out[i] = 0xff;
                }
            }
        }
        else if(IS_UPPER(board[x][y])) // if selected square has white player
        {
            for(int i = 0; i < posibility_cnt; i++)
            {
                char square[3];
                square[0] = y_out[i] + 'a';
                square[1] = x_out[i] + '1';
                square[2] = '\0';
                uint8_t piece = 0;
                piece = find_piece_in_square(square, board);
                if(IS_UPPER(piece)) // if there is same player's piece at possible move
                {
                    y_out[i] = 0xff;
                    x_out[i] = 0xff;
                }
            }
        }
        else
        {
            REDB;
            printf("\nshould not come to this line\n");
            reset;
        }

        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("(%d, %d); ", x_out[i], y_out[i]);
        }
        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("%c%c ", y_out[i] + 'a', x_out[i] + '1');
        }

        highlight_possible_moves(board, posibility_cnt, x_out, y_out);
    }
    else if(board[x][y] == 'r' || board[x][y] == 'R')
    {
        uint8_t x_out[100], y_out[100];
        uint32_t posibility_cnt = 0;
        rook_possible_moves(black_rook, x, y, board, x_out, y_out, &posibility_cnt);

        if(IS_LOWER(board[x][y])) // if selected square has black player
        {
            for(int i = 0; i < posibility_cnt; i++)
            {
                char square[3];
                square[0] = y_out[i] + 'a';
                square[1] = x_out[i] + '1';
                square[2] = '\0';
                uint8_t piece = 0;
                piece = find_piece_in_square(square, board);
                if(IS_LOWER(piece)) // if there is same player's piece at possible move
                {
                    y_out[i] = 0xff;
                    x_out[i] = 0xff;
                }
            }
        }
        else if(IS_UPPER(board[x][y])) // if selected square has white player
        {
            for(int i = 0; i < posibility_cnt; i++)
            {
                char square[3];
                square[0] = y_out[i] + 'a';
                square[1] = x_out[i] + '1';
                square[2] = '\0';
                uint8_t piece = 0;
                piece = find_piece_in_square(square, board);
                if(IS_UPPER(piece)) // if there is same player's piece at possible move
                {
                    y_out[i] = 0xff;
                    x_out[i] = 0xff;
                }
            }
        }
        else
        {
            REDB;
            printf("\nshould not come to this line\n");
            reset;
        }

        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("(%d, %d); ", x_out[i], y_out[i]);
        }
        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("%c%c ", y_out[i] + 'a', x_out[i] + '1');
        }

        highlight_possible_moves(board, posibility_cnt, x_out, y_out);
    }
    else if(board[x][y] == 'b' || board[x][y] == 'B')
    {
        uint8_t x_out[100], y_out[100];
        uint32_t posibility_cnt = 0;
        bishop_moves(black_bishop, x, y, board, x_out, y_out, &posibility_cnt);

        if(IS_LOWER(board[x][y])) // if selected square has black player
        {
            for(int i = 0; i < posibility_cnt; i++)
            {
                char square[3];
                square[0] = y_out[i] + 'a';
                square[1] = x_out[i] + '1';
                square[2] = '\0';
                uint8_t piece = 0;
                piece = find_piece_in_square(square, board);
                if(IS_LOWER(piece)) // if there is same player's piece at possible move
                {
                    y_out[i] = 0xff;
                    x_out[i] = 0xff;
                    break;
                }
            }
        }
        else if(IS_UPPER(board[x][y])) // if selected square has white player
        {
            for(int i = 0; i < posibility_cnt; i++)
            {
                char square[3];
                square[0] = y_out[i] + 'a';
                square[1] = x_out[i] + '1';
                square[2] = '\0';
                uint8_t piece = 0;
                piece = find_piece_in_square(square, board);
                if(IS_UPPER(piece)) // if there is same player's piece at possible move
                {
                    y_out[i] = 0xff;
                    x_out[i] = 0xff;
                    break;
                }
            }
        }
        else
        {
            REDB;
            printf("\nshould not come to this line\n");
            reset;
        }

        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("(%d, %d); ", x_out[i], y_out[i]);
        }
        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("%c%c ", y_out[i] + 'a', x_out[i] + '1');
        }

        highlight_possible_moves(board, posibility_cnt, x_out, y_out);
    }
    else if(board[x][y] == 'q' || board[x][y] == 'Q')
    {
        uint8_t x_out2[100], y_out2[100], x_out1[100], y_out1[100];
        uint32_t posibility_cnt2 = 0, posibility_cnt1 = 0;
        rook_possible_moves(black_rook, x, y, board, x_out1, y_out1, &posibility_cnt1);
        bishop_moves(black_bishop, x, y, board, x_out2, y_out2, &posibility_cnt2);

        uint8_t x_out[100], y_out[100];
        uint32_t posibility_cnt = 0;

        for(int i = 0; i < posibility_cnt1; i++)
        {
            x_out[posibility_cnt] = x_out1[i];
            y_out[posibility_cnt++] = y_out1[i];
        }
        for(int i = 0; i < posibility_cnt2; i++)
        {
            x_out[posibility_cnt] = x_out2[i];
            y_out[posibility_cnt++] = y_out2[i];
        }

        // not needed these else if blocks?
        if(IS_LOWER(board[x][y])) // if selected square has black player
        {
            for(int i = 0; i < posibility_cnt; i++)
            {
                char square[3];
                square[0] = y_out[i] + 'a';
                square[1] = x_out[i] + '1';
                square[2] = '\0';
                uint8_t piece = 0;
                piece = find_piece_in_square(square, board);
                if(IS_LOWER(piece)) // if there is same player's piece at possible move
                {
                    y_out[i] = 0xff;
                    x_out[i] = 0xff;
                    break;
                }
            }
        }
        else if(IS_UPPER(board[x][y])) // if selected square has white player
        {
            for(int i = 0; i < posibility_cnt; i++)
            {
                char square[3];
                square[0] = y_out[i] + 'a';
                square[1] = x_out[i] + '1';
                square[2] = '\0';
                uint8_t piece = 0;
                piece = find_piece_in_square(square, board);
                if(IS_UPPER(piece)) // if there is same player's piece at possible move
                {
                    y_out[i] = 0xff;
                    x_out[i] = 0xff;
                    break;
                }
            }
        }
        else
        {
            REDB;
            printf("\nshould not come to this line\n");
            reset;
        }

        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("(%d, %d); ", x_out[i], y_out[i]);
        }
        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("%c%c ", y_out[i] + 'a', x_out[i] + '1');
        }

        highlight_possible_moves(board, posibility_cnt, x_out, y_out);
    }
    else if(board[x][y] == 'p' || board[x][y] == 'P')
    {
        uint8_t x_out[100], y_out[100];
        uint32_t posibility_cnt = 0;

        pawn_possible_moves(x, y, board, x_out, y_out, &posibility_cnt);

        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("(%d, %d); ", x_out[i], y_out[i]);
        }
        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("%c%c ", y_out[i] + 'a', x_out[i] + '1');
        }

        highlight_possible_moves(board, posibility_cnt, x_out, y_out);
    }
    else if(board[x][y] == 'k' || board[x][y] == 'K')
    {
        uint8_t x_out[100], y_out[100];
        uint32_t posibility_cnt = 0;

        king_possible_moves(x, y, board, x_out, y_out, &posibility_cnt);

        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("(%d, %d); ", x_out[i], y_out[i]);
        }
        for(int i = 0; i < posibility_cnt; i++)
        {
            printf("%c%c ", y_out[i] + 'a', x_out[i] + '1');
        }

        highlight_possible_moves(board, posibility_cnt, x_out, y_out);
    }
    return;
}

uint8_t find_piece_in_square(const char *square, uint8_t board[][8])
{
    uint8_t len = strlen(square);
    if(len != 2)
    {
        REDB;
        printf("\n[%s][%d]:Invalid square selected..!\n", __FILE__, __LINE__);
        reset;
        return 0xff;
    }

    if(square[0] < 'a' || square[0] > 'h')
    {
        REDB;
        printf("\n[%s][%d]:Invalid x coordinate %c selected..!\n", __FILE__, __LINE__, square[0]);
        reset;
        return 0xff;
    }
    if(square[1] < '1' || square[1] > '8')
    {
        REDB;
        printf("\n[%s][%d]:Invalid y coordinate %c selected..!\n", __FILE__, __LINE__, square[1]);
        reset;
        return 0xff;
    }

    uint8_t y = (square[0] - 'a');
    uint8_t x = (square[1] - '1');

    // MAGB;
    // printf("\nx : %d, y : %d\n", x, y);
    // printf("\npiece on square %s : %c\n", square,  board[x][y]);
    // reset;

    return board[x][y];
}

void highlight_possible_moves(const uint8_t board[][8], const uint32_t possible_cnt, uint8_t *possible_x, uint8_t *possible_y)
{
    uint8_t cnt = 0;
    uint8_t cnt_dwn = possible_cnt;
    int i = 0, j = 0;

    bool light_square = true;
    printf("\n");
    // for x-axis coordinates
    printf("  ");
    for(int i = 0; i < 8; i++)
    printf("\e[4;37m %c ", i+'a');
    for(i = 8; i > 0; i--)
    {
        reset;
        light_square = (i%2 == 0);
        
        printf("\n%d", (i)); // for y-axis coordinates
        for(j = 0; j < 8; j++)
        {
            light_square ? ((j%2 == 0) ? MAGHB : BLKB) : ((j%2 == 0) ? BLKB : MAGHB);

            if(cnt_dwn > 0)
            {
                for(int k = 0; k < possible_cnt; k++)
                {
                    if((i-1) == possible_x[k] && j == possible_y[k])
                    {
                        GRNB;
                        cnt_dwn--;
                    }
                }
            }

            uint8_t piece = board[i-1][j];
            char piece_to_place = ' ';
            if(piece != 0)
            {
                piece_to_place = piece;
            }
            printf("|\e[4;37m%c ", piece_to_place);
            if(j == 7)
            {
                printf("|");
            }
            cnt++;
        }
    }
    reset;
}

void knight_moves(uint8_t knight_info, const uint8_t position_x, const uint8_t position_y, uint8_t *possible_x, uint8_t *possible_y, uint32_t *possible_cnt)
{
    unsigned char all_x_positions[100] = {0};
    uint8_t all_y_positions[100] = {0};
    uint32_t all_possible_cnt = 0;

    if((position_x+2)<8 && (position_x+2)>=0)
    {
        if((position_y+1)<8 && (position_y+1)>=0)
        {
            all_x_positions[all_possible_cnt] = position_x+2; 
            all_y_positions[all_possible_cnt] = position_y+1;
            all_possible_cnt++;            
        }
        if((position_y-1)<8 && (position_y-1)>=0)
        {
            all_x_positions[all_possible_cnt] = position_x+2; 
            all_y_positions[all_possible_cnt] = position_y-1;
            all_possible_cnt++; 
        }
    }
    if((position_x-2)<8 && (position_x-2)>=0)
    {
        if((position_y+1)<8 && (position_y+1)>=0)
        {
            all_x_positions[all_possible_cnt] = position_x-2; 
            all_y_positions[all_possible_cnt] = position_y+1;
            all_possible_cnt++; 
        }
        if((position_y-1)<8 && (position_y-1)>=0)
        {
            all_x_positions[all_possible_cnt] = position_x-2; 
            all_y_positions[all_possible_cnt] = position_y-1;
            all_possible_cnt++; 
        }
    }
    if((position_x-1)<8 && (position_x-1)>=0)
    {
        if((position_y+2)<8 && (position_y+2)>=0)
        {
            all_x_positions[all_possible_cnt] = position_x-1; 
            all_y_positions[all_possible_cnt] = position_y+2;
            all_possible_cnt++; 
        }
        if((position_y-2)<8 && (position_y-2)>=0)
        {
            all_x_positions[all_possible_cnt] = position_x-1; 
            all_y_positions[all_possible_cnt] = position_y-2;
            all_possible_cnt++; 
        }
    }
    if((position_x+1)<8 && (position_x+1)>=0)
    {
        if((position_y+2)<8 && (position_y+2)>=0)
        {
            all_x_positions[all_possible_cnt] = position_x+1; 
            all_y_positions[all_possible_cnt] = position_y+2;
            all_possible_cnt++; 
        }
        if((position_y-2)<8 && (position_y-2)>=0)
        {
            all_x_positions[all_possible_cnt] = position_x+1; 
            all_y_positions[all_possible_cnt] = position_y-2;
            all_possible_cnt++; 
        }
    }

    *possible_cnt = all_possible_cnt;
    printf("\n");
    for(int i = 0; i < all_possible_cnt; i++)
    {
        possible_x[i] = all_x_positions[i];
        possible_y[i] = all_y_positions[i];
    }
    printf("\n");

}

void rook_possible_moves(uint8_t rook_info, const uint8_t position_x, const uint8_t position_y, const uint8_t board[][8], uint8_t *possible_x, uint8_t *possible_y, uint32_t *possible_cnt)
{
    uint8_t piece = 0;
    bool current_player_color = IS_UPPER(board[position_x][position_y]) ? true : false;
    bool player_there = 0;
    uint32_t possibilities_cnt = 0;
    printf("\ncurrent player color = %s\n", (current_player_color ? "W" : "B"));

    // right
    for(int8_t x = (position_x+1); x < board_x; x++)
    {
        // if no piece is there.
        if(board[x][position_y] == 0)
        {
            possible_x[possibilities_cnt] = x;   // can go here.
            possible_y[possibilities_cnt] = position_y;
            possibilities_cnt++;
        }
        else
        {
            player_there = IS_UPPER(board[x][position_y]) ? true : false;
            if(player_there != current_player_color) // if piece is opposite color.
            {
                possible_x[possibilities_cnt] = x;   // can go here.
                possible_y[possibilities_cnt] = position_y;
                possibilities_cnt++;
            }
            break;
        }
    }

    // left
    for(int8_t x = (position_x-1); x >= 0; x--)
    {
        // if no piece is there.
        if(board[x][position_y] == 0)
        {
            possible_x[possibilities_cnt] = x;   // can go here.
            possible_y[possibilities_cnt] = position_y;
            possibilities_cnt++;
        }
        else
        {
            player_there = IS_UPPER(board[x][position_y]) ? true : false;
            if(player_there != current_player_color) // if piece is opposite color.
            {
                possible_x[possibilities_cnt] = x;   // can go here.
                possible_y[possibilities_cnt] = position_y;
                possibilities_cnt++;
            }
            break;
        }
    }
    
    // up
    for(int8_t y = (position_y+1); y < board_y; y++)
    {
        // if no piece is there.
        if(board[position_x][y] == 0)
        {
            possible_x[possibilities_cnt] = position_x;   // can go here.
            possible_y[possibilities_cnt] = y;
            possibilities_cnt++;
        }
        else
        {
            player_there = IS_UPPER(board[position_x][y]) ? true : false;
            if(player_there != current_player_color) // if piece is opposite color.
            {
                possible_x[possibilities_cnt] = position_x;   // can go here.
                possible_y[possibilities_cnt] = y;
                possibilities_cnt++;
            }
            break;
        }
    }
    
    // down
    for(int8_t y = (position_y-1); y >= 0; y--)
    {
        // if no piece is there.
        if(board[position_x][y] == 0)
        {
            possible_x[possibilities_cnt] = position_x;   // can go here.
            possible_y[possibilities_cnt] = y;
            possibilities_cnt++;
        }
        else
        {
            player_there = IS_UPPER(board[position_x][y]) ? true : false;
            if(player_there != current_player_color) // if piece is opposite color.
            {
                possible_x[possibilities_cnt] = position_x;   // can go here.
                possible_y[possibilities_cnt] = y;
                possibilities_cnt++;
            }
            break;
        }
    }
    
    *possible_cnt = possibilities_cnt;

    printf("\npossible cnt for rook : %d", *possible_cnt);
    return;
}

void bishop_moves(uint8_t bishop_info, const uint8_t position_x, const uint8_t position_y, const uint8_t board[][8], uint8_t *possible_x, uint8_t *possible_y, uint32_t *possible_cnt)
{
    uint8_t piece = 0;

    int c = position_x - position_y;
    uint8_t y1 = board_y - 1 - position_y;
    int c1 = position_x - y1;

    unsigned char all_x_positions[100] = {0};
    uint8_t all_y_positions[100] = {0};
    uint32_t possibilities_cnt = 0;
    bool player_there = 0;
    bool current_player_color = IS_UPPER(board[position_x][position_y]) ? true : false;
    printf("\ncurrent player color = %s\n", (current_player_color ? "W" : "B"));

    int8_t x = 0;
    int8_t y = 0;
    // right up
    for(x = (position_x+1), y = position_y+1; (x < board_x && y < board_y); x++, y++)
    {
        // if no piece is there.
        if(board[x][y] == 0)
        {
            possible_x[possibilities_cnt] = x;   // can go here.
            possible_y[possibilities_cnt] = y;
            possibilities_cnt++;
        }
        else
        {
            player_there = IS_UPPER(board[x][y]) ? true : false;
            if(player_there != current_player_color) // if piece is opposite color.
            {
                possible_x[possibilities_cnt] = x;   // can go here.
                possible_y[possibilities_cnt] = y;
                possibilities_cnt++;
            }
            break;
        }
    }

    // left up
    for(x = (position_x+1), y = position_y-1; (x < board_x && y >= 0); x++, y--)
    {
        // if no piece is there.
        if(board[x][y] == 0)
        {
            possible_x[possibilities_cnt] = x;   // can go here.
            possible_y[possibilities_cnt] = y;
            possibilities_cnt++;
        }
        else
        {
            player_there = IS_UPPER(board[x][y]) ? true : false;
            if(player_there != current_player_color) // if piece is opposite color.
            {
                possible_x[possibilities_cnt] = x;   // can go here.
                possible_y[possibilities_cnt] = y;
                possibilities_cnt++;
            }
            break;
        }
    }

    // right down
    for(x = (position_x-1), y = position_y+1; (x >= 0 && y < board_y); x--, y++)
    {
        // if no piece is there.
        if(board[x][y] == 0)
        {
            possible_x[possibilities_cnt] = x;   // can go here.
            possible_y[possibilities_cnt] = y;
            possibilities_cnt++;
        }
        else
        {
            player_there = IS_UPPER(board[x][y]) ? true : false;
            if(player_there != current_player_color) // if piece is opposite color.
            {
                possible_x[possibilities_cnt] = x;   // can go here.
                possible_y[possibilities_cnt] = y;
                possibilities_cnt++;
            }
            break;
        }
    }

    // left down
    for(x = (position_x-1), y = position_y-1; (x >= 0 && y >= 0); x--, y--)
    {
        // if no piece is there.
        if(board[x][y] == 0)
        {
            possible_x[possibilities_cnt] = x;   // can go here.
            possible_y[possibilities_cnt] = y;
            possibilities_cnt++;
        }
        else
        {
            player_there = IS_UPPER(board[x][y]) ? true : false;
            if(player_there != current_player_color) // if piece is opposite color.
            {
                possible_x[possibilities_cnt] = x;   // can go here.
                possible_y[possibilities_cnt] = y;
                possibilities_cnt++;
            }
            break;
        }
    }

    *possible_cnt = possibilities_cnt;
}

void pawn_possible_moves(const uint8_t position_x, const uint8_t position_y, const uint8_t board[][8], uint8_t *possible_x, uint8_t *possible_y, uint32_t *possible_cnt)
{
    uint32_t cnt = 0;

    bool piece_color = IS_UPPER(board[position_x][position_y]) ? true : false; // true --> white, false --> black
    int8_t adder = piece_color ? 1 : -1;

    // double start for white
    // pawn is moving for the first time.
    if((piece_color && (position_x == 1)) || ((piece_color == false) && (position_x == 6)))
    {
        if(board[position_x+adder][position_y] == 0) // if there is no piece.
        {
            possible_x[cnt] = position_x+adder;
            possible_y[cnt] = position_y;
            cnt++;

            if(board[position_x+adder+adder][position_y] == 0) // if there is no piece.
            {
                possible_x[cnt] = position_x+adder+adder;
                possible_y[cnt] = position_y;
                cnt++;
            }
        }
    }
    else // pawn is moved atleast once already.
    {
        if((position_x + adder < board_x) && (position_x + adder >= 0))
        {
            if(board[position_x+adder][position_y] == 0) // if there is no piece.
            {
                possible_x[cnt] = position_x+adder;
                possible_y[cnt] = position_y;
                cnt++;
            }
        }
    }

    if((position_x + adder < board_x) && (position_x + adder >= 0))
    {
        bool piece_color_at_cross_square = 0; // considering black.
        if((position_y+1 < board_y) && (position_y+1 >= 0))
        {
            piece_color_at_cross_square = IS_UPPER(board[position_x+adder][position_y+1]); // true --> white, false --> black
            printf("\npice at right cross : %c\n", board[position_x+adder][position_y+1]);
            if((board[position_x+adder][position_y+1] != 0) && (piece_color_at_cross_square != piece_color)) // if there is a piece.
            {
                possible_x[cnt] = position_x+adder;
                possible_y[cnt] = position_y+1;
                cnt++;
            }
        }
        if((position_y-1 < board_y) && (position_y-1 >= 0))
        {
            piece_color_at_cross_square = IS_UPPER(board[position_x+adder][position_y-1]); // true --> white, false --> black
            printf("\npice at left cross : %c\n", board[position_x+adder][position_y-1]);
            if((board[position_x+adder][position_y-1] != 0) && (piece_color_at_cross_square != piece_color)) // if there is a piece.
            {
                possible_x[cnt] = position_x+adder;
                possible_y[cnt] = position_y-1;
                cnt++;
            }
        }
    }

    *possible_cnt = cnt;
}

void king_possible_moves(const uint8_t position_x, const uint8_t position_y, const uint8_t board[][8], uint8_t *possible_x,  uint8_t *possible_y, uint32_t *possible_cnt) 
{
    uint32_t cnt = 0;
    bool piece_color = IS_UPPER(board[position_x][position_y]); // true -> white, false -> black

    // Possible king moves (x, y offsets)
    int8_t moves[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, // Top-left, Top, Top-right
        {0, -1},{0, 1},    // Left, Right
        {1, -1}, {1, 0}, {1, 1}     // Bottom-left, Bottom, Bottom-right
    };

    for (int i = 0; i < 8; i++) {
        int8_t new_x = position_x + moves[i][0];
        int8_t new_y = position_y + moves[i][1];

        // Check if within board limits
        if (new_x >= 0 && new_x < board_x && new_y >= 0 && new_y < board_y)
         {
            uint8_t target_piece = board[new_x][new_y];

            // King can move if the square is empty or occupied by an enemy piece
            if (target_piece == 0 || IS_UPPER(target_piece) != piece_color) {
                possible_x[cnt] = new_x;
                possible_y[cnt] = new_y;
                cnt++;
            }
        }
    }

    *possible_cnt = cnt;
}
