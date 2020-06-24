#include <stdio.h>
#include <math.h>

void map_display (unsigned long long H) {
	//functia afiseaza harta :)
	int i; unsigned long long mask;

	for (i = 63; i >= 0; i--) {
		mask = 1ULL << i;
		if (H & mask) 
			printf ("#");
		else printf (".");
		if (i % 8 == 0) 
			printf ("\n"); 
		
	}
	printf ("\n");
} 

int bit (unsigned long long mask, unsigned long long piece) {
	/*	verify if a piece that spans over two rows has been fully
	displayed */
	int i, zeroes1 = 0, zeroes2 = 0;
	/* zeroes1, zeroes2 vor number of zeroes for mask/piece */
	unsigned long long byte;
	for (i = 63; i >= 0; i--) {
		byte = 1ULL << i;
		if ((byte & mask) == 0)
			zeroes1++; 
	}
	for (i = 63; i >= 0; i--) {
		byte = 1ULL << i;
		if ((byte & piece) == 0)
			zeroes2++;
	}
	if (zeroes1 == zeroes2) 
		 return 1;
	else return 0; 

}

float score (int noOfDeletedLines, unsigned long long H) {
	//functia calculeaza scoreul jocului
	int i, zeroes = 0;
	float Score;
	unsigned long long mask;

	for (i = 63; i >= 0; i--) {
		mask = 1ULL << i;
		if ((H & mask) == 0)
			zeroes++; 
	}
	Score = sqrt (zeroes) + pow (1.25, noOfDeletedLines);
	return Score;
}

unsigned long long delete (unsigned long long H, unsigned *noOfDeletedLines) {
	// function eliminates full lines
	int i, j = 1, k; 
	unsigned long long byte, byte2, byte3;

	for (i = 63; i >= 0; i--) {
		byte = 1ULL << i;
		if ((byte & H) == 0) 
			j = 0;
		if ((i % 8 == 0) && (j == 1)) {
			
			byte3 = H;
			for (k = i + 7; k >= 0; k--) { 		
				byte2 = ~(1ULL << k); 
				byte3 = byte3 & byte2;
			}

			
			for (k = 63; k >= i; k--) { 		
				byte2 = ~(1ULL << k); 
				H = H & byte2;
			}
			byte3 = byte3 >> 8;
			H = H | byte3;

				


			*noOfDeletedLines = *noOfDeletedLines + 1;
			
		}		
		if (i % 8 == 0)
			j = 1;
			
	}
	return H;
}



int collisions (unsigned long long mask, unsigned long long H) {
	if ((mask & H) == 0)
		return 1;
	else    return 0;

}

int left_right (unsigned long long mask, int move, unsigned long long H){

	int i, k, ok = 0, min = 100, max = 100;
	 
	
	unsigned long long mask2, byte;  
	if (move > 0) {
		for (i = 0; i <= 63; i++) {
			byte = 1ULL << i;
			if (byte & mask) {
				min = i;
				break;
			}
		}

		byte = 1ULL << (min + 7);
		min = min % 8;
		if (byte & mask)
			min = min - 1;

	}

	if (move < 0) {
		for (i = 63; i >= 0; i--) {
			byte = 1ULL << i;
			if (byte & mask) {
				max = i;
				break;
			}
		}

		byte = 1ULL << (max - 7);
		max = 7 - max % 8;
		if (byte & mask)
			max = max - 1;

	}
	max = - max;
	if ((move > 0) && (min < move))
		ok = min;
	else if ((move < 0) && (max > move))
		ok = max;
	else ok = move;

	
	
	if (move > 0)
		mask2 = mask >> ok;
	else    mask2 = mask << (-ok);
	
	
	while ((collisions (mask2, H) == 0) && (ok!=0)) {
		if (move > 0) {
			mask2 = mask2 << 1;
			ok--;
		}
		else  { mask2 = mask2 >> 1;
			ok++; 
		}
	} 	
	mask2 = mask;
	k = -1;
	if (move > 0) {
		for (i = 1; i <= ok; i++) {
			mask2 = mask2 >> 1;
			if (collisions (mask2, H) == 0) {
				k = i - 1;
				break;
			}
		}
		if (k < ok && k != -1)
			ok = k;
	}

	if (move < 0) {
		for (i = 1; i <= -ok; i++) {
			mask2 = mask2 << 1;
			if (collisions (mask2, H) == 0) {
				k = i - 1;
				break;
			}
		}
		if (-k > ok && k != -1)
			ok = -k;
	}
	





	
	return ok;
}

unsigned long long moves 
	(unsigned long long mask, unsigned long long H, int *ok1) {
	
	int move, ok; 

		
		scanf ("%d", & move);
			ok = left_right (mask, move, H);
			*ok1 = ok;
			
			
			if (move > 0) {				
				mask = mask >> ok;
				H = H | mask;
			}
			else if (move < 0) {
				ok = - ok;
				mask = mask << ok;
				H = H | mask;
			}
			else H = H | mask;

	return H;
}


int main () {
	unsigned long long H, H2, piece, upp = 24ULL << 56, mask;
	// upp == last possible piece
	unsigned M, i, j, k, noOfDeletedLines = 0, nr;
	int ok1, move; 
	 // H - map, M - number of moves
	
	scanf ("%llu", &H);
	map_display (H);
	
	scanf ("%u\n", &M); 
	
	
	for (i = 1; i <= M; i++) { 
		nr = noOfDeletedLines;
			H2 = delete (H2, & noOfDeletedLines);
			if (noOfDeletedLines != nr)
				map_display (H2);
		scanf ("%lld", & piece); 
		mask = (piece << 56);
		if (collisions (mask, H) == 0 || (H & upp) != 0){
 				map_display (H);
 				break;
 			}

		for (j = 1; j <= 8; j++) {

			if ((j == 2) && (piece << 48) != mask) {
				piece = (piece << 48);
				if (ok1 > 0)
					piece = (piece >> ok1);
				else { 
					ok1 = - ok1;
					piece = (piece << ok1);
				}
				mask = piece;
			} 

 			if (collisions (mask, H) == 0) {
 				for (k = j; k <= 8; k++)
 					scanf ("%d", &move);
				break;
 			}
 			
 			

			H2 = moves (mask, H, & ok1);
			map_display (H2);

			

			mask = (~H) & H2;
			
			
			if (j != 8)
				mask = (mask >> 8);
			
			
		
		}

		nr = noOfDeletedLines;
			H2 = delete (H2, & noOfDeletedLines);
			if (noOfDeletedLines != nr)
				map_display (H2);
		H = H2;
		if ((bit(mask, piece) == 0) && (collisions(mask, H) == 0)) {
			map_display (H);
			break; }
		
		else if (collisions (mask, H) && (nr == noOfDeletedLines))
			map_display (H);

		
	}
	printf("GAME OVER!\nScore:%.2f\n", score (noOfDeletedLines, H));
return 0;	
}
