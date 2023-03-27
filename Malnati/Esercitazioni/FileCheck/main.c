#include <stdio.h>
#include <time.h>

typedef struct {
    int type;
    float val;
    long timestamp;
} ValueStruct;

typedef struct {
    int type;
    float val[10];
    long timestamp;
} MValueStruct;

typedef struct {
    int type;
    char message[21]; // stringa null terminated lung max 20
} MessageStruct;

typedef struct {
    int type;
    union {
        ValueStruct val;
        MValueStruct mvals;
        MessageStruct messages;
    };
} ExportData;

int main() {
    FILE  *pf;
    if((pf = fopen("export_data.bin", "rb")) == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    ExportData exportData[100];
    for (int i = 0; i < 100; i++) {
        if ((fread(&exportData[i], 1, sizeof (ExportData), pf)) < 0) {
            printf("Error reading from file...");
            return -2;
        }
        
        switch (exportData[i].type) {
            case 1:
                printf("\nValueStruct [%d]:\n", i+1);
                printf("Type --> %d\n", exportData[i].val.type);
                printf("Value --> %f\n", exportData[i].val.val);
                printf("Timestamp --> %lld\n", exportData[i].val.timestamp);
                break;
            case 2:
                printf("\nMValueStruct [%d]:\n", i+1);
                printf("Type --> %d\n", exportData[i].mvals.type);
                printf("Value's Array:\n");
                for(int j=0; j<10; j++) {
                    printf("%f ", exportData[i].mvals.val[j]);
                }
                printf("Timestamp\n --> %lld", exportData[i].mvals.timestamp);
                break;
            case 3:
                printf("\nMessageStruct [%d]:\n", i+1);
                printf("Type --> %d\n", exportData[i].messages.type);
                printf("Message --> %s\n", exportData[i].messages.message);
                break;
            default:    
                printf("Error reading element %d\n", i+1);
                return -3;
        }

    }

    printf("Legacy data has been stored successfully!\n");
    return 0;
}
