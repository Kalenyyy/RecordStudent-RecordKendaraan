#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char platNomor[12];
    char jenisKendaraan[20];
    int tahunProduksi;
} CarRecord;

typedef CarRecord CarArray[100 + 1];

// Opsi 1 Tambah Kendaraan
void tambahDataKendaraan(FILE *carRecordFile, CarRecord carRecord, int n);

// Opsi 2 Membaca data kendaraan
void addFiletoArray(FILE *carRecordFile, CarArray carArray, int *n);
void printArrayKendaraan(CarArray carArray, int n);

// Opsi 3 Update data kendaraan
void updateDataKendaraan(FILE *carRecordFile, int idTarget);

// Opsi 4 Delete data kendaraan
void deleteDataKendaraan(FILE *carRecordFile, int idTarget);

int main() {
    FILE *carRecordFile;
    CarRecord Car;
    CarArray carArray;
    int pilihMenu;
    int n;
    int idTarget;

    do {
        printf("****** DATA KENDARAAN ****** \n");

        printf("[1] Tambah Data Kendaraan \n");
        printf("[2] Lihat Data Kendaraan \n");
        printf("[3] Ubah Data Kendaraan \n");
        printf("[4] Hapus Data Kendaraan \n");
        printf("[5] Keluar Program \n");

        printf("Pilih Menu : ");
        scanf("%d", &pilihMenu);

        if (pilihMenu < 1 || pilihMenu > 5) {
            printf("Mohon Pilih Menu sesuai dengan ketentuan \n\n");
        }

        if (pilihMenu == 1) {
            printf("Berapa banyak kendaraan yang ingin ditambah? : ");
            scanf("%d", &n);
            tambahDataKendaraan(carRecordFile, Car, n);
        } else if (pilihMenu == 2) {
            addFiletoArray(carRecordFile, carArray, &n);
            printArrayKendaraan(carArray, n);
        } else if (pilihMenu == 3) {
            printf("\n****** Update Data Kendaraan ******\n");
            printf("ID Kendaraan : ");
            scanf("%d", &idTarget);

            updateDataKendaraan(carRecordFile, idTarget);
        } else if (pilihMenu == 4) {
            printf("\n****** Delete Data Kendaraan ******\n");
            printf("ID Kendaraan : ");
            scanf("%d", &idTarget);

            deleteDataKendaraan(carRecordFile, idTarget);
        }
    } while (pilihMenu != 5);

    if (pilihMenu == 5) {
        printf("Terimakasih Telah Menggunakan Program ini!");
    }

    return 0;
}

void tambahDataKendaraan(FILE *carRecordFile, CarRecord carRecord, int n) {
    carRecordFile = fopen("CarRecordFile.dat", "ab");

    printf("\n****** Tambah Data Kendaraan ******");

    for (int i = 1; i <= n; i++) {
        printf("\nID Kendaraan    : ");
        scanf("%d", &carRecord.id);
        printf("Nomor Plat      : ");
        scanf(" %[^\n]", carRecord.platNomor);
        printf("Jenis Kendaraan : ");
        scanf(" %[^\n]", carRecord.jenisKendaraan);
        printf("Tahun Produksi  : ");
        scanf("%d", &carRecord.tahunProduksi);

        fwrite(&carRecord, sizeof(carRecord), 1, carRecordFile);
    }
    fclose(carRecordFile);
}

void addFiletoArray(FILE *carRecordFile, CarArray carArray, int *n) {
    carRecordFile = fopen("CarRecordFile.dat", "rb");
    CarRecord carRecord;

    int i = 0;
    while (fread(&carRecord, sizeof(carRecord), 1, carRecordFile) == 1) {
        i = i + 1;
        carArray[i] = carRecord;
    }
    fclose(carRecordFile);
    *n = i;
}

void printArrayKendaraan(CarArray carArray, int n) {
    printf("\n****** Lihat Data Kendaraan ****** \n\n");
    for (int i = 1; i <= n; i++) {
        printf("ID Kendaraan    : %d \n", carArray[i].id);
        printf("Nomor Plat      : %s \n", carArray[i].platNomor);
        printf("Jenis Kendaraan : %s \n", carArray[i].jenisKendaraan);
        printf("Tahun Produksi  : %d \n\n", carArray[i].tahunProduksi);
    }

    getchar();
    getchar();
}

void updateDataKendaraan(FILE *carRecordFile, int idTarget) {
    FILE *tempFile;
    CarRecord carRecord;
    int found = 0;
    char newPlat[12];

    // Siapkan file sementara
    carRecordFile = fopen("CarRecordFile.dat", "rb");
    tempFile = fopen("TempFile.dat", "wb");

    while (fread(&carRecord, sizeof(carRecord), 1, carRecordFile) == 1) {
        if (carRecord.id == idTarget) {
            printf("ID Kendaraan    : %d \n", carRecord.id);
            printf("Nomor Plat      : %s \n", carRecord.platNomor);
            printf("Jenis Kendaraan : %s \n", carRecord.jenisKendaraan);
            printf("Tahun Produksi  : %d \n\n", carRecord.tahunProduksi);

            printf("Masukkan nomor plat baru: ");
            scanf(" %[^\n]", newPlat);

            strcpy(carRecord.platNomor, newPlat);

            found = 1;
        }

        fwrite(&carRecord, sizeof(carRecord), 1, tempFile);
    }

    fclose(carRecordFile);
    fclose(tempFile);

    // diputar balikkan
    carRecordFile = fopen("CarRecordFile.dat", "wb");
    tempFile = fopen("TempFile.dat", "rb");

    while (fread(&carRecord, sizeof(carRecord), 1, tempFile) == 1) {
        fwrite(&carRecord, sizeof(carRecord), 1, carRecordFile);
    }

    fclose(tempFile);
    fclose(carRecordFile);

    if (found == 0) {
        printf("Data Kendaraan dengan ID %d Tidak Ditemukan \n", idTarget);
        getchar();
        getchar();
    } else {
        printf("Data Kendaraan berhasil di perbaharui!");
        getchar();
        getchar();
    }
}

void deleteDataKendaraan(FILE *carRecordFile, int idTarget) {
    FILE *tempFile;
    CarRecord carRecord;
    int found = 0;

    // Siapkan file sementara
    carRecordFile = fopen("CarRecordFile.dat", "rb");
    tempFile = fopen("TempFile.dat", "wb");

    while (fread(&carRecord, sizeof(carRecord), 1, carRecordFile) == 1) {
        if (carRecord.id == idTarget) {
            found = 1;
            // jika ditemukan idnya maka id tersebut dilewat
            continue;
        }
        fwrite(&carRecord, sizeof(carRecord), 1, tempFile);
    }

    fclose(carRecordFile);
    fclose(tempFile);

    // diputar balikkan
    carRecordFile = fopen("CarRecordFile.dat", "wb");
    tempFile = fopen("TempFile.dat", "rb");

    while (fread(&carRecord, sizeof(carRecord), 1, tempFile) == 1) {
        fwrite(&carRecord, sizeof(carRecord), 1, carRecordFile);
    }

    fclose(tempFile);
    fclose(carRecordFile);

    if (found == 0) {
        printf("Data Kendaraan dengan ID %d Tidak Ditemukan \n", idTarget);
        getchar();
        getchar();
    } else {
        printf("Data Kendaraan berhasil di hapus!");
        getchar();
        getchar();
    }
}
