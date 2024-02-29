#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>   // library waktu

// struct menyimpan data barang
struct Barang {
    int nomor;
    char nama[50];
    int harga;
    int jumlah_beli;
};

// fungsi untuk menukar dua elemen dalam array Barang
void swap(struct Barang *a, struct Barang *b) {
    struct Barang temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    // deklarasi array untuk menyimpan data barang
    struct Barang daftar_barang[5]; // jumlah barang nya ada 5

    // inisialisasi data barang
    daftar_barang[0].nomor = 1;
    strcpy(daftar_barang[0].nama, "Buku Tulis");
    daftar_barang[0].harga = 5000;
    daftar_barang[0].jumlah_beli = 0; // inisialisasi jumlah pembelian ke 0

    daftar_barang[1].nomor = 2;
    strcpy(daftar_barang[1].nama, "Pensil");
    daftar_barang[1].harga = 2000;
    daftar_barang[1].jumlah_beli = 0;

    daftar_barang[2].nomor = 3;
    strcpy(daftar_barang[2].nama, "Penghapus");
    daftar_barang[2].harga = 1000;
    daftar_barang[2].jumlah_beli = 0;

    daftar_barang[3].nomor = 4;
    strcpy(daftar_barang[3].nama, "Penggaris");
    daftar_barang[3].harga = 1000;
    daftar_barang[3].jumlah_beli = 0;

    daftar_barang[4].nomor = 5;
    strcpy(daftar_barang[4].nama, "Bujur Sangkar");
    daftar_barang[4].harga = 500;
    daftar_barang[4].jumlah_beli = 0;

    int total_harga_setelah_diskon = 0; // total harga setelah dipotong diskon

    int nomor_barang, jumlah_beli, pembayaran;

    printf("Selamat datang di Toko Skensa\n");
    printf("Silahkan pilih barang yang anda inginkan\n");

    printf("===================================\n");
    printf("|No|     Barang       |  Harga    |\n");
    printf("----------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("|%d|   %-15s|   Rp.%-4d  |\n", daftar_barang[i].nomor, daftar_barang[i].nama, daftar_barang[i].harga);
    }
    printf("===================================\n");

    printf("\n");

    printf("99. Struk Pembayaran\n");
    printf("55. Reset Pilihan\n");
    printf("00. Keluar\n");
    printf("\n===================================");


    do {
        // input pilihan barang maupun opsi menu
        printf("\nInput pilihan yang anda inginkan: ");
        scanf("%d", &nomor_barang);

        if (nomor_barang == 99) {
            // menghitung total harga setelah diskon
            total_harga_setelah_diskon = 0;
            for (int i = 0; i < 5; i++) {
                int diskon = 0;
                if (daftar_barang[i].jumlah_beli >= 5) {
                    diskon = 15;
                } else if (daftar_barang[i].jumlah_beli >= 3) {
                    diskon = 10;
                }
                int subtotal = (long long)daftar_barang[i].harga * daftar_barang[i].jumlah_beli;
                int nilai_diskon = (subtotal * diskon) / 100;
                int total_setelah_diskon = subtotal - nilai_diskon;
                total_harga_setelah_diskon += total_setelah_diskon;
            }
            
            
            // mengurutkan berdasarkan jumlah pembelian terbanyak
            for (int i = 0; i < 5 - 1; i++) {
            for (int j = 0; j < 5 - i - 1; j++) {
            if (daftar_barang[j].jumlah_beli < daftar_barang[j+1].jumlah_beli) {
                swap(&daftar_barang[j], &daftar_barang[j+1]);
                    }
                }
            }

            // tampilan rekapan pesanan barang
            printf("\nRekapan Pesanan Barang\n");
            printf("Nama Barang   Harga   Jumlah   Diskon  Total Harga\n");
            printf("---------------------------------------------------------\n");

            for (int i = 0; i < 5; i++) {
                if (daftar_barang[i].jumlah_beli > 0) {
                    int diskon = 0;
                    if (daftar_barang[i].jumlah_beli >= 5) {
                        diskon = 15;
                    } else if (daftar_barang[i].jumlah_beli >= 3) {
                        diskon = 10;
                    }
                    int subtotal = (int)daftar_barang[i].harga * daftar_barang[i].jumlah_beli;
                    int nilai_diskon = (subtotal * diskon) / 100;
                    int total_setelah_diskon = subtotal - nilai_diskon;
                    printf("%-14s%-8d%-9d%-9d%-10d%\n", daftar_barang[i].nama, daftar_barang[i].harga, daftar_barang[i].jumlah_beli, diskon, total_setelah_diskon);
                }
            }

            printf("------------------------------------------------------\n");
            printf("Total Harga: Rp %lld\n", total_harga_setelah_diskon);

            // memasukkan uang pembayaran
            do {
                printf("\nMasukkan jumlah uang yang dibayarkan: ");
                scanf("%d", &pembayaran);
                if (pembayaran < total_harga_setelah_diskon) {
                    printf("Uang yang dimasukkan kurang. Silakan masukkan uang yang cukup.\n");
                }
            } while (pembayaran < total_harga_setelah_diskon);

            // hasil kembalian
            int kembalian = pembayaran - total_harga_setelah_diskon;
            printf("|Kembalian: %d\n", kembalian);

            // menghentikan loop
            break;
        } else if (nomor_barang == 55) {
            // reset pilihan barang yang sudah dipilih
            for (int i = 0; i < 5; i++) {
                daftar_barang[i].jumlah_beli = 0;
            }
            printf("Pilihan Anda telah direset.\n");
        } else if (nomor_barang < 1 || nomor_barang > 5) {
            printf("Nomor barang tidak valid!\n");
        } else {
            // masukkan jumlah barang yang akan dibeli
            printf("\n[%d] pemesanan %s\n", daftar_barang[nomor_barang - 1].nomor, daftar_barang[nomor_barang - 1].nama);
            printf("Masukkan jumlah barang yang akan dibeli: ");
            scanf("%d", &jumlah_beli);
            printf("===================================\n");

            // kondisi jika jumlah barang yang dibeli kurang dari 0
            if (jumlah_beli <= 0) {
                printf("Jumlah barang tidak valid!\n");
            } else {
                daftar_barang[nomor_barang - 1].jumlah_beli += jumlah_beli;
            }
        }
    } while (1); // proses looping tanpa henti

    // MASUK KE BAGIAN STRUK TRANSAKSI

    system("cls"); // membersihkan terminal

    printf("\n=================================================================\n");
    printf("|                        TOKO SKENSA                            |\n");
    printf("|             Jl. HOS Cokroaminoto No. 84, Denpasar             |\n");
    printf("|                             Bali                              |\n");
    printf("|                       Telp : 03616285791                      |\n");

    printf("|---------------------------------------------------------------|\n");
    printf("|Nama Barang   Harga   Jumlah   Diskon   Potongan    Total      |\n");
    printf("|---------------------------------------------------------------|\n");

    for (int i = 0; i < 5; i++) {
        if (daftar_barang[i].jumlah_beli > 0) {
            int diskon = 0;
            if (daftar_barang[i].jumlah_beli >= 5) {
                diskon = 15;
            } else if (daftar_barang[i].jumlah_beli >= 3) {
                diskon = 10;
            }
            int subtotal = (int)daftar_barang[i].harga * daftar_barang[i].jumlah_beli;
            int nilai_diskon = (subtotal * diskon) / 100;
            int total_setelah_diskon = subtotal - nilai_diskon;
            printf("|%-14s%-8d%-9d%-9d%-10d%-8d%     |\n", daftar_barang[i].nama, daftar_barang[i].harga, daftar_barang[i].jumlah_beli, diskon, nilai_diskon, total_setelah_diskon);

        }
    }

    printf("|---------------------------------------------------------------|\n");
    printf("|Total Keseluruhan: Rp %lld                                     |\n", total_harga_setelah_diskon);
    printf("|Uang bayar: %d                                                 |\n", pembayaran);
    int kembalian = pembayaran - total_harga_setelah_diskon;
    printf("|Kembalian: %d                                                  |\n", kembalian);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("|Tanggal dan Waktu Pembayaran: %d-%02d-%02d %02d:%02d:%02d      |", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("\n=================================================================\n");


    return 0;
}
