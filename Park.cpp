#include<iostream>
#include<ctime>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<sstream>

using namespace std;
struct vehicle{
	string dname;
	int id;
	string make;
	string model;
	string colour;
	string time;
	vehicle*nptr;
};vehicle*fptr=NULL;
int time(){
	time_t now=time(0);
	tm*ltm=localtime(&now);
	ltm->tm_hour;
	ltm->tm_min;
	ltm->tm_sec;
cout<<ltm->tm_hour<<":"<<ltm->tm_min<<":"<<ltm->tm_sec<<endl;
return ltm->tm_min*60+ltm->tm_sec;	
}
vehicle*vehiclecheck(int id)
{ vehicle*ptr=fptr;
if(ptr==NULL)
 return NULL;
 if(ptr!=NULL)
 {  
      if(ptr->id==id)
      return ptr;
      else
      ptr=ptr->nptr;
 }
}

void vehicleentry()
{  vehicle*ptr=new vehicle;
   cout<<"Enter Vehicle Registration Number\n";
 cin>>ptr->id;
 cout<<"Enter Driver Name: "<<endl;
 cin.ignore();
 getline(cin,ptr->dname);
 cout<<"Enter Vehicle Make: "<<endl;
 cin.ignore();
 getline(cin,ptr->make);
 cout<<"Enter Vehicle Model: "<<endl;
 cin.ignore();
 getline(cin,ptr->model);
 cout<<"Enter Vehicle Colour: "<<endl;
 cin.ignore();
 getline(cin,ptr->colour);

 ptr->nptr=NULL;
 if(fptr==NULL)
{  
   fptr=ptr;
}
else
{  
   if(fptr->id>ptr->id)
   {  
      ptr->nptr=fptr;
      fptr=ptr;
   }
   else
   {  
      vehicle*currentptr=fptr;
      while(currentptr->nptr!=NULL){
	  
      if(currentptr->nptr->id>ptr->id)
      {  
         ptr->nptr=currentptr->nptr;
         currentptr->nptr=ptr;
         break;
	  }currentptr->nptr=ptr;
   }
   if(currentptr->nptr==NULL)
   {  
      currentptr->nptr=ptr;
   }
}
}
 
 }
 

void vehicleexit(vehicle*ptr,int id)
{ 
 ptr=fptr;
 while(ptr!=NULL)
 {  
    if(id==fptr->id)
    {  
        fptr=fptr->nptr;
        
        break;
	}
	else
	{  vehicle*currentptr=ptr;
	   if(id==currentptr->nptr->id)
	   {  
	      currentptr->nptr=currentptr->nptr->nptr;
	      break;
	   }
	  currentptr=currentptr->nptr; 
	}
 }
}


	

void display(vehicle*ptr)
{
	while(ptr!=NULL)
	{  cout<<"Vehicle Registration No: "<<ptr->id<<endl;
	   cout<<"Vehicle Make: "<<ptr->make<<endl;
	   cout<<"Vehicle Model: "<<ptr->model<<endl;
	   ptr=ptr->nptr;
}
}
vehiclefee(vehicle*ptr,int id,int fee)
{  int total=0;
  while(ptr!=NULL)
  {  if(id==ptr->id)
       {  cout<<"Rs."<<fee<<" Has Been Charged To ID No. "<<ptr->id<<endl;
        int total=0;
	   total=total+fee;
	   return total; 

       break;
	   }
	     
	   else
	   ptr=ptr->nptr; 
	   fstream myfile;
		myfile.open("parkingfee_collection.txt",ios::out | ios::app);
		myfile<<"&"<<endl;
		myfile<<id<<endl;
		myfile<<fee<<endl;
	   
}
}
int main()
{ int opt,id_check=0,v,z,total=0;


	string line;
	fstream file;
	file.open("last_saved_data.txt",ios::in);
	if(file){
		while(!file.eof()){
			getline(file,line);
			if(line =="&"){
				int identity , etime;
				string s1,s2,s3,s4,s5,s6;
				vehicle *ptr = new vehicle;
				
				getline(file,s1);
				stringstream ss(s1);
				ss>>identity;
				ptr->id = identity;
				
				getline(file,s2);
				ptr->dname = s2;
				
				getline(file,s3);
				ptr->make = s3;
				
				getline(file,s4);
				ptr->model = s4;
				
				getline(file,s5);
				ptr->colour =s5;
				
				getline(file,s6);
				stringstream s0(s6);
				s0>>etime;
				ptr->time = etime;
				

				ptr->nptr = NULL;
				
				if(fptr == NULL ){
					fptr = ptr;
				}
				
				else{
					vehicle *currentptr;
					currentptr = fptr;
					while(currentptr->nptr != NULL){
						currentptr = currentptr->nptr;
					}
					currentptr->nptr = ptr;
					currentptr->nptr->nptr=NULL;
				}
			}
		}
		file.close();
	}

while(1)
{


     cout<<"Main Menu:\n1.Vehicle Entry\n2.Vehicle Exit\n3.Parking Fee Colection\n4.Prking Statistics\n5.Exit\n";
     cin>>opt;
     if(opt==1)
     {    vehicleentry();
		int	v=time();
		  } 
		  if (opt==2)
		  {  int id;
		  while(id_check==0)
		    {
			 cout<<"Enter Vehicle Registration Number\n";
		     cin>>id;
		     if(vehiclecheck(id)==NULL)
		     {  
		         cout<<"Vehicle Doesnot Exists\n";
		         id_check=0;
		        
			 }
			 else if (vehiclecheck(id)!=NULL)
			 {  
			    id_check=1;
			 } }
			 if(id_check==1)
			 {  
			   
			    int z=time();
			    if(v-z<60);
			   {
				int fee=50;
			    total=total+vehiclefee(fptr,id,fee);
				 }
			    if(v-z>60 ||v-z==60)
			    { int fee=70;
				
			   total= total+vehiclefee(fptr,id,fee);
			    }
			    
			    vehicleexit(fptr,id);
			 } id_check=0;
			 
		  }
		  
		  if(opt==3){
		  	cout<<"Total Parking Fee Collected:Rs. "<<total<<endl;}
		  
		if(opt==4)	
		  display(fptr);
		if(opt==5)
		{  	fstream parkingdata;
				parkingdata.open("lastsaved_data.txt",ios::out | ios::app);
				vehicle *dataptr = fptr;
				while(dataptr != NULL){
					parkingdata<<"&"<<endl;
					parkingdata<<dataptr->id<<endl;
					parkingdata<<dataptr->dname<<endl;
					parkingdata<<dataptr->make<<endl;
					parkingdata<<dataptr->model<<endl;
					parkingdata<<dataptr->colour<<endl;
					parkingdata<<dataptr->time<<endl;
					dataptr = dataptr->nptr;
			}
				parkingdata.close();
				exit(0);
				
		}
			 }	 
	 
			  }
