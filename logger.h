typedef struct record
    {
    char type;
    int year;
    int month;
    int day;
    char *timestamp;
    char *user;
    char *command;
    double opcost;
    } Record;
void writeTableToFile(char *fileName,Record **logs,int size);
void freeRecord(Record **,int);
double sumOpCost(Record **,int);
Record **readRecords(char *,int *);
Record **mergeRecords(Record **,int,Record **,int);
void displayRecordTable(Record **,int);
Record *newRecord(char,int,int,int,char*,char*,char*,double);
Record *readRecord(FILE *);
char getRecordType(Record *);
int getRecordYear(Record *);
int getRecordMonth(Record *);
int getRecordDay(Record *);
char *getRecordTimestamp(Record *);
char *getRecordUser(Record *);
char *getRecordCommand(Record *);
double getRecordOpCost(Record *);
void displayRecord(Record *);
