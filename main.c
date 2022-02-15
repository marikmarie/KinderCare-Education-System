#include<stdio.h>
#include<mysql.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>
MYSQL *getConnection();
void printWelcome();
void availableCommands();
void viewAll(MYSQL *, char *);
//void checkStatus(MYSQL *, char *)
void checkDates(MYSQL *con, char *, char *, char *);
void viewAssignment(MYSQL *, char *, char *);
void requestActivation(char *userId, MYSQL *conn);
char *commandPrompt();
int isActivated(MYSQL*,char*);
void compareCommand(char *);
void printCharacter(int array[7][5]);
float attemptCharacter(char, int pupilCharacters[7][5]);
float gradeCharacter(int correctCharacter[7][5], int pupilCharacters[7][5]);

float timer(clock_t starTime, clock_t endTime){
    float time = 0;
    time =(float) ((endTime - starTime)/CLOCKS_PER_SEC);
    return time;
}

void currentDate(char*date){
        time_t t= time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(date,"%d-%02d-%02d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
}
// Characters
int A[7][5] = {{0,1,1,0,0}, {1,0,0,1,0}, {1,0,0,1,0}, {1,1,1,1,0}, {1,0,0,1,0},  {1,0,0,1,0}, {1,0,0,1,0} };

int B[7][5] = {{1,1,1,1,0}, {1,0,0,0,1}, {1,0,0,1,0}, {1,0,1,0,0}, {1,0,0,1,0},  {1,0,0,0,1}, {1,1,1,1,0} };

int C[7][5] = {{0,1,1,1,1}, {1,0,0,0,0}, {1,0,0,0,0}, {1,0,0,0,0}, {1,0,0,0,0},  {1,0,0,0,0}, {0,1,1,1,1} };

int D[7][5] = {{1,1,1,1,0}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1},  {1,0,0,0,1}, {1,1,1,1,0} };

int E[7][5] = {{1,1,1,1,1}, {1,0,0,0,0}, {1,0,0,0,0}, {1,1,1,1,0}, {1,0,0,0,0},  {1,0,0,0,0}, {1,1,1,1,1} };

int F[7][5] = {{1,1,1,1,1}, {1,0,0,0,0}, {1,0,0,0,0}, {1,1,1,1,0}, {1,0,0,0,0},  {1,0,0,0,0}, {1,0,0,0,0} };

int G[7][5] = {{0,1,1,1,1}, {1,0,0,0,1}, {1,0,0,0,0}, {1,0,0,0,0}, {1,0,0,1,1},  {1,0,0,0,1}, {0,1,1,1,1} };

int H[7][5] = {{1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1},  {1,0,0,0,1}, {1,0,0,0,1} };

int I[7][5] = {{0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0},  {0,0,1,0,0}, {0,0,1,0,0} };

int J[7][5] = {{1,1,1,1,1}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0},  {1,0,1,0,0}, {1,1,1,0,0} };

int K[7][5] = {{1,0,0,0,1}, {1,0,0,1,0}, {1,0,1,0,0}, {1,1,0,0,0}, {1,0,1,0,0},  {1,0,0,1,0}, {1,0,0,0,1} };

int L[7][5] = {{1,0,0,0,0}, {1,0,0,0,0}, {1,0,0,0,0}, {1,0,0,0,0}, {1,0,0,0,0},  {1,0,0,0,0}, {1,0,0,0,0} };

int M[7][5] = {{1,0,0,0,1}, {1,1,0,1,1}, {1,0,1,0,1}, {1,0,0,0,1}, {1,0,0,0,1},  {1,0,0,0,1}, {1,0,0,0,1} };

int N[7][5] = {{1,0,0,0,1}, {}, {}, {}, {},  {}, {1,0,0,0,1} };

int O[7][5] = {{0,1,1,1,0}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1},  {1,0,0,0,1}, {0,1,1,1,0} };

int P[7][5] = {{1,1,1,1,0}, {1,0,0,0,1}, {1,0,0,0,1}, {1,1,1,1,0}, {1,0,0,0,0},  {1,0,0,0,0}, {1,0,0,0,0} };

int Q[7][5] = {{0,1,1,1,0}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1},  {1,0,0,1,1}, {0,1,1,1,1} };

