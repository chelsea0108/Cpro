#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//int GetRandom(int min,int max);
int con;

add(){
		int num;
		char name[10],team[20],posi[10],fea[10];
		FILE *fp;
		char ch[256];
for(;;){
		fp = fopen("playerdata.txt","a"); //ファイルを書き込みモード

		if(fp==NULL){
			printf("FILE OPEN ERROR!!\n");
			return -1;
		}
		printf("選手名を入力してください\n");
		scanf("%s",name);
		printf("所属チームを入力してください\n");
		scanf("%s",team);
		printf("背番号を入力してください\n");
		scanf("%d",&num);
		printf("守備位置を入力してください\n");
		scanf("%s",posi);
		printf("特徴を入力してください\n");
		scanf("%s",fea);
			
		fprintf(fp,"%s %s %d %s %s\n",name,team,num,posi,fea);
		fclose(fp);

		printf("編集を続けますか?\n");
		printf("1.続ける\n");
		printf("2.モード選択に戻る\n");
		scanf("%d",&con);
		if(con==1){
			printf("\n");
		}else if(con==2){
			break;
		}else{
			printf("エラーのためモード選択に戻ります\n");
			break;
		}
	}
}

del()
{
	//変数//
	FILE*fp,*fp2;
	char word;
	int fig,num,gyou;
	char *filename = "output.txt";//ファイル作成後ファイル消すため	
	wchar_t name[10],team[20],posi[10],fea[10];
	int bango;

for(;;){
	num=1;
	fig=0;
	gyou=0;
	fp=fopen("playerdata.txt","r");//全体表示　行番号付き	
	if(fp == NULL){
		printf("ファイルを開けません！\n");
		exit(1);
		}
		
		while(fscanf(fp,"%s %s %d %s %s",name,team,&bango,posi,fea)!=EOF){
			printf("%d %s %s %d %s %s\n",gyou+1,name,team,bango,posi,fea);
			gyou++;
			
		}
fclose(fp);
		
	printf("削除したい行を指定してください\n");//削除行指定
	scanf("%d",&fig);
		if(fig>gyou)printf("その行は存在しません\n");//error
		else{
			
	fp=fopen("playerdata.txt","r");
		if(fp == NULL){
			printf("ファイルを開けません！\n");
			exit(1);
		}
	fp2=fopen("output.txt","w");//別ファイルに削除行以外を写す
	
	
	while(num<fig){
		fscanf(fp,"%s %s %d %s %s",name,team,&bango,posi,fea);
		fprintf(fp2,"%s %s %d %s %s\n",name,team,bango,posi,fea);
		num++;
	}
	
	fscanf(fp,"%s %s %d %s %s",name,team,&bango,posi,fea);
	printf("%s %s %d %s %s",name,team,bango,posi,fea);
	while(num<gyou){
		fscanf(fp,"%s %s %d %s %s",name,team,&bango,posi,fea);
		fprintf(fp2,"%s %s %d %s %s\n",name,team,bango,posi,fea);
		num++;
		}
		fclose(fp);
		fclose(fp2);
	
	num=0;
	fp2=fopen("output.txt","r");
	if(fp2 == NULL){
		printf("ファイルを開けません！\n");
		exit(1);
	}
	fp=fopen("playerdata.txt","w");//元のファイルにうつし直す
	
	while(num<gyou-1){
		fscanf(fp2,"%s %s %d %s %s",name,team,&bango,posi,fea);
		fprintf(fp,"%s %s %d %s %s\n",name,team,bango,posi,fea);
		num++;
	}
		fclose(fp);
		fclose(fp2);

  remove(filename);//output.txtの削除

printf("\n↑ を削除しました。\n");

	printf("編集を続けますか?\n");
		printf("1.続ける\n");
		printf("2.モード選択に戻る\n");
		scanf("%d",&con);
		if(con==1){
			printf("\n");
		}else if(con==2){
			break;
		}else{
			printf("エラーのためモード選択に戻ります\n");
			break;	
		}
	}
}

}


