#include <stdio.h>
#include <stdlib.h>

#define N		3
#define M		3
#define TRUE	1
#define FALSE	0
typedef int bool;

int board[N * M][M * N];

void board_horizontal_line_print(){
	/* 区切りを表示 */
	printf("+-------+-------+-------+");

	printf("\n");
}

bool is_print_horizontal_position(int pos){
	/* 区切りを表示すべき場所の場合は1を、表示すべきでない場所の場合は0をreturn */
	if( (pos + 1) % N == 0 )
		return TRUE;
	else
		return FALSE;
}

void board_print(){
	int i,j;
	board_horizontal_line_print();
	for(i = 0;i < N * N;i++){
		printf("|");
		for(j = 0;j < N * N;j++){
			if(board[i][j] != 0)
				printf(" %d",board[i][j]);
			else
				printf(" .");

			if(is_print_horizontal_position(j)) printf(" |");
		}
		printf("\n");
		if(is_print_horizontal_position(i))
			board_horizontal_line_print();
	}
}

void board_read(const char *filename){
	/* File Pointerを作成 */
	FILE *fp;
	/* 読みだしたデータの保管用 */
	char buf[N + 1];
	/* ループ用の変数 */
	int i,j;
	/* ファイルオープン */
	if( (fp = fopen(filename,"r")) == NULL ){
		printf("ファイルのオープンに失敗しました。\n");
		exit(EXIT_FAILURE);
	}

	/* %で始まる最初の行を読み飛ばす。 */
	fscanf(fp,"%*[^\n]");

	/* 1行ずつ読み込む */
	for(i = 0;(fscanf(fp,"%9s%*[^\n]",buf)) != EOF;i++){
		/* 一文字ずつ読み込む */
		for(j = 0;j < N * N;j++){
			if(buf[j] == '.'){
				board[i][j] = 0;
			}else if('0' <= buf[j] && buf[j] <= '9'){
				board[i][j] = buf[j] - '0';
			}else{
				printf("不正な値が入力されました。%d\n",buf[j]);
				exit(EXIT_FAILURE);
			}
		}
	}
	fclose(fp);
}

int main(int argc,char *argv[]){
	if(argc == 2){
		board_read(argv[1]);
		board_print();
	}else if(argc == 1){
		printf("コマンドライン引数にボードファイルを指定してください。\n");
		exit(EXIT_FAILURE);
	}else{
		printf("コマンドライン引数が多すぎます。\n");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}