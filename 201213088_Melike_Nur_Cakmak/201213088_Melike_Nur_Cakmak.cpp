#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include <string.h>

typedef struct urun{
	char ad[20];
	double fiyat;
	int   gram;
	struct urun *sonra;
} yemek;

typedef struct urun  yemek;
yemek *ilk = NULL;

yemek *Ekle(yemek *ilk,double fiyat,int gram,char ad[20])
{
	
	yemek*gez;
	yemek *yeter=ilk;
  	if (ilk==NULL)
	{
    	ilk=(yemek *)malloc(sizeof(yemek));
    	for(int i=0;i<20;i++){
    		ilk->ad[i]=ad[i];
		}
        ilk->sonra=ilk;
		ilk->fiyat=fiyat;
    	ilk->gram=gram;
    	return ilk;
    }
    
  	if (ilk->fiyat >fiyat )
	{
    	yemek * gec=(yemek*)malloc(sizeof(yemek));
    	for(int i=0;i<20;i++){
    		gec->ad[i]=ad[i];
		}
		gec->fiyat=fiyat;
     	gec->gram=gram;
    	gec->sonra=ilk;
    	while(yeter->sonra!=ilk){
    		yeter=yeter->sonra;
		}
    	yeter->sonra=gec;
    	return gec;
   }
   
  	yemek * gec1=ilk;
  	while(gec1->sonra!=ilk && gec1->sonra->fiyat < fiyat ){
    	gec1=gec1->sonra;
  }	
  	yemek * gec=(yemek*)malloc(sizeof(yemek));
  	gec->sonra=gec1->sonra; ////ilk deeeee
  	gec1->sonra=gec;
    for(int i=0;i<20;i++){
    	gec->ad[i]=ad[i];
	}  	
  	gec->fiyat=fiyat;
  	gec->gram=gram;
  	return ilk;
}


void listele(yemek*ilk) {
	yemek *gec=ilk;
	do{
		printf("%s %d gr %.2lf TL\n",gec->ad,gec->gram,gec->fiyat);	
		gec=gec->sonra;
	}while(gec!=ilk);	
}

yemek *  dosyaOku(){
	yemek temp2;
	FILE *fp;
    if ( (fp = fopen("dosya.txt","r"))==NULL) {
        printf("Dosya açýlamadý");
        exit(1);
    }
    while(!feof(fp)){
    fscanf(fp, "%s %d %lf",temp2.ad,&temp2.gram,&temp2.fiyat);	
	ilk = Ekle(ilk,temp2.fiyat,temp2.gram,temp2.ad); 
	}	
	
	return ilk;
}
void menu(yemek * ilk){

	int s=2;
	yemek *temp= ilk;
	yemek *yaz;
	printf("Yemek secimi icin:1\nBir sonraki yemek icin:2\nAna menuye donmek icin:3\n");
	
	while(s==2){
	 printf("%s %d %lf (1/2/3)\n",temp->ad,temp->gram,temp->fiyat);
	 scanf("%d",&s);
	 yaz=temp;
	 temp=temp->sonra;	
	}
	if(s==1){
		printf("%s sectiniz. Siparisiniz en kisa zamanda teslim edilecekir.Afiyet olsun\n",yaz->ad);
		getch();
	}
	if(s==3){
		return;	
	}	
}
	
void Sil( yemek **ilk, char sil[20])
{
    int i, sayac;
    yemek *once, *gec;

    if (*ilk == NULL)
    {
        printf("Liste bos silme gecersiz .\n");
        return;
    }

    sayac = 0;
    gec   = *ilk;
	once  = gec;

    while (once->sonra != *ilk) 
    {
        once = once->sonra;
        sayac++;
    }

    i = 0;
    while (i <= sayac)
    {
        if (strcmp(gec->ad,sil)==0)
        {
            if (gec->sonra != gec)
            {
                once->sonra = gec->sonra; 	
			}

            else
			{
                once->sonra = NULL;           	
			}

            if (gec == *ilk)
			{
               *ilk = once->sonra;           	
			}

            free(gec);

            if (once != NULL) 
            {
                gec = once->sonra;            		
			}
            else
			{
                once = NULL;            	
			}

        }
        
        else 
        {	
            once = gec;
            gec  = gec->sonra;
        }
        i++;
    }
}
int main(){
	char ad[20],sil[20];
	double fiyat;
	int gram;
	char secim;
	ilk = dosyaOku();
	while(1){
		system("CLS"); 
		puts("Ekleme yapmak icin 'e'\nSilme islemi icin 's'\nListeleme icin'l'\nMenu icin 'm'\nCikis icin'c'");
		secim=getchar();
		switch(secim){
			case 'e':
			   printf("Yemek ismi giriniz\n");
               scanf("%s",ad);
			   puts("fiyat giriniz");
			   scanf("%lf",&fiyat);
			   puts("gramaj giriniz");
			   scanf("%d",&gram);
			   ilk=Ekle(ilk,fiyat,gram,ad);
		       break;
		     case 's':
		     	printf("Silinecek yemek ismini giriniz:");
		     	scanf("%s",sil);
		     	Sil(&ilk,sil);
				break; 
			case 'm':
				menu(ilk);
				break;
			case 'l':
				listele(ilk);
				getch();
				break;
			case 'c':
				exit(0);		
		}	
	}		
return 0;			
}		


