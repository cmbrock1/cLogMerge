#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "logger.h"
void freeRecord(Record **logs,int size)
    {
    int i = 0;
    //declare and index and initilize it
    while(i < size)
        {
        free(logs[i++]);
        //free individual logs
        }
    free(logs);
    //free the table of logs
    return;
    }

void 
writeTableToFile(char *fileName,Record **logs,int size)
    {
    FILE *fp = fopen(fileName,"w");
    //open the file
    if (fp == 0)
        {
        fprintf(stderr,"file data could not be opened for writing\n");
        exit(1);
        //test to check if the file was opened
        }
    int i = 0;
    //initialize i and set it to 0
    while(i < size)
        { 
        //write the records to file
        fprintf(fp,"%c ",getRecordType(logs[i]));
        fprintf(fp,"%d ",getRecordYear(logs[i]));
        fprintf(fp,"%d ",getRecordMonth(logs[i]));
        fprintf(fp,"%d ",getRecordDay(logs[i]));
        fprintf(fp,"%s ",getRecordTimestamp(logs[i]));
        fprintf(fp,"%s ",getRecordUser(logs[i]));
        fprintf(fp,"%s ",getRecordCommand(logs[i]));
        fprintf(fp,"%f ",getRecordOpCost(logs[i]));
        fprintf(fp,"\n");
        i++;
        }
    fprintf(fp,"# total cost: %f\n",sumOpCost(logs,size));
    //write the total cost to the file
    fclose(fp);
    //close the file
    }

double
sumOpCost(Record **logs,int size)
    {
    double sumOfOpCost = 0;
    int i = 0;
    while (i < size)
        {
        sumOfOpCost += getRecordOpCost(logs[i]);
        //sum the individual op costs
        i++;
        }
    return sumOfOpCost;
    }

void
displayRecordTable(Record **logs,int size)
    {
    int i = 0;
    while(i < size)
        {
        displayRecord(logs[i]);
        //display all the records in a table
        i++;
        }
    return;
    }

Record **
mergeRecords(Record **a,int aSize,Record **b,int bSize)
    {
    int i,j,spot;
    Record **c = allocate(sizeof(Record*) * (aSize + bSize));
    //merge until one source is exhausted
    spot = 0;
    for (i = 0,j = 0; i < aSize && j < bSize; ++spot)
        {
        if (getRecordYear(a[i]) < getRecordYear(b[j])) 
            {
            c[spot] = a[i]; //if a's year is earlier put it first
            i++;
            }
        else if (getRecordYear(a[i]) > getRecordYear(b[j]))           
            {
            c[spot] = b[j]; //if b's year is earlier put it first
            j++;
            }
        else
            {
            if (getRecordMonth(a[i]) < getRecordMonth(b[j])) 
                {
                c[spot] = a[i]; //if a's month is earlier put it first
                i++;
                }
            else if (getRecordMonth(a[i]) > getRecordMonth(b[j]))           
                {
                c[spot] = b[j]; //if b's month is earlier put it first
                j++;
                }
            else
                {
                if (getRecordDay(a[i]) < getRecordDay(b[j])) 
                    {
                    c[spot] = a[i]; //if a's day is earlier put it first
                    i++;
                    }
                else if (getRecordDay(a[i]) > getRecordDay(b[j]))            
                    {
                    c[spot] = b[j]; //if b's day is earlier put it first
                    j++;
                    }
                else
                    {
                    if (strcmp(getRecordTimestamp(a[i]),getRecordTimestamp(b[j])) > 0)
                        {
                        c[spot] = a[i]; //if a's timestamp is earlier put it first
                        i++;
                        }
                    else
                        {
                        c[spot] = b[j]; //if b's timestamp is earlier put it first
                        j++;
                        }
                    }
                }
            }
        }

    //i is either equal to aSize or j is equal to bSize
    //spot holds the index of the 1st available slot in c

    // copy over leftover elements in a, if any
    for ( ; i < aSize; ++i)
        {
        c[spot] = a[i];
        ++spot;
        }

    // copy over leftover elements in b, if any
    for ( ; j < bSize; ++j)
        {
        c[spot] = b[j];
        ++spot;
        }

    //c now holds the shuffle of a and b
    return c;
    }

Record **
readRecords(char *fileName,int *finalSize)
    {
    FILE *fp = fopen(fileName,"r");    
    if (fp == 0)
        {
        fprintf(stderr,"file data could not be opened for reading\n");
        exit(1);
        }
    int size = 10;                      //initial size of destination array
    Record *rec;
    int count;

    //allocate the destination array
    //Record ** is a pointer to an array of Records
    Record **table = allocate(sizeof(Record *) * size);

    count = 0;
    rec = readRecord(fp);
    while (!feof(fp))
         {
         if (count == size)              //array is full!
            {
            // grow the array by doubling its size
            size = size * 2;
            table = reallocate(table,sizeof(Record *) * size);
            //now there is enough room
            }
         table[count] = rec;           //DO NOT FREE THE RECORD!
         ++count;
         rec = readRecord(fp);
         }
    fclose(fp);

    //shrink the array to 'count' number of elements
    table = reallocate(table,sizeof(Record *) * count);

    //count holds the number of items, store it in *finalSize
    *finalSize = count;
    return table;
    }


Record *
newRecord(char t,int y,int m,int d,char *ts,char *u,char *c,double op)
    {
    //create a new record
    Record *r = allocate(sizeof(Record));
    r->type = t;
    r->year = y;
    r->month = m;
    r->day = d;
    r->timestamp = ts;
    r->user = u;
    r->command = c;
    r->opcost = op;
    return r;
    }

char 
getRecordType(Record *record) { return record->type; }
//accessor for record
int 
getRecordYear(Record *record) { return record->year; }
//accessor for record
int 
getRecordMonth(Record *record) { return record->month; }
//accessor for record
int 
getRecordDay(Record *record) { return record->day; }
//accessor for record
char *
getRecordTimestamp(Record *record) { return record->timestamp; }
//accessor for record
char *
getRecordUser(Record *record) { return record->user; }
//accessor for record
char *
getRecordCommand(Record *record) { return record->command; }
//accessor for record
double 
getRecordOpCost(Record *record) { return record->opcost; }
//accessor for record

Record *
readRecord(FILE *fp)
    {
    char type,*timestamp,*user,*command;
    int year,month,day;
    double opcost;

    type = readChar(fp);
    if (feof(fp)) { return 0; }
    //if end of file return 0
    while (type == '#') 
        {
        //ignore comments
        readLine(fp);
        type = readChar(fp);
        if (type == '@') { break; }
        }
        //read the rest of the record
        year = readInt(fp);
        month = readInt(fp);
        day = readInt(fp);
        timestamp = readToken(fp);
        user = readToken(fp);
        command = readString(fp);
        opcost = readReal(fp);
        return newRecord(type,year,month,day,timestamp,user,command,opcost);
    }

void
displayRecord(Record *rec)
    {
    //display an individual record
    printf("%c ",getRecordType(rec));
    printf("%d ",getRecordYear(rec));
    printf("%d ",getRecordMonth(rec));
    printf("%d ",getRecordDay(rec));
    printf("%s ",getRecordTimestamp(rec));
    printf("%s ",getRecordUser(rec));
    printf("%s ",getRecordCommand(rec));
    printf("%f ",getRecordOpCost(rec));
    printf("\n");
    }
    