int R[7][5] = {{1,1,1,1,0}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,1,1,0}, {1,0,1,1,0},  {1,0,0,1,0}, {1,0,0,0,1} };

int S[7][5] = {{0,1,1,1,0}, {1,0,0,0,1}, {1,0,0,0,0}, {0,1,0,0,0}, {0,0,1,1,0},  {1,0,0,0,1}, {0,1,1,1,1} };

int T[7][5] = {{1,1,1,1,1}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0},  {0,0,1,0,0}, {0,0,1,0,0} };

int U[7][5] = {{1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1},  {1,0,0,0,1}, {0,1,1,1,0} };

int V[7][5] = {{1,0,0,0,1}, {}, {}, {}, {},  {}, {} };

int W[7][5] = {{1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,1,0,1},  {1,1,0,1,1}, {1,0,0,0,1} };

int X[7][5] = {{1,0,0,0,1}, {0,0,0,0,0}, {}, {0,0,1,0,0}, {},  {0,0,0,0,0}, {1,0,0,0,1} };

int Y[7][5] = {{1,0,0,0,1}, {0,1,0,1,0}, {0,0,0,0,0}, {0,0,1,0,0}, {0,0,1,0,0},  {0,0,1,0,0}, {0,0,1,0,0} };

int Z[7][5] = {{1,1,1,1,1}, {0,0,0,0,0}, {0,0,0,1,0}, {0,0,0,0,0}, {0,1,0,0,0},  {0,0,0,0,0}, {1,1,1,1,1} };

void main()
{
    // Mysql variables
    MYSQL *con;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char date[50];
    currentDate(date);
    // user information variables for session tracking
    char userId[50];
    char firstName[50];
    char lastName[50];
    char userCode[20];
    char status[50];
    char phoneNumber[30];
    int loop = 1;

    while (loop)
    {
        // Get user information..
        printWelcome();
        printf("\n \t Enter Usercode: ");
        scanf("%s", userCode);

        // Connect to the database..
        con = mysql_init(NULL);
        con = getConnection();

        // Login in the system..
        char query[255];
        sprintf(query, "SELECT * FROM pupil WHERE userCode='%s'", userCode);

        // Run query and see, if it returns a non zero value, it means connection has failed..
        if (mysql_query(con, query) != 0)
        {
            printf("Query failed  with the following message:\n");
            printf("%s\n", mysql_error(con));
            exit(1);
        }

        // Query successful now check if the user exists
        result = mysql_store_result(con);

        int total = (int)mysql_num_rows(result);
        if (total == 0)
        {
            printf("Wrong Usercode, retry!!\n");
        }
        else
        {
            printf("\nLogged in successfully\n");

            while ((row = mysql_fetch_row(result)) != NULL)
            {
                strcpy(userId, (char *)row[0]);
                strcpy(firstName, (char *)row[1]);
                strcpy(lastName, (char *)row[2]);
                //strcpy(status, (char *)row[5]);
            }

            printf("\nDate: %s \tWelcome, You are logged in as %s %s\n",date, firstName, lastName);

            availableCommands();

            char command[255];
        cmd:
            printf("Enter Command:\t ");
            fflush(stdin);

            scanf("%s", command);
            // Process command
            if (strcmp("Viewall", command) == 0)
            {
                viewAll(con, userId);
                goto cmd;
            }
            else if (strcmp("Checkstatus", command) == 0)
            {
                checkStatus(con,userId);
                goto cmd;
            }
            else if (strcmp("Viewassignment", command) == 0)
            {
                char assinmentId[50];
                scanf("%s", assinmentId);
                viewAssignment(con, assinmentId, userId);
                goto cmd;
            }
            else if (strncmp("Checkdates", command, 10) == 0)
            {
                char fromDate[50];
                char toDate[50];
                scanf("%s", fromDate);
                scanf("%s", toDate);
                checkDates(con, fromDate, toDate, userId);
                goto cmd;
            }
            else if (strcmp("RequestActivation", command) == 0)
            {
                printf("\nRequesting Activation...\n");
                requestActivation(userId, con);
                printf("\nActivation Request Sent!\n");
                goto cmd;
            }
            else if (strcmp("Logout", command) == 0)
            {
                printf("Logged out!\n\n");
                exit(0);
            }
            else
            {
                printf("\nSorry Command %s is unrecognized\n", command);
                goto cmd;
            }
        }
    }
    printf("Re enter command please!!");
}
//getting connection to the database..
MYSQL *getConnection()
{
    MYSQL *con;
    con = mysql_init(NULL);

    if (mysql_real_connect(con, "127.0.0.1", "root", "", "recess", 0, NULL, 0) == NULL)
    {
        printf("The authentication failed with the following message:\n");
        printf("%s\n", mysql_error(con));
        exit(1);
    }
    return con;
}

void requestActivation(char *userId, MYSQL *conn)
{
    char query[255];
    sprintf(query, "UPDATE `pupil` SET `activation_request` = '1' WHERE `pupil`.`id` = '%s'", userId);
    mysql_query(conn, query);
}

void viewAll(MYSQL *con, char *pupil_id)
{
    MYSQL_ROW row;
    MYSQL_RES *result;
    MYSQL_RES *result1;
    char query[255];
    strcpy(query, "SELECT * FROM assignments");
    mysql_query(con, query);
    result = mysql_store_result(con);
    printf("\n%5s\t%10s\t%22s\t%22s\t%10s\n", "ID", "Assignment", "Start(Date Time)", "Due Time", "Attempt");
    printf("\n------------------------------------------------------------------------------------------------\n");
    int count = 0;
    int attempted = 0;
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        // Ckeck if attempted
        sprintf(query, "SELECT * FROM `marks` WHERE assignment_id='%s' AND pupil_id='%s';", row[0], pupil_id);
        mysql_query(con, query);
        result1 = mysql_store_result(con);
        int total = (int)mysql_num_rows(result1);
        if (total > 0)
        {
            attempted++;
            printf("\n%2s\t%10s\t%10s %10s\t%20s\t%10s\n", row[0], row[1], row[3], row[4], row[5], "Attempted");
        }
        else
        {
            printf("\n%2s\t%10s\t%10s %10s\t%20s\t%10s\n", row[0], row[1], row[3], row[4], row[5], "No Attempt");
        }
        count++;
    }
    printf("\n_________________________________________________________________________________________________\n");
    printf("\t\tSummary\n\t \tTotal assignments:%d \n\t\tTotal Attempted: %d\n", count, attempted);
    printf("\n------------------------------------------------------------------------------------------------\n");
}
void checkStatus(MYSQL *con, char *pupil_id){
    MYSQL_RES *result;
    MYSQL_ROW row;
    float totalMarks=0;
    int totalAssignments = 0;
    char query[255];
    sprintf(query,"SELECT assignment_id,assignments.name,marks,marks.comment FROM pupil INNER JOIN marks ON pupil.id = marks.pupil_id INNER JOIN assignments ON assignments.id = marks.assignment_id WHERE pupil.id =%s",pupil_id);
    mysql_query(con,query);
    result = mysql_store_result(con);
    printf("\n%10s%20s\t%10s\t%s\n","ID","Assignment","Mark(/100%)","Comment");
    while((row = mysql_fetch_row(result))!=NULL){
            printf("\n%10s%20s\t%8s%2s\t%s\n\n",row[0],row[1],row[2],"%",row[3]);
            totalAssignments++;
    }
    sprintf(query,"SELECT ROUND(AVG(marks),2) FROM pupil INNER JOIN marks ON pupil.id = marks.pupil_id INNER JOIN assignments ON assignments.id = marks.assignment_id WHERE pupil.id =%s GROUP BY pupil.id",pupil_id);
    mysql_query(con,query);
    result = mysql_store_result(con);

    printf("\n\t\t----------------Summary--------------------");
    printf("\n\t\tTotal assignments: %d \n",totalAssignments);
    while((row = mysql_fetch_row(result))!=NULL){
            printf("\n\t\tMean Mark: %4s %s",row[0],"%");
            printf("\n\n\t\t---------------------------------------\n\n\n");
            break;
    }
}
void checkDates(MYSQL *con, char *dateFrom, char *dateTo, char *pupil_id)
{
    MYSQL_ROW row;
    MYSQL_RES *result;
    MYSQL_RES *result1;
    char query[255];
    sprintf(query, "SELECT * FROM assignments WHERE dateOfAttempt>='%s' AND dateOfAttempt<='%s'", dateFrom, dateTo);
    printf("\n----------------------------------------------------------------------------------------------------\n");
    printf("\tViewing assignments between %s and %s",dateFrom,dateTo);
    printf("\n----------------------------------------------------------------------------------------------------\n");
    mysql_query(con, query);
    result = mysql_store_result(con);
    printf("\n%5s\t%10s\t%22s\t%22s\t%10s\n", "ID", "Assignment", "Start(Date Time)", "Due(Date Time)", "Attempt");
    printf("\n------------------------------------------------------------------------------------------------\n");
    int count = 0;
    int attempted = 0;
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        // Ckeck if attempted
        sprintf(query, "SELECT * FROM `marks` WHERE assignment_id='%s' AND pupil_id='%s';", row[0], pupil_id);
        mysql_query(con, query);
        result1 = mysql_store_result(con);
        int total = (int)mysql_num_rows(result1);
        if (total > 0)
        {
            attempted++;
            printf("\n%2s\t%10s\t%10s %10s\t%20s\t%10s\n", row[0], row[1], row[3], row[4], row[5], "Attempted");
        }
        else
        {
            printf("\n%2s\t%10s\t%10s %10s\t%20s\t%10s\n", row[0], row[1], row[3], row[4], row[5], "No Attempt");
        }

        count++;
    }
    printf("\tSummary\n\t Total assignments:%d \n\tTotal Attempted: %d\n", count, attempted);
    printf("\n------------------------------------------------------------------------------------------------\n");
}
//void checkStatus (MYSQL *con, char *, char *){}
void viewAssignment(MYSQL *con, char *assignmentId, char *pupil_id)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[255];
    char characters[8];
    float times[8];
    float grades[8];
    char today[50];
    currentDate(today);
    clock_t startTime,endTime;

    float totalGrade,avgGrade,totalTime;
    int pupilCharacters[8][7][5];
    int totalCharacters = 0;

    //Check if pupil is activated
    int available = 0;
    if(isActivated(con,pupil_id)){
    sprintf(query, "SELECT * FROM assignments WHERE id='%s' AND dateOfAttempt='%s'", assignmentId,today);
    mysql_query(con, query);
    result = mysql_store_result(con);
    printf("\n\n-------------------------------------------\n\n");
    //Check if pupil has at least attempted the assignment
    if(isAttempted(con,assignmentId,pupil_id)){
        printf("\n\tIt seems you attempted this assignment\n\t .\n ");
        printf("\n\n-------------------------------------------\n\n");
        return;
    }
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        available=1;
        totalCharacters = (int)strlen(row[2]);
        strcpy(characters, row[2]);

        printf("\n\tId:\t %s \n",row[0]);
        printf("\n\tAssignment: %s\n",row[1]);
        printf("\n\tCharacters: %d Character(s)\n",totalCharacters);
        printf("\n\tStart Date: %s\n",row[3]);
        printf("\n\tStart Time: %s\n",row[4]);
        printf("\n\tEnd Time: %s\n\n",row[5]);
        printf("\n\n-------------------------------------------\n\n");

    }
    if(available==0){
        printf("\n\tSorry the assignment NOT AVAILABLE for Attempting\n\t\n ");
    printf("\n\n-------------------------------------------\n\n");
    return;
    }

    int choice;
    printf("\tEnter \n\t 1. To attempt\n\t 2. To Continue\n\t :");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int columns = 5;
        int rows = 7;
        int i;
    attempt:

        for (i = 0; i < totalCharacters; i++)
        {

            printf("\n\n-------------------Attempting: %c-------------------\n", characters[i]);
            startTime = clock();

            for (int i1 = 0; i1 < rows; i1++)
            {
                for (int j = 0; j < columns; j++)
                {
                    printf("Cell [%d,%d]: ", i1 + 1, j + 1);
                    scanf("%d", &pupilCharacters[i][i1][j]);

                }
            }
            endTime = clock();
            times[i] = timer(startTime,endTime);
            totalTime += times[i];
            grades[i] = attemptCharacter(characters[i], pupilCharacters[i]);
            totalGrade += grades[i];
        }
        avgGrade = totalGrade/i;
        //Time taken..
        printf("Time taken : %d seconds\n\n ");
        printf("\n-------------------------------------------------------------------\n");
        printf("\n-------------------Attempt Summary------------------------------\n");
        for (int i = 0; i < totalCharacters; i++)
        {
            printf("\n---------------------Character: %c ------------------------\n", characters[i]);
            printf("\n\nRepresentation\n");
            printCharacter(pupilCharacters[i]);
            printf("\n\nGrade: %.2f %s\n\\n", grades[i], "%");
            printf("\nTime Taken: %.2f seconds\n",times[i]);
            printf("\n----------------------------------------------------------------\n");
        }
        printf("-------------- Final Grade summary---------------------\n");
        printf("\n\tFinal Grade: %.2f %s\n",avgGrade,"%");
        printf("\n\tTotal time Taken: %f seconds\n",totalTime);

        int choice1 = 0;
        char date[100];
        currentDate(date);
        printf("\n\n\tEnter \n\t1. To Submit\n\t2.Re-Attempt\n\t_> ");
        scanf("%d", &choice1);
        switch (choice1)
        {
        case 1:

            sprintf(query,"INSERT INTO marks SET assignment_id='%s', pupil_id='%s', marks ='%.2f', created_at='%s',totalTime='%.2f'",assignmentId,pupil_id,avgGrade,date,totalTime);
            mysql_query(con,query);
            printf("\n---------------Submitted for grading----------------\n\n");
            break;
        case 2:
            goto attempt;
            break;
        default:
            break;
        }
    }
    }
    else{
        printf("\nSorry!, You can't view or attempt this assignment\nReason: You are not Activated.\n\n");
    }

}
int isAttempted(MYSQL *con, char *assignmentId,char *pupilId){
    char query[255];
    MYSQL_RES *result;
    sprintf(query,"SELECT * FROM assignments INNER JOIN marks on assignments.id = assignment_id WHERE marks.assignment_id='%s' AND marks.pupil_id ='%s'",assignmentId,pupilId);
    mysql_query(con,query);
    result = mysql_store_result(con);
    int total = mysql_num_rows(result);
    if(total>=1){
        return 1;
    }
    else{
        return 0;
    }
}
void compareCommand(char *command)
{

    if (strcmp("Viewall", command) == 0)
    {
    }
    else if (strcmp("Checkstatus", command) == 0)
    {
    }
    else if (strcmp("Viewassignment", command) == 0)
    {
    }
    else if (strcmp("Checkdates", command) == 0)
    {
    }
    else if (strcmp("RequestActivation", command) == 0)
    {
    }
    else
    {
    }
}
void printCharacter(int characterMatrix[][5])
{
    char draw[35];

    int i, j, k = 0;

    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 5; j++)
        {
            if(characterMatrix[i][j] == 1 )
                draw[k++] = '*';
            else
                draw[k++] = ' ';
        }
    }

       printf(" ___ ___ ___ ___ ___\n");
       printf("| %c | %c | %c | %c | %c |\n",draw[0],draw[1],draw[2],draw[3],draw[4] );
       printf("|___|___|___|___|___|\n");
       printf("| %c | %c | %c | %c | %c |\n",draw[5],draw[6],draw[7],draw[8],draw[9]);
       printf("|___|___|___|___|___|\n");
       printf("| %c | %c | %c | %c | %c |\n",draw[10],draw[11],draw[12],draw[13], draw[14]);
       printf("|___|___|___|___|___|\n");
       printf("| %c | %c | %c | %c | %c |\n",draw[15],draw[16],draw[17],draw[18], draw[19]);
       printf("|___|___|___|___|___|\n");
       printf("| %c | %c | %c | %c | %c |\n",draw[20],draw[21],draw[22],draw[23], draw[24]);
       printf("|___|___|___|___|___|\n");
       printf("| %c | %c | %c | %c | %c |\n",draw[25],draw[26],draw[27],draw[28], draw[29]);
       printf("|___|___|___|___|___|\n");
       printf("| %c | %c | %c | %c | %c |\n",draw[30],draw[31],draw[32],draw[33], draw[34]);
       printf("|___|___|___|___|___|\n\n");
}

