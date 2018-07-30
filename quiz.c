#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void shuffle(int ary[],int size)
{
	int i;
	for(i=0;i<size;i++){
		int j = rand() % size;
		int t = ary[i];
		ary[i] = ary[j];
		ary[j] = t;
	}
}	

int gouhi(int kaito,int kotae){
	if(kaito==kotae){
		return 1;
	}else{
		return 2;
	}
}

int quiz()
{
	FILE *fi;
	int i,ret,gyo,kaitosu,mon,answer,maru;
	float seiritu;
	fi=fopen("hyou.txt","r");
	if(fi==NULL){
		puts("ファイルオープンエラー\n");
		return -1;
	}

	struct{
		int tosi;
		int number;
		int tf;
		wchar_t koto[20];
	} nenpyo[200];
	i=ret=gyo=kaitosu=mon=answer=maru=seiritu=0;
	srand(time(NULL));

	while( ( ret = fscanf(fi,"%d %d %s %d",&nenpyo[gyo].number,&nenpyo[gyo].tosi,nenpyo[gyo].koto,&nenpyo[gyo].tf) ) != EOF){
		gyo++;
	}
	
	int list[gyo];
	for(i=0;i<gyo;i++){
		list[i]=i;
	}

	puts("問題数を入力してください。(100問まで)\n");
	scanf("%d",&kaitosu);
	if(kaitosu>100){
		puts("エラーのため終了します。");
		return -1;
	}

	int size = sizeof(list) / sizeof(int);
	shuffle(list,size);
	puts("次に表示される出来事が起こった年を入力しなさい。\n");
	for(i=0; i<kaitosu; i++){
		printf("%d  %s \n",i+1,nenpyo[ list[i] ].koto);
		scanf("%d",&answer);
		if( gouhi(answer,nenpyo[ list[i]].tosi) == 1){
			nenpyo[ list[i] ].tf=1;
			puts("〇\n");
			maru++;
		}else{
			nenpyo[ list[i] ].tf=2;
			puts("×\n");
		}
	}

	seiritu = (float)maru/kaitosu *100;
	printf("%d問中%d問正解です。　正答率：%.3f %\n",kaitosu,maru,seiritu);
	fclose(fi);
}

int main()
{
	quiz();
	return 0;
}	
		
