#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char outtoken[200][10];  //トークン出力用配列
int tnum;

char token[20];
char res[13][20]={"begin","end","if","then","while","do",
				  "return","function","var","const","odd",
				  "write","writeln"};
char sign[17][10]={"+","-","*","/","(",")","=","<",">",
			      "<>","<=",">=",",",".",";",":="};
FILE *fi;
//関数宣言
void nexttoken(int);  //次のトークンを読み込む関数
int ch(char[]);    //引数の文字列との比較　同じ:1　違う:0
int ttype();       //トークンのタイプを返す 1:予約語 2:記号
		   //		      3:名前   4:整数
void exit_func();  //構文解析エラー　強制終了
void backtoken();  //現在のトークンの番号を1つ前に戻す

void block(), varDecl(), constDecl(), funcDecl(),
	 statement(), condition(), expression(), term(),
	 factor();              //構文規則を指定
void get_token();
int check_word(char);

int main(int argc, char **argv)
{
	get_token();  //1週目で行ったトークン分割プログラム
	tnum=0;
	block();
	nexttoken(1);
	if(ch(".")) printf("Complete\n");
	else printf("Syntax Error\n");

	return 0;
}

void block()
{
	int c;
	c=0;
	nexttoken(0);
	while(ch("const")||ch("var")||ch("function")){
		c++;
		if(ch("const")) constDecl();
		else if(ch("var")) varDecl();
		else if(ch("function")) funcDecl();
	}
	if(!c) backtoken();
	statement();
}

void varDecl()
{
	nexttoken(1);
	if(ttype()!=3) exit_func("Syntax Error");
	nexttoken(1);
	while(ch(",")){
		nexttoken(1);
		if(ttype()!=3) nexttoken(1);
		else exit_func("Syntax Error");
	}
	if(ch(";")){}
	else exit_func("Syntax Error");
}

void funcDecl()
{
	nexttoken(3);
	if(ttype()!=3) exit_func("Syntax Error");
	nexttoken(3);
	if(!ch("(")) exit_func("Syntax Error");
	nexttoken(3);
	if(ttype()!=3) 
			exit_func("Syntax Error");
	nexttoken(3);
	while(ch(",")){
		nexttoken(3);
		if(ttype()==3) nexttoken(3);
		else exit_func("function error");
	}
	if(ch(")")) block();
	else exit_func("funcdec3");
	nexttoken(3);
	if(ch(";")) nexttoken(3);
	else exit_func("funcdec4");
}

void constDecl()
{
	do{
		nexttoken(2);
		if(ttype()!=3) exit_func("Syntax Error");
		nexttoken(2);
		if(!ch("=")) exit_func("Syntax Error");
		nexttoken(2);
		if(ttype()!=4) exit_func("Syntax Error");
		nexttoken(2);
	}while(ch(","));
	if(ch(";"))nexttoken(2);
	else exit_func("Syntax Error");
}

void statement()
{
	int a,b,n;
	int t_now, t_next;

	nexttoken(4);
	if(ttype()==3){	//ident
		nexttoken(4);
		if(ch(":=")==0) exit_func("Syntax Error");
		expression();
	}
	else if(ch("begin")){
		statement();
		nexttoken(4);
		while(ch(";")==1){
			statement();
			nexttoken(4);
		}
		if(ch("end")==0) exit_func("Syntax Error");
	}
	else if(ch("if")){
		condition();
		nexttoken(4);
		if(ch("then")==0) exit_func("Syntax Error");
		statement();
	}
	else if(ch("while")){
		condition();
		nexttoken(4);
		if(ch("do")==0) exit_func("Syntax Error");
		statement();
	}
	else if(ch("return")){
		expression();
	}else if(ch("write")){
		expression();
	}else if(ch("writeln")){
	}else{   //何もせずにスルー 
		backtoken();
	}
}

void condition()
{
	nexttoken(5);
	if(ch("odd")==1){
		expression();
	}else{
		backtoken();
		expression();
		nexttoken(5);
		if(ch("=")==1 || ch("<>")==1 || ch("<")==1 || ch(">")==1 ||ch("<=")==1 ||ch(">=")==1 ){
			expression();
		}else{
			exit_func("Syntax Error");
		}
	}
}

void expression()
{
	nexttoken(6);
	if(ch("+")==1 || ch("-")==1){
		term();
		nexttoken(6);
		while(ch("+")==1 || ch("-")==1){
			term();
			nexttoken(6);
		}
	}else{
		backtoken(6);
		term();
		nexttoken(6);
		while(ch("+")==1 || ch("-")==1){
			term();
			nexttoken(6);
		}
	}
	backtoken();
}

