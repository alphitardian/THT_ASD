#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//varible global
int i;

//inisialisasi fungsi
void addItem(), deleteData(), editData(), searchData(), display();
void menu(), backToMenu(), gotoxy();

struct Ticket {
	int code;
	char name[30];
	char origin[30];
	char destination[30];
	int seats;
	char trainClass[30];
	struct Ticket *next;
};

// Pendeklarasian struct, head, dan tail
typedef struct Ticket ticket;
ticket *head = NULL;
ticket *tail = NULL;

void gotoxy(int x, int y) {
	
	//Digunakan untuk mengatur layout tampilan
	
    COORD coord;
     
    coord.X = x;
    coord.Y = y;
     
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void titleBar() {
	gotoxy(25,3); printf("======================================================================\n");
	gotoxy(45,4); printf("+===== DATA TIKET KERETA =====+");
	gotoxy(25,5); printf("======================================================================\n");
}

void displayTitle() {
	
	titleBar();
	gotoxy(7,8); printf("+--------------------------------------------------------------------------------------------------------+\n");
	gotoxy(17,9); 
	printf("KODE\t\t");
	printf("NAMA\t\t");
	printf("ASAL\t\t");
	printf("TUJUAN\t\t");
	printf("KURSI\t\t");
	printf("KELAS\t\t");
	gotoxy(7,10); printf("+--------------------------------------------------------------------------------------------------------+\n");
	
}

void displayRowData(ticket *ticketList) {
	printf("%d\t\t", ticketList->code);
    printf("%s\t\t", ticketList->name);
    printf("%s\t\t", ticketList->origin);
    printf("%s\t\t", ticketList->destination);
    printf("%d\t\t", ticketList->seats);
    printf("%s\t\t", ticketList->trainClass);
}

void backToMenu() {
	
	// Digunakan untuk kembali ke menu utama
	
	printf("Press Enter to Continue >>>");
	getch();
	system("cls");
	menu();
}

void display() {
	
	/*
	Digunakan untuk menampilkan isi list.
	struct diinisialisasikan sebagai head agar perulangan dimulai dari head.
	*/

    ticket *ticketList = head;
    int loopCoord = 0;
    
    displayTitle();
    
    // Bila terdapat data yang telah dimasukkan maka akan dilakukan perulangan untuk menampilkan data yang ada
	if (ticketList == NULL) {
		gotoxy(38,11); printf("Tidak ada data, masukkan data terlebih dahulu");
		gotoxy(47,15); backToMenu();
	} else {
		while(ticketList != NULL) {
	        gotoxy(17,11 + loopCoord); displayRowData(ticketList);
			loopCoord += 1;
	
	        ticketList = ticketList->next;			// Digunakan untuk melanjutkan ke data berikutnya
    	}
	}
}

void userInputData() {
	
	int code, seats;
	char name[30], origin[30], destination[30], trainClass[30];
	
	titleBar();
	
	gotoxy(43,7); printf("Masukkan kode \t\t: ");
	scanf("%d", &code);
	gotoxy(43,8); printf("Masukkan nama \t\t: ");
	scanf("%s", &name);
	gotoxy(43,9); printf("Masukkan kota asal \t\t: ");
	scanf("%s", &origin);
	gotoxy(43,10); printf("Masukkan kota tujuan \t: ");
	scanf("%s", &destination);
	gotoxy(43,11); printf("Masukkan nomor kursi \t: ");
	scanf("%d", &seats);
	gotoxy(43,12); printf("Masukkan kelas yang diambil \t: ");
	scanf("%s", &trainClass);
	
	addItem(code, name, origin, destination, seats, trainClass);
	
	gotoxy(43, 14); backToMenu();
	
}

void addItem(int code, char name[], char origin[], char destination[], int seats, char trainClass[]) {
	
	
	/*
	Digunakan untuk menambahkan item pada list.
	Diperlukan alokasi memori terlebiih dahulu sesuai ukuran struct.
	baru dilanjutkan dengan pengisian value di setiap field struct.
	untuk next struct selalu dibuat NULL, karena data yang baru ditambahkan akan selalu diletakkan di belakang.
	*/
	
	ticket *newItem;
	
	newItem = malloc(sizeof(ticket));		// alokasi memori
	newItem->code = code;					// pengisian value
	strcpy(newItem->name, name);			// pengisian value char
	strcpy(newItem->origin, origin);
	strcpy(newItem->destination, destination);
	newItem->seats = seats;
	strcpy(newItem->trainClass, trainClass);
	newItem->next = NULL;					// pengisian value
	
	/*
	Kemudian dilakukan pengecekan apakah sudah ada data atau belum.
	Jika belum ada, maka data yang baru masuk akan menjadi head sekaligus tail.
	Jika sudah ada, maka data yang baru masuk akan menjadi tail.
	*/
	
	if(head == NULL) {
		head = tail = newItem;						// pengisian value 
    } else {
        tail->next = newItem;				// pengisian value tail->next
        tail = newItem;						// pengisian value tail sehingga data baru akan berada dibelakang
    }
    tail->next = NULL;
    
}

void editData(int code) {
	
	/*
	Digunakan untuk mengubah value dari struct yang sudah ada.
	struct diinisialisasikan sebagai head agar perulangan dimulai dari head.
	dibentuk suatu variable check yang diberi nilai awal 0 yang digunakan untuk mengecek, apakah pencarian data yang diinginkan
	bisa ditemukan.
	*/
	
	ticket *item = head;
	int check = 0;
	
	titleBar();
	
	// Dilakukan pengecekan apakah sudah ada data yang diinput atau belum
	if (item == NULL) {
		system("COLOR 4F");
		gotoxy(48, 15); printf("==== TIDAK ADA DATA ====");
		gotoxy(47, 16); backToMenu();
	} else {
		while(item != NULL) {
			
			// Jika data ditemukan maka akan dilakukan penggantian data
			if (item->code == code) {
				
				check = 1;
				char newName[30], newOrigin[30], newDestination[30], newClass[30];
				int newSeats;
				
				gotoxy(41,10); printf(": : DATA");
				gotoxy(45,11); printf("Nama \t\t\t: %s", item->name);
				gotoxy(45,12); printf("Kota Asal \t\t\t: %s", item->origin);
				gotoxy(45,13); printf("Kota Tujuan \t\t: %s", item->destination);
				gotoxy(45,14); printf("Nomor Kursi \t\t: %d", item->seats);
				gotoxy(45,15); printf("Kelas Kereta \t\t: %s", item->trainClass);
				
				gotoxy(25,17); printf("======================================================================\n");
				
				gotoxy(41,19); printf("Masukkan data baru");
				gotoxy(45,21); printf("Nama \t\t\t: "); scanf("%s", &newName);
				gotoxy(45,22); printf("Kota Asal \t\t\t: "); scanf("%s", &newOrigin);
				gotoxy(45,23); printf("Kota Tujuan \t\t: "); scanf("%s", &newDestination);
				gotoxy(45,24); printf("Nomor Kursi \t\t: "); scanf("%d", &newSeats);
				gotoxy(45,25); printf("Kelas Kereta \t\t: "); scanf("%s", &newClass);
				
				strcpy(item->name, newName);		// Penggantian data lama dengan data baru
				strcpy(item->origin, newOrigin);
				strcpy(item->destination, newDestination);
				item->seats = newSeats;
				strcpy(item->trainClass, newClass);
				
				gotoxy(41,8); printf("DATA BERHASIL DIUBAH");
				gotoxy(47,30); backToMenu();
			} else {
				item = item->next;					// Bila data tidak ditemukan maka akan dilanjutkan ke data pada link berikutnya
			}
		}
		
		// Akan muncul bila sampai perulangan selesai, data masih belum ditemukan
		if (check == 0) {
			system("COLOR 4F");
			gotoxy(50, 15); printf("DATA TIDAK DITEMUKAN");
			gotoxy(47, 16); backToMenu();
		}
	}
}

void searchData(int code) {
	
	/*
	Digunakan untuk mencari data struct menggunakan kode yang telah diinputkan.
	struct diinisialisasikan sebagai head agar perulangan dimulai dari head.
	dibentuk suatu variable check yang diberi nilai awal 0 yang digunakan untuk mengecek, apakah pencarian data yang diinginkan
	bisa ditemukan.
	*/
	
	ticket *item = head;
	int check = 0;
	
	if (item == NULL) {
		system("COLOR 4F");
		gotoxy(48, 9); printf("==== TIDAK ADA DATA ====");
		gotoxy(47, 10); backToMenu();
	} else {
		while(item != NULL) {
			
			// Jika data ditemukan, maka akan dicetak isi seluruh struct pada kode tersebut
			if (item->code == code) {
				
				check = 1;
				
				system("cls");
				displayTitle();
				
				gotoxy(48, 7); printf("+=== DATA DITEMUKAN ===+");
				gotoxy(17,11); displayRowData(item);
				
				gotoxy(47, 16); backToMenu();
			} else {
				item = item->next;
			}
		}
		
		// Akan muncul bila sampai perulangan selesai, data masih belum ditemukan
		if (check == 0) {
			system("COLOR 4F");
			gotoxy(50, 15); printf("DATA TIDAK DITEMUKAN");
			gotoxy(47, 16); backToMenu();
		}
	}
}

void deleteData(int code) {
	
	/*
	Digunakan untuk menghapus value dari struct yang sudah ada.
	struct diinisialisasikan sebagai head agar perulangan dimulai dari head.
	dibentuk suatu variable check yang diberi nilai awal 0 yang digunakan untuk mengecek, apakah pencarian data yang diinginkan
	bisa ditemukan.
	*/
	
	ticket *item = head, *prevItem = NULL;
	int check = 0;
	char choice;
	
	if (item == NULL) {
		system("COLOR 4F");
		gotoxy(48, 10); printf("==== TIDAK ADA DATA ====");
		gotoxy(47, 11); backToMenu();
	} else {
		while(item != NULL) {
			
			// Jika data ditemukan maka akan dilakukan penghapusan
			if (item->code == code) {
				
				system("cls");
				displayTitle();
				gotoxy(17, 11); displayRowData(item);
				
				gotoxy(40, 13); printf("Apakah anda ingin melanjutkan penghapusan?");
				gotoxy(46, 14); printf("Masukkan pilihan anda (y/n): ");
				scanf("%s", &choice);
				
				if (choice == 'y' || choice == 'Y') {
					
					if (prevItem == NULL) {
						
						/*
						Apa bila item sebelumnya kosong, maka diasumsikan sebagai head.
						head akan dipindah ke node berikutnya, dan head sebelumnya (item) akan dihapus
						*/
						
						head = item->next;					
					} else if (item->next == NULL) {
						
						/*
						Apa bila item setelah node (item) yang dicapai kosong
						maka tail akan dipindah ke node sebelum item yang telah dicapai oleh looping.
						kemudian item akan dibuat NULL
						*/
						
						tail = prevItem;
						prevItem->next = NULL;
					} else {
						
						/*
						Jika ada node sebelumnya, maka node setelah prevItem akan diganti menjadi node setelah current item.
						jadi current item akan dilompati dan nantinya akan dihapus.
						*/
						
						prevItem->next = item->next;		
					}
					
					gotoxy(50, 17); printf("DATA BERHASIL DIHAPUS");
					check = 1;
					free(item);						// Penghapusan current item, dengan pengdealokasian memory
					gotoxy(47, 18); backToMenu();
						
				} else if (choice == 'n' || choice == 'N') {
					system("cls");
					menu();
				} else {
					gotoxy(50, 15); printf("PILIHAN TIDAK ADA");
					gotoxy(47, 16); backToMenu();
				}	
				
			} else {
				// Digunakan untuk melanjutkan ke item berikutnya
				prevItem = item;
				item = item->next;
			}
		}
		
		// Akan muncul bila sampai perulangan selesai, data masih belum ditemukan
		if (check == 0) {
			system("COLOR 4F");
			gotoxy(50, 10); printf("DATA TIDAK DITEMUKAN");
			gotoxy(47, 11); backToMenu();
		}
	}
	
}

void menu() {
	
	int choice, code;
	
	system("COLOR 1E");
	titleBar();
	
	gotoxy(48,7); printf("1. Tambah Data Transaksi\n");
	gotoxy(48,8); printf("2. Lihat Data Transaksi\n");
	gotoxy(48,9); printf("3. Ubah Data Transaksi\n");
	gotoxy(48,10); printf("4. Cari Data Transaksi\n");
	gotoxy(48,11); printf("5. Hapus Data Transaksi\n");
	gotoxy(48,12); printf("6. Keluar\n");
	gotoxy(48,14); printf("Masukkan Pilihan Anda : ");
	scanf("%d", &choice);
	
	if (choice == 1) {
		system("cls");
		userInputData();
	} else if (choice == 2) {
		system("cls");
		system("COLOR 0F");
		display();
		gotoxy(47, 25); backToMenu();
	} else if (choice == 3) {
		system("cls");
		titleBar();
		gotoxy(41, 8); printf("Masukkan kode buku yang ingin diedit : ");
		scanf("%d", &code);
		editData(code);
	} else if (choice == 4) {
		system("cls");
		titleBar();
		gotoxy(41, 8); printf("Masukkan kode buku yang ingin dicari : ");
		scanf("%d", &code);
		searchData(code);
	} else if (choice == 5) {
		system("cls");
		titleBar();
		gotoxy(41, 8); printf("Masukkan kode buku yang ingin dihapus : ");
		scanf("%d", &code);
		deleteData(code);
	} else if (choice == 6) {
		system("cls");
		gotoxy(53,13); printf("TERIMA KASIH");
		Sleep(1000);
		exit(0);
	} else {
		gotoxy(72,14); printf("Pilihan Anda Tidak Ada");
		backToMenu();
	}
}

void main() {
	menu();
}

