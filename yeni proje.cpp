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

int Menu();
void filmEkle();
void film_sil();
void FilmListele();
void Film_ara();
int main()
{
	setlocale(LC_ALL, "Turkish");
	system("color fc");
	printf("+++++++++++++++++++++++++++++++F�LM AR��VLEME S�STEM�++++++++++++++++++++++++++++++\n\n");
	Menu();
    getch();
    return 0;
}
int Menu()
{
     char Tercih = 'r';
     printf("\n");
	printf(" Film Ekle-->1\n Filmleri Listele-->2\n Film G�ncelle-->3\n Film Sil-->4\n Film Ara-->5\n Programdan ��k-->E\n");	
     Tercih = getche();
     while(Tercih != 'E' || Tercih != 'e') {
          switch(Tercih)
          {
                        case '1': {filmEkle();break;}
                        case '2': {FilmListele();break;}
                        case '3': {;break;}
                        case '4': {film_sil();break;}
                        case '5': {Film_ara();break;}
						
						
						
          }
          printf("\nBa�ka i�lem yapmak istiyor musunuz(E/H)?\n");
          Tercih = getche();
          if(Tercih == 'H' || Tercih == 'h') {
                    break;
          }
          if(Tercih == 'E' || Tercih== 'e'){
          	return Menu();
		  }
     }
}
void filmEkle()
{
	FILE *fp;
	fp = fopen("filmveritaban�.dat","a");
	printf("\nfilm ad�n�,ba�rol�,senaristi,y�netmeni ve yay�nlanma y�l�n� giriniz:\n");
	fflush(stdin);
	gets(filmler.film_adi);
	gets(filmler.basrol);
	gets(filmler.senarist);
	gets(filmler.yonetmen);
	fflush(stdin);
	scanf("%d",&filmler.yil);
	
	fwrite(&filmler,sizeof(film_bilgileri),1,fp);
	fclose(fp);
	return;
}
void film_sil(){
     char filmad_temp[30];
     FILE *FilmDB;
     FILE *TempFilmDB;
     printf("\nSilmek istedi�iniz filmin ad�n� giriniz: \n");
     scanf("%s", &filmad_temp);
     // Dosyadaki b�t�n kay�tlar taran�r ve silinmesini istedi�imiz kay�t atlanarak ge�ici bir dosyaya, silinecek kay�t d���ndakilerin hepsi yaz�l�r. 
     FilmDB = fopen("filmveritaban�.dat","r");
     TempFilmDB = fopen("TempFile.dat","a");
    
     while(!feof(FilmDB))
     {
            fread(&filmler, sizeof(film_bilgileri),1,FilmDB);
            if(&filmler != NULL)
            {
                if(strcmp(filmler.film_adi,filmad_temp))
                {
                    fwrite(&filmler, sizeof(film_bilgileri),1,TempFilmDB);    
                }
                else if(strcmp(filmler.film_adi,filmad_temp))
                {
                    
                }
            }
     }printf("\nFilm ba�ar�yla silindi!\n");
     fclose(FilmDB);
     fclose(TempFilmDB);
     // Dosya silinir.
     remove("filmveritaban�.dat");
     // ge�ici dosyan�n ismi as�l dosya ismi de�i�tirilir.
     rename("TempFile.dat","filmveritaban�.dat");
}
void FilmListele(){
	//	struct filmBilgi filmsira[25],gecici;
	FILE *fp;
	fp = fopen("filmveritaban�.dat","r+");
	int k = 0;
	while(fread(&filmler,sizeof(film_bilgileri),1,fp)){
	 printf("\n%s\t%s\t%s\t%s\t%d\n",filmler.film_adi,filmler.basrol,filmler.senarist,filmler.yonetmen,filmler.yil);

		}
	
	fclose(fp);
	return;
}
 
 void Film_ara()
{
	printf("\nFilm ad�na g�re arama:1\n");
	printf("Filmin yay�nlanma y�l�na g�re arama:2\n");
	printf("Filmin y�netmenine g�re arama:3\n");
	printf("Filmin senaristine g�re arama:4\n");
    printf("Filmin ba�rol oyuncusuna g�re arama:5\n");
    int a;
    scanf("%d" , &a);
    if(a==1)
    {
    	film_bilgileri *KullaniciObj;
		    FILE *FilmDB;
		    char isim[30];
		     
		    printf("Aramak istediginiz filmin ismini giriniz: \n");
		    scanf("%s", &isim);
		     
		    if ((FilmDB = fopen("filmveritaban�.dat","r"))==NULL){
		    	printf("B�yle Bir Dosya Bulunamad�!!");
			}
		     else{
			 
		    while(!feof(FilmDB))
		     {
		            KullaniciObj = (film_bilgileri*) malloc(sizeof(film_bilgileri));
		            fread(KullaniciObj, sizeof(film_bilgileri) - 2*sizeof(KullaniciObj), 1, FilmDB);
		            
		            printf(KullaniciObj->film_adi);
		            if(KullaniciObj != NULL)
		            {
		                if(!strcmp(KullaniciObj->film_adi, isim))
		                {
			                 printf("\nFilmin Ad�:%s\n", KullaniciObj->film_adi);
			                 printf("Filmin Y�netmeni:%s\n", KullaniciObj->yonetmen);
			                 printf("Filmin Senaristi:%s\n", KullaniciObj->senarist);
			                 printf("Filmin Ba�rol�:%s\n", KullaniciObj->basrol);
			                 printf("Filmin Yay�nlanma Y�l�:%d\n", KullaniciObj->yil);
			                 printf("---------------------------\n");
		                
						}
		            }
		     }
		
fclose(FilmDB);	
}
}		     
}
