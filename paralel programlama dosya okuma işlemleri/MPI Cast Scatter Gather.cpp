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
   		    *sabitDizi,
			*sabitDizi2,     //dizi pointerlarýmýz
			*yeniDizi,
			*yeniDizi2,
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
	
 sabitDizi = new int[en*boy];      //ödevde istenilen üzere 0-255 deðer aralýðý icin unsigned char 
 yeniDizi= new int[en*boy];
for(int i=0;i<(en*boy);i++){//okuduðumuz dosyadaki sayýlarý dizimize attýk
    f_okuma>>OkuGelen;
    *(sabitDizi+i)=OkuGelen;

} 
	
	baslangicZamani = MPI_Wtime();//baþlangýç zamaný
	blokBoyutu=boy*en/size;//blok boyutu
	D_baslangic=2*en+2;//baslangic degeri
	
}
 
 	MPI_Bcast(&blokBoyutu,1,MPI_INT,0,MPI_COMM_WORLD);//blok boyutu myrank 0 aldýk
 	MPI_Bcast(&en,1,MPI_INT,0,MPI_COMM_WORLD);//en myrank 0 aldýk
   	MPI_Bcast(&D_baslangic,1,MPI_INT,0,MPI_COMM_WORLD);//baslangic deðerimizi myrank 0 aldýk
 	
 	sabitDizi2=new int[blokBoyutu];//sabit dizi elemanlarý tutan dizi
 	yeniDizi2=new int[blokBoyutu];//filtreleme uygulanacak elemanlarý tutan dizi

 	MPI_Scatter(sabitDizi,blokBoyutu,MPI_INT,sabitDizi2,blokBoyutu,MPI_INT,0,MPI_COMM_WORLD);//sabit dizimizden blok boyutu kadar bölerek sabit dizi2 içine attýk her bilgisayara

 	for(int i=0;i<blokBoyutu;i++)//sabit dizimizi yeni dizimize kopyaladýk
 	yeniDizi2[i]=sabitDizi2[i];
 	 	
 	for(D_baslangic;D_baslangic<=blokBoyutu-2*en-3;D_baslangic++){
		toplam=0;
		if(D_baslangic%(en)==en-2 || D_baslangic%(en)==en-1 || D_baslangic%(en)==0 || D_baslangic%(en)==1){


   /*         Buradaki if koþulu koyma sebebim ödevde verilen "ilk 2 satýrýndaki ve ilk 2 sütunundaki, 
             ayrýca son 2 satýrýndaki ve son 2 sütunundaki piksellerine filtre uygulanmaz"  bu koþulu
                                                saðlamasý için
  */
continue;

 }	//Belirgin olsun diye alt alta yazdým	
        //Kordinatlara göre kodlarýn yazýlýþý 

    deger[0]= *(sabitDizi2+D_baslangic-2*en-2);    //(x-2,y-2)
    deger[1]= *(sabitDizi2+D_baslangic-2*en-1);    //(x-2,y-1)
 	deger[2]= *(sabitDizi2+D_baslangic-2*en);       //(x-2,y)
 	deger[3]= *(sabitDizi2+D_baslangic-2*en+1);     //(x-2,y+1)
 	deger[4]= *(sabitDizi2+D_baslangic-2*en+2);     //(x-2,y+2)
 	deger[5]= *(sabitDizi2+D_baslangic-en-2);       //(x-1,y-2)
 	deger[6]= *(sabitDizi2+D_baslangic-en-1);       //(x-1,y-1)
 	deger[7]= *(sabitDizi2+D_baslangic-en);	        //(x-1,y)
 	deger[8]= *(sabitDizi2+D_baslangic-en+1);       //(x-1,y+1)
 	deger[9]= *(sabitDizi2+D_baslangic-en+2);       //(x-1,y+2)
 	deger[10]= *(sabitDizi2+D_baslangic-2);         //(x,y-2)
 	deger[11]= *(sabitDizi2+D_baslangic-1);         //(x,y-1)
 	deger[12]= *(sabitDizi2+D_baslangic);           //(x,y)
 	deger[13]= *(sabitDizi2+D_baslangic+1);         //(x,y+1)
 	deger[14]= *(sabitDizi2+D_baslangic+2);         //(x,y+2)
 	deger[15]= *(sabitDizi2+D_baslangic+en-2);      //(x+1,y-2)
 	deger[16]= *(sabitDizi2+D_baslangic+en-1);      //(x+1,y-1)
 	deger[17]= *(sabitDizi2+D_baslangic+en);        //(x+1,y)
 	deger[18]= *(sabitDizi2+D_baslangic+en+1);      //(x+1,y+1)
 	deger[19]= *(sabitDizi2+D_baslangic+en+2);      //(x+1,y+2)
 	deger[20]= *(sabitDizi2+D_baslangic+2*en-2);    //(x+2,y-2)
 	deger[21]= *(sabitDizi2+D_baslangic+2*en-1);    //(x+2,y-1)
 	deger[22]= *(sabitDizi2+D_baslangic+2*en);      //(x+2,y)
 	deger[23]= *(sabitDizi2+D_baslangic+2*en+1);    //(x+2,y+1)
 	deger[24]= *(sabitDizi2+D_baslangic+2*en+2);    //(x+2,y+2)

 
     
*(yeniDizi2+D_baslangic) = filtre(deger);//deger dizimi filtreyip  yenidizimizin içine attýk 12. elemaný

		}				
 	
   
	MPI_Gather(yeniDizi2,blokBoyutu,MPI_INT,yeniDizi,blokBoyutu,MPI_INT,0,MPI_COMM_WORLD);//admine gather ile filtreleme iþlemleri bitince myrank 0 içindeki dizimizin içine gönderdik 
	
	
	if(myRank==0){
		
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
delete [] sabitDizi2; //oluþturduðumuz pointer dizilerimizi yok ettik
delete [] yeniDizi2;
	MPI_Finalize();			
	return 0;
}
