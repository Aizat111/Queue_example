#include<stdio.h>
#include<stdlib.h>
#define boyut  30

struct Liste1{
	int numara;
	char *isim;
};

typedef struct Liste{
	int son;
	struct Liste1 bilgi[boyut];
}kListe;

kListe Kuyruk;
kListe TamponKuyruk;//sirali ekleme yapmak icin tutucu kuyruk

int Kuyruk_Dolumu(kListe a)
{
	if(a.son>=boyut-1)return 1;//kuyruk doluysa 1 gonderiyor
	else return -1;
}

int Kuyruk_Bosmu(kListe a)
{
	if(a.son==-1)return 1;//kuyruk bossa 1 gonderiyor
	else return -1;
}

void Ekle(int num,char ad[])//asil kuyruga veri eklenecek fonksiyon
{
	if(Kuyruk_Dolumu(Kuyruk)==1)
	printf("Kuyruk dolu\n");
	{
		Kuyruk.son++;
		Kuyruk.bilgi[Kuyruk.son].numara=num;
		Kuyruk.bilgi[Kuyruk.son].isim=(char*)malloc(sizeof(char));
		for(int i=0;ad[i]!=NULL;i++) *(Kuyruk.bilgi[Kuyruk.son].isim+i)=ad[i];
	}
}

void TutucuKuyrugaEkle(Liste1 bil)//tutucu kuyruga veri eklenecek fonksiyon
{
	if(Kuyruk_Dolumu(TamponKuyruk)==1)
	printf("kuyruk dolu\n");
	else
	{
		TamponKuyruk.son++;
		TamponKuyruk.bilgi[TamponKuyruk.son].numara=bil.numara;
		TamponKuyruk.bilgi[TamponKuyruk.son].isim=(char*)malloc(sizeof(char));
		for(int i=0;bil.isim[i]!=NULL;i++) *(TamponKuyruk.bilgi[TamponKuyruk.son].isim+i)=bil.isim[i];
	}
}

Liste1 cikar1()//asil kuyrugu bosaltacak fonksiyon
{
		Liste1 temp;
		temp=Kuyruk.bilgi[0];
		for(int i=1;i<=Kuyruk.son;i++)
		{
			Kuyruk.bilgi[i-1].numara=Kuyruk.bilgi[i].numara;
			Kuyruk.bilgi[i-1].isim=Kuyruk.bilgi[i].isim;
		}
		Kuyruk.son--;
		return temp;
}

Liste1 cikar2()//tutucu kuyrugu bosaltacak fonksiyon
{
		Liste1 temp;
		temp=TamponKuyruk.bilgi[0];
		for(int i=1;i<=TamponKuyruk.son;i++)
		{
			TamponKuyruk.bilgi[i-1].numara=TamponKuyruk.bilgi[i].numara;
			TamponKuyruk.bilgi[i-1].isim=TamponKuyruk.bilgi[i].isim;
		}
		TamponKuyruk.son--;
		return temp;
}

void Listele()//kuyrugu listeleyici fonksiyon
{
	for(int k=0;k<=Kuyruk.son;k++)
	{
		printf("%d\t%s\n",Kuyruk.bilgi[k].numara,Kuyruk.bilgi[k].isim);
	}
}

int Ara(char ad[])
{
	int uzunluk=0,sira=0;
	for(int i=0;ad[i]!=NULL;i++)uzunluk++;
	for(int i=0;i<=Kuyruk.son;i++)
	{
		int j=0;
		while(j<uzunluk)//kelimenin her harfinin benzerligini kontrol ediyor
		{
			if(ad[j]==*(Kuyruk.bilgi[i].isim+j)) j++;
			else break;
		}
		if(j==uzunluk) 
		return sira;//butun harfleri benziyorsa fonksiyon deger gonderiyor
		else 	sira++;
	}
	if(sira>Kuyruk.son) return sira;//aranilan adin kuyrukta bukunmamamsi durumunda
}

int main()
{
	Kuyruk.son=-1;
	TamponKuyruk.son=-1;
	FILE *dosya;
	int numara;
	char isim[15];
	dosya=fopen("adsiz.txt","r");
	while(!feof(dosya))//dosyanin sonuna kadar  verileri okutuyoruz
	{
		fscanf(dosya,"%d",&numara);
		fscanf(dosya,"%s",isim);
		Ekle(numara,isim);
	}
	fclose(dosya);
	int secim;
	printf("***Dosyadaki butun veriler kuyruga aktarildi***\n");
	do
	{
		printf("\n***Buyurun menunuz***\n1.Kuyrugu listele\n2.Kuyruga yeni veri ekle\n3.Kuyruktan isime gore verinin yerini arat\n4.Bitir\n");
		printf("\nSizin secim--->");
		scanf("%d",&secim);
		switch(secim)
		{
			case 1:	Listele();
					break;
			case 2:	{
					Liste1 b;
					while(Kuyruk_Bosmu(Kuyruk)!=1)
					{
							b=cikar1();
							TutucuKuyrugaEkle(b);//asil kuyrugu tutucu kuyruga aktariyoruz
					}
						printf("\n numarasini giriniz:");
						scanf("%d",&numara);
						printf("\nadini giriniz:");
						scanf("%s",isim);
						int sayac=0;//girilen verinin sadece bir kere eklenmesini ya da sona eklenmesini kontrol etmek icin
						while(Kuyruk_Bosmu(TamponKuyruk)!=1)//tutucu kuyruktaki butun verileri geri asil kuyruga aktariyoruz
						{
							b=cikar2();
							if(numara<b.numara&&sayac<1)
							{
								Ekle(numara,isim);
								Ekle(b.numara,b.isim);
								sayac++;
							}
							else
							{
								Ekle(b.numara,b.isim);
							}		
						}
						if(sayac==0)Ekle(numara,isim);
						break;
					}
					
						
			case 3:		
					{
						printf("\nAratmak istediginiz ismi giriniz:");
						scanf("%s",isim);
						int sira=Ara(isim);
						if(sira==0)printf("%s ilk sirada\n",isim);
						else if(sira>Kuyruk.son) printf("Aradigini isim kuyrukta bulunmamaktadir....\n");
						else printf("%s nin onunde %d kisi var\n",isim,sira);
						break;
					}
			default:	if(secim!=4)printf("Menu disi bir secim yaptiniz:/"); break;
		}
	}while(secim!=4);
	return 0;
}
