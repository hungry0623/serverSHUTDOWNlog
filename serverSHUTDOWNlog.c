#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

//void main_reason(char* log, char* main_number); 	//write main activity (ex, shutdown, restart)
//void write_comment(char* log, char* comment, char* user_comment); 	//write the reason why shutdown the computer
void write_time_info(char* LOGFILENAME);		//write time info
void write_log_info(char* log, char* LOGFILENAME);		//write all log to file
void crypt_shutdown();

//char LOGFILENAME[20] = {0};
//char system_chmod[20] = "chmod 644 ";
//char system_chown[20] = "chown root.root ";

int main()
{
	char main_number[10] ={0};
	char log[100] = {0};
	char user_comment[150] = {0};
	char comment[50] = "SERVER SHUTDOWN comment:[";
	char system_chmod[50] = "chmod 644 ";	
	char system_chown[50] = "chown root.root ";
	char LOGFILENAME[50] = "./server_control_log";
//	strcpy(LOGFILENAME,"server_control_log");
//	LOGFILENAME[20] = "server_control_log";

	write_time_info(LOGFILENAME);

//	printf("Select the main activity pls\n");
//	printf("1. Server SHUTDOWN\n");
//	printf("2. Server RESTART\n");
//	gets(main_number);
//	printf("%s\n",main_number);
//	main_reason(log, main_number);

	printf("Write the reason why SHUTDOWN the Server.\nComment : ");
//	__fpurge(stdin);
	scanf("%s",user_comment);

	strcat(log,comment);
	strcat(log,user_comment);
	strcat(log,"]");

	write_log_info(log,LOGFILENAME);
	strcat(system_chmod,LOGFILENAME);
//	printf("\ntest\n%s\n",system_chmod);

	system(system_chmod);

	strcat(system_chown,LOGFILENAME);
//	printf("\ntest\n%s\n",system_chown);
	system(system_chown);

	crypt_shutdown();

	return 0;
}

void write_time_info(char* LOGFILENAME)
{
	FILE* f;
	time_t timer;
	struct tm *t;

	timer = time(NULL);

	t = localtime(&timer);
	
	f = fopen(LOGFILENAME,"a");
	fprintf(f,"%02d/%02d/%02d %02d:%02d:%02d ", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	fclose(f);
}
/*
void main_reason(char* log, char* main_number)
{
	char shutdown[] = "SHUTDOWN ";
	char restart[] = "RESTART  ";
	FILE* f;	

	if(!strcmp(main_number,"1"))
	{
		strcat(log,shutdown);
	}
	else if(!strcmp(main_number,"2"))
	{
		strcat(log,restart);
	}
	else
	{	
		f = fopen(LOGFILENAME,"a");
		fprintf(f,"Error, Invaild input number\n");
		printf("Wrong input!\n");
		exit(0);
	}
}

char* write_comment(char* log, char* comment, char* user_comment)
{
	char for_write[100] = {0};
	strcat(log,comment);
	strcat(log,user_comment);
	strcat(log,"]");
}
*/
void write_log_info(char* log, char* LOGFILENAME)
{
	FILE* f;
	f = fopen(LOGFILENAME,"a");
	fprintf(f, "%s\n", log);
	fclose(f);
}

void crypt_shutdown()
{
	char key[50] = {0};
	char salt[25] = "$6$3.2sh3Fj$";
	char answer_key[1000] = "$6$3.2sh3Fj$s2UZVqJckAxgdVVpXHcV1fPJPj0tX7Ik.p0c/gLU2M/gBmAGRrpaTperS8xg.5iAoKn1zaADG4CjEH/W9Qd6k/\0";
	char* check_key;

	printf("Enter root password : ");
	scanf("%s",key);

	check_key = crypt(key,salt);
//	printf("%s\n", check_key);

	if(!strcmp(answer_key, check_key))
	{
		printf("Shutdown computer now.....\n");
		system("init 0");
	}
	else
	{
		printf("Invaild password\n");
	}
}
