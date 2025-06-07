#include <stdio.h>
#include <limits.h>   // Untuk menggunakan nilai INT_MAX sebagai representasi tak terhingga
#include <stdbool.h>  // Untuk menggunakan tipe data bool, true, dan false (standar C99)

// Jumlah node dalam graf
#define V 6

// Fungsi untuk mencari node dengan jarak minimum yang belum diproses
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Fungsi untuk mencetak hasil jarak terpendek
void printSolution(int dist[], int src) {
    char nodes[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    printf("Jarak terpendek dari Node %c\n", nodes[src]);
    for (int i = 0; i < V; i++) {
        printf("Node %c \t->\t ", nodes[i]);
        if(dist[i] == INT_MAX){
            printf("Tidak Terjangkau\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }
}

// Fungsi utama algoritma Dijkstra
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // Array untuk menyimpan jarak terpendek dari src ke i
    bool sptSet[V];   // sptSet[i] akan true jika node i sudah diproses

    // 1. Inisialisasi:
    //    - Semua jarak diatur sebagai tak terhingga (INT_MAX)
    //    - Semua node ditandai belum diproses (false)
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Jarak dari node sumber ke dirinya sendiri selalu 0
    dist[src] = 0;

    // 2. Loop Utama: Cari jalur terpendek untuk semua node
    for (int count = 0; count < V - 1; count++) {
        // Pilih node dengan jarak minimum dari himpunan node yang belum diproses
        int u = minDistance(dist, sptSet);

        // Tandai node yang sudah dipilih sebagai sudah diproses
        sptSet[u] = true;

        // 3. Update Jarak (Relaksasi):
        //    Perbarui nilai jarak dari tetangga-tetangga node yang dipilih.
        for (int v = 0; v < V; v++) {
            // Update dist[v] hanya jika:
            // - Belum diproses (ada di sptSet)
            // - Ada jalur dari u ke v (graph[u][v] tidak 0)
            // - Total bobot jalur dari src ke v melalui u lebih kecil dari nilai dist[v] saat ini
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Cetak array jarak yang sudah dihitung
    printSolution(dist, src);
}

// Fungsi utama program
int main() {
    // Inisialisasi graf berdasarkan gambar (matriks adjasensi)
    int graph[V][V] = {
        {0, 6, 5, 0, 0, 0},
        {6, 0, 6, 4, 7, 0},
        {5, 6, 0, 3, 0, 6},
        {0, 4, 3, 0, 2, 0},
        {0, 7, 0, 2, 0, 4},
        {0, 0, 6, 0, 4, 0}
    };

    // Menjalankan algoritma Dijkstra dimulai dari Node A (indeks 0)
    dijkstra(graph, 0);

    return 0;
}