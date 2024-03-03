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

// fungsi untuk membuat id struk
int id_struk() {
    srand(time(NULL)); // agar hasil setiap detik beda
    int id = rand() % 9000 + 1000; // menghasilkan angka acak dari 0 hingga 8999 lalu ditambah 1000 agar range jadi 1000-8999
    return id;
}

int main() {
    struct Barang barang[] = { // jumlah barang nya ada 5;

    {1, "Buku Tulis", 5000, 0},
    {2, "Pensil", 2000, 0},
    {3, "Penghapus", 1000, 0},
    {4, "Penggaris", 1000, 0},
    {5, "Bujur Sangkar", 500, 0}
    };

    int nomor_barang, jumlah_beli, pembayaran;
    int total_diskon = 0; // total potongan diskon
    int total = 0; // total harga sebelum diskon
    int total_setelah_diskon = 0; // total harga setelah dipotong diskon
    int kembalian;

    FILE *file_struk = fopen("struk_transaksi.txt", "w");
    if (file_struk == NULL) {
        printf("Gagal membuka file untuk penulisan.\n");
        return 1;
    }

    printf("Selamat datang di Toko Skensa\n");
    printf("Silahkan pilih barang yang anda inginkan\n");
    printf("===================================\n");
    printf("|No|     Barang       |  Harga    |\n");
    printf("----------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("|%d|   %-15s|   Rp.%-4d  |\n", barang[i].nomor, barang[i].nama, barang[i].harga);
    }
    printf("===================================\n");
    printf("\n");
    printf("99. Struk Pembayaran\n");
    printf("55. Reset Pilihan\n");
    printf("00. Keluar\n");
    printf("\n===================================");

    do {
        printf("\nInput pilihan yang anda inginkan: "); // input pilihan barang maupun opsi menu
        scanf("%d", &nomor_barang);

        if (nomor_barang == 99) {
            total = 0;
            total_diskon = 0;
            total_setelah_diskon = 0;

            for (int i = 0; i < 5; i++) { // mengecek barang mana yang dapat diskon
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

            for (int i = 0; i < 5 - 1; i++) {    // mengurutkan struk berdasarkan jumlah pembelian terbanyak
                for (int j = 0; j < 5 - i - 1; j++) {
                    if (barang[j].jumlah_beli < barang[j+1].jumlah_beli) {
                        swap(&barang[j], &barang[j+1]);
                    }
                }
            }

           printf("\nRekapan Pesanan Barang\n"); // tampilan rekapan
           printf("=========================================================\n");
           printf("|No|Jumlah| Nama Barang | Harga |  Total Harga | Diskon |\n");
           printf("=========================================================\n");

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
           int diskon_barang = (total_harga* diskon) / 100;

           printf("|%2d|%6d|%-5s|Rp.%-9d|Rp.%-9d|Rp.%-13d|\n", no_rekapan, barang[i].jumlah_beli, barang[i].nama, barang[i].harga, total_harga, diskon_barang);
           no_rekapan++;
    }
}
           printf("=========================================================\n");
           printf("Total Harga : Rp %d\n", total);
           printf("Total Diskon: Rp %d\n", total_diskon);
           printf("Total Bayar : Rp %d\n", total_setelah_diskon);
           printf("=========================================================\n");

            // memasukkan uang pembayaran
            do {
                printf("Masukkan jumlah uang yang dibayarkan: ");
                scanf("%d", &pembayaran);
                if (pembayaran < total_setelah_diskon) {
                    printf("Uang yang dimasukkan kurang. Silakan masukkan uang yang cukup.\n");
                }
            } while (pembayaran < total_setelah_diskon);

            int kembalian = pembayaran - total_setelah_diskon; // hasil kembalian
            printf("Kembalian    : Rp %d\n", kembalian);

            // STRUK TRANSAKSI DI FILE .TXT
            fprintf(file_struk, "\n=================================================================\n");
            fprintf(file_struk, "|                        TOKO SKENSA                            |\n");
            fprintf(file_struk, "|             Jl. HOS Cokroaminoto No. 84, Denpasar             |\n");
            fprintf(file_struk, "|                             Bali                              |\n");
            fprintf(file_struk, "|                       Telp : 03616285791                      |\n");
            fprintf(file_struk, "|ID Struk: %d                                                   |\n", id_struk());
            fprintf(file_struk, "|---------------------------------------------------------------|\n");
            fprintf(file_struk, "|Nama Barang          Harga      Total      Diskon      |\n");
            fprintf(file_struk, "|---------------------------------------------------------------|\n");

            for (int i = 0; i < 5; i++) {
                if (barang[i].jumlah_beli > 0) {
                    int diskon = 0;
                    if (barang[i].jumlah_beli >= 5) {
                        diskon = 15;
                    } else if (barang[i].jumlah_beli >= 3) {
                        diskon = 10; }
                    int subtotal_barang = barang[i].harga * barang[i].jumlah_beli;
                    int nilai_diskon_barang = (subtotal_barang * diskon) / 100;
                    int total_setelah_diskon = subtotal_barang - nilai_diskon_barang;
                    fprintf(file_struk, "|%-dx%-14sRp.%-10dRp.%-10dRp.%-10d     |\n", barang[i].jumlah_beli, barang[i].nama, barang[i].harga, subtotal_barang, nilai_diskon_barang);
                }

            }

            fprintf(file_struk, "|---------------------------------------------------------------|\n");
            fprintf(file_struk, "|Total Keseluruhan : Rp %lld                                   |\n", total);
            fprintf(file_struk, "|Total diskon      : Rp %d                                     |\n", total_diskon);
            fprintf(file_struk, "|Tagihan           : Rp %d                                     |\n", total_setelah_diskon);
            fprintf(file_struk, "|Uang bayar        : Rp %d                                     |\n", pembayaran);
            kembalian = pembayaran - total_setelah_diskon;
            fprintf(file_struk, "|Kembalian         : Rp %d                                    |\n", kembalian);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char tanggal[50];
            strftime(tanggal, sizeof(tanggal), "|Waktu/hari     : %a %b %d %H:%M:%S %Y     |", &tm);
            fprintf(file_struk, "%s\n", tanggal);
            fprintf(file_struk, "\n=================================================================\n");

            break; // menghentikan loop
        } else if (nomor_barang == 55) {
            // reset pilihan barang yang sudah dipilih
            for (int i = 0; i < 5; i++) {
                barang[i].jumlah_beli = 0;
            }
            printf("Pilihan Anda telah direset.\n");
        } else if (nomor_barang == 00) {
            printf("Terima kasih telah menggunakan layanan kami.\n");
            return 0; // Keluar dari program
        } else if (nomor_barang < 1 || nomor_barang > 5) {
            printf("Pilihan tidak valid!\n");
        } else {
            // masukkan jumlah barang yang akan dibeli
            printf("\n[%d] pemesanan %s\n", barang[nomor_barang - 1].nomor, barang[nomor_barang - 1].nama);
            printf("Masukkan jumlah barang yang akan dibeli: ");
            scanf("%d", &jumlah_beli);
            printf("===================================\n");

            // kondisi jika jumlah barang yang dibeli kurang dari 0
            if (jumlah_beli <= 0) {
                printf("Jumlah barang tidak valid!\n");
            } else {
                barang[nomor_barang - 1].jumlah_beli += jumlah_beli;
            }
        }
    } while (1); // proses looping tanpa henti

            // STRUK TRANSAKSI DI TERMINAL
            system("cls"); // membersihkan terminal

            printf("\n=================================================================\n");
            printf("|                        TOKO SKENSA                            |\n");
            printf("|             Jl. HOS Cokroaminoto No. 84, Denpasar             |\n");
            printf("|                             Bali                              |\n");
            printf("|                       Telp : 03616285791                      |\n");
            printf("|ID Struk: %d                                                   |\n", id_struk());
            printf("|---------------------------------------------------------------|\n");
            printf("|Nama Barang          Harga      Total      Diskon      |\n");
            printf("|---------------------------------------------------------------|\n");

            for (int i = 0; i < 5; i++) {
                if (barang[i].jumlah_beli > 0) {
                int diskon = 0;
                    if (barang[i].jumlah_beli >= 5) {
                        diskon = 15;
                    } else if (barang[i].jumlah_beli >= 3) {
                        diskon = 10; }
                int subtotal_barang = barang[i].harga * barang[i].jumlah_beli;
                int nilai_diskon_barang = (subtotal_barang * diskon) / 100;
                int total_setelah_diskon = subtotal_barang - nilai_diskon_barang;
                printf("|%-dx%-14sRp.%-10dRp.%-10dRp.%-10d     |\n", barang[i].jumlah_beli, barang[i].nama, barang[i].harga, subtotal_barang, nilai_diskon_barang);
            }
        }

            printf("|---------------------------------------------------------------|\n");
            printf("|Total Keseluruhan : Rp %lld                                   |\n", total);
            printf("|Total diskon      : Rp %d                                     |\n", total_diskon);
            printf("|Tagihan           : Rp %d                                     |\n", total_setelah_diskon);
            printf("|Uang bayar        : Rp %d                                     |\n", pembayaran);
            kembalian = pembayaran - total_setelah_diskon;
            printf("|Kembalian         : Rp %d                                    |\n", kembalian);

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char tanggal[50];
            strftime(tanggal, sizeof(tanggal), "|Waktu/hari   : %a %b %d %H:%M:%S %Y     |", &tm);
            printf("%s\n", tanggal);
            printf("\n=================================================================\n");

    fclose(file_struk);

    return 0;
}
