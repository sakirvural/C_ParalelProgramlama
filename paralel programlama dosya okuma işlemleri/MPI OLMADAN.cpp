#include <stdio.h>
#include <sys/time.h>
#include <ctime>
#include <fstream> //okuma yazma iþlemi iþlemleri için
#include <iostream>
//bubble sort algoritmasýna göre küçükten büyüðe sýralanýp 12. eleman yani 25 boyutluk dizide ortadaki eleman ifade eder
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
	*deger = new int[25];//filtre için

ifstream f_okuma;
ofstream f_yazma;

f_okuma.open(argv[1] , ios::in);        //txt dosyamiza girdik okuma modunda ios::in ile
f_okuma>>boy;                   //girilen txt dosyasýnda boy ve en aldýk
f_okuma>>en;

unsigned char *sabitDizi = new unsigned char[en*boy];      //ödevde istenilen üzere 0-255 deðer aralýðý icin unsigned char 
unsigned char *yeniDizi= new unsigned char[en*boy];

for(int i=0;i<(en*boy);i++){//okuduðumuz dosyadaki sayýlarý dizimize attýk
    f_okuma>>OkuGelen;
    *(sabitDizi+i)=OkuGelen;
    *(yeniDizi+i)=OkuGelen;
}


int D_baslangic=2*en+2, //for döngümüzün baþlayacaðý konum                 
    D_bitis=en*boy-2*en-3, //for döngümüzün sonlanacaðý konum
    toplam=0,
    bolum;
    
    //zaman hesaplamasý
double baslangicZamani,bitisZamani,gecenZaman;
struct timeval currentTime;
gettimeofday(&currentTime,NULL);
baslangicZamani=currentTime.tv_sec+(currentTime.tv_usec/1000000.0); 

//fonksiyona atýp yapmak istemedim filtreleme iþlemini çünkü sýralý iþlemler daha iyi gözüksün diye 
for(D_baslangic;D_baslangic<=D_bitis;D_baslangic++){//dinamik dizimizi pointer mantýðý ile dolaþtým
toplam=0;
    /* 						1. txt dosyamýz içerisindeki 250 250 boyut üzerinden konuþuyorum ...
		baslangic degerim 502 di bunun üzerinden degerimiz 748 749 750 751 geldiðinde verilen koþul üzerine 
                buralarda filtre uygulanmadan geçer ver her 246 adýmda tekrarlanýr */
 if(D_baslangic%(en)==en-2 || D_baslangic%(en)==en-1 || D_baslangic%(en)==0 || D_baslangic%(en)==1){

   /*         Buradaki if koþulu koyma sebebim ödevde verilen "ilk 2 satýrýndaki ve ilk 2 sütunundaki, 
             ayrýca son 2 satýrýndaki ve son 2 sütunundaki piksellerine filtre uygulanmaz"  bu koþulu
                                                saðlamasý için
  */
     continue;  //else kullanmak yerine direk yeni D_baslangic sayisine gecsin

 }
  		//Belirgin olsun diye alt alta yazdým	
        //Kordinatlara göre kodlarýn yazýlýþý 

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

 
     
*(yeniDizi+D_baslangic) = filtre(deger);//deger dizimi filtreyip  yenidizimizin içine attýk 12. elemaný

}
//gecen  zaman hesabi
gettimeofday(&currentTime,NULL);
bitisZamani=currentTime.tv_sec+(currentTime.tv_usec/1000000.0);
gecenZaman=bitisZamani-baslangicZamani;

cout<<argv[1]<<" Icin Harcanan Zaman= "<<gecenZaman<<endl;	//gecen zamani ekrana yazdirdim
//106-112 aralýðý istenilen üzerine oluþulacak yeni dosyanýn sonuna _filtered.txt uzantýsý ekledik
string cikti_ismi;
int i=22;
while(argv[1][i]!='.'){//buradaki iþlemde . olmayýnca kadar cikti_ismi stringte toplasýn
	cikti_ismi+=argv[1][i++];
}
cikti_ismi+="_filtered.txt";//burada sonuna _filtered.txt ekledik.


f_yazma.open(cikti_ismi, ios::app); //yazma islemini yaptýk
f_yazma<<boy<<" ";//en boy yazdýrdýk
f_yazma<<en<<"\n";
for(int i=0;i<(en*boy);i++){//yazmak için dizimizi
	if(i!=0 && i%(en)==0){
		f_yazma<<"\n";//her en sayýmýz bitince 1 alt satýra geçsin
	}	
	f_yazma<<int(yeniDizi[i])<<"\t"; //yazdýr bir tab boþluk býrak
	
}

delete sabitDizi,yeniDizi; //oluþturduðumuz pointer dizilerimizi yok ettik
f_okuma.close();//dosya okuma kapattýk
f_yazma.close();// dosya yazmayý kapattýk




    return 0;
}
