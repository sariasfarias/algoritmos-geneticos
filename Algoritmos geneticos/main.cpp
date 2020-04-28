#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

#define pieza 50

char genotipo[pieza], partida;
int piezas, cromosoma[pieza+1][pieza+1], n_cromosoma[pieza+1][pieza+1], aptitud[pieza][2], padres[2][pieza+1], hijos[2][pieza+1], fitness[pieza];
float fx[pieza][pieza];

//funciones
void muestra (void);
int salida (void);
void creacion (void);
void seleccion (int a[pieza+1][pieza+1]);
void ruleta (int a[pieza+1][pieza+1]);
void descendencia (void);

//programa 

main(){
	int i,j,apt;
	srand(time(NULL));
	muestra();
	creacion();
	seleccion(cromosoma);
	ruleta(cromosoma);
	for(i=0;i<piezas;i++){
		descendencia();
		ruleta(n_cromosoma);
	}
	apt=aptitud[0][1];
	cout<<endl<<"LA MEJOR RUTA ES: "<<endl;
	for(i=0;i<piezas;i++){
		cout<<genotipo[n_cromosoma[apt][i]]<<" ";
	}
	cout<<"Distancia: "<<aptitud[0][0]<<" cm aproximadamente";
	getch();
}

void muestra (void){
	int i,j;
	cout<<"Ingrese cantidad de piezas: ";
	cin>>piezas;
	for(i=0;i<piezas;i++){
		genotipo[i]='A'+i;
		if((i>=26) && ( i<=53)){
			genotipo[i]='a'+(i-26);	
		}
	}
	int distancia[piezas];
	float dist [piezas];
	float coordenadas_cm [piezas][2];
	
	for(i=0;i<piezas;i++){
		coordenadas_cm [i][0]=rand()%100;
		coordenadas_cm [i][1]=rand()%100;
		cout<<"coordenadas pieza "<<genotipo[i]<<": "<<coordenadas_cm [i][0]<<","<<coordenadas_cm [i][1]<<endl;
	}
	for(i=0;i<piezas;i++){
		for(j=i+1;j<piezas;j++){
			dist[i]=pow(pow(coordenadas_cm[i][0]-coordenadas_cm[j][0],2)+pow(coordenadas_cm[i][1]-coordenadas_cm[j][1],2),0.5);
			
			fx[i][j]=dist[i]; 
			fx[j][i]=fx[i][j];
			cout<<"La distancia en cm entre la pieza "<<genotipo[i]<<" y la pieza"<<genotipo[j]<<" es:  "<<dist[i]<<endl ;
			
		}
	}
}

int salida(void){
	int i;
	cout<<endl<<endl<<"Pieza Inicial: ";
	cin>>partida;
	for(i=0;i<piezas;i++){
		if(partida==genotipo[i])
		   return i;
	}
}

void creacion (void){
	int i, sal, dist, j, v;
	sal=salida();
	for(i=0;i<piezas;i++){
		for(j=1;j<piezas;j++){
			cromosoma[i][j]=-1;
		}
	}		
	for(i=0;i<piezas;i++){
		cromosoma[i][0]=sal;
	}
	for(i=0;i<piezas;i++){
		for(j=1;j<piezas;j++){ 
			dist=rand()%piezas;
			for(v=0;v<piezas;v++){
				if(cromosoma[i][v]==dist){
					dist++;
					if(dist>=piezas) dist=0;
					v=-1;
				}
			}
			cromosoma[i][j]=dist;
		}
	}				
	for(i=0;i<piezas;i++){
		cromosoma[i][piezas]=sal;
	}
}

void seleccion (int crm[pieza+1][pieza+1]){
	int i,j,x,y,sum,sal;
	
	for(i=0;i<piezas;i++){
		fitness[i]=0;
	}
	
	
	for(i=0;i<piezas;i++){
		for(j=0;j<piezas;j++){
			x=crm[i][j];
			y=crm[i][j+1];
			fitness[i]+=fx[x][y];
		}
	}
	
	for(i=0;i<piezas;i++){
		aptitud[i][0]=fitness[i];
		aptitud[i][1]=i;
	}
	
	for(i=0;i<piezas;i++){
		for(j=0;j<piezas;j++){
			if(aptitud[i][0]<aptitud[j][0]){
				sum=aptitud[i][0];
				sal=aptitud[i][1];
				aptitud[i][0]=aptitud[j][0];
				aptitud[i][1]=aptitud[j][1];
				aptitud[j][0]=sum;
				aptitud[j][1]=sal;
			}
		}
	}
}

void ruleta (int crm[pieza+1][pieza+1]){
	int media, apt, i, j, mejor;
	media=piezas/2;
	
	mejor=aptitud[0][1];
	for(j=0;j<piezas+1;j++){
		padres[0][j]=crm[mejor][j];
	}
	apt=rand()%media;
	if(apt==0) apt++;
	mejor=aptitud[apt][1];
	for(j=0;j<piezas+1;j++){
		
		padres[1][j]=crm[mejor][j];
	}
}


void descendencia (void){
	int crc1, crc2, media, i, j, dist, x, l, k;
	media=piezas/2;
	crc1=media-1;
	crc2=crc1*2;
	
	for(x=0;x<2;x++){
		for(j=0;j<piezas+1;j++)	{
			n_cromosoma[x][j]=padres[x][j];
		}
	}
	x=0;
	
	for(l=0;l<media;l++){
		for(i=0;i<2;i++){
			for(j=0;j<piezas+1;j++){
				hijos[i][j]=-1;
			}
		}
		
		hijos[0][0]=padres[0][0];
		hijos[0][piezas]=padres[0][piezas];
		hijos[1][0]=padres[1][0];
		hijos[1][piezas]=padres[1][piezas];
		x+=2;
		
		for(i=crc1;i<=crc2;i++){
			hijos[0][i]=padres[0][i];
			hijos[1][i]=padres[1][i];
		}
		
		for(i=1;i<crc1;i++){
			dist=padres[1][i];
			for(j=0;j<=crc2;j++){
				if(hijos[0][j]==dist){
					dist++;
					if(dist>=piezas) dist=0;
					j=-1;
				}
			}
			hijos[0][i]=dist;
		}
		
		for(i=1;i<crc1;i++){
			dist=padres[0][i];
			for(j=0;j<=crc2;j++){
				if(hijos[1][j]==dist){
					dist++;
					if(dist>=piezas) dist=0;
					j=-1;
					
				}
			}
			hijos[1][i]=dist;
		}
		
		for(i=crc2+1;i<piezas;i++){
			dist=padres[1][i];
			for(j=0;j<piezas;j++){
				if(hijos[0][j]==dist){
					dist++;
					if(dist>=piezas) dist=0;
					j=-1;
				}
			}
			hijos[0][i]=dist;
		}
		
		for(i=crc2+1;i<piezas;i++){
			dist=padres[0][i];
			for(j=0;j<piezas;j++){
				if(hijos[1][j]==dist){
					dist++;
					if(dist>=piezas) dist=0;
					j=-1;
				}
			}
			hijos[1][i]=dist;
		}
		
		k=0;
		for(i=x;i<x+2;i++){
			for(j=0;j<piezas+1;j++){
				n_cromosoma[i][j]=hijos[k][j];
			}
			k++;
		}
	}
	seleccion(n_cromosoma);
}