hensyu()
{
	FILE *fi,*fw;
	int i,n,ret,gyo;
	fi=fopen("playerdata.txt","r+");
	if(fi==NULL){
	        printf("ファイルオープンエラー\n");
	        return -1;
	}
	struct{
		wchar_t name[20];
		wchar_t team[20];
		int number;
		wchar_t syubi[20];
		wchar_t tokucho[30];
	} data[100];
	i=n=ret=gyo=0;
	
	while( (ret = fscanf(fi,"%s %s %d %s %s",data[n].name,data[n].team,&data[n].number,data[n].syubi,data[n].tokucho) ) != EOF){
		n++;
	}
	for(;;){
		printf("\n");
		for(i=0;i<n;i++){
			printf("%d %s %s %d %s %s\n",i+1,data[i].name,data[i].team,data[i].number,data[i].syubi,data[i].tokucho);
		}
		printf("\n");

		printf("編集する行を入力してください\n");
		scanf("%d",&gyo);
		printf("選手名を入力してください\n");
		scanf("%s",&data[gyo-1].name);
		printf("所属チームを入力してください\n");
		scanf("%s",&data[gyo-1].team);
		printf("背番号を入力してください\n");
		scanf("%d",&data[gyo-1].number);
		printf("守備位置を入力してください\n");
		scanf("%s",&data[gyo-1].syubi);
		printf("特徴を入力してください\n");
		scanf("%s",&data[gyo-1].tokucho);
		printf("%d行目を変更しました\n",gyo);

		fw=fopen("playerdata.txt","w+");
		for(i=0;i<n;i++){
			fprintf(fw,"%s %s %d %s %s\n",data[i].name,data[i].team,data[i].number,data[i].syubi,data[i].tokucho);
		}
		
		while( (ret = fscanf(fw,"%s %s %d %s %s",data[n].name,data[n].team,&data[n].number,data[n].syubi,data[n].tokucho) ) != EOF){
		n++;
		}
		fclose(fw);

		printf("編集を続けますか?\n");
		printf("1.続ける\n");
		printf("2.モード選択に戻る\n");
		scanf("%d",&con);
		if(con==1){
			printf("\n");
		}else if(con==2){
			break;
		}else{
			printf("エラーのためモード選択に戻ります\n");
			break;
		}
	}

	fclose(fi);
}


search()
{
	char buff[256];
	char find[256];
	char l[256];
	int c;
	FILE *fp;
	FILE *fo;

	for(;;){
	printf("検索語句を入力してください\n");
	scanf("%s",find);

	if(find[0]=='\n'){
		printf("検索語句が入力されませんでした\n検索を終了します\n");
	}
	else if(find[0]!='\n')
	{
		c=0;
		printf("検索語句が入力されました\n");
		printf("\n");

		fp=fopen("playerdata.txt","r");
		fo=fopen("search.txt","w+");

		while(fgets(buff,sizeof(buff),fp)!=NULL){
			if(strstr(buff,find)!=NULL){
			fputs(buff,fo);
			c=c+1;
			}
		}

		fclose(fp);
		fclose(fo);

		printf("検索結果 %d件 \n",c);
		fo=fopen("search.txt","r");
		while(fgets(l,sizeof(l),fo)!=NULL){
			printf("%s",l);
		}

		fclose(fo);
		printf("編集を続けますか?\n");
		printf("1.続ける\n");
		printf("2.モード選択に戻る\n");
		scanf("%d",&con);
		if(con==1){
			printf("\n");
		}else if(con==2){
			break;
		}else{
			printf("エラーのためモード選択に戻ります\n");
			break;
		}
	}
}
}

output(){

		FILE *fp;
		char str;

		fp = fopen("playerdata.txt","r"); //ファイル読み込みモード

		if(fp==NULL){
			printf("FILE OPEN ERROR!!\n");
			return -1;
		}

		while((str = fgetc(fp)) != EOF){
			printf("%c",str);
		}

		fclose(fp);

}


