
int InitFiles(char *fnprfx);
long GetALine(char frommark,char tomark,char *linebuf);
int MarkLineWith(long at,char *tomark);
long AppendDataFile(char *buf,long buflen);
int AppendLine(char *buf);
int AppendLineIfNew(char *buf,char *substr);
long FindNextMatchingLine(long at,char *match,char *buf);
int ReadDataFile(long at,long len,char *buf);
int MakeNewFiles(char *fnprfx);
int ResetSem(char *fnprfx);
int SemSignal(void);
int SemWait(void);
