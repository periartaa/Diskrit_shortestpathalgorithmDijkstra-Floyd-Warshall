#include <stdio.h>

// Mendefinisikan jumlah simpul (vertices) dalam graf
#define V 6 
// Mendefinisikan nilai untuk "tak hingga" (infinity)
#define INF 99999

// Fungsi untuk mencetak matriks
// Di C, kita harus menentukan ukuran array saat melewatkannya ke fungsi
void printMatrix(int dist[V][V]) {
    // Header untuk kolom (A, B, C, D, E, F)
    printf("      ");
    for (int i = 0; i < V; ++i) {
        printf("%5c", (char)('A' + i));
    }
    printf("\n----------------------------------------\n");

    for (int i = 0; i < V; ++i) {
        // Header untuk baris
        printf("%c | ", (char)('A' + i));
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) {
                printf("%5s", "INF");
            } else {
                printf("%5d", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    // Inisialisasi matriks jarak berdasarkan graf pada gambar.
    // Indeks: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F
    int graph[V][V] = {
        //      A,   B,   C,   D,   E,   F
        /*A*/ {   0,   6,   5, INF, INF, INF },
        /*B*/ {   6,   0,   2,   4,   7, INF },
        /*C*/ {   5,   2,   0,   3, INF,   6 },
        /*D*/ { INF,   4,   3,   0,   2, INF },
        /*E*/ { INF,   7, INF,   2,   0,   4 },
        /*F*/ { INF, INF,   6, INF,   4,   0 }
    };

    // Membuat matriks untuk menyimpan hasil jarak terpendek
    int dist[V][V];

    // Salin data dari graph ke dist (tidak bisa langsung seperti di C++)
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    printf("## Matriks Jarak Awal:\n\n");
    printMatrix(dist);
    printf("\n----------------------------------------\n\n");

    // Algoritma Floyd-Warshall (logikanya sama persis dengan C++)
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Jika jalur dari i ke j melalui k lebih pendek,
                // maka perbarui jarak dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Mencetak matriks hasil akhir yang berisi jarak terpendek
    printf("## Matriks Jarak Terpendek (Hasil Floyd-Warshall):\n\n");
    printMatrix(dist);

    return 0;
}