void term()
{
	factor();
	nexttoken(7);
	while(ch("*")==1 || ch("/")==1){
		factor();
		nexttoken(7);
	}
	backtoken();
}

void factor()
{
	nexttoken(8);
	if(ttype()==3){
		nexttoken(8);
			if(ch("(")==1){
				nexttoken(8);
				if(ch(")")==1){
				}else{
					backtoken();
					expression();
					nexttoken(8);
					while(ch(",")==1){
						expression();
						nexttoken(8);
					}
				}
			}else{
				backtoken();
			}
	}else if(ttype()==4){
	}else if(ch("(")==1){
		expression();
		nexttoken(8);
		if(ch(")")==1){
		}else{
			backtoken();
		}
	}
}

void nexttoken(int s)
{
	char state[30];
	switch(s){
		case 0: sprintf(state,"block");
				break;
		case 1: sprintf(state, "constDecl");
				break;
		case 2: sprintf(state, "verDecl");
				break;
		case 3: sprintf(state, "funcDecl");
				break;
		case 4: sprintf(state, "statement");
				break;
		case 5: sprintf(state, "condition");
				break;
		case 6: sprintf(state, "expression");
				break;
		case 7: sprintf(state, "term");
				break;
		case 8: sprintf(state, "factor");
				break;
	}
	strcpy(token,outtoken[tnum]);
	tnum++;
	printf("%-13s : [%s]\n",state,token);
}

int ch(char str[20]) //文字列の比較
{
	if(strcmp(token,str)==0) return 1;
	else return 0;
}

int ttype()  //トークンのタイプを返す
{
	int i,c;
	for(i=0;i<13;i++){
		c=strcmp(token,res[i]);
		if(c==0){
			return 1;
			break;
		}
	}

	for(i=0;i<16;i++){
		c=strcmp(token,sign[i]);
		if(c==0){
			return 2;
			break;
		}
	}

	if(token[0] >='0' && token[0]<='9')
		return 4;
	else
		return 3;
}

void backtoken() //トークン番号を1つ前に戻す
{
	tnum--;
}

void exit_func(char str[20])  //文法規則に合わないため終了
{
	printf("Syntax Error Near the Word \"%s\"\n",token);
	printf("%s\n",str);
	exit(1);  //強制終了
}


void get_token()
{
	int i,j,token_num;
	char c;
	fi=fopen("program1","r");
	token_num=0;  //トークンの数の初期化
	j=0;
	while(1){
		c=fgetc(fi);  //1文字ずつ入力
		//printf("%c\n",c);
		if(c==EOF)break;

		if(check_word(c)==0){//数字なら 
			outtoken[token_num][j]=c;
			j++;
		}
		else if(check_word(c)==1){//文字なら
			outtoken[token_num][j]=c; 
			j++;
		}
		else if(check_word(c)==2){  //改行，スペース，タブなら
			if(j!=0){
				outtoken[token_num][j]='\0';
				j=0;
				token_num++;
			}
			else{
				//do nothing!!
			}
		}else if(check_word(c)==3){  //記号なら(1文字)
			if(j!=0){
				token_num++;
				j=0;
				outtoken[token_num][j]=c;
				token_num++;
				
			}else{
				outtoken[token_num][j]=c;
				j=0;
				token_num++;
			}
		} else if(check_word(c)==4){  //記号なら(2文字)
			if(j!=0){
				token_num++;
				j=0;
				outtoken[token_num][j]=c;
				c=fgetc(fi);
				outtoken[token_num][j+1]=c;
				token_num++;
				j=0;
			}else{
				outtoken[token_num][j]=c;
				c=fgetc(fi);
				outtoken[token_num][j+1]=c;
				token_num++;
				j=0;
			}
		} 
	}
	
	for(i=0;i<token_num;i++)
		printf("%3d  %s\n",i,outtoken[i]);
}

int check_word(char c)
{
	if(c>='0' && c<='9') // 数字なら 
		return 0;
	else if(c>='a' && c<='z')        //アルファベット
		return 1;
	else if(c=='\n' || c=='\t' || c==' ')        //改行，スペース，タブ
		return 2;
	else if(c== '+' || c=='-' || c=='/' || c=='(' ||c== ')' ||c== ',' || c== ';' || c=='.' || c=='=' )        //1文字のみの記号
		return 3;
	else if(c==':')      //コロンは'='と必ず一緒になる
		return 4;
	else if(c=='<' || c=='>'){  //この場合は次の文字を見る必要がある
		c=fgetc(fi);
		fseek(fi,-1,1);   //ファイルポインタを1つ戻す 
		if(c=='=' || c=='>'){
			return 4;
		}else{
			return 3;
		}
	}
}

