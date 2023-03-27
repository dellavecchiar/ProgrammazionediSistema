#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void export(ExportData *data, int n, FILE *pf){
    for(int i = 0; i < 100; i++){
        fwrite(&data[i], 1, sizeof(ExportData), pf);
        printf("%d)\t EXPORT FROM ARRAY TO FILE!\n", i+1);
    }
}

int main() {
    ExportData exportDataArray[100];
    FILE *pf;

    char *strings[100] = {
            "Artificial heart",
            "Space exploration",
            "Quantum computing",
            "Renewable energy",
            "Virtual reality",
            "AI",
            "Robotics technology",
            "Neuroscience research",
            "Genetic engineering",
            "3D printing",
            "Smart cities",
            "Blockchain technology",
            "Augmented reality",
            "Nanotechnology",
            "Clean water",
            "Green energy",
            "Autonomous vehicles",
            "Wireless power",
            "Smart homes",
            "Advanced materials",
    };

    if((pf = fopen("export_data.bin", "wb+")) == NULL){
        printf("Error opening file!");
        return -1;
    }else {
        printf("File opened correctely!\n\n");
    }

    for (int i = 0; i < 100; i++) {
        int type = rand() % 3 + i;
        ExportData exportData;
        exportData.type = type;

        switch (type) {
            case 1:
                exportData.val.type = type;
                exportData.val.val = (float) rand() / (RAND_MAX * 100);
                exportData.val.timestamp = time(NULL);
                break;
            case 2:
                exportData.mvals.type = type;
                for(int j = 0; j < 10; j++) {
                    exportData.mvals.val[j] = (float) rand() / (RAND_MAX * 100);
                }
                exportData.mvals.timestamp = time(NULL);
            case 3:
                exportData.messages.type = type;
                char *strMessage = strings[(int) (rand() % 20)];
                int lenMessage = strlen(strMessage);
                strncpy(exportData.messages.message, strMessage, lenMessage);
                exportData.messages.message[lenMessage] = '\0';
        }
        exportDataArray[i] = exportData;
    }

    export(exportDataArray, 100, pf);
    printf("\nArray exported correctely!\n");
    fclose(pf);
    return 0;
}
