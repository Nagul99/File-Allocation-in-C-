#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
char *buffer[500]; //Memory created-500 bytes
int s_b[10][2],empty[10]; //Stores size and number of blocks
int mem=500; //keeps track of free memory
char *block[10]; //store address of the blocks
int *address[10]; //stores address of files
char name[10][30]; //stores name of the file
void create() //to create a file
{
char fname[30],c;
int size=1,i;
printf("Enter .txt file name\n");
scanf("%s",fname);;
FILE *inputf;
inputf = fopen(fname,"r");
if (inputf == NULL)
{
printf("\nFile unable to open ");
exit(0);
}
rewind(inputf);
c=fgetc(inputf);
while(c!=EOF)
{
c=fgetc(inputf);
size=size+1;
}
printf("The size of given file is : %d\n", size);
if(mem>=size)
{
int n=1,parts=0,m=1;
while(address[n]!=0)
n++;
strcpy(name[n],fname);
s_b[n][1]=size;
int bnum=size/50;
if(size%50!=0)
bnum=bnum+1;
s_b[n][2]=bnum;
mem=mem-(bnum*50);
int *bfile=(int*)malloc(bnum*(sizeof(int)));
address[n]=bfile;
printf("Number of blocks required: %d\n",bnum);
rewind(inputf);
c = fgetc(inputf);
while(parts!=bnum && c!=EOF)
{
int k=0;
if(empty[m]==0)
{
char *temp=block[m];
while(k!=50)
{
*temp=c;
c=fgetc(inputf);
temp++;
k=k+1;
}
*(bfile+parts)=m;
parts=parts+1;
empty[m]=1;
}
else
m=m+1;
}
printf("File created\n");
printf("\n");
fclose(inputf);
}
else
printf("Not enough memory\n");
}

int filenum(char fname[30])
{
int i=1,fnum=0;
while(name[i])
{
if(strcmp(name[i], fname) == 0)
{
fnum=i;
break;
}
i++;
}
return fnum;
}
void blocks()
{
int i;
printf(" Block address empty/free\n");
for(i=1;i<=10;i++)
printf("%d. %d - %d\n",i,block[i],empty[i]);
printf("\n");
}
void file()
{
int i=1;
printf("File name size address\n");
for(i=1;i<=10;i++)
{
if(address[i]!=0)
printf("%s %d %d\n",name[i],s_b[i][1],address[i]);
}
printf("\n");
}
void print()
{
char fname[30];
int i=1,j,k,fnum=0;
printf("Enter the file name: ");
scanf("%s",fname);
fnum=filenum(fname);
if(fnum!=0&& address[fnum]!=0)
{
int *temp;
temp=address[fnum];
printf("Content of the file %s is:\n",name[fnum]);
int b=(s_b[fnum][2]);
for(j=0;j<b;j++)
{
int s=*(temp+j);
char *prt=block[s];
for(k=0;k<50;k++)
{
printf("%c",*prt);
prt++;
}
}
printf("\n");
printf("\n");
}
else
printf("File not available:/n");
}
void remove1()
{
char fname[30];
int i=1,j,k,fnum=0;
printf("Enter the file name: ");
scanf("%s",fname);
fnum=filenum(fname);
if(fnum==0)
printf("File not available:/n");
else
{
int *temp=address[fnum];
int b=(s_b[fnum][2]);
mem=mem+b*50;
for(j=0;j<b;j++)
{
int s=*(temp+j);
empty[s]=0;
}
address[fnum]=0;
}
printf("\n");
}
int main()
{
int choice,i;
char *temp;
if (buffer == NULL)
{
fputs ("Memory error",stderr);
exit (2);
}
temp=buffer;
block[1]=buffer;
empty[1]=0;
for(i=2;i<=10;i++)
{
block[i]=block[i-1]+50;
empty[i]=0;
}
while(1)
{
printf("1.Create a new file\n");
printf("2.Delete a file\n");
printf("3.Print a file \n");
printf("4.Display FAT table\n");
printf("5.Display Block Details\n");
printf("6.Exit.\n");
printf("Enter your choice: ");
scanf("%d",&choice);
switch(choice)
{
case 1:
create();
break;
case 2:
remove1();
break;
case 3:
print();
break;
case 4:
file();
break;
case 5:
blocks();
break;
case 6:
exit(1);
}
}
return 0;
}
