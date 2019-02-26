#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<locale.h>

#define size 25
using namespace std;

struct film_bilgileri{
	char film_adi[size];
	char yonetmen[size];
	char basrol[size];
	char senarist[size];
	int yil;
}filmler;
//Fonksiyon imzalar�.
int Menu();
void filmEkle();
void film_sil();
void FilmListele();
void Film_ara();
void film_guncelle();
void Film_ara();
int main()
{
	//Alt sat�rda ki kodu printler i�ine T�rk�e dil deste�i eklemek i�in yazd�m.
	setlocale(LC_ALL, "Turkish");
	//Alt sat�rda ki kod cmd ekran�n�n renkli olmas�n� sa�lar.
	system("color fc");
	printf("+++++++++++++++++++++++++++++++F�LM AR��VLEME S�STEM�++++++++++++++++++++++++++++++\n\n");
	Menu();
    getch();
    return 0;
}
//Men� sistemini fonksiyon olarak yazd�m.G�r�n�� a��s�ndan daha ho�.
int Menu()
{
	//Switch-case sistemi ve if yard�m�yla men� sistemini yazd�m.
     char Tercih = 'r';
     printf("\n");
	printf(" Film Ekle-->1\n Filmleri Listele-->2\n Film G�ncelle-->3\n Film Sil-->4\n Film Ara-->5\n");	
     Tercih = getche();
     while(Tercih != 'E' || Tercih != 'e') {
          switch(Tercih)
          {
                        case '1': {filmEkle();break;}
                        case '2': {FilmListele();break;}
                        case '3': {film_guncelle();break;}
                        case '4': {film_sil();break;}
                        case '5': {Film_ara();break;}
						
						
						
          }
          printf("\nBa�ka i�lem yapmak istiyor musunuz(E/H)?\n");
          Tercih = getche();
          if(Tercih == 'H' || Tercih == 'h') {
                    break;
          }
          if(Tercih == 'E' || Tercih== 'e'){
          	//��lemlerin tekrar yap�labilmesi i�in kendini yenileyip men�ye giden fonksiyonu yazd�m.
          	return Menu();
		  }
     }
}
void filmEkle()
{
	//Dosya tipinde pointer olu�turarak veritaban�n� olu�turdum.
	FILE *fp;
	fp = fopen("filmveritaban�.dat","a");
	fflush(stdin);//bo�luklar� karakter olarak almas�n� engellemek i�in fflush(stdin) fonksiyonunu yazd�m ve gets ile verileri ald�m.
	printf("\n");
	printf("L�tfen Filmin Ad�n� giriniz:\n");
	gets(filmler.film_adi);
	fflush(stdin);
	fflush(stdin);
	printf("L�tfen Filmin Ba�rol�n� giriniz:\n");
	gets(filmler.basrol);
	fflush(stdin);
	fflush(stdin);
	printf("L�tfen Filmin Senaristini giriniz:\n");
	gets(filmler.senarist);
	fflush(stdin);
	fflush(stdin);
	printf("L�tfen Filmin Y�netmenini giriniz:\n");
	gets(filmler.yonetmen);
	fflush(stdin);
	printf("L�tfen Filmin Yay�nlanma Y�l�n� giriniz:\n");
	scanf("%d",&filmler.yil);
	//fwrite komutu ald���m�z verileri dosyaya yazmak i�in kullan�l�r.
	fwrite(&filmler,sizeof(film_bilgileri),1,fp);
	//fclose fonksiyonu dosyay� kapatmaya yarar.
	fseek(fp,0,SEEK_SET);
	fclose(fp);
	printf("Film ba�ar�yla eklendi^__^\n");
	return;
}
void film_sil(){
     char filmad_temp[30];
     FILE *FilmDB;
     FILE *TempFilmDB;
     printf("\nSilmek istedi�iniz filmin ad�n� giriniz: \n");
     fflush(stdin);
     gets(filmad_temp);
     // Dosyadaki b�t�n kay�tlar taran�r ve silinmesini istedi�imiz kay�t atlanarak ge�ici bir dosyaya, silinecek kay�t d���ndakilerin hepsi yaz�l�r. 
     FilmDB = fopen("filmveritaban�.dat","r");
     TempFilmDB = fopen("TempFile.dat","a");
     //Burada temp dosyas�na yazd�rma i�lemi yap�l�yor.
	 while(fread(&filmler, sizeof(film_bilgileri),1,FilmDB))
     {
                if(strcmp(filmler.film_adi,filmad_temp)==0)
                {
                	char x;
				printf("Film silinecek emin misiniz?(Silmek i�in y/vazge�mek i�in n)\n");
				fflush(stdin);
				scanf("%c" ,&x);
				if(x=='y'|| x=='Y'){
                    printf("\nFilm ba�ar�yla silindi^__^\n");
					}
					else{
						printf("Silme iptal edildi-__-\n");
						fwrite(&filmler, sizeof(film_bilgileri),1,TempFilmDB);
					}
				}
					else{
						fwrite(&filmler, sizeof(film_bilgileri),1,TempFilmDB);
					}
					if(strcmp(filmler.film_adi,filmad_temp)==0){
					}
                	
                
            
     }
     //�mle� dosya ba��na g�nderiliyor.
     fseek(TempFilmDB,0,SEEK_SET);
     fclose(FilmDB);
     fclose(TempFilmDB);
     // Dosya silinir.
     remove("filmveritaban�.dat");
     // ge�ici dosyan�n ismi as�l dosya ismi de�i�tirilir.
     rename("TempFile.dat","filmveritaban�.dat");
}
void FilmListele(){
	struct film_bilgileri gecici;
	FILE *fp;
	fp = fopen("filmveritaban�.dat","r");
	//struct dizisi olu�turarak s�ralama i�ini ger�ekle�tirdim.
	struct film_bilgileri filmler[size] = {"","","","",0};
	int i = 0;
	if(fp == NULL)
	{	printf("\nDosya a��lamad�-__-\n");
	return;
	}
	else{
		while(fread(&filmler[i],sizeof(film_bilgileri),1,fp))
		{ i++;
		}
		//Bubble sort algoritmas� ile s�ralama ger�ekle�tirildi.
	for(i = 0; i < size-1; i++){
		for(int j = 0; j < size-i-1; j++){
			if(filmler[j+1].yil > filmler[j].yil){
				gecici = filmler[j];
				filmler[j] = filmler[j+1];
				filmler[j+1] = gecici;

				}
			}
		}
	printf("\nFilm Ad�\tBa�rol\t\tY�netmen\tSenarist\tYay�nlanma Y�l�\n");
	for (i = 0; i < size; i++){
		if(filmler[i].yil == 0 ){
			}
		else{
			printf("\n");
			printf("%s\t\t%s\t\t%s\t\t%s\t\t%4d\n",filmler[i].film_adi,filmler[i].basrol,filmler[i].yonetmen,filmler[i].senarist,filmler[i].yil);
			}
		}
	}
rewind(fp); //Dosyay� ba�a yollayarak fonlsiyonun stabil �al��mas�n� sa�lad�m. 
fclose(fp);
printf("\n");
return;
}
void film_guncelle(){
	//struct dizileri olu�turup verileri buraya kaydettik.
	struct film_bilgileri guncelleme = {"","","","",0};
	struct film_bilgileri sil = {"","","","",0};
	FILE *filep;//File cinsinde bir pointer olu�turuldu.
    char isim[size];	 
    
    printf("G�ncellemek istedi�iniz filmin ad�n� giriniz: ");
    scanf("%s",&isim);
    //burada film verilerini �ekiyoruz.
        if((filep=fopen("filmveritaban�.dat","r+"))==NULL)
        {
            printf("Veritaban� bulunamad�-__-");
        }
        else
        {	rewind(filep);
         while (fread(&guncelleme,sizeof(filmler),1,filep))
            {
		
        //Burada g�ncelleme i�lemleri yap�l�yor.
            if(strcmp(guncelleme.film_adi,isim)==0)
            {
                
            	           
                printf("G�ncellenecek film "
                        "%s %s %s %s %d",
		        guncelleme.film_adi,guncelleme.yonetmen,guncelleme.basrol,guncelleme.senarist,guncelleme.yil);
				            
                fflush(stdin);
                printf("\nyeni film ad�:");
                gets(guncelleme.film_adi);
				printf("\n%s filminin y�netmenini giriniz:",guncelleme.film_adi);
                gets(guncelleme.yonetmen);
				printf("\n%s filminin ba�rol�n� giriniz:",guncelleme.film_adi);
                gets(guncelleme.basrol);
				printf("\n%s filminin senaristini giriniz:",guncelleme.film_adi);
                gets(guncelleme.senarist);
				printf("\n%s filminin y�l�n� giriniz :",guncelleme.film_adi);
                scanf("%d",&guncelleme.yil);
                
                //Silme ve g�ncelleme i�lemleri yap�l�yor.
                int imlec=ftell(filep);

                fseek(filep,-imlec,SEEK_CUR );
                  fwrite(&sil,sizeof(filmler),1,filep);
				                  
                 fseek(filep,-imlec,SEEK_CUR);
                fwrite(&guncelleme,sizeof(filmler),1,filep);
                 imlec=ftell(filep);

                break;
            }
        }}
        fclose(filep);
}
 void Film_ara(){
 	//i�imize yarayacak de�i�kinler tan�mland�.
	struct film_bilgileri arama = {"","","","",0};
	FILE *fileptr;
	char filmadi[size];
	char yonetmenadi[size];
	char basroladi[size];
	char senaristadi[size];
	int yil;
	int bulundu=0;
	char secim;
			
	if((fileptr=fopen("filmveritaban�.dat","r"))==NULL)
        {
            printf("Dosya bulunamad�-__-");
        }
        
    else
        {
        	
    printf("\nFilm ad�na g�re arama:1\n");
    printf("Filmin y�netmenine g�re arama:2\n");
    printf("Filmin ba�rol oyuncusuna g�re arama:3\n");
    printf("Filmin senaristine g�re arama:4\n");
    printf("Filmin yay�nlanma y�l�na g�re arama:5\n");
    printf("��k�� yapmak i�in:0\n");
    
    printf("\nMenudekilerden Birini Se�iniz.\n");
    scanf("%d",&secim);
	    	
    switch(secim){    	
	case 1:		
		fflush(stdin);
		printf("Arad���n�z filmin ad�n� giriniz:");
        gets(filmadi);            
	while(!feof(fileptr))
        {            
            fread(&arama,sizeof(filmler),1,fileptr);
            if((strcmp(arama.film_adi,filmadi))==0)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Arad���n�z �simdeki Filmler\n\n"
                    "Filmin ad� : %s\nFilmin y�netmeni : %s\nFilmin ba�rol� : %s\nFilmin senaristi : %s\nYay�nlanma y�l� : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHi�bir film bulunamad�-__-");	
		}        
	break;	
	case 2:		
		fflush(stdin);
		printf("Arad���n�z y�netmeninin ad�n� giriniz:");
        gets(yonetmenadi);            
	while(!feof(fileptr))
        {            
            fread(&arama,sizeof(filmler),1,fileptr);
            if((strcmp(arama.yonetmen,yonetmenadi))==0)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Arad���n�z Y�netmenin Filmleri\n\n"
                    "Filmin ad� : %s\nFilmin y�netmeni : %s\nFilmin ba�rol� : %s\nFilmin senaristi : %s\nYay�nlanma y�l� : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHi�bir film bulunamad�-__-");	
		}	
	break;			
	case 3:		
		fflush(stdin);
		printf("Arad���n�z basrolun ad�n� girin:");
        gets(basroladi);           
	while(!feof(fileptr))
        {            
            fread(&arama,sizeof(filmler),1,fileptr);
            if((strcmp(arama.basrol,basroladi))==0)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Arad���n�z Ba�rol�n Filmleri\n\n"
                    "Filmin ad� : %s\nFilmin y�netmeni : %s\nFilmin ba�rol� : %s\nFilmin senaristi : %s\nYay�nlanma y�l� : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHi�bir film bulunamad�-__-");	
		}		
	break;	
	case 4:	
		fflush(stdin);
		printf("Arad���n�z senaristin ad�n� girin:");
        gets(senaristadi);            
	while(!feof(fileptr))
        {            
            fread(&arama,sizeof(filmler),1,fileptr);
            if((strcmp(arama.senarist,senaristadi))==0)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Arad���n�z Senaristin Filmleri\n\n"
                    "Filmin ad� : %s\nFilmin y�netmeni : %s\nFilmin ba�rol� : %s\nFilmin senaristi : %s\nYay�nlanma y�l� : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHi�bir film bulunamad�-__-");	
		}		
	break;	
	case 5:
	
		fflush(stdin);
		printf("Arad���n�z y�l� girin:");
        scanf("%d",&yil);            
	while(fread(&arama,sizeof(filmler),1,fileptr))
        {            
            if(yil != 0){
            	if(arama.yil == yil)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Arad���n�z Y�ldaki Filmler\n\n"
                    "Filmin ad� : %s\nFilmin y�netmeni : %s\nFilmin ba�rol� : %s\nFilmin senaristi : %s\nYay�nlanma y�l� : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
			}            
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHi�bir film bulunamad�-__-");	
		}		
	break;	
	case 0:
		printf("Ana men�ye d�n�yorsunuz.");
	break;	
	default :	
	printf("Gecersiz bir deger girdiniz-__-\n\n");
	break;			
    }
        }
    fclose(fileptr);		        
}
