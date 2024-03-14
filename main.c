#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Barang {
    int nomor;
    char nama[50];
    int harga;
    int jumlah_beli;
};

void swap(struct Barang *a, struct Barang *b) {
    struct Barang temp = *a;
    *a = *b;
    *b = temp;
}

int id_struk() {
    srand(time(NULL));
    int id = rand() % 9000000000 + 1000000000;
    return id;
}

int main() {
    struct Barang barang[] = {
        {1, "Buku Tulis", 5000, 0},
        {2, "Pensil", 2000, 0},
        {3, "Penghapus", 1000, 0},
        {4, "Penggaris", 1000, 0},
        {5, "Bujur Sangkar", 500, 0},
    };

    int pembayaran = 0, kembalian;
    int total = 0;
    int total_diskon = 0;
    int total_setelah_diskon = 0;
    
    time_t rawtime;
    struct tm *timeinfo;
    char filename[50];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(filename, sizeof(filename), "struk_%Y%m%d_%H%M%S.txt", timeinfo);

     FILE *struk = fopen(filename, "w");
    if (struk == NULL) {
        printf("Gagal membuat file struk.\n");
        return 1;
    }

    printf("Selamat datang di Toko SKENSA\n");
    printf("Silakan pilih barang yang anda inginkan\n");
    printf("\n");
    printf("====================================================\n");
    printf("|No|   Barang       |  Harga  |\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("|%d| %-15s | Rp.%-4d |\n", barang[i].nomor, barang[i].nama, barang[i].harga);
    }
    printf("====================================================\n");
    printf("\n");
    printf("99. Struk Pembayaran\n");
    printf("55. Reset Pilihan\n");
    printf("00. Keluar\n");
    printf("\n");
    printf("====================================================\n\n");

    do {
        int no_barang, jumlah_beli; // deklarasi variabel nya disini
        printf("Input pilihan yang anda inginkan: ");
        scanf("%d", &no_barang);

        if (no_barang == 99) {
            total = 0;
            total_diskon = 0;
            total_setelah_diskon = 0;

            for (int i = 0; i < 5; i++) {
                int diskon = 0;
                if (barang[i].jumlah_beli >= 5) {
                    diskon = 15;
                } else if (barang[i].jumlah_beli >= 3) {
                    diskon = 10;
                }
                int total_harga = barang[i].harga * barang[i].jumlah_beli;
                int diskon_barang = (total_harga * diskon) / 100;

                total_diskon += diskon_barang;
                total += total_harga;
                total_setelah_diskon += total_harga - diskon_barang;
            }

            for (int i = 0; i < 4; i++) { // swap nya < 4
                for (int j = 0; j < 4 - i; j++) {
                    if (barang[j].jumlah_beli < barang[j + 1].jumlah_beli) {
                        swap(&barang[j], &barang[j + 1]);
                    }
                }
            }

            printf("\n");
            printf("Rekapan Pesanan Barang\n");
            printf("======================================================================\n");
            printf("|No| Jumlah |  Nama Barang  |   Harga   | Total Harga |  Diskon  |\n");
            printf("======================================================================\n");

            int no_rekapan = 1;
            for (int i = 0; i < 5; i++) {
                if (barang[i].jumlah_beli > 0) {
                    int diskon = 0;
                    if (barang[i].jumlah_beli >= 5) {
                        diskon = 15;
                    } else if (barang[i].jumlah_beli >= 3) {
                        diskon = 10;
                    }

                    int total_harga = barang[i].harga * barang[i].jumlah_beli;
                    int diskon_barang = (total_harga * diskon) / 100;

                    printf("|%-2d|%-8d|%-15s|Rp.%-8d|Rp.%-10d|Rp.%-7d|\n", no_rekapan, barang[i].jumlah_beli, barang[i].nama, barang[i].harga, total_harga, diskon_barang);
                    no_rekapan++;
                }
            }

            printf("======================================================================\n");
            printf("Total Harga  : %d\n", total);
            printf("Total Diskon : %d\n", total_diskon);
            printf("Total Bayar  : %d\n", total_setelah_diskon);
            printf("======================================================================\n\n");

            do {
                printf("Masukkan uang bayar: ");
                scanf("%d", &pembayaran);
                if (pembayaran < total_setelah_diskon) {
                    printf("Uang yang dibayarkan kurang. Silahkan masukkan uang yang cukup.\n");
                }
            } while (pembayaran < total_setelah_diskon);

            kembalian = pembayaran - total_setelah_diskon;
            printf("Kembalian   : %d\n\n", kembalian);

            printf("Klik Enter untuk mencetak struk.\n");
            getchar();
            while (getchar() != '\n');

            // STRUK TXT
            fprintf(struk, "==========================================================\n");
            fprintf(struk, "|                    TOKO SKENSA                         |\n");
            fprintf(struk, "|          Jl. HOS Cokroaminoto No. 84 Denpasar          |\n");
            fprintf(struk, "|                       Bali                             |\n");
            fprintf(struk, "|                Telp: 0819348394                        |\n");
            fprintf(struk, "|ID Struk: %d                                    |\n", id_struk());
            fprintf(struk, "==========================================================\n");
            fprintf(struk, "|    Nama Barang    |   Harga   |   Total   |   Diskon   |\n");
            fprintf(struk, "==========================================================\n");
            for (int i = 0; i < 5; i++) {
                if (barang[i].jumlah_beli > 0) {
                    int diskon = 0;
                    if (barang[i].jumlah_beli >= 5) {
                        diskon = 15;
                    } else if (barang[i].jumlah_beli >= 3) {
                        diskon = 10;
                    }
                    int total_barang = barang[i].harga * barang[i].jumlah_beli;
                    int diskon_barang = (total_barang * diskon) / 100;
                    int total_setelah_diskon = total_barang - diskon_barang;
                    fprintf(struk, "|%-2dx %-15s|Rp.%-8d|Rp.%-8d|Rp.%-9d|\n", barang[i].jumlah_beli, barang[i].nama, barang[i].harga, total_barang, diskon_barang);
                }
            }

            fprintf(struk, "==========================================================\n");
            fprintf(struk, "|Total Harga  : %-41d,-|\n", total);
            fprintf(struk, "|Total Diskon : %-41d|\n", total_diskon);
            fprintf(struk, "|Tagihan      : %-41d|\n", total_setelah_diskon);
            fprintf(struk, "|Pembayaran   : %-41d|\n", pembayaran);
            kembalian = pembayaran - total_setelah_diskon;
            fprintf(struk, "|Kembalian    : %-41d|\n", kembalian);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char tanggal[50];
            strftime(tanggal, sizeof(tanggal), "|Waktu/hari   : %a %b %d %H:%M:%S %Y \t \t |\n", &tm);
            fprintf(struk, "%s", tanggal);
            fprintf(struk, "==========================================================\n");

            fclose(struk); //tambahin close di struk txt

            break;

        } else if (no_barang == 55) {
            for (int i = 0; i < 5; i++) {
                barang[i].jumlah_beli = 0;
            }
            printf("Pilihan anda telah direset.\n");
        } else if (no_barang == 00) {
            printf("Terima kasih. Selamat berbelanja kembali di Toko SKENSA.\n");
            return 0;
        } else if (no_barang < 1 || no_barang > 5) {
            printf("Pilihan tidak valid!\n");
        } else {
            printf("[%d] Jumlah %s dipesan: ", barang[no_barang - 1].nomor, barang[no_barang - 1].nama);
            scanf("%d", &jumlah_beli);
            printf("\n");
            printf("===========================================\n\n");

            if (jumlah_beli <= 0) {
                printf("Jumlah barang tidak valid!\n");
            } else {
                barang[no_barang - 1].jumlah_beli += jumlah_beli;
            }
        }
    } while (1);

    system("cls");

    printf("Mencetak struk ...\n\n");
    printf("Struk sudah dicetak.\n\n");
    printf("Terima kasih telah berbelanja di Toko SKENSA.");

    return 0;
}