ranteam()
{

	int GetRandom(int min,int max);

	FILE *fi;
	fi=fopen("playerdata.txt","r");
	int i,j,ja,jb,jc,jd,je,jf,jg,jh,ji,jk,jl,k,ka,kb,kc,kd,ke,kf,kg,kh,ki,kj,kk,kl,l,num[10][999],max,pit,cat,fir,sec,thi,sho,lef,cen,rig,dhn;
	char name[20][999],wc;
	char	*s1="投手",*s2="捕手",*s3="一塁手",*s4="二塁手",*s5="三塁手",*s6="遊撃手",*s7="左翼手",*s8="中堅手",*s9="右翼手",*s10="指名打者",*s01="ピッチャー",*s02="キャッチャー",*s03="ファースト",*s04="セカンド",*s05="サード",*s06="ショート",*s07="レフト",*s08="センター",*s09="ライト",*s010="DH",*s99="";


struct list{
	char lname[100];
	char team[100];
	char number[3];
	char position[100];
	char advantage[100];
};

struct list list[999];

	srand((unsigned int)time(NULL));

	max=0,k=0;

	for(i=0;;i++){
		fscanf( fi, "%s %s %s %s %s", list[i].lname,list[i].team,list[i].number,list[i].position,list[i].advantage);
//		printf("%s %s %s %s %s\n",list[i].lname,list[i].team,list[i].number,list[i].position,list[i].advantage);
		max++;
		if(feof(fi)){
			break;
		}
	}


		struct list pitcher[999];					//ピッチャー
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s1)==0)||(strcmp(list[j].position,s01)==0)){
			strcpy(pitcher[k].lname,list[j].lname);
			k++;
		}
		ka=k;
	}

		struct list catcher[999];					//キャッチャー
		k=0;
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s2)==0)||(strcmp(list[j].position,s02)==0)){
			strcpy(catcher[k].lname,list[j].lname);
			k++;
		}
		kb=k;
	}

		struct list first[999];					//ファースト
		k=0;
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s3)==0)||(strcmp(list[j].position,s03)==0)){
			strcpy(first[k].lname,list[j].lname);
			k++;
		}
		kc=k;
	}

		struct list second[999];					//セカンド
		k=0;
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s4)==0)||(strcmp(list[j].position,s04)==0)){
			strcpy(second[k].lname,list[j].lname);
			k++;
		}
		kd=k;
	}
		struct list third[999];					//サード
		k=0;
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s5)==0)||(strcmp(list[j].position,s05)==0)){
			strcpy(third[k].lname,list[j].lname);
			k++;
		}
		ke=k;
	}
		struct list shor_t[999];					//ショート
		k=0;
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s6)==0)||(strcmp(list[j].position,s06)==0)){
			strcpy(shor_t[k].lname,list[j].lname);
			k++;
		}
		kf=k;
	}
		struct list left[999];					//レフト
		k=0;
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s7)==0)||(strcmp(list[j].position,s07)==0)){
			strcpy(left[k].lname,list[j].lname);
			k++;
		}
		kg=k;
	}
		struct list center[999];					//センター
		k=0;
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s8)==0)||(strcmp(list[j].position,s08)==0)){
			strcpy(center[k].lname,list[j].lname);
			k++;
		}
		kh=k;
	}
		struct list right[999];					//ライト
		k=0;
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s9)==0)||(strcmp(list[j].position,s09)==0)){
			strcpy(right[k].lname,list[j].lname);
			k++;
		}
		ki=k;
	}
		struct list DH[999];					//DH
	for(j=0;j<max;j++){
		if((strcmp(list[j].position,s10)==0)||(strcmp(list[j].position,s010)==0)){
			strcpy(DH[k].lname,list[j].lname);
			k++;
		}
		kj=k;
	}




	for(;;){
		pit=GetRandom(0,ka);
		if(strcmp(pitcher[pit].lname,s99)!=0){
			printf("投手 %s\n",pitcher[pit].lname);
			break;
		}
	}

	for(;;){
		cat=GetRandom(0,kb);
		if(strcmp(catcher[cat].lname,s99)!=0){
			printf("捕手 %s\n",catcher[cat].lname);
			break;
		}
	}
	for(;;){
		fir=GetRandom(0,kc);
		if(strcmp(first[fir].lname,s99)!=0){
			printf("一塁手 %s\n",first[fir].lname);
			break;
		}
	}
	for(;;){
		sec=GetRandom(0,kd);
		if(strcmp(second[sec].lname,s99)!=0){
			printf("二塁手 %s\n",second[sec].lname);
			break;
		}
	}
	for(;;){
		thi=GetRandom(0,ke);
		if(strcmp(third[thi].lname,s99)!=0){
			printf("三塁手 %s\n",third[thi].lname);
			break;
		}
	}
	for(;;){
		sho=GetRandom(0,kf);
		if(strcmp(shor_t[sho].lname,s99)!=0){
			printf("遊撃手 %s\n",shor_t[sho].lname);
			break;
		}
	}
	for(;;){
		lef=GetRandom(0,kg);
		if(strcmp(left[lef].lname,s99)!=0){
			printf("左翼手 %s\n",left[lef].lname);
			break;
		}
	}
	for(;;){
		cen=GetRandom(0,kh);
		if(strcmp(center[cen].lname,s99)!=0){
			printf("中堅手 %s\n",center[cen].lname);
			break;
		}
	}
	for(;;){
		rig=GetRandom(0,ki);
		if(strcmp(right[rig].lname,s99)!=0){
			printf("右翼手 %s\n",right[rig].lname);
			break;
		}
	}
	for(;;){
		dhn=GetRandom(0,kj);
		if(strcmp(DH[dhn].lname,s99)!=0){
			printf("指名打者 %s\n",DH[dhn].lname);
			break;
		}
	}


	fclose(fi);
}

int GetRandom(int min,int max){
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}


int main()
{
	int mode;
	mode=0;
	printf("************プロ野球選手名鑑*************\n");
	
	for(;;){
   		printf("何を実行しますか？\n");
    	printf("1.追加\n");
    	printf("2.削除\n");
    	printf("3.編集\n");
    	printf("4.検索\n");
		printf("5.全体表示\n");
		printf("6.チーム作成\n");
		printf("7.終了\n");\
    	scanf("%d",&mode);

  		switch(mode){
        	case 1:
				add();
				printf("\n");
				break;

			case 2:
				del();
				printf("\n");
				break;

			case 3:
				hensyu();
				printf("\n");
				break;

			case 4:
				search();
				printf("\n");
				break;

			case 5:
				output();
				printf("\n");
				break;

			case 6:
				ranteam();
				printf("\n");
				break;

			case 7:
				printf("プログラムを終了します．\nGood bye!!\n");
				break;

			default:
				printf("ERROR!\n");
				printf("\n");
				break;
		}
		if(mode==7)	break;
	}

	return 0;
}
	
