#include <stdio.h>
#include <ctime>
#include <fstream> //okuma yazma i�lemi i�lemleri i�in
#include <iostream>
#include <mpi.h>

//bubble sort algoritmas�na g�re k���kten b�y��e s�ralan�p 12. eleman yani 25 boyutluk dizide ortadaki eleman ifade eder
int *deger = new int[25];//filtre i�in
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

int main(int argc, char *argv[])
{
	double baslangicZamani,bitisZamani,gecenZaman;
	//Adim 1 -> Degiskenleri Deklare Et
		int myRank,//pclerimiz
	    	size,//ka� pc var
			blokBoyutu,//her rank yap�ca�� i�lem boyutu
			D_baslangic,//ba�l�yca�� de�er
			en,//okunacak en
    		boy,//okunacak boy
   			OkuGelen,//gelen sayilar
   		    *sabitDizi,     //dizi pointerlar�m�z
			*yeniDizi,
			toplam=0,
			bolum=0;
			
ifstream f_okuma;//okuma yazma i�in
ofstream f_yazma;			
				


	
	MPI_Status status;

	//Adim 2 -> MPI Ortamini Ilklendir
	MPI_Init(&argc,&argv);

	//Adim 3 -> Rankini ve dunyadaki bilgisayar sayisini ogren
	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(myRank==0)
	{
f_okuma.open(argv[1]);        //txt dosyamiza girdik okuma modunda ios::in ile
f_okuma>>boy;                   //girilen txt dosyas�nda boy ve en ald�k
f_okuma>>en;
	
 int *sabitDizi = new int[en*boy];      //�devde istenilen �zere 0-255 de�er aral��� icin unsigned char 
 int *yeniDizi= new int[en*boy];
for(int i=0;i<(en*boy);i++){//okudu�umuz dosyadaki say�lar� dizimize att�k
    f_okuma>>OkuGelen;
    *(sabitDizi+i)=OkuGelen;
    
} 
	
	baslangicZamani = MPI_Wtime();//baslangic zamani
	
	blokBoyutu=boy/size*en;//blok boyutu
	
	for(int i=1;i<size;i++)//block boyutumuzu ranklere g�nderdik
		MPI_Send(&blokBoyutu,1,MPI_INT,i,34,MPI_COMM_WORLD);
	
		for(int i=1;i<size;i++)//en g�nderdik
		MPI_Send(&en,1,MPI_INT,i,34,MPI_COMM_WORLD);	
		
		
	for(int i=1;i<size;i++)//bloklad���m�z dizideki elemanlar�m�z her myrank i�in
		MPI_Send(&sabitDizi[i*blokBoyutu],blokBoyutu,MPI_INT,i,53,MPI_COMM_WORLD);
	
	
		D_baslangic=2*en+2;//baslangic degeri
		
		//dizimizi blockboyutu kadar yeni dizi att�k myrank0 i�in
		for(int i=0;i<blokBoyutu;i++)
			*(yeniDizi+i)=*(sabitDizi+i);
		
		
		
//filtreleme i�lemi
	for(D_baslangic;D_baslangic<=blokBoyutu;D_baslangic++){
		toplam=0;
		if(D_baslangic%(en)==en-2 || D_baslangic%(en)==en-1 || D_baslangic%(en)==0 || D_baslangic%(en)==1){


   /*         Buradaki if ko�ulu koyma sebebim �devde verilen "ilk 2 sat�r�ndaki ve ilk 2 s�tunundaki, 
             ayr�ca son 2 sat�r�ndaki ve son 2 s�tunundaki piksellerine filtre uygulanmaz"  bu ko�ulu
                                                sa�lamas� i�in
  */
continue;

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
		
		//myranklar�m�z�n yapt��� filtreleme i�lemleri ald�k ve yeni dizimize kaydettik
		for(int i=1;i<size;i++)
			MPI_Recv(&yeniDizi[i*blokBoyutu],blokBoyutu,MPI_INT,i,34,MPI_COMM_WORLD,&status);	
	
bitisZamani = MPI_Wtime();	//bitis zamani
	
gecenZaman=bitisZamani-baslangicZamani;//zaman� ekrana yazd�rd�k
cout<<"Gecen Zaman :"<<gecenZaman<<endl;

string cikti_ismi;
int i=22;
while(argv[1][i]!='.'){//buradaki i�lemde . olmay�nca kadar cikti_ismi stringte toplas�n
	cikti_ismi+=argv[1][i++];
}
cikti_ismi+="_filtered.txt";//burada sonuna _filtered.txt ekledik.


f_yazma.open(cikti_ismi); //yazma islemini yapt�k
f_yazma<<boy<<" ";//en boy yazd�rd�k
f_yazma<<en<<"\n";
for(int i=0;i<(en*boy);i++){//yazmak i�in dizimizi
	if(i!=0 && i%(en)==0){
		f_yazma<<"\n";//her en say�m�z bitince 1 alt sat�ra ge�sin
	}	
	f_yazma<<int(yeniDizi[i])<<"\t"; //yazd�r bir tab bo�luk b�rak
	
}


delete [] sabitDizi; //olu�turdu�umuz pointer dizilerimizi yok ettik
delete [] yeniDizi;
f_okuma.close();//dosya okuma kapatt�k
f_yazma.close();// dosya yazmay� kapatt�k
	
	}
	else
	{
		
		MPI_Recv(&blokBoyutu,1,MPI_INT,0,34,MPI_COMM_WORLD,&status);//blok boyutumuzu ald�k

		int *sabitDizi = new int[blokBoyutu];//blok boyutuna sabit sabit dizi olu�turduk
			
		MPI_Recv(&en,1,MPI_INT,0,34,MPI_COMM_WORLD,&status);//en ald�k
		MPI_Recv(&sabitDizi[0],blokBoyutu,MPI_INT,0,53,MPI_COMM_WORLD,&status);//sabit dizimize myrank 0 daki ald���m�z par�alanm�� say�lar� ald�k
		
		D_baslangic=2*en+2;//baslangic zaman�
	
		
		int *yeniDizi = new int[blokBoyutu];//de�i�ecek dizimizi blok boyutunda olu�turduk
		
		for(int i=0;i<blokBoyutu;i++)//sabit dizimizi degisecek dizi kaydettik
			*(yeniDizi+i)=*(sabitDizi+i);
		
		
		
		
	for(D_baslangic;D_baslangic<=blokBoyutu-2*en-3;D_baslangic++){

		toplam=0;
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

	

//myrank 0 a filtrelenmi� matrisi yollad�k
MPI_Send(&yeniDizi[0],blokBoyutu,MPI_INT,0,34,MPI_COMM_WORLD);

	}
	

	//Adim ? -> MPI Ortamini Sonlandir
	MPI_Finalize();
	
	return 0;
}
