//gcc sql.c `mysql_config --cflags --libs`

#include<stdio.h>
#include<mysql/mysql.h>
#include<string.h>

int main()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW *row;
	char *server="localhost";
	char user[20];
	char password[20];
	char database[20];
	printf("Enter username,password,database\n");
	scanf("%s%s%s",user,password,database);
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	int i,flag;
	char table[50];
	char statement[1000];
	char values[50];
	char query[100];
	while(1)
	{
		flag=0;
		//printf("%s ssscscs\n",database);
		if(strcmp(database,"ENROLLMENT")==0)
			printf("Enter the operation number:1)Read 2)Write 3)Get timetable of a given COURSENO 4)Change database 5)Query\n");
		else if(strcmp(database,"UNIVERSITY")==0)	
			printf("Enter the operation number:1)Read 2)Write 3)Courses enrolled by a student in a sem 4)Change database 5)Query\n");
		else
			printf("Enter the operation number:1)Read 2)Write 4)Change database 5)Query\n");
		scanf("%d",&i);
		switch(i)
		{
			case(1):
						printf("Enter table\n");
						scanf("%s",table);
						snprintf(statement,1000,"select * from %s",table);
						if (mysql_query(conn,statement)) 
						{
      						fprintf(stderr, "%s\n", mysql_error(conn));
      						exit(1);
   						}
						res = mysql_use_result(conn);
						unsigned long *lengths;
						unsigned int num_fields;
						while ((row = mysql_fetch_row(res)) != NULL)
						{
							num_fields = mysql_num_fields(res);
    						lengths = mysql_fetch_lengths(res);
    						for(i = 0; i < num_fields; i++)
    						{
							printf("%s\t\t",row[i]);
    						}
							printf("\n");
										
						}
						break;
			case(2):
						printf("Enter table,values\n");
						scanf("%s%s",table,values);
						//printf("%s",values);
						snprintf(statement,1000,"Insert into %s values (%s)",table,values);
					//	printf("%s\n",statement );
						if (mysql_query(conn,statement)) 
						{
      						fprintf(stderr, "%s\n", mysql_error(conn));
      						exit(1);
   						}
						break;
			case(3):	if(strcmp(database,"ENROLLMENT")==0)
						{
							char cno[50];
							printf("enter COURSE NO\n");
							scanf("%s",cno);
							snprintf(statement,1000,"select * from TIMETABLE WHERE CNO='%s' ",cno);
							if (mysql_query(conn,statement)) 
						{
      						fprintf(stderr, "%s\n", mysql_error(conn));
      						exit(1);
   						}
						res = mysql_use_result(conn);
						while ((row = mysql_fetch_row(res)) != NULL)
						{
							num_fields = mysql_num_fields(res);
    						lengths = mysql_fetch_lengths(res);
    						for(i = 0; i < num_fields; i++)
    						{
							printf("%s\t\t",row[i]);
    						}
							printf("\n");
										
						}

						}
						else if(strcmp(database,"UNIVERSITY")==0)	
						{
							
							char sem[50],student[50];
							printf("enter student name,sem\n");
							scanf("%s%s",sem,student);
							printf("%s,%s",sem,student);
							
							snprintf(statement,1000,"select * from student s join takes t on t.id=s.id WHERE s.name='%s' AND t.semester='%s'",sem,student);
							printf("%s\n",statement );
							if (mysql_query(conn,statement)) 
							{
      						fprintf(stderr, "%s\n", mysql_error(conn));
      						exit(1);
   							}
						res = mysql_use_result(conn);
						while ((row = mysql_fetch_row(res)) != NULL)
						{
							num_fields = mysql_num_fields(res);
    						lengths = mysql_fetch_lengths(res);
    						printf("s dfhjklj h\n");
    						for(i = 0; i < num_fields; i++)
    						{
							printf("%s\t\t",row[i]);
    						}
							printf("\n");
										
						}
					}
						else
							flag=1;
						break;
			case(4):
						printf("Enter database\n");
						scanf("%s",database);
						conn = mysql_init(NULL);
						if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) 
						{
							fprintf(stderr, "%s\n", mysql_error(conn));
							exit(1);
						}
						break;
			case(5):
						printf("Enter Query in SQL syntax(including semicolon)\n");
						getchar();
						gets(query);
						//printf("%s",query);
						snprintf(statement,1000,"%s",query);
						if (mysql_query(conn,statement)) 
						{
      						fprintf(stderr, "%s\n", mysql_error(conn));
      						exit(1);
   						}
   						res = mysql_use_result(conn);
						while ((row = mysql_fetch_row(res)) != NULL)
						{
							num_fields = mysql_num_fields(res);
    						lengths = mysql_fetch_lengths(res);
    						for(i = 0; i < num_fields; i++)
    						{
							printf("%s\t\t",row[i]);
    						}
							printf("\n");
										
						}
						break;

			default:
						flag=1;
						break;
		}
		if(flag==1)
			break;
	}

	//mysql_free_result(res);
	mysql_close(conn);
	return(0);
}