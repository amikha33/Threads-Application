#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<pthread.h>
#include <time.h>
int row , row2, column, column2,xx,yy;
int twoArray[20][20];
int twoArray_2[20][20];
int resultRow;
int sumRow;
int resultColumn;
int resultArr[20][20];
int columnArrayCopy[25];
int rowArrayCopy[25];
int firstArr[25];
int sizeThreads;
int elementMove,sizeThreadsCell;
void *multiplyCell(void* param);
void *multiplyRow(void *param);
void main()
{
   clock_t start_t, end_t; float total_t;
   clock_t start_t2, end_t2; float total_t2;
    pthread_t *threadPointer;

    FILE* file = fopen ("input.txt", "r");
    int i = 0;
    int integerArr[50];
    int count =0;
    fscanf (file, "%d", &i);
    while (!feof (file))

    {
        integerArr[count]=i;
       // printf ("%d\t",  integerArr[count]);
        fscanf (file, "%d", &i);

        count ++;
    }
    fclose (file);
    int rowOfMatrixOne =integerArr[0];
   // printf("%d -> row \n",rowOfMatrixOne);
    int columnsOfMatrixOne =integerArr[1];
   // printf("%d -> Columns\n",columnsOfMatrixOne);
    int lengthMatrix= (columnsOfMatrixOne*rowOfMatrixOne)+1;

    //printf("%d -> Size\n",lengthMatrix);
    for(int loop = 0; loop <lengthMatrix-1; loop++)
    {
        firstArr[loop] = integerArr[loop+2];
        //printf("%d LOOP First MAtrix \t",loop);
       // printf("%d\t", firstArr[loop]);
    }

    int stratMAtrixTwo =lengthMatrix+3;
   // printf("%d -> Start Matrix two Index \n",stratMAtrixTwo);
    int rowOfMatrixTwo=integerArr[stratMAtrixTwo-2];
  //  printf("%d -> row Matrix two \n",rowOfMatrixTwo);
    int columnsofMatrixTwo=integerArr[stratMAtrixTwo-1];
  //  printf("%d -> row Matrix two \n",columnsofMatrixTwo);


    int lengthMatrix2= (columnsofMatrixTwo*rowOfMatrixTwo);

    int secondArr[50];
    int beginL=stratMAtrixTwo;
    //printf("BEGIN MAT 2 : %d\n",beginL);
    int endArrIndex=beginL+lengthMatrix2-1;
    //printf("end MAT 2 : %d\n",endArrIndex);
  // printf("%d len :\n ",lengthMatrix2);
    for(int loop2 = 0; loop2 <lengthMatrix2; loop2++)
    {
        int copyIndex =loop2+beginL;
        secondArr[loop2]=integerArr[copyIndex];
       // printf("   index taken from Array  %d :  %d \n  ", secondArr[loop2],loop2);

    }

   // printf("^^^^^^^^^ 2D ARRAY Matrix 1^^^^^^^^^^\n");
printf("row 2D ->>>>>>>>>%d , %d\n",lengthMatrix,rowOfMatrixOne);
    int  counter = 0;
    for ( row = 0; row < rowOfMatrixOne; row++)
    {
        for ( column  = 0; column <(lengthMatrix-1)/rowOfMatrixOne; column++)
        {

            twoArray[row][column] = firstArr[counter];
             printf("Two D MAT 1 %d %d%d ! \n",twoArray[row][column],row,column);
                                   counter++;
            //printf("Counter%d",counter);


        }



    }

    int counter2 =0;
    for ( row2 = 0; row2 < rowOfMatrixTwo; row2++)
    {
        for ( column2  = 0; column2 <lengthMatrix2/rowOfMatrixTwo; column2++)
        {

            twoArray_2[row2][column2] = secondArr[counter2];
            printf("Two D2 %d %d%d  \n",twoArray_2[row2][column2],row2,column2);
            counter2++;
        }
    }

    resultRow=row;
    resultColumn=column2;
    sizeThreads==resultRow*resultColumn;
   sizeThreadsCell=resultRow*resultColumn;
    pthread_t tid[sizeThreadsCell]; //->12 thread
   // printf("Size %d\n ",sizeThreadsCell);

    	 start_t = clock();


    for( int threadID = 0; threadID < sizeThreadsCell; threadID++)
    {int value =threadID ;
    int *p;
    p=&value;

            pthread_create(&tid[threadID],NULL,multiplyCell,p);}
                for( int threadID = 0; threadID < sizeThreadsCell; threadID++)
{
            pthread_join(tid[threadID], NULL);}


	   end_t = clock();
	   	      total_t = (float)(end_t-start_t) / CLOCKS_PER_SEC;

	      printf("Starting of the program, start_t = %ld\n", start_t);

	      printf("End of the big loop, end_t = %ld\n", end_t);
   printf("Total time taken by CPU: %f\n",total_t);

   printf("\n$$$$$$$$$$$$$$$$$\n");
   	 start_t2= clock();


    for( int threadID = 0; threadID < row; threadID++)
    {int value =threadID ;
    int *p;
    p=&value;

            pthread_create(&tid[threadID],NULL,multiplyRow,p);}
             for( int threadID = 0; threadID < row; threadID++)
    {
            pthread_join(tid[threadID], NULL);
	}

	   end_t2 = clock();
	   	      total_t2 = (float)(end_t2-start_t2) / CLOCKS_PER_SEC;

	      printf("Starting of the program, start_t = %ld\n", start_t2);

	      printf("End of the big loop, end_t = %ld\n", end_t2);
   printf("Total time taken by CPU: %f\n",total_t2);










   }

void *multiplyCell(void * param)
{
    int threadID = *(int *) param;
    int sumCell=0;
    int i =threadID/resultColumn;
    int j=threadID%resultColumn ;


  for ( int k = 0 ; k <column; k++ ){
    printf("Matrix 1 : %d [%d] [%d]\n",twoArray[i][k],i,k);
  printf("Matrix 2  : %d [%d] [%d]\n",twoArray_2[k][j],k,j);
    sumCell= sumCell+twoArray_2[k][j]*twoArray[i][k] ;



}
 FILE *fptr;
   fptr = fopen("output.txt", "a");
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   fprintf(fptr,"\n%d", sumCell);
   fclose(fptr);
        printf("****RESUL : %d ThreadID : %d****\n",sumCell,threadID);


        return NULL;

}
void *multiplyRow(void * param){
int multiplyCell,i,j;
int threadIDrow = *(int *) param;
for (  i= 0 ; i<column2; i++ ){
  for (  j= 0 ; j<row2; j++ ){
      multiplyCell=twoArray[threadIDrow][j]*twoArray_2[j][i];

}
FILE *fptr;
   fptr = fopen("output_2.txt", "a");
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   fprintf(fptr,"\n%d", multiplyCell);
   fclose(fptr);

} return NULL;
}
