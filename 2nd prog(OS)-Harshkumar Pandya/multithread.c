#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int x,b; 							//Variable declaration
int space=0; 				
int Factors[100]; 						// Buffer for storing factors
int A,P; 				
pthread_mutex_t region_mutex = PTHREAD_MUTEX_INITIALIZER;

//Initialize a Mutex

void* P_NO(void* no_thread);
int main(int argc, const char * argv[])
{
	A = atoi(argv[1]); 					//Takes the first argument and converts it to integer
	P = atoi(argv[2]); 					//Takes the second thread argument and converts it to integer
	printf("NUMBER ENTERED IN THE COMMAND LINE IS : %d \n",A);
	b=sqrt(A); 						//Quicker calculation we use SquareRoot of N
	printf("NUMBER OF THREADS USED FOR TESTING : %d \n",P);
	b=A;
	pthread_t T[P]; 					//Stores the ThreadID
	int i; 					
	int Summation=0; 					//To calculate the sum of Factors
	for(i=0;i<P;i++)
	{
		pthread_create(&T[i],NULL,P_NO,(void *)i); 	// 'P' Threads are created
	}
	for(i=0;i<P;i++)
	{
		pthread_join(T[i],NULL);
		//Using Sychronization and merging it with the parent thread
	}
	int c,j,k;
	printf(" The Factors of the number you entered are \n" );
	for (i = 0; i < space; i++) 
	{
		for (j = i + 1; j < space;) 
		{
			if (Factors[j] == Factors[i])		//removes double repeated factors
			{
				for (k = j; k < space; k++) 
				{
					Factors[k] = Factors[k + 1];
				}
				space--;
			} 
			else
			j++;
		}
	}
	for(c=0;c<space;c++) 					//To evaluate Summation of all Factors
	{
		Summation+=Factors[c];
		printf("%d \n",Factors[c]);
	}
	printf("Summation is %d \n",Summation); 		//To check if Sum Of Factors = Number
	if(Summation==A)
	{
		printf("%d is a Perfect number \n", A);
	}
	else
	{
		printf("%d is NOT a Perfect Number \n", A);
	}
	return 0;
}

void* P_NO(void* no_thread)
{
	x=b/P; 							// work to be done by each thread
	int i;
	int Begin,Last; 					//Declaring the variables to save the boundaries
	int id_thread= (int) no_thread; 			//Typecasting
	if(id_thread==(P-1)) 					//Calculating the Begin and Last boundaries for thread
	{ 					
		Begin=id_thread*x+1;
		Last=b;
	}
	else
	{
		Begin=id_thread*x+1;
		Last=Begin+x;
	}
	//Each thread calculates factors of A					
	for(i=Begin;i<Last;i++)
	{
		if(A%i==0)
		{
			pthread_mutex_lock(&region_mutex);
			{
				if(i==1)
				{
					Factors[space]=1; 	//saves result in Buffer
					space++; 		//pointer gets incremented.
				}
				else
				{	
					Factors[space]=i; 	//for quicker results we calculate the factors of other half
					space++;
					Factors[space]=A/i;
					space++;
				}
			}

			pthread_mutex_unlock(&region_mutex);
		}
	}

	return 0;
}
