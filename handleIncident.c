/**********************
**Rantses Vinse
**AM:2022201900196
**dit19196@uop.gr
**
**Alexandropoulos Ilias
**AM:2022201900007
**dit19007@uop.gr
***********************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define STRMAX 1000
 
typedef struct
{
	int year;
	int month;
	int day;
}date;

typedef struct
{
	char latitude[50];
	char longitude[20];
}location;

typedef struct Incident
{
	char perioxi[40];  
	date reported;
	int missing;
	int women;
	int men;
	int kids;
	char death[200];
	char meros[200];	
	location coordinates;
	char url[50];
	struct Incident *nextPtr;
}incident;

incident *head=NULL, *telos = NULL, *temp;

void insert();
void COUNT(char *Str);
void FIND(char *Str);
void PRINT(char *Str);
void DELETE(char *Str);
void SAVE(char *Str);
void LOAD(char *Str);
int  EXIT(char *Str);
void printReverse();
int sum_list(int x);
void search_list(char *Str, int x);
void date_list(int mera, int mhnas, int etos, int x);
void print_list(incident *TEMP);
void delete_list(int x);
void load_checker(char *STR);
int string_se_int( char *Str, int max);
int counter(char *Str);
int counter_cords(char *Str);
void command(char *Str);
void perioxi_checker(char *Str, int *shmaia, incident *listPtr, int flag_file);
void date_checker(char *Str, int *shmaia, incident *listPtr, int flag_file);
void Missing(char *Str, int *shmaia, incident *listPtr, int flag_file);
void Women(char *Str, int *shmaia, incident *listPtr, int flag_file);
void Men(char *Str, int *shmaia, incident *listPtr, int flag_file);
void Kids(char *Str, int *shmaia, incident *listPtr, int flag_file);
void death_checker(char *Str, int *shmaia, incident *listPtr, int flag_file);
void meros_checker(char *Str, int *shmaia, incident *listPtr, int flag_file);
void cords_checker(char *Str, int *shmaia, incident *listPtr, int flag_file);
void url_checker(char *Str, int *shmaia, incident *listPtr, int flag_file);
int str_is_digit(char *Str, int max);
void clear_str(char *Str);
int counter_path(char *checker,int max);
void time_sleep (double secs);

char str[STRMAX], *strtemp;
int load_checker_flag = 0;

int main(void)
{	
	strtemp = (char *)malloc(sizeof(char)*STRMAX);
	char str2[STRMAX];
	int flag, i = 0;
	do{
		printf("\n$ > ");
		clear_str(str);
		fgets(str, STRMAX, stdin);
		printf("\033[1;34m");
		printf("Epejergasia dedomenwn...\n");
		printf("\033[0m");
		time_sleep(1.5);
  		str[strlen(str)-1] = '\0';
  		strcpy(str2, str);
		command(str2);
		if( !strncmp(str2, "newincident", 11) )
		{		
			strcpy(strtemp, str+11);
			insert();
		}
		else if( !strncmp(str2, "count",5) )
			COUNT(str+5);
			
		else if( !strncmp(str2, "find", 4) )
			FIND(str+4);
		else if( !strncmp(str2, "printreverse", 12) )
		{
			temp = head;
			printReverse();
		}		
		else if( !strncmp(str2, "print", 5) )
			PRINT(str+5);
		
		else if( !strncmp(str2, "delete", 6) )
			DELETE(str+6);
		
		else if( !strncmp(str2, "save", 4) )
			SAVE(str+4);
		
		else if( !strncmp(str2, "load", 4) )
			LOAD(str+4);
		else if( !strncmp(str2, "exit", 4) )
		{
			if( EXIT(str+4) )
				printf("Lathos syntaksi ths entolhs exit\n");	
			else
			{
				printf("Made by ");
				printf("\033[1;36m");
				printf("L0uSg3");
				printf("\033[0m");
				printf(" and ");
				printf("\033[1;31m");
				printf("TheHueMaster");
				printf("\033[0m");	
				printf("!!\n\nExiting...\n");
				time_sleep(2);
				break;
			}
		}
		else
		{
			printf("\033[1;31m");
			printf("Lathos entoli\n");
			printf("\033[0m");
		}
	}
	while(1);
	return 0;	 
}

void insert()
{ 
	if(strtemp[0] != ' ')
	{
		printf("\033[1;31m");
		printf("Lathos entoli\n");
		printf("\033[0m");
		return;
	}
	strtemp++;
   	incident *newPtr, *temp;
   	int flag[9] = {0};
   	newPtr = (incident *)malloc(sizeof(incident));
   	temp = newPtr;
   	//ANTIGRAFI TIMWN STIN LISTA
   	//Perioxi
   	perioxi_checker(strtemp, flag, newPtr, 0);
   	if(flag[0] == 0)
   	{
   		strncpy(newPtr->perioxi, strtemp, counter(strtemp)+1);
   		strtemp += counter(strtemp) + 1;
   	}
   	//Hmerominia
   	date_checker(strtemp, flag, newPtr, 0);
   	if(flag[1] == 0)
	{
		//day
		newPtr->reported.day = (*strtemp - '0')*10 + (*(strtemp+1) - '0');
		strtemp += 3;
	
		//month
   		newPtr->reported.month = (*(strtemp) - '0')*10 + (*(strtemp+1) - '0');
		strtemp += 3;
		//year
   		newPtr->reported.year = (strtemp[0]- '0')*1000 + (strtemp[1]- '0')*100 + (strtemp[2] - '0')*10 + (strtemp[3] - '0');
   		strtemp += 5;
   	}
   	//missing
   	Missing(strtemp, flag, newPtr, 0);
   	if( flag[2] == 0)
   	{
    		newPtr->missing = string_se_int(strtemp, counter(strtemp));
    		strtemp += counter(strtemp) + 1;
    	}
    	//women 
    	Women(strtemp, flag, newPtr, 0);
    	if( flag[3] == 0)
    	{
    		newPtr->women = string_se_int(strtemp, counter(strtemp));
    		strtemp += counter(strtemp) + 1;
    	}
    	//men
    	Men(strtemp, flag, newPtr, 0);
    	if( flag[4] == 0)
    	{
    		newPtr->men = string_se_int(strtemp,counter(strtemp) );
    		strtemp += counter(strtemp) + 1;
    	}
    	//kids
    	Kids(strtemp, flag, newPtr, 0);
    	if( flag[5] == 0)
    	{
    		newPtr->kids = string_se_int(strtemp, counter(strtemp) );
    		strtemp += counter(strtemp) + 1;
    	}
    	//death
    	death_checker(strtemp, flag, newPtr, 0);
    	if(flag[6] == 0)
    	{
    		strncpy(newPtr->death, strtemp, counter(strtemp)+1);
        clear_str(newPtr->death + counter(strtemp)+1);
    		strtemp += counter(strtemp)+1;
    	}
    	//meros/perioxi
    	meros_checker(strtemp, flag, newPtr, 0);
    	if( flag[7] == 0)
    	{
    		strncpy(newPtr->meros, strtemp, counter(strtemp)+1);
    		strtemp += counter(strtemp)+1;
    	}
    	//cords
    	cords_checker(strtemp, flag, newPtr, 0);
        //url
    	url_checker(strtemp, flag, newPtr, 0);
    	
	newPtr->nextPtr = NULL;
   	if ( telos == NULL )
      	{
      		head =  newPtr;
		telos = newPtr;
   	}
   	else
   	{
   		telos->nextPtr = newPtr;
   		telos = newPtr;
   	}
   	telos->nextPtr = head;		
}
void COUNT(char *Str)
{
	if( Str[0] != ' ')
	{
		printf("\033[1;31m");
		printf("Lathos stoixeia entolis.\n");
		printf("\033[033[0m");
		return;
	}
	Str++;
	int i;
	for( i = 0; i < strlen(Str); i++)
		Str[i] = (char)tolower( (int)Str[i] );
	
	if( !strncmp(Str, "missing", 7) )
	{
		printf("Synolikos arithmos agnooumenwn: %d\n", sum_list(1) );
	}
	else if( !strncmp(Str, "men", 3) )
	{
		printf("Synolikos arithmos nekrwn andrwn: %d\n", sum_list(2) );
	}
	else if( !strncmp(Str, "women", 5) )
	{
		printf("Synolikos arithmos nekrwn gynaikwn: %d\n", sum_list(3) );
	}
	else if( !strncmp(Str, "children", 8) )
	{
		printf("Synolikos arithmos nekrwn paidiwn: %d\n", sum_list(4) );
	}
	else
	{
		printf("\033[1;31m");
		printf("Lathos to akolouthoumeno, apo to count, lektiko.\n");
		printf("Epitrepta lektika: 'missing', 'men', 'women', 'children'\n");
		printf("\033[0m");
		return;
	}
}

void FIND(char *Str)
{
	if( Str[1] != ' ')
	{
		printf("\033[1;31m");
		printf("Lathos stoixeia entolis.\n");
		printf("\033[0m");
		return;
	}
	command(Str);
	if( Str[0] == 'r')
	{
		Str += 2;	
		search_list(Str, 1);
	}
	else if( Str[0] == 'c')
	{
		Str += 2;
		search_list(Str, 2);
	}
	else if(Str[0] == 'l')
	{
		Str += 2;
		search_list(Str, 3);
	}
	else
	{
		printf("\033[1;31m");
		printf("Lathos entoli\n");
		printf("Oi epitreptes entoles tis 'find' einai oi akolouthes: findR/findC/findL\n");
		printf("\033[0m");
		return;
	}
}

void PRINT(char *Str)
{
	int i, flag = 0, Counter = 0, mera, mhnas, etos;
	char checker[15] ={0};
	strcpy(checker, Str+2);
	if(Str[1] != ' ')
	{
		printf("\033[1;31m");
		printf("Lathos stoixeia entolis.\n");
		printf("\033[0m");
		return;
	}	
	command(Str);
	//
	if(Str[0] != 'a' && Str[0] != 'b')
	{
		printf("\033[1;31m");
		printf("Lathos entoli\n");
		printf("Oi epitreptes entoles tis 'print' einai oi akolouthes: printA/printB\n");
		printf("\033[0m");
		return;
	}
	//Elegxos hmerominias
	for(i = 0; i < strlen(checker); i++)
	{
		if(checker[2] != '/' || checker[5] != '/' )
		{
			flag = 1;
			break;
		}
		if( isdigit( (int)checker[i] ) )
			Counter++;
	}
	if( Counter == 8 && flag != 1)
	{
		mera = string_se_int(checker, 2);
		mhnas = string_se_int(checker+3, 2);
		etos = string_se_int(checker+6, 4);
		if( mera <= 0 || mera > 31)
			flag = 1;
		else if( mhnas <= 0 || mhnas > 12)
			flag = 1;
		else if( etos < 1000 || etos > 2020)
			flag = 1;
		if( flag != 1 && mhnas == 2 && mera > 28)
			flag = 1;	
	}
	else
		flag = 1;
	if(flag == 1)
	{
		printf("\033[1;31m");
		printf("Lathos stoixeia hmerominias.\n");
		printf("\033[0m");
		return;
	}
	mera = string_se_int(checker, 2);
	mhnas = string_se_int(checker+3, 2);
	etos = string_se_int(checker+6, 4);
	if(Str[0] == 'a')
		date_list(mera, mhnas, etos, 1);
	else 
		date_list(mera, mhnas, etos, 2);
}
void DELETE(char *Str)
{

	if( Str[0] == 'N' || Str[0] == 'n')
	{
		delete_list(1);				
	}
	else if( Str[0] == 'O' || Str[0] == 'o')
	{
		delete_list(2);
	}
	else
	{
		printf("\033[1;31m");
		printf("Lathos stoixeia entolis.\n");
		printf("Epitreptes entoles tis 'delete' einai: deleteN/deleteO\n");
		printf("\033[0m");
		return;
	}
}

void SAVE(char *Str)
{
	FILE *myFile;
	char clear = '\0';
	if(Str[0] != ' ')
	{
		printf("\033[1;31m");
		printf("Lathos stoixeia entolis\n");
		printf("\033[0m");
		return;
	}
	Str++;
	myFile = fopen(Str, "w");
	if( myFile == NULL )
	{
		printf("\033[1;31m");
		printf("Sfalma anoigmatos tou arxeiou.\n");
		printf("\033[0m");
		return;
	}
	temp = head;
	do
        {    	
            	fprintf(myFile,"%s",temp->perioxi);
           	if(temp->reported.day >= 1 && temp->reported.day <= 9 && temp->reported.month >= 1 && temp->reported.month <= 9)
                	fprintf(myFile,"0%d/0%d/%d;", temp->reported.day, temp->reported.month, temp->reported.year);
    	        else if( temp->reported.day >= 1 && temp->reported.day <= 9 )
    	            fprintf(myFile,"0%d/%d/%d;", temp->reported.day, temp->reported.month, temp->reported.year);
    	        else if(temp->reported.month >= 1 && temp->reported.month <= 9)
    	            fprintf(myFile,"%d/0%d/%d;", temp->reported.day, temp->reported.month, temp->reported.year);
    	        else
    	            fprintf(myFile,"%d/%d/%d;", temp->reported.day, temp->reported.month, temp->reported.year);
    	        fprintf(myFile,"%d;%d;%d;%d;", temp->missing, temp->women, temp->men, temp->kids);
    	        fprintf(myFile,"%s", temp->death);
    	        fprintf(myFile,"%s", temp->meros);
    	        fprintf(myFile,"%s%s", temp->coordinates.latitude, temp->coordinates.longitude);
    	        fprintf(myFile,"%s\n", temp->url);
    	        temp=temp->nextPtr;
        }while( temp != head);
	fclose(myFile);
}	

void LOAD(char *Str)
{
	char **STR, c;
	if(Str[0] != ' ')
	{
		printf("\033[1;31m");
		printf("Lathos stoixeia entolis.\n");
		printf("\033[0m");
		return;
	}
	FILE *myFile;
	Str++;
	myFile = fopen(Str, "r");
	if( myFile == NULL)
	{
		printf("\033[1;31m");
		printf("Sfalma anoigmatos tou arxeiou.\n");
		printf("\033[0m");
		return;
	}
	int i = 0, count = 0;
	for (c = getc(myFile); c != EOF; c = getc(myFile)) 
       		if (c == '\n') 
            		count++;
        fclose(myFile);
       	myFile = fopen(Str, "r");
       	STR = (char **)malloc(sizeof(char*)*count);
	for(i = 0; i < count; i++)
		STR[i] = (char *)malloc(sizeof(char)*STRMAX);   
	i = 0;
	while(!feof(myFile) )
	{
		fgets(&STR[i][0], 1000, myFile);
		i++;
	}
	for( i = 0; i < count; i++)
	{
		STR[i][strlen(&STR[i][0])-1] = '\0';   
		load_checker_flag = 0;
		load_checker(&STR[i][0]);
  	}
	for(i = 0; i < count; i++)
		free(STR[i]);
	free(STR);	
	fclose(myFile);
}

int EXIT(char *Str)
{
	int i;
	for(i = 0; i < strlen(Str); i++)
	{
		if( !isspace( (int)Str[i] ) )
			return 1;
	}
	return 0;
}

void printReverse()
{
	if( temp == NULL )
	{
		printf("\033[1;31m");
		printf("\nEmpty List\n");
		printf("\033[0m");
		return;
	}	
	incident *x;
	x = temp;
	if( temp->nextPtr != head )
	{
		temp = temp->nextPtr;
		printReverse();
	}
	print_list(x);
}

int sum_list(int x)
{
	int sum = 0;
	switch(x)
	{
		case 1:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					sum += temp->missing;
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
		
		case 2:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					sum += temp->men;
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
		
		case 3:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					sum += temp->women;
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
		
		case 4:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					sum += temp->kids;
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
	}
	return sum;
}
void search_list(char *Str, int x)
{
	int i, flag = 0, first = 0;
	char arr[40] = {0}, list_mikra[200] = {0};
	Str[strlen(str)-1] = '\0';
	switch(x)
	{
		case 1:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					clear_str(list_mikra);
					strcpy(arr, Str);//O pinakas arr einai to string meta to findR
					strcpy(list_mikra, temp->perioxi);//O pinakas list_mikra einai to pedio perioxi se peza
					
					for(i = 0; i < strlen(list_mikra); i++)
						list_mikra[i] = tolower( (int)list_mikra[i] );
						
					for(i = 0; i < strlen(arr); i++)
						arr[i] = tolower( (int)arr[i] );
						
					for(i = 0; i < strlen(list_mikra); i++)
					{
						if( !strncmp(arr, &list_mikra[i], strlen(arr) ) )
						{
							flag = 1;
							clear_str(list_mikra);
							strcat(list_mikra, temp->perioxi);
							list_mikra[strlen(list_mikra)-1] = '\0';
							printf("\033[0;32m");
							if( first != 0)
								printf(", %s", list_mikra);
							else 
								printf("%s", list_mikra);
							printf("\033[0m");
							first = 1;
							break;
						}
					}						
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
		
		case 2:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					clear_str(list_mikra);
					strcpy(arr, Str);//O pinakas arr einai to string meta to findC
					strcpy(list_mikra, temp->death);//O pinakas list_mikra einai to pedio death se peza
					
					for(i = 0; i < strlen(list_mikra); i++)
						list_mikra[i] = tolower( (int)list_mikra[i] );
						
					for(i = 0; i < strlen(arr); i++)
						arr[i] = tolower( (int)arr[i] );
						
					for(i = 0; i < strlen(list_mikra); i++)
					{
						if( !strncmp(arr, &list_mikra[i], strlen(arr) ) )
						{
							flag = 1;
							clear_str(list_mikra);
							strcat(list_mikra, temp->death);
							list_mikra[strlen(list_mikra)-1] = '\0';
							printf("\033[0;31m");
							if( first != 0)
								printf(", %s", list_mikra);
							else 
								printf("%s", list_mikra);
							printf("\033[0m");
							first = 1;
							break;
						}
					}						
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
		
		case 3:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					clear_str(list_mikra);
					strcpy(arr, Str);//O pinakas arr einai to string meta to findL
					strcpy(list_mikra, temp->meros);//O pinakas list_mikra einai to pedio meros se peza
					
					for(i = 0; i < strlen(list_mikra); i++)
						list_mikra[i] = tolower( (int)list_mikra[i] );
						
					for(i = 0; i < strlen(arr); i++)
						arr[i] = tolower( (int)arr[i] );
						
					for(i = 0; i < strlen(list_mikra); i++)
					{
						if( !strncmp(arr, &list_mikra[i], strlen(arr) ) )
						{
							clear_str(list_mikra);
							strcat(list_mikra, temp->meros);
							list_mikra[strlen(list_mikra)-1] = '\0';
							flag = 1;
							printf("\033[0;32m");
							if( first != 0)
								printf(", %s", list_mikra);
							else 
								printf("%s", list_mikra);
							printf("\033[0m");
							first = 1;
							break;
						}
					}						
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
	}
	if( flag != 1)
	{
		printf("\033[1;31m");
		printf("Den vrethike to lektiko\n");
		printf("\033[0m");
	}
}
void date_list(int mera, int mhnas, int etos, int x)
{
	switch(x)
	{
		case 1:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					if(etos < temp->reported.year )
						print_list(temp);
					else if( etos == temp-> reported.year )
					{
						if( mhnas < temp->reported.month )
							print_list(temp);
						else if( mhnas == temp->reported.month)
						{
							if( mera <= temp->reported.day)
								print_list(temp);			
						}
					}
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
		
		case 2:
			temp=head;
			if(head==NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				do
				{
					if(etos > temp->reported.year )
						print_list(temp);
					else if( etos == temp-> reported.year )
					{
						if( mhnas > temp->reported.month )
							print_list(temp);
						else if( mhnas == temp->reported.month)
						{
							if( mera >= temp->reported.day)
								print_list(temp);
						}
					}
					temp=temp->nextPtr;
				}while( temp != head);
			}
		break;
	}
}			

void print_list(incident *TEMP)
{
	printf("\033[0;32m");
	printf("\n%s",TEMP->perioxi);
	printf("\033[0m");
	printf("\033[0;36m"); 
	if(TEMP->reported.day >= 1 && TEMP->reported.day <= 9 && TEMP->reported.month >= 1 && TEMP->reported.month <= 9)
		printf("0%d/0%d/%d;", TEMP->reported.day, TEMP->reported.month, TEMP->reported.year);
	else if( TEMP->reported.day >= 1 && TEMP->reported.day <= 9 )
		printf("0%d/%d/%d;", TEMP->reported.day, TEMP->reported.month, TEMP->reported.year);
	else if(TEMP->reported.month >= 1 && TEMP->reported.month <= 9)
		printf("%d/0%d/%d;", TEMP->reported.day, TEMP->reported.month, TEMP->reported.year);
	else
		printf("%d/%d/%d;", TEMP->reported.day, TEMP->reported.month, TEMP->reported.year);
	printf("\033[0m");
	printf("\033[0;34m"); 
	printf("%d;", TEMP->missing);
	printf("\033[0m");
	printf("\033[0;31m"); 
	printf("%d;%d;%d;",TEMP->women, TEMP->men, TEMP->kids);
	printf("%s", TEMP->death);
	printf("\033[0m");
	printf("\033[0;32m");
	printf("%s", TEMP->meros);
	printf("\033[0m");
	printf("\033[0;33m"); 
	printf("%s%s", TEMP->coordinates.latitude, TEMP->coordinates.longitude);
	printf("\033[0m");
	printf("\033[0;35m"); 
	printf("%s\n", TEMP->url);
	printf("\033[0m");
}	
void delete_list(int x)
{
	switch(x)
	{
		case 1:
			temp = telos;
			if(temp == NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				if(head == temp)
				{
					head = NULL;
					telos = NULL;
					free(temp);
				}
				else
				{
					temp = head;
					while( (temp->nextPtr)->nextPtr != head)
						temp = temp->nextPtr;
					free(temp->nextPtr);
					temp->nextPtr = head;
					telos = temp;
				}

			}
		break;
		
		case 2:
			temp = head;
			if(temp == NULL)
			{
				printf("\033[1;31m");
				printf("\nEmpty List\n");
				printf("\033[0m");
			}
			else
			{
				if(head == telos)
				{
					head = NULL;
					telos = NULL;
				}
				else
				{
					head = head->nextPtr;
					telos->nextPtr = head;
				}
 				temp->nextPtr=NULL;
				free(temp);
			}
		break;	
	}		
}

void load_checker(char *STR)
{
	incident *newPtr, *temp;
   	int i, flag;
   	newPtr = (incident *)malloc(sizeof(incident));
   	temp = newPtr;	
   	perioxi_checker(STR, &flag, newPtr, 1);
   	STR += counter(STR) + 1;
   	if(load_checker_flag != 1)
   		date_checker(STR, &flag, newPtr, 1);
   	else 
   	{
   		free(newPtr);
   		return;
   	}
   	STR += counter(STR) + 1;
   	if(load_checker_flag != 1)
   		Missing(STR, &flag, newPtr, 1);
   	else 
   	{
   		free(newPtr);
   		return;
	}   	
	STR += counter(STR) + 1;
   	if(load_checker_flag != 1)
   		Women(STR, &flag, newPtr, 1);
   	else
   	{
   		free(newPtr);
   		return;
   	}
   	STR += counter(STR)+1;
   	if(load_checker_flag != 1)
   		Men(STR, &flag, newPtr, 1);
   	else
   	{
   		free(newPtr);
   		return;
   	}
   	STR += counter(STR)+1;
   	if(load_checker_flag != 1)
   		Kids(STR, &flag, newPtr, 1);
   	else 
   	{
   		free(newPtr);
   		return;
   	}
   	STR += counter(STR)+1;
   	if(load_checker_flag != 1)
   		death_checker(STR, &flag, newPtr, 1);
   	else
   		return;
   	STR += counter(STR)+1;
   	if(load_checker_flag != 1)
   		meros_checker(STR, &flag, newPtr, 1);
   	else
   		return;
   	STR += counter(STR)+1;
   	if(load_checker_flag != 1)
   		cords_checker(STR, &flag, newPtr, 1);
   	else
   		return;
   	STR += counter(STR)+1;
   	if(load_checker_flag != 1)
   		url_checker(STR, &flag, newPtr, 1);
   	else
   		return;
   	newPtr->nextPtr = NULL;
   	if ( telos == NULL )
      	{
      		head =  newPtr;
		telos = newPtr;
   	}
   	else
   	{
   		telos->nextPtr = newPtr;
   		telos = newPtr;
   	}
   	telos->nextPtr = head;			
}
int string_se_int( char *Str, int max)
{
	int i, div = 1, x = 0;
	for(i = 0; i < max-1; i++)
		div *= 10;
	for( i = 0; i <= max-1; i++)
	{
		x += (Str[i] - '0')*div;
		div /= 10;
	}
	return x;
}

int counter(char *Str)
{
	int x = 0, i=0; 
	while(Str[i] != ';' )
	{
		if( i == strlen(Str) )
			break;
		if( isalnum( (int)Str[i] ) || ispunct( (int)Str[i] ) || Str[i] == ' ')
			x++;
		i++;
	}
	return x;
} 

int counter_cords(char *Str)
{
	int i=0, x = 0;
	while(Str[i] != ',' && Str[i] != ' ')
	{
		x++;
		i++;
	}
	return x;	
}

void command(char *Str)
{
	int i = 0;
	while( i < strlen(Str) )
	{
		Str[i] = (char)tolower( (int)Str[i] );
		i++;
	}
}

void perioxi_checker(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int i = 0, flag, Counter = 0; 
	char checker[200] = {0};
	strncpy(checker, Str, counter(Str)+1);
	do{
		i = 0;
		flag = 0;
		while(checker[i] != ';')
		{
			if( !isalpha( (int)checker[i] ) )
			{
				if(checker[i] != ',' && checker[i] != ' ' && checker[i] != '-' )
				{
					flag = 1;
					break;
				}
			}
			i++;
		}
		if( flag == 1)
		{
			if( flag_file == 1)
				break;
			clear_str(checker);
			printf("\033[1;31m");
			printf("Lathos stoixeia perioxis. Parakalw plhktrologiste ksana tin perioxi: ");
			printf("\033[0m");
			fgets(checker, 200, stdin);
			checker[strlen(checker)-1] = ';';
			shmaia[0] = 1;
		}
		if(flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		strcpy(listPtr->perioxi, checker);
		return;
	}
	else if(flag_file == 1 && flag == 1)
	{
		load_checker_flag = 1;
		return;
	}
	if(shmaia [0] == 1)
	{
		strtemp += counter(strtemp) + 1;
		strcpy(listPtr->perioxi, checker);
	}	 	
}
void date_checker(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	char checker[20] = {0};
	int i, mera, mhnas, etos, flag, Counter = 0;
	strncpy(checker, Str, counter(Str) + 1);
	do{
		i = 0;
		flag = 0;
		Counter = 0;
		while(checker[i] != ';')
		{
			if(checker[2] != '/' || checker[5] != '/' )
			{
				flag = 1;
				break;
			}
			if( isdigit( (int)checker[i] ) )
				Counter++;
			i++;
		}
		if( Counter == 8 && flag != 1)
		{
			mera = string_se_int(checker, 2);
			mhnas = string_se_int(checker+3, 2);
			etos = string_se_int(checker+6, 4);
			if( mera <= 0 || mera > 31)
				flag = 1;
			else if( mhnas <= 0 || mhnas > 12)
				flag = 1;
			else if( etos < 1000 || etos > 2020)
				flag = 1;
			if( flag != 1 && mhnas == 2 && mera > 28)
				flag = 1;	
		}
		else
			flag = 1;
		if(flag == 1)
		{
			if(flag_file == 1)
				break;
			clear_str(checker);
			printf("\033[1;31m");
			printf("Lathos stoixeia hmerominias. Parakalw plhktrologiste ksana hmerominia: ");
			printf("\033[0m");
			fgets(checker, 20, stdin);
			checker[strlen(checker)-1] = ';';
			listPtr->reported.day = string_se_int(checker, 2);
			listPtr->reported.month = string_se_int(checker+3, 2);
			listPtr->reported.year = string_se_int(checker+6, 4);
			shmaia[1] = 1;
		}
		if(flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		listPtr->reported.day = mera;
		listPtr->reported.month = mhnas;
		listPtr->reported.year = etos;
		return;
	}
	else if(flag_file == 1 && flag == 1)
	{
		load_checker_flag = 1;
		return;
	}
	if( shmaia[1] == 1)
		strtemp += counter(strtemp)+1;
}
void Missing(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int flag;
	char checker[50] = {0};
	strncpy(checker, Str, counter(Str)+1);
	do{
		flag = str_is_digit(checker, strlen(checker)-1);
		if(flag == 1)
		{
			if(flag_file == 1)
				break;
			clear_str(checker);
			printf("\033[1;31m");
			printf("Lathos arithmos agnooumenwn. Parakalw pliktrologiste ksana ton arithmo twn agnooumenwn: ");
			printf("\033[0m");
			fgets(checker, 50, stdin);
			checker[strlen(checker)-1] = ';';
			shmaia[2] = 1;
		}
		if(flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		listPtr->missing = string_se_int(checker,strlen(checker)-1);
		return;
	}
	else if(flag_file == 1 && flag == 1)
	{
		load_checker_flag = 1;
		return;
	}
	if( shmaia[2] == 1)
	{
		listPtr->missing = string_se_int(checker, strlen(checker)-1);
		strtemp += counter(strtemp)+1;
	}
}

void Women(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int flag;
	char checker[50] = {0};
	strncpy(checker, Str, counter(Str)+1);
	do{
		flag = str_is_digit(checker, strlen(checker)-1);
		if(flag == 1)
		{
			if(flag_file == 1)
				break;
			clear_str(checker);
			printf("\033[1;31m");
			printf("Lathos arithmos nekrwn gynaikwn. Parakalw pliktrologiste ksana ton arithmo twn nekrwn gynaikwn: ");
			printf("\033[0m");
			fgets(checker, 50, stdin);
			checker[strlen(checker)-1] = ';';
			shmaia[3] = 1;
		}
		if(flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		listPtr->women = string_se_int(checker, strlen(checker)-1);
		return;
	}
	else if( flag_file == 1 && flag == 1)
	{
		load_checker_flag = 1;
		return;
	}
	if( shmaia[3] == 1)
	{
		listPtr->women = string_se_int(checker, strlen(checker)-1);
		strtemp += counter(strtemp)+1;
	}
}

void Men(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int flag;
	char checker[50] = {0};
	strncpy(checker, Str, counter(Str)+1);
	do{
		flag = str_is_digit(checker, strlen(checker)-1);
		if(flag == 1)
		{
			if(flag_file == 1)
				break;
			clear_str(checker);
			printf("\033[1;31m");
			printf("Lathos arithmos nekrwn andrwn. Parakalw pliktrologiste ksana ton arithmo twn nekrwn andrwn: ");
			printf("\033[0m");
			fgets(checker, 50, stdin);
			checker[strlen(checker)-1] = ';';
			shmaia[4] = 1;
		}
		if(flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		listPtr->men = string_se_int(checker, strlen(checker)-1);
		return;
	}
	else if(flag_file == 1 && flag != 1)
	{
		load_checker_flag = 1;
		return;
	}
	if( shmaia[4] == 1)
	{
		listPtr->men = string_se_int(checker, strlen(checker)-1);
		strtemp += counter(strtemp)+1;
	}
}

void Kids(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int flag;
	char checker[50] = {0};
	strncpy(checker, Str, counter(Str)+1);
	do{
		flag = str_is_digit(checker, strlen(checker)-1);
		if(flag == 1)
		{
			if(flag_file == 1)
				break;
			clear_str(checker);
			printf("\033[1;31m");
			printf("Lathos arithmos nekrwn paidiwn. Parakalw pliktrologiste ksana ton arithmo twn nekrwn paidiwn: ");
			printf("\033[0m");
			fgets(checker, 50, stdin);
			checker[strlen(checker)-1] = ';';
			shmaia[5] = 1;
		}
		if( flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		listPtr->kids = string_se_int(checker, strlen(checker)-1);
		return;
	}
	else if(flag_file == 1 && flag == 1)
	{
		load_checker_flag = 1;
		return;
	}
	if( shmaia[5] == 1)
	{
		listPtr->kids = string_se_int(checker, strlen(checker)-1);
		strtemp += counter(strtemp)+1;
	}
}
	
void death_checker(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int i, flag;
	char checker[200] = {0};
	strncpy(checker, Str, counter(Str)+1);
	do{
		i = 0;
		flag = 0;
		while(checker[i] != ';')
		{
			if( !isalpha( (int)checker[i] ) )
			{
				if(checker[i] != ',' && checker[i] != ' ' )
				{
					flag = 1;
					break;
				}
			}
			i++;
		}
		if( flag == 1)
		{
			if(flag_file == 1)
				break;
			clear_str(checker);
			printf("\033[1;31m");
			printf("Lathos stoixeia aitias thanatou. Parakalw plhktrologiste ksana aitia thanatou: ");
			printf("\033[0m");
			fgets(checker, 200, stdin);
			checker[strlen(checker)-1] = ';';
			shmaia[6] = 1;
		}
		if(flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		strcpy(listPtr->death, checker);
		return;
	}
	else if(flag_file == 1 && flag == 1)
	{
		load_checker_flag = 1;
		return;
	}
	if(shmaia [6] == 1)
	{
		strtemp += counter(strtemp) + 1;
		strcpy(listPtr->death, checker);
	}
}
void meros_checker(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int i, flag;
	char check[200] = {0};
	strncpy(check, Str, counter(Str)+1);
	do{
		i = 0;
		flag = 0;
		while(check[i] != ';')
		{
			if( !isalpha( (int)check[i] ) )
			{
				if(check[i] != ',' && check[i] != ' ' && check[i] != '-' )
				{
					flag = 1;
					break;
				}
			}
			i++;
		}
		if( flag == 1)
		{
			if(flag_file == 1)
				break;
			clear_str(check);
			printf("\033[1;31m");
			printf("Lathos stoixeia perigrafhs topothesias. Parakalw plhktrologiste ksana perigrafi topothesias: ");
			printf("\033[0m");
			fgets(check, 200, stdin);
			check[strlen(check)-1] = ';';
			shmaia[7] = 1;
		}
		if(flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		strcpy(listPtr->meros, check);
		return;
	}
	else if(flag_file == 1 && flag == 1)
	{
		load_checker_flag = 1;
		return;
	}
	if(shmaia [7] == 1)
	{
		strtemp += counter(strtemp) + 1;
		strcpy(listPtr->meros, check);
	}
}	
void cords_checker(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int i, flag, Count, counter_komma, counter_teleia, counter_keno, x, y, c = 0;
	char *checker, longtitude[30] = {0}, latitude[30] = {0}, temp[60] = {0};
	checker = (char *)malloc(sizeof(char)*60);
        checker[counter(Str)+1] = '\0';
	strncpy(checker, Str, counter(Str)+1);
	strcpy(temp, checker);
	do{
		flag = 0;
		i = 0;
		Count = 0;
		counter_komma = 0;
		counter_teleia = 0;
		counter_keno = 0;
		while(checker[i] != ';')
		{
			if(!isdigit( (int)checker[i] ))
			{
				if( checker[i] != ',' && checker[i] != '.' && checker[i] != ' ' && checker[i] != '-')
				{
					flag = 1;
					break;
				}
				if(checker[i] == ',')
					counter_komma++;
				if( checker[i] == '.')
					counter_teleia++;
				if( checker[i] == ' ')
					counter_keno++;
			}
			i++;
		}
		if( flag != 1 && (counter_komma != 1 || counter_keno != 1 || counter_teleia != 2) )
			flag = 1;
	
		if( flag != 1)
		{
			for(i = 0; i < strlen(checker); i++)
				if( checker[i] == ',' || checker[i] == ' ' )
				{
					counter_komma = i;
					break;
				}
			for(i = counter_komma; i < strlen(checker); i++)
				if( isdigit( (int)checker[i]) || checker[i] == '-')
				{
					counter_komma = i-1;
					break;
				}
			strncpy(latitude, checker, counter_komma);
			latitude[counter_komma] = '\0';
			strcpy(longtitude, checker+counter_komma+1);
			//Elegxos latitude
			Count = 0;
			for(i = 0; i < strlen(latitude); i++)
			{
				if(latitude[i] != '.')
					Count++;
				else
					break;
			}
			if( Count != 3 && Count != 2 && Count != 1)
				flag = 1;
			if( flag != 1)
			{
				if( str_is_digit(latitude, 1) )
					y = string_se_int(latitude+1, Count-1);
				else
					y = string_se_int(latitude, Count);
				if( y > 90)
					flag = 1;
				else
				{
					c = 0;
					if( y == 90)
					{
						for(i = Count+1; i < strlen(latitude); i++)
							if( latitude[i] != '0' && latitude[i] != ' ' && latitude[i] != ',') 
							{
								flag = 1;
								break;
							}
					}
					if( flag != 1)
					{
						for(i = Count+1; i < strlen(latitude); i++)
						{	
							if( !isdigit( (int)latitude[i] ) )
							{
								if( latitude[i] != ' ' && latitude[i] != ',')
								{
									flag = 1;
									break;
								}
							}
							else
								c++;
						}
					}
				}
				if( c != 12 )
					flag = 1;
			}
			//Elegxos longtitude
			if( flag != 1)
			{
				Count = 0;
				for(i = 0; i < strlen(longtitude); i++)
				{
					if( longtitude[i] != '.')
						Count++;
					else 
						break;
				}
				if( Count != 3 && Count != 4 && Count != 2 && Count != 1)
					flag = 1;
				if( flag != 1)
				{
					if( str_is_digit(longtitude, 1) )
						x = string_se_int(longtitude+1, Count-1);
					else
						x = string_se_int(longtitude, Count);
					if( x > 180 )
						flag = 1;
					else
					{
						if( x == 180)
						{
							for(i = Count+1; i < strlen(longtitude)-1; i++)
							{
								if( longtitude[i] != '0' &&longtitude[i] != ' ' && longtitude[i] != ',')
								{
									flag = 1;
									break;
								}
					
							}
						}
						if( flag != 1)
						{	
							c = 0;
							for(i = Count+1; i < strlen(longtitude)-1; i++)
							{
								if( !isdigit( (int)longtitude[i] ) )
								{
									flag = 1;
									break;
								}
								else
									c++;
							}
						}
					}
					if( c != 12)
						flag = 1;
				}
			}
		}
		if( flag == 1)
		{
			if( flag_file == 1)
				break;
			clear_str(checker);
			clear_str(longtitude);
			clear_str(latitude);
			printf("\033[1;31m");
			printf("Lathos stoixeia syntetagmenwn. Parakalw pliktrologiste ksana tis synentetagmenes: ");
			printf("\033[0m");
			fgets(checker, 60, stdin);
			checker[strlen(checker)-1] = ';';
			shmaia[8] = 1;
		}		 
		if(flag_file == 1)
			break;
	}while(flag == 1);
	if(flag_file == 1 && flag != 1)
	{
		strncpy(listPtr->coordinates.latitude, temp, counter_komma+1);
    		strncpy(listPtr->coordinates.longitude, temp+counter_komma+1, counter(temp+counter_komma+1) + 1);
    		free(checker);
		return;
	}
	else if(flag_file == 1 && flag == 1)
	{
		free(checker);
		free(listPtr);
		load_checker_flag = 1;
		return;
	}		
	if( shmaia[8] == 1)
	{
		strncpy(listPtr->coordinates.latitude, checker, counter_cords(checker)+1);
    		checker += counter_cords(checker)+1 ;
    		strncpy(listPtr->coordinates.longitude, checker, counter(checker));
    		listPtr->coordinates.longitude[strlen(listPtr->coordinates.longitude)] = ';';
    		strtemp+= counter(strtemp)+1;
    	}
    	else
    	{
    		strncpy(listPtr->coordinates.latitude, temp, counter_komma+1);
    		strncpy(listPtr->coordinates.longitude, temp+counter_komma+1, counter(temp+counter_komma+1) + 1); 
    		strtemp+= counter(strtemp)+1;
    	}
}				
void url_checker(char *Str, int *shmaia, incident *listPtr, int flag_file)
{
	int i, flag = 0, Count  = 0, counter_teleia = 0;
	char *checker, *free_checker, temp[60] = {0};
	checker = (char *)malloc(sizeof(char)*60);
	strncpy(checker, Str, counter(Str));
  	free_checker = checker;
  	checker[counter(Str)] = '\0';
  	for(i = 0; i < strlen(checker); i++)
  		if( isspace( (int)checker[i] ) )
  			Count++;
  		else
  			break;
  	if(Count == strlen(checker))
  	{
  		strcpy(listPtr->url, Str);
  		return;
  	}
  	if(checker[0] == ' ')
  		checker++;
	do{
		flag = 0;
		//Protokollo
		if( strncmp(checker, "http", 4) && strncmp(checker, "https", 5) )
			flag = 1;
		if( !strncmp(checker, "https", 5) )
			checker += 5;
		else if( !strncmp(checker, "http", 4) )
			checker += 4;
		if( strncmp(checker, "://", 3) )
			flag = 1;
		if( flag != 1)
		{
			checker += 3;
			Count = 0;
			counter_teleia = 0;
			i = 0;
			//www
			for(i = 0; i < strlen(checker); i++)
				if( checker[i] == '.')
					counter_teleia++;
			if(counter_teleia >= 2)
			{
				i = 0;
				while(checker[i] != '.')
				{
					if( !isalpha( (int)checker[i] ) )
					{
						flag = 1;
						break;
					}
					Count++;
					i++;
				}	
				//domain
				if( flag != 1)
				{
					checker += Count + 1;
					i = 0;
					Count = 0;
					while(checker[i] != '.')
					{
						if( !isalpha( (int)checker[i] ) )
						{
							flag = 1;
							break;
						}
						Count++;
						i++;
					}
					//.com
					if(flag != 1)
					{
						checker += Count+1;
						i = 0;
						Count = 0;
						for(i = 0; i < 4; i++)
						{
							if( isalpha( (int)checker[i] ) )
								Count++;
							else
								break;
						}
						if( Count < 2 || Count > 4)
							flag = 1;
						if( flag != 1)
						{
							//Path
							checker += Count;
							if( checker[0] != '/')
									flag = 1;
							else
							{
								do{
									if(strlen(checker) == 1)
										break;
									checker ++;
									if( counter_path(checker, strlen(checker) ) )
									{
										for(i = 0; i < counter_path(checker, strlen(checker) ); i++)
										{	
											if( !isalnum( (int)checker[i] ) && checker[i] != '-')
											{
												flag = 1;
												break;
											}
										}
										if( flag != 1)
											checker += counter_path(checker, strlen(checker) );
										else
										{
											flag = 1;
											break;
										}
									}
									else//Telos tou path
									{
										Count = 0;
										for(i = 0; i < strlen(checker); i++)
										{
											if( !isalnum( (int)checker[i] ) && checker[i] != '-' && checker[i] != '.')
											{
												flag = 1;
												break;
											}
											else if( isalpha( (int)checker[i] ) )
												Count++;
										}
										if(Count == 0 )
											flag = 1; 
										break;
									}																	
								}while(1);
							}
						}
					}
				}
			}
			else if( counter_teleia == 1)
			{
				i = 0;
				Count = 0;
				while(checker[i] != '.')
				{
					if(!isalpha( (int)checker[i] ) )
					{
						flag = 1;
						break;
					}
					Count++;
					i++;
				}
				if( flag != 1)
				{
					checker += Count + 1;
					i = 0;
					Count = 0;
					for(i = 0; i < 4; i++)
					{
						if( isalpha( (int)checker[i] ) )
							Count++;
						else
							break;
					}
					if( Count < 2 || Count > 4)
						flag = 1;
					if( flag != 1)
					{
						//Path
						checker += Count;
						if( checker[0] != '/')
								flag = 1;
						else
						{
							do{
								if( strlen(checker) == 1)
									break;
								checker ++;
								if( counter_path(checker, strlen(checker) ) )
								{
									for(i = 0; i < counter_path(checker, strlen(checker) ); i++)
									{	
										if( !isalnum( (int)checker[i] ) && checker[i] != '-')
										{
											flag = 1;
											break;
										}
									}
									if( flag != 1)
										checker += counter_path(checker, strlen(checker) );
									else
										break;
								}
								else//Telos tou path
								{
									Count = 0;
									for(i = 0; i < strlen(checker); i++)
									{
										if( !isalnum( (int)checker[i] ) && checker[i] != '-' && checker[i] != '.')
										{
											flag = 1;
											break;
										}
										else if( isalpha( (int)checker[i] ) )
											Count++;
									}
									if(Count == 0 )
										flag = 1;
									break;
								}																	
							}while(1);
						}
					}
				}
			}
			else
				flag = 1;
		}
		if( flag == 1)
		{
			if(flag_file == 1)
				break;
			clear_str(checker);
			printf("\033[1;31m");
			printf("Lathos stoixeia. Parakalw pliktrologiste ksana to url: ");
			printf("\033[0m");
			fgets(checker, 60, stdin);
			checker[strlen(checker)-1] = '\0';
			strcpy(temp, checker);
			shmaia[9] = 1;
		}
		if(flag_file == 1)
			break;
	}while(flag == 1);
  	free(free_checker);
	if(flag_file == 1 && flag != 1)
	{
		strcpy(listPtr->url, Str);
		return;
	}
	else if( flag_file == 1 && flag == 1)
	{
		free(listPtr);
		return;
	}
	if(shmaia[9] == 1)
		strcpy(listPtr->url, temp);
	else
		strcpy(listPtr->url, Str);
}											
											
int str_is_digit(char *Str, int max)//EPISTREFEI 0 AN TO STRING EINAI THETIKOS ARITHMOS ALLIWS 1 
{
	int i;
	for(i = 0; i < max; i++)
	{
		if( !isdigit( (int)Str[i] ) )
			return 1;
	}
	return 0;
}	
void clear_str(char *Str)
{
	int i; 
	for(i = 0; i < strlen(Str); i++)
		Str[i] = '\0';
}

int counter_path(char *checker,int max)//Epistrefei posa stoixeia exei to alpharithmitiko mexri na vrei '/' alliws epistrefei 0
{
	int i, counter = 0, flag = 0;
	for( i = 0; i < max; i++)
		if( checker[i] == '/' )
			flag = 1;
	if( flag == 1)
	{		
		for(i = 0; i < max; i++)
		{
			if( checker[i] != '/' )
				counter++;
			else 
				return counter;
		}
	}
	else
		return 0;
}

void time_sleep (double secs) 
{
	int kathisterish;	
	kathisterish = time(NULL) + secs;  
	while( time(NULL) < kathisterish );
}
