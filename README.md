# I. Petunjuk penggunaan program
    gcc -g -Wall -o dijkstra dijkstra.c -fopenmp
    ./dijkstra [jumlah thread] [jumlah node]
    
# II. Laporan pengerjaan
1.  Deskripsi solusi paralel<br/>
    Solusi yang digunakan adalah dengan menginisialisasi thread sejumlah thread\_count menggunakan #pragma omp parallel num\_threads(),
    setelah itu membagi task dijkstra untuk setiap node ke setiap thread yang sudah diinisialisasi dengan #pragma omp for sejumlah node.

2.  Analisis solusi<br/>
    Solusi yang kami gunakan adalah memparalelkan proses eksekusi dijkstra untuk setiap node ke semua server.

3.  Jumlah thread yang digunakan<br/> 
    Jumlah thread yang digunakan adalah 2 thread dimana prosesor server hanya memiliki 2 prosesor yang dapat dilihat dengan command
    nproc. Hal itu dikarenakan jika menggunakan banyak thread maka waktu yang digunakan untuk switching akan semakin besar.

4.  Pengukuran kinerja untuk tiap kasus uji (jumlah N pada graf) dibandingkan dengan dijkstra algorithm serial<br/>
    1. Node 100 :
     *  Serial : 23,566617980 ms
     *  Paralel 1 : 6,276092026 ms
     *  Paralel 2 : 10,123373009 ms
     *  Paralel 3 : 12,125744019 ms
    2. Node 500 :
     *  Serial : 1240,478164982 ms
     *  Paralel 1 : 1199,427668005 ms
     *  Paralel 2 : 1203,883039067 ms
     *  Paralel 3 : 1157,052313909 ms
    3. Node 1000 :
     *  Serial : 14454,813088058 ms
     *  Paralel 1 : 9392,668731045 ms
     *  Paralel 2 : 9323,413665057 ms
     *  Paralel 3 : 9438,282919000 ms
    4. Node 3000 :
     *  Serial : 364557,538866997 ms
     *  Paralel 1 : 240620,507878019 ms
    <br/>
5.  Analisis perbandingan kinerja serial dan paralel<br/>
    Berdasarkan hasil setiap kasus uji menunjukkan bahwa algoritma paralel yang diterapkan menggunakan pragma omp lebih cepat <br/> 
    dibandingkan dengan algoritma secara serial.
