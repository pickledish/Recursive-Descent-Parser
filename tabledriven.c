#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

int isProduction(token test) {
	switch(token) {
		case (t_SL):
		case (t_S):
		case (t_D):
		case (t_E):
		case (t_T):
		case (t_F):
		case (t_TT):
		case (t_FT):
		case (t_ao):
		case (t_mo):
			return 1;
		default:
			return 0;
	}
}

list* tokens;
						//   N/a     lit      +       *      (       $$      \n
                        //       id      :=       -       /       )      let
int parseTable[11][13] = {{-1,  0,  0, -1, -1, -1, -1, -1,  0, -1,  0,  0, -1} , // P 
                          {-1,  1,  1, -1, -1, -1, -1, -1,  1, -1,  2,  1, -1} , // SL
                          {-1,  4,  4, -1, -1, -1, -1, -1,  4, -1, -1,  3, -1} , // S 
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  5, -1} , // D 
                          {-1,  6,  6, -1, -1, -1, -1, -1,  6, -1, -1, -1, -1} , // E 
                          {-1,  7,  7, -1, -1, -1, -1, -1,  7, -1, -1, -1, -1} , // T 
                          {-1,  9, 10, -1, -1, -1, -1, -1,  8, -1, -1, -1, -1} , // F 
                          {-1, 12, 12, -1, 11, 11, -1, -1, 12, 12, 12, 12, -1} , // TT
                          {-1, 14, 14, -1, 14, 14, 13, 13, 14, 14, 14, 14, -1} , // FT
                          {-1, -1, -1, -1, 15, 16, -1, -1, -1, -1, -1, -1, -1} , // ao
                          {-1, -1, -1, -1, -1, -1, 17, 18, -1, -1, -1, -1, -1}   // mo
	
};

token Productions[19][5] =  {{t_SL, t_eof, t_none},
							 {t_S, t_SL, t_none},
							 {, t_none},
							 {t_D, t_none},
							 {t_E, t_none},
							 {t_let, t_id, t_gets, t_E, t_none},
							 {t_T, t_TT, t_none},
							 {t_F, t_FT, t_none},
							 {t_lparen, t_E, t_rparen, t_none},
							 {t_id, t_none},
							 {t_literal, t_none},
							 {t_ao, t_T, t_TT, t_none},
							 {, t_none},
							 {t_mo, t_F, t_FT, t_none},
							 {, t_none},
							 {t_add, t_none},
							 {t_sub, t_none},
							 {t_mul, t_none},
							 {t_div, t_none},
};

