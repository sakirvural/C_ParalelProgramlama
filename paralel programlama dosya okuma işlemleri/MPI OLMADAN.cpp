#include <stdio.h>
#include <sys/time.h>
#include <ctime>
#include <fstream> //okuma yazma i�lemi i�lemleri i�in
#include <iostream>
//bubble sort algoritmas�na g�re k���kten b�y��e s�ralan�p 12. eleman yani 25 boyutluk dizide ortadaki eleman ifade eder
int filtre (int* deger)
{
   
   int kucuk;
   int temp;
     for (int i=0; i<24; i++)
     {
         kucuk = i;
         for (int j=i+1; j<25; j++)
         {
             if (deger[j] < deger[kucuk])
             kucuk = j;
         }
         temp = deger[i];
         deger[i] = deger[kucuk];
         deger[kucuk] = temp;
     }
    return deger[12];
}

using namespace std;
//Paralel 
int main(int argc , char *argv[]){

if(argc !=2){//2 arguman kontrolu
    cout<<"Sadece 2 arguman giriniz";
    return 0;
}
/*ios::in (Veri okuma modu)

ios::app (Veri ekleme modu)*/
int en,
    boy,
    OkuGelen,
	*deger = new int[25];//filtre i�in

ifstream f_okuma;
ofstream f_yazma;

f_okuma.open(argv[1] , ios::in);        //txt dosyamiza girdik okuma modunda ios::in ile
f_okuma>>boy;                   //girilen txt dosyas�nda boy ve en ald�k
f_okuma>>en;

unsigned char *sabitDizi = new unsigned char[en*boy];      //�devde istenilen �zere 0-255 de�er aral��� icin unsigned char 
unsigned char *yeniDizi= new unsigned char[en*boy];

for(int i=0;i<(en*boy);i++){//okudu�umuz dosyadaki say�lar� dizimize att�k
    f_okuma>>OkuGelen;
    *(sabitDizi+i)=OkuGelen;
    *(yeniDizi+i)=OkuGelen;
}


int D_baslangic=2*en+2, //for d�ng�m�z�n ba�layaca�� konum                 
    D_bitis=en*boy-2*en-3, //for d�ng�m�z�n sonlanaca�� konum
    toplam=0,
    bolum;
    
    //zaman hesaplamas�
double baslangicZamani,bitisZamani,gecenZaman;
struct timeval currentTime;
gettimeofday(&currentTime,NULL);
baslangicZamani=currentTime.tv_sec+(currentTime.tv_usec/1000000.0); 

//fonksiyona at�p yapmak istemedim filtreleme i�lemini ��nk� s�ral� i�lemler daha iyi g�z�ks�n diye 
for(D_baslangic;D_baslangic<=D_bitis;D_baslangic++){//dinamik dizimizi pointer mant��� ile dola�t�m
toplam=0;
    /* 						1. txt dosyam�z i�erisindeki 250 250 boyut �zerinden konu�uyorum ...
		baslangic degerim 502 di bunun �zerinden degerimiz 748 749 750 751 geldi�inde verilen ko�ul �zerine 
                buralarda filtre uygulanmadan ge�er ver her 246 ad�mda tekrarlan�r */
 if(D_baslangic%(en)==en-2 || D_baslangic%(en)==en-1 || D_baslangic%(en)==0 || D_baslangic%(en)==1){

   /*         Buradaki if ko�ulu koyma sebebim �devde verilen "ilk 2 sat�r�ndaki ve ilk 2 s�tunundaki, 
             ayr�ca son 2 sat�r�ndaki ve son 2 s�tunundaki piksellerine filtre uygulanmaz"  bu ko�ulu
                                                sa�lamas� i�in
  */
     continue;  //else kullanmak yerine direk yeni D_baslangic sayisine gecsin

 }
  		//Belirgin olsun diye alt alta yazd�m	
        //Kordinatlara g�re kodlar�n yaz�l��� 

    deger[0]= *(sabitDizi+D_baslangic-2*en-2);    //(x-2,y-2)
    deger[1]= *(sabitDizi+D_baslangic-2*en-1);    //(x-2,y-1)
 	deger[2]= *(sabitDizi+D_baslangic-2*en);       //(x-2,y)
 	deger[3]= *(sabitDizi+D_baslangic-2*en+1);     //(x-2,y+1)
 	deger[4]= *(sabitDizi+D_baslangic-2*en+2);     //(x-2,y+2)
 	deger[5]= *(sabitDizi+D_baslangic-en-2);       //(x-1,y-2)
 	deger[6]= *(sabitDizi+D_baslangic-en-1);       //(x-1,y-1)
 	deger[7]= *(sabitDizi+D_baslangic-en);	        //(x-1,y)
 	deger[8]= *(sabitDizi+D_baslangic-en+1);       //(x-1,y+1)
 	deger[9]= *(sabitDizi+D_baslangic-en+2);       //(x-1,y+2)
 	deger[10]= *(sabitDizi+D_baslangic-2);         //(x,y-2)
 	deger[11]= *(sabitDizi+D_baslangic-1);         //(x,y-1)
 	deger[12]= *(sabitDizi+D_baslangic);           //(x,y)
 	deger[13]= *(sabitDizi+D_baslangic+1);         //(x,y+1)
 	deger[14]= *(sabitDizi+D_baslangic+2);         //(x,y+2)
 	deger[15]= *(sabitDizi+D_baslangic+en-2);      //(x+1,y-2)
 	deger[16]= *(sabitDizi+D_baslangic+en-1);      //(x+1,y-1)
 	deger[17]= *(sabitDizi+D_baslangic+en);        //(x+1,y)
 	deger[18]= *(sabitDizi+D_baslangic+en+1);      //(x+1,y+1)
 	deger[19]= *(sabitDizi+D_baslangic+en+2);      //(x+1,y+2)
 	deger[20]= *(sabitDizi+D_baslangic+2*en-2);    //(x+2,y-2)
 	deger[21]= *(sabitDizi+D_baslangic+2*en-1);    //(x+2,y-1)
 	deger[22]= *(sabitDizi+D_baslangic+2*en);      //(x+2,y)
 	deger[23]= *(sabitDizi+D_baslangic+2*en+1);    //(x+2,y+1)
 	deger[24]= *(sabitDizi+D_baslangic+2*en+2);    //(x+2,y+2)

 
     
*(yeniDizi+D_baslangic) = filtre(deger);//deger dizimi filtreyip  yenidizimizin i�ine att�k 12. eleman�

}
//gecen  zaman hesabi
gettimeofday(&currentTime,NULL);
bitisZamani=currentTime.tv_sec+(currentTime.tv_usec/1000000.0);
gecenZaman=bitisZamani-baslangicZamani;

cout<<argv[1]<<" Icin Harcanan Zaman= "<<gecenZaman<<endl;	//gecen zamani ekrana yazdirdim
//106-112 aral��� istenilen �zerine olu�ulacak yeni dosyan�n sonuna _filtered.txt uzant�s� ekledik
string cikti_ismi;
int i=22;
while(argv[1][i]!='.'){//buradaki i�lemde . olmay�nca kadar cikti_ismi stringte toplas�n
	cikti_ismi+=argv[1][i++];
}
cikti_ismi+="_filtered.txt";//burada sonuna _filtered.txt ekledik.


f_yazma.open(cikti_ismi, ios::app); //yazma islemini yapt�k
f_yazma<<boy<<" ";//en boy yazd�rd�k
f_yazma<<en<<"\n";
for(int i=0;i<(en*boy);i++){//yazmak i�in dizimizi
	if(i!=0 && i%(en)==0){
		f_yazma<<"\n";//her en say�m�z bitince 1 alt sat�ra ge�sin
	}	
	f_yazma<<int(yeniDizi[i])<<"\t"; //yazd�r bir tab bo�luk b�rak
	
}

delete sabitDizi,yeniDizi; //olu�turdu�umuz pointer dizilerimizi yok ettik
f_okuma.close();//dosya okuma kapatt�k
f_yazma.close();// dosya yazmay� kapatt�k




    return 0;
}
