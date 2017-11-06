#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>
#include <time.h>
#include <stdlib.h>

void main_reason(char* log, int main_number); 	//write main activity (ex, shutdown, restart)
//void write_comment(char* log, char* comment, char* user_comment); 	//write the reason why shutdown the computer
void write_time_info();		//write time info
void write_log_info();		//write all log to file

char LOGFILENAME[20] = "server_control_log";
//char system_chmod[20] = "chmod 644 ";
//char system_chown[20] = "chown root.root ";

int main()
{
	int main_number = 0;
	char log[100] = {0};
	char user_comment[100] = {0};
	char comment[10] = "comment:[";
	char system_chmod[20] = "chmod 644 ";	
	char system_chown[20] = "chown root.root ";

	write_time_info(log);

	printf("Select the main activity pls\n");
	printf("1. Server SHUTDOWN\n");
	printf("2. Server RESTART\n");
	scanf("%d",&main_number);

	main_reason(log, main_number);

	printf("Write Comment : ");
	__fpurge(stdin);
	scanf("%[^\n]s", user_comment);

	strcat(log,comment);
	strcat(log,user_comment);
	strcat(log,"]");

	write_log_info(log);
	strcat(system_chmod,LOGFILENAME);
	system(system_chmod);

	strcat(system_chown,LOGFILENAME);
	system(system_chown);

	return 0;
}

void write_time_info()
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

void main_reason(char* log, int main_number)
{
	char shutdown[] = "SHUTDOWN ";
	char restart[] = "RESTART  ";
	FILE* f;	

	if(main_number == 1)
	{
		strcat(log,shutdown);
	}
	else if(main_number == 2)
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
/*
char* write_comment(char* log, char* comment, char* user_comment)
{
	char for_write[100] = {0};
	strcat(log,comment);
	strcat(log,user_comment);
	strcat(log,"]");
}
*/
void write_log_info(char* log)
{
	FILE* f;
	f = fopen(LOGFILENAME,"a");
	fprintf(f, "%s\n", log);
	fclose(f);
}
