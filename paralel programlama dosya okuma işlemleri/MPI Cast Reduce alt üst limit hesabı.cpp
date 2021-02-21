#include <mpi.h>
#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	//Adim 1 -> Degiskenleri Deklare Et
	int myRank,
	     size;
	     
    int   n,//alt limit
            blokBoyutu,//Her bilgisayarin payina dusen veri miktari
            
            _n;//üst limit 
	    
	long long altLimit,ustLimit;
	long long  toplam=0;
	int asilToplam=0;
	int asilT=0;
	int bol,kalan=0;

                        
	MPI_Status status;
	//Adim 2 -> MPI Ortamini Ilklendir
	MPI_Init(&argc,&argv);

	//Adim 3 -> Rankini ve dunyadaki bilgisayar sayisini ogren
	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(myRank==0)
	{
		cout<<"alt limit: ";
		cin>>n;
		cout<<"ust limit:";
		cin>>_n;
		
		blokBoyutu=(_n-n)/size;
	}
	MPI_Bcast(&n,1,MPI_UNSIGNED_LONG_LONG,0,MPI_COMM_WORLD);
	MPI_Bcast(&blokBoyutu,1,MPI_UNSIGNED_LONG_LONG,0,MPI_COMM_WORLD);
	
	

	altLimit=n+(blokBoyutu*myRank);
    ustLimit=altLimit+blokBoyutu;
    
    
    	for(long long i=altLimit; i<ustLimit; i++) {
    		toplam=0;
    	for(long long j=1;j<i;j++){
    	
		if((i%j) == 0){
		bol=j;
		kalan=0;
		while(bol!=0){
			kalan=bol%10;
			bol=bol/10;
		if(kalan==4){
			toplam += j;
			bol=0;
			}
		}
			
		}
		}
		if(toplam==i)
		asilToplam++;
			
	}

cout<<asilToplam<<endl;
	
	MPI_Reduce(&asilToplam,&asilT,1,MPI_UNSIGNED_LONG_LONG,MPI_SUM,0,MPI_COMM_WORLD);

	if(myRank==0)
	cout<<"toplam :"<<asilT<<endl;

	//Adim ? -> MPI Ortamini Sonlandir
	MPI_Finalize();
	
	return 0;
}
