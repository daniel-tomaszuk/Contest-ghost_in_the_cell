#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int factoryCount; // the number of factories
    cin >> factoryCount; cin.ignore();
    int linkCount; // the number of links between factories
    cin >> linkCount; cin.ignore();
    
    // zmienna dla obliczania odleglosci


    int my_id[factoryCount];
    int neut_id[factoryCount];
    int enem_id[factoryCount];
    int my_fac_force[factoryCount];
    int neut_prod[factoryCount];
    int enem_prod[factoryCount];
    int dist[factoryCount][factoryCount];
    int dist2[linkCount];
    int fac1[linkCount];
    int fac2[linkCount];
    int enem_fac_force[factoryCount];
    int licznik=0;   
    int factory[3][factoryCount];
    
    int triplets[7][100];

    int bomb_count=0;
    int bomb_count2=3;
    int bomb_mem=100;

       
    for(int i=0;i<factoryCount;i++){
        for(int j=0;j<factoryCount;j++){
        
            dist[i][j]=0;
        
        }
    }   
       
    for(int i=0;i<3;i++){
        for(int j=0;j<factoryCount;j++){
            factory[i][j]=100;
        }
    }
    
   
       
       
    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        cin >> factory1 >> factory2 >> distance; cin.ignore();
       
        dist2[i]=distance;
        fac1[i]=factory1;
        fac2[i]=factory2;
        // indeksy fabryk i odleglosci miedzy nimi
        dist[factory1][factory2]=distance;
        dist[factory2][factory1]=distance;

      //  dist1_2[i]=distance;
    }
  
     /*
     for (int i = 0; i < factoryCount; i++) {
         for (int j=0;j<factoryCount;j++){
          cout<<dist[i][j]<<" ";  
         }
     }    
    cout<<"WAIT"<<endl;  
    */  
    // game loop
    while (1) {
      
        int entityCount; // the number of entities (e.g. factories and troops)

        cin >> entityCount; cin.ignore();

        int k=0;
  
        
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            int arg5;
            cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5; cin.ignore();
          
        
        
            //fabryki     
            if (entityType=="FACTORY"){      
                factory[0][k]=arg1; //wlasnosc
                factory[1][k]=arg2; //jednostki
                factory[2][k]=arg3; //produkcja
                k++; //factoryCount
            }                         
        }
   
   
   
    for(int i=0;i<7;i++){
        for(int j=0;j<100;j++){
            triplets[i][j]=100;
        }
    } 
    
    
   
    int my_max=-100;
    int minima=101;
    int minima2=101;
    int kk=0; 
    int flag1=0;
    
    int min_i=100;
    int min_j=100;
    int min_ii=100;
    int min_jj=100;
    
    for (int i=0;i<factoryCount;i++){       //fac1 - moje
        minima=100;
        if (factory[0][i]==1){ //jezeli znaleziona moja baze
            for (int j=0; j<factoryCount;j++){  //fac2 - obce           
                if (minima>dist[i][j] && factory[2][j]>0 && i!=j && factory[0][j]!=1 && factory[1][i]>=factory[1][j]){
                    
                    minima=dist[i][j];
                    triplets[0][i]=i; // moj
                    triplets[1][i]=j; // minimum
                    min_i=i;
                    min_j=j;
                }
            } 
        }
    }
    

    
    for (int i=0;i<factoryCount;i++){       //fac1 - moje
        minima2=101;
        if (factory[0][i]==1){ //jezeli znaleziona moja baze            
            for (int j=0; j<factoryCount;j++){  //fac2 - obce  
            
                if(i==min_i && j==min_j){
                    continue;
                }
                else if (minima2>=dist[i][j] && triplets[2][i]!=triplets[1][i] && factory[2][j]>0 && factory[0][j]!=1 && factory[1][i]>=factory[1][j]){
                 
                   minima2=dist[i][j];
                   triplets[2][i]=j; // second best  
                   min_ii=i;
                   min_jj=j;
                }
            }
        }
    }

    for (int i=0;i<factoryCount;i++){       //fac1 - moje
        if (factory[0][i]==1){ //jezeli znaleziona moja baze            
            for (int j=0; j<factoryCount;j++){  //fac2 - obce  
            
                if((i==min_i && j==min_j) || (i==min_ii && j==min_jj) ){
                    continue;
                }
                else if (minima2>=dist[i][j] && triplets[2][i]!=triplets[1][i] && factory[2][j]>0 && factory[0][j]!=1 && factory[1][i]>=factory[1][j]){
                 
                   minima2=dist[i][j];
                   triplets[3][i]=j; // second best  

                }
            }
        }
    }


 //ATAK BABOWY BLISKICH NEUTRALNYCH Z PROD =3 i jednostkami >10

    // szukanie wrogiej fabryki z max iloscia jednostek do BOMBY
    int enem_max=-100;
    int enem_max_force=-100;
    for (int i=0;i<factoryCount;i++){ 
        if (factory[0][i]==-1 && enem_max<factory[1][i] && factory[2][i]>=2 && bomb_mem!=i){
            enem_max=i; // max jednostek
            enem_max_force=factory[1][i];
        }
    }
    
    int mymin_dist=100;
    int my_min_dist=100;
    //szukanie najblizszej mojej od wrogiego max
    for (int i=0;i<factoryCount;i++){       //fac1
        for (int j=0; j<factoryCount;j++){  //fac2
            if (dist[i][j]>0 && i==enem_max && my_min_dist>dist[i][j] && factory[0][j]==1){
                my_min_dist=dist[i][j];
                mymin_dist=j;    
            }
        }
    }
 

   
    // jednostki
    for (int j=0; j<factoryCount;j++){
        if(triplets[0][j]<100 && triplets[1][j]<100 && triplets[2][j]<100){
        
                if (factory[1][triplets[1][j]]<=factory[1][triplets[0][j]]){
                    
                    triplets[4][j]=(factory[1][triplets[1][j]])+1;
                    triplets[5][j]=(factory[1][triplets[2][j]])+1;
                    triplets[6][j]=(factory[1][triplets[3][j]])+1;
                }
           
           /*
                if (triplets[3][j]>10){
                    triplets[3][j]=5;
                }
                
                if (triplets[4][j]>10){
                    triplets[4][j]=5;
                }

                if (factory[1][j]>21&& factory[0][j]==1){
                    triplets[3][j]=50;
                    triplets[4][j]=50;
                }
                */
                if(factory[0][j]==1 && factory[2][j]==0){
                    triplets[4][j]=30;
                }
             
        }
        
    }
    

    
    if ((bomb_count>1 || bomb_count2>1 ) && bomb_mem!=enem_max && enem_max_force>=4 && mymin_dist<100 && dist[mymin_dist][enem_max]<=6){
        cout<<"BOMB "<<mymin_dist<<" "<<enem_max<<" ; ";
        bomb_mem=enem_max;
        bomb_count=0;
    }
    
    
    bomb_count++;
    bomb_count2--;




    // zwiekszenie produkcji
    for (int i=0; i<factoryCount; i++){
        if(factory[0][i]==1 && factory[1][i]>10 && factory[2][i]<3 && licznik>2){
            cout<<"INC "<<i<<" ; ";
        }
    }
    
    


    //cout<<kk<<endl;
    for (int i=0;i<factoryCount;i++){
        

        if(factory[2][i]==3 && factory[1][i]>=6){
        
            if(triplets[1][i]<100 && triplets[0][i]<100){
                    cout<<"MOVE "<<triplets[0][i]<<" "<<triplets[1][i]<<" "<<triplets[4][i]<<"; ";
                    factory[1][i]=factory[1][i]-triplets[4][i];
            }
                    
            if(triplets[2][i]<100 && triplets[0][i]<100){
                    cout<<"MOVE "<<triplets[0][i]<<" "<<triplets[2][i]<<" "<<triplets[5][i]<<"; ";
                    factory[1][i]=factory[1][i]-triplets[5][i];
                    
            }
            
            if(triplets[3][i]<100 && triplets[0][i]<100){
                    cout<<"MOVE "<<triplets[0][i]<<" "<<triplets[3][i]<<" "<<triplets[6][i]<<"; ";
                    factory[1][i]=factory[1][i]-triplets[6][i];
                    
            }
        }
        
        
        if(factory[2][i]<3){
        
            if(triplets[1][i]<100 && triplets[0][i]<100 && factory[1][i]>=3){
                    cout<<"MOVE "<<triplets[0][i]<<" "<<triplets[1][i]<<" "<<triplets[4][i]<<"; ";
                    factory[1][i]=factory[1][i]-triplets[4][i];
            }
                    
            if(triplets[2][i]<100 && triplets[0][i]<100 && factory[1][i]>=3){
                    cout<<"MOVE "<<triplets[0][i]<<" "<<triplets[2][i]<<" "<<triplets[5][i]<<"; ";
                    factory[1][i]=factory[1][i]-triplets[5][i];
                    
            }
            
            if(triplets[3][i]<100 && triplets[0][i]<100 && factory[1][i]>=3){
                    cout<<"MOVE "<<triplets[0][i]<<" "<<triplets[3][i]<<" "<<triplets[6][i]<<"; ";
                    factory[1][i]=factory[1][i]-triplets[6][i];
                    
            }
        }
        
        
        
        
        
        
    }  

    

    
        cout<<"WAIT; MSG Thanks for gaming!"<<endl;
    
    
/*    for (int i=0;i<factoryCount;i++){
        if(neut_dist_id[i]<100 && factory[1][my_max_id[i]]-unit[i]>=1 && my_max_id[i]>=0){
            cout<<"MOVE "<<my_max_id[i]<<" "<<neut_dist_id[i]<<" "<< unit[i]<<"; ";
            factory[1][my_max_id[i]]=factory[1][my_max_id[i]]-unit[i];
        }
        if (i+1==factoryCount){
            cout<<"MSG NEUTRALS"<<endl;
        }
        
    }
*/    
       
     
    licznik++;        
    }
}