float attemptCharacter(char systemCharacter, int pupilCharacter[7][5])
{
    switch (systemCharacter)
    {
    case 'A':
        return gradeCharacter(A, pupilCharacter);
        break;
    case 'B':
        return gradeCharacter(B, pupilCharacter);
        break;
    case 'C':
        return gradeCharacter(C, pupilCharacter);
        break;
    case 'D':
        return gradeCharacter(D, pupilCharacter);
        break;
    case 'E':
        return gradeCharacter(E, pupilCharacter);
        break;
    case 'F':
        return gradeCharacter(F, pupilCharacter);
        break;
    case 'G':
        return gradeCharacter(G, pupilCharacter);
        break;
    case 'H':
        return gradeCharacter(H, pupilCharacter);
        break;
    case 'I':
        return gradeCharacter(I, pupilCharacter);
        break;
    case 'J':
        return gradeCharacter(J, pupilCharacter);
        break;
    case 'K':
        return gradeCharacter(K, pupilCharacter);
        break;
    case 'L':
        return gradeCharacter(L, pupilCharacter);
        break;
    case 'M':
        return gradeCharacter(M, pupilCharacter);
        break;
    case 'N':
        return gradeCharacter(N, pupilCharacter);
        break;
    case 'O':
        return gradeCharacter(O, pupilCharacter);
        break;
    case 'P':
        return gradeCharacter(P, pupilCharacter);
        break;
    case 'Q':
        return gradeCharacter(Q, pupilCharacter);
        break;
    case 'R':
        return gradeCharacter(R, pupilCharacter);
        break;
    case 'S':
        return gradeCharacter(S, pupilCharacter);
        break;
    case 'T':
        return gradeCharacter(T, pupilCharacter);
        break;
    case 'U':
        return gradeCharacter(U, pupilCharacter);
        break;
    case 'V':
        return gradeCharacter(V, pupilCharacter);
        break;
    case 'W':
        return gradeCharacter(W, pupilCharacter);
        break;
    case 'X':
        return gradeCharacter(X, pupilCharacter);
        break;
    case 'Y':
        return gradeCharacter(Y, pupilCharacter);
        break;
    case 'Z':
        return gradeCharacter(Z, pupilCharacter);
        break;
    }
}
float gradeCharacter(int correctCharacter[7][5], int pupilCharacter[7][5])
{
    int columns = 5;
    int rows = 7;
    int totalCells = columns * rows;
    int correctCells = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (correctCharacter[i][j] == pupilCharacter[i][j])
            {
                correctCells += 1;
            }
        }
    }
    // Calculate the grade
    float grade = ((float)correctCells / totalCells) * 100;
    return grade;
}
int isActivated(MYSQL*con, char *pupilId){
    char query[255];
    MYSQL_RES* result;
    MYSQL_ROW row;
    char status[10];
    sprintf(query,"SELECT * FROM pupil WHERE id='%s'",pupilId);
    mysql_query(con,query);
    result = mysql_store_result(con);
    while((row = mysql_fetch_row(result))!=NULL){
        strcpy(status,row[5]);
        break;
    }
    if(strncmp(status,"1",1)==0){
        return 1;
    }
    else{
        return 0;
    }
}
void printWelcome()
{
    printf("\t\t\t***************************************************\n");
    printf("\t \t\t\tKINDERCARE CHARACTER DRAWING SYSTEM\t\n");
    printf("\t\t\t***************************************************\n");
}
void availableCommands()
{
    printf("\nThe following are the available commands\n");
    printf("\n%20s\t%40s\n", "Command", "Function");
    printf("\n%20s\t%40s\n", "Viewall", "To view your assignments and your attempt history");
    printf("\n%20s\t%40s\n", "Checkstatus", "To view a summary of your attempts, marks, average etc");
    printf("\n%20s\t%40s\n", "Viewassignment", "To see the details of assignment with the given id,enter assignment id.");
    printf("\n%20s\t%40s\n", "Checkdates", "Checkdates dateFrom dateTo To see assignments with in the dates");
    printf("\n%20s\t%40s\n", "RequestActivation", "Request for activation from the teacher");
    printf("\n%20s\t%20s\n", "Logout", "Logout of the system\n");
}
