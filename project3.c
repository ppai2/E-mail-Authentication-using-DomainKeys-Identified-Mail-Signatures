#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
/*
References: http://www.tutorialspoint.com/c_standard_library/c_function_system.htm
https://www.openssl.org/docs/apps/dgst.html
http://stackoverflow.com/questions/2774408/openssl-sign-sha1-a-message-and-make-s-mime
http://stackoverflow.com/questions/5244129/use-rsa-private-key-to-generate-public-key
*/

void SHA1();
void SHA256();
uint total_timetakensigning[11], total_timetakenverifying[11],total_timetakensigning2[11], total_timetakenverifying2[11];
int main(int argc, char* argv[])
{
	int i;
	for (i = 0; i < 5; ++i)
	{
			SHA1();
			SHA256();
	}
	printf("SHA1 signing 		SHA1 verifying 		SHA256 signing 		SHA256 verifying\n");
	for (i = 1; i <= 10; i++)
	{
		printf("%d			%d	 		%d	 		%d\n",total_timetakensigning[i]/5, total_timetakenverifying[i]/5 ,total_timetakensigning2[i]/5, total_timetakenverifying2[i]/5 );
	}
	return 0;
}
void SHA1()
{
	struct timeval start, end;
	int i;
	for (i = 1; i <= 10; i++)
	{
		char command[1024];
		sprintf(command, "openssl sha1 -sign /home/krishna/COMP_SEC/Comp_sec_project_3/rsaprivatekey1024.pem -out /home/krishna/COMP_SEC/Comp_sec_project_3/Output/file%d /home/krishna/COMP_SEC/Comp_sec_project_3/Mail/msg.%d.eml",i,i);	
		gettimeofday(&start,NULL);
		system(command);
		gettimeofday(&end, NULL);
		total_timetakensigning[i]= total_timetakensigning[i] + ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec))/1000;
	}
	for (i = 1; i <=10; i++)
	{
		char command2[1024];
		sprintf(command2, "openssl sha1 -verify /home/krishna/COMP_SEC/Comp_sec_project_3/rsapublickey1024.pem -signature /home/krishna/COMP_SEC/Comp_sec_project_3/Output/file%d /home/krishna/COMP_SEC/Comp_sec_project_3/Mail/msg.%d.eml",i,i);
		gettimeofday(&start,NULL);
		system(command2);
		gettimeofday(&end, NULL);
		total_timetakenverifying[i]= total_timetakenverifying[i] + ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec))/1000;
	}
}
void SHA256()
{
	struct timeval start, end;	
	int i;
	for (i = 1; i <= 10; i++)
	{
		char command[1024];
		sprintf(command, "openssl sha256 -sign /home/krishna/COMP_SEC/Comp_sec_project_3/rsaprivatekey1024.pem -out /home/krishna/COMP_SEC/Comp_sec_project_3/Output/file%d /home/krishna/COMP_SEC/Comp_sec_project_3/Mail/msg.%d.eml",i,i);
		gettimeofday(&start,NULL);
		system(command);
		gettimeofday(&end, NULL);
		total_timetakensigning2[i] = total_timetakensigning2[i] + ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec))/1000;
	}

	for (i = 1; i <= 10; i++)
	{
		char command2[1024];
		sprintf(command2, "openssl sha256 -verify /home/krishna/COMP_SEC/Comp_sec_project_3/rsapublickey1024.pem -signature /home/krishna/COMP_SEC/Comp_sec_project_3/Output/file%d /home/krishna/COMP_SEC/Comp_sec_project_3/Mail/msg.%d.eml",i,i);
		gettimeofday(&start,NULL);
		system(command2);
		gettimeofday(&end, NULL);
		total_timetakenverifying2[i]= total_timetakenverifying2[i] + ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec))/1000;
	}
}