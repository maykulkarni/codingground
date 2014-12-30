#include<stdio.h>

#include<conio.h>

#include<string.h>

#include<stdlib.h>

FILE *mp,*ip,*tp;

char POT[][7]={“START”,”END”,”LTORG”,”EQU”,”ORIGIN”};

char MOT[][6]={“MOVER”,”MOVEM”,”ADD”,”SUB”,”MUL”,”DIV”};

char reg[][5]={“AREG”,”BREG”,”CREG”,”DREG”};

char declstat[][3]={“DC”,”DS”};

 

typedef struct symbol

{

int symbol_no;

char symbol_name[10];

int symbol_addr;

}symbol;

 

typedef struct litral

{

int litral_no;

char litral_name[10];

int litral_addr;

}litral;

 

symbol s[10];

litral l[10];

pooltable[6];

void generate_mc();

void accept();

 

void main()

{

int ch;

char chr;

clrscr();

do

{

printf(“\n\tMENU”);

printf(“\n1.view intermediate code”);

printf(“\n2.generate machine code”);

printf(“\n4.exit”);

printf(“\n\nenter your choice:”);

scanf(“%d”,&ch);

switch(ch)

{

case 1:  ip=fopen(“ir.txt”,”r”);

while(!feof(ip))

{

chr=fgetc(ip);

printf(“%c”,chr);

}

break;

 

case 2: accept();

generate_mc();

printf(“generated machine code:\n\n”);

mp=fopen(“mc.txt”,”r”);

while(!feof(mp))

{

chr=getc(mp);

printf(“%c”,chr);

}

fclose(mp);

break;

}

}while(ch!=4);

getch();

}

int lp=0,sp=0,lc,ptb;

int sn,ln,pn;

void accept()

{

int i;

printf(“\nenter the no of symbols:”);

scanf(“%d”,&sn);

printf(“\n\nsymbol table contents”);

printf(“\nenter the contents of symbol table”);

printf(“\nsym_name addr\n”);

for(i=1;i<=sn;i++)

{

scanf(“%s%d”,&s[i].symbol_name,&s[i].symbol_addr);

s[i].symbol_no=i;

}

printf(“\nenter the no of literals:”);

scanf(“%d”,&ln);

printf(“\n\nliteral table contents”);

printf(“\nenter the contents of literal table”);

printf(“\nliteral_name addr\n”);

for(i=1;i<=ln;i++)

{

scanf(“%s%d”,&l[i].litral_name,&l[i].litral_addr);

l[i].litral_no=i;

}

printf(“\nenter the contents of pool table”);

printf(“\nenter the no of pools:”);

scanf(“%d”,&pn);

printf(“\nenter the literal no in sequence:\n”);

for(i=1;i<=pn;i++)

{

scanf(“%d”,pooltable[i]);

}

}

void generate_mc()

{

char buffer[80],tok1[10],tok2[10],tok3[10],tok4[10],tok5[10];

int n,x,i;

int temp;

ip=fopen(“ir.txt”,”r”);

mp=fopen(“mc.txt”,”w”);

 

while(fgets(buffer,80,ip))

{

n=sscanf(buffer,”%s%s%s%s%s”,tok1,tok2,tok3,tok4,tok5);

switch(n)

{

case 2: lc=0;

break;

case 3:  //ltorg

fprintf(mp,”00 – 00%s\n”,tok3);

break;

case 4: //start with const.

if(strcmp(tok2,”01″)==0)

{

x=atoi(tok4);

lc=x;

}

if(strcmp(tok2,”05″)==0)

{

temp=atoi(tok4);

fprintf(mp,”00 – 00%s\n”,tok4);

}

if(strcmp(tok2,”06″)==0)

{

temp=atoi(tok4);

for(i=0;i<temp;i++)

fprintf(mp,”00\n”);

}

break;

case 5:  //imperative statements

if(strcmp(tok4,”S”)==0)

{

temp=atoi(tok5);

fprintf(mp,”%s %s %d\n”,tok2,tok3,s[temp].symbol_addr);

}

if(strcmp(tok4,”L”)==0)

{

temp=atoi(tok5);

fprintf(mp,”%s %s %d\n”,tok2,tok3,l[temp].litral_addr);

}

break;

} //switch

} //while

fclose(ip);

fclose(mp);

}