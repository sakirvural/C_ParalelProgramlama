#include <stdio.h>
#include <ctime>
#include <fstream> //okuma yazma iþlemi iþlemleri için
#include <iostream>
#include <mpi.h>

//bubble sort algoritmasýna göre küçükten büyüðe sýralanýp 12. eleman yani 25 boyutluk dizide ortadaki eleman ifade eder
int *deger = new int[25];//filtre için
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
	    	size,//kaç pc var
			blokBoyutu,//her rank yapýcaðý iþlem boyutu
			D_baslangic,//baþlýycaðý deðer
			en,//okunacak en
    		boy,//okunacak boy
   			OkuGelen,//gelen sayilar
   		    *sabitDizi,     //dizi pointerlarýmýz
			*yeniDizi,
			toplam=0,
			bolum=0;
			
ifstream f_okuma;//okuma yazma için
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
f_okuma>>boy;                   //girilen txt dosyasýnda boy ve en aldýk
f_okuma>>en;
	
 int *sabitDizi = new int[en*boy];      //ödevde istenilen üzere 0-255 deðer aralýðý icin unsigned char 
 int *yeniDizi= new int[en*boy];
for(int i=0;i<(en*boy);i++){//okuduðumuz dosyadaki sayýlarý dizimize attýk
    f_okuma>>OkuGelen;
    *(sabitDizi+i)=OkuGelen;
    
} 
	
	baslangicZamani = MPI_Wtime();//baslangic zamani
	
	blokBoyutu=boy/size*en;//blok boyutu
	
	for(int i=1;i<size;i++)//block boyutumuzu ranklere gönderdik
		MPI_Send(&blokBoyutu,1,MPI_INT,i,34,MPI_COMM_WORLD);
	
		for(int i=1;i<size;i++)//en gönderdik
		MPI_Send(&en,1,MPI_INT,i,34,MPI_COMM_WORLD);	
		
		
	for(int i=1;i<size;i++)//blokladýðýmýz dizideki elemanlarýmýz her myrank için
		MPI_Send(&sabitDizi[i*blokBoyutu],blokBoyutu,MPI_INT,i,53,MPI_COMM_WORLD);
	
	
		D_baslangic=2*en+2;//baslangic degeri
		
		//dizimizi blockboyutu kadar yeni dizi attýk myrank0 için
		for(int i=0;i<blokBoyutu;i++)
			*(yeniDizi+i)=*(sabitDizi+i);
		
		
		
//filtreleme iþlemi
	for(D_baslangic;D_baslangic<=blokBoyutu;D_baslangic++){
		toplam=0;
		if(D_baslangic%(en)==en-2 || D_baslangic%(en)==en-1 || D_baslangic%(en)==0 || D_baslangic%(en)==1){


   /*         Buradaki if koþulu koyma sebebim ödevde verilen "ilk 2 satýrýndaki ve ilk 2 sütunundaki, 
             ayrýca son 2 satýrýndaki ve son 2 sütunundaki piksellerine filtre uygulanmaz"  bu koþulu
                                                saðlamasý için
  */
continue;

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
		
		//myranklarýmýzýn yaptýðý filtreleme iþlemleri aldýk ve yeni dizimize kaydettik
		for(int i=1;i<size;i++)
			MPI_Recv(&yeniDizi[i*blokBoyutu],blokBoyutu,MPI_INT,i,34,MPI_COMM_WORLD,&status);	
	
bitisZamani = MPI_Wtime();	//bitis zamani
	
gecenZaman=bitisZamani-baslangicZamani;//zamaný ekrana yazdýrdýk
cout<<"Gecen Zaman :"<<gecenZaman<<endl;

string cikti_ismi;
int i=22;
while(argv[1][i]!='.'){//buradaki iþlemde . olmayýnca kadar cikti_ismi stringte toplasýn
	cikti_ismi+=argv[1][i++];
}
cikti_ismi+="_filtered.txt";//burada sonuna _filtered.txt ekledik.


f_yazma.open(cikti_ismi); //yazma islemini yaptýk
f_yazma<<boy<<" ";//en boy yazdýrdýk
f_yazma<<en<<"\n";
for(int i=0;i<(en*boy);i++){//yazmak için dizimizi
	if(i!=0 && i%(en)==0){
		f_yazma<<"\n";//her en sayýmýz bitince 1 alt satýra geçsin
	}	
	f_yazma<<int(yeniDizi[i])<<"\t"; //yazdýr bir tab boþluk býrak
	
}


delete [] sabitDizi; //oluþturduðumuz pointer dizilerimizi yok ettik
delete [] yeniDizi;
f_okuma.close();//dosya okuma kapattýk
f_yazma.close();// dosya yazmayý kapattýk
	
	}
	else
	{
		
		MPI_Recv(&blokBoyutu,1,MPI_INT,0,34,MPI_COMM_WORLD,&status);//blok boyutumuzu aldýk

		int *sabitDizi = new int[blokBoyutu];//blok boyutuna sabit sabit dizi oluþturduk
			
		MPI_Recv(&en,1,MPI_INT,0,34,MPI_COMM_WORLD,&status);//en aldýk
		MPI_Recv(&sabitDizi[0],blokBoyutu,MPI_INT,0,53,MPI_COMM_WORLD,&status);//sabit dizimize myrank 0 daki aldýðýmýz parçalanmýþ sayýlarý aldýk
		
		D_baslangic=2*en+2;//baslangic zamaný
	
		
		int *yeniDizi = new int[blokBoyutu];//deðiþecek dizimizi blok boyutunda oluþturduk
		
		for(int i=0;i<blokBoyutu;i++)//sabit dizimizi degisecek dizi kaydettik
			*(yeniDizi+i)=*(sabitDizi+i);
		
		
		
		
	for(D_baslangic;D_baslangic<=blokBoyutu-2*en-3;D_baslangic++){

		toplam=0;
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

	

//myrank 0 a filtrelenmiþ matrisi yolladýk
MPI_Send(&yeniDizi[0],blokBoyutu,MPI_INT,0,34,MPI_COMM_WORLD);

	}
	

	//Adim ? -> MPI Ortamini Sonlandir
	MPI_Finalize();
	
	return 0;
}
