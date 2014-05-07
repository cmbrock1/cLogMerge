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
Record *newRecord(char,int,int,int,char*,char*,char*,double);
char getRecordType(Record*);
int getRecordYear(Record*);
int getRecordMonth(Record*);
int getRecordDay(Record*);
char *getRecordTimestamp(Record*);
char *getRecordUser(Record*);
char *getRecordCommand(Record*);
double getRecordOpCost(Record*);

