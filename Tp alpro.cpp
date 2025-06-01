#include<iostream>
#include<string>
#include <fstream>
#include <sstream>
#include <iomanip>	//memanipulasi input output
using namespace std;

class Warnet {
    friend ostream &operator<<(ostream &out, Warnet &warnet);
    friend istream &operator>>(istream &in, Warnet &warnet);

public:
    void tampilanAwal() {
        cout << "==============================================\n";
        cout << "              Warnet Suka Suka                \n";
        cout << "==============================================\n";
    }

    void login() {
        cout << "\nSELAMAT DATANG DI WARNET SUKA-SUKA\n";
        cout << "Silahkan login terlebih dahulu:\n";
        cout << "Masukkan username : ";
        cin >> username;
        cout << "Masukkan password : ";
        cin >> password;

        if (username == "admin" && password == 1234) {
            roles = 1;
        } else {
            roles = 2;
        }
    }
    
    void cekRole() {
        if (roles == 1) {
            admin();
        } else {
            anggota();
        }
    }

    void admin() {
    	int pilihan;
        cout << "\nAnda login sebagai ADMIN\n";
        cout<<endl;
        cout<<"Note kode: \n";
        cout<<"Kode A: Gaming\n";
        cout<<"Kode B: Kantoran\n";
        cout<<"Kode C: internet\n";
        cout<<endl;
        cout<<"1. Tambah Komputer\n";
        cout<<"2. Lihat Daftar Komputer\n";
        cout<<"3. Sewa Komputer\n";
        cout<<"masukan pilihan : ";
        cin>>pilihan;
        
        if(pilihan == 1){
        	int n;
        	tambahKomputer(n);
		}else if(pilihan == 2){
			lihatDaftar();
		}
		else if (pilihan==3){
			sewakomp();
		}
    }

    void anggota() {
        cout << "\nAnda login sebagai MEMBER\n";
    }
    
    void sewakomp(){
    	string kodekomp, namaPelanggan;
    	int jam;
    	double harga=0, totalbayar=0;
    	bool temukan=false;
    	
    	cin.ignore();
    	cout<<"Masukkan nama pelanggan: ";
    	getline(cin,namaPelanggan);
    	cout<<"Masukkan kode komputer ysng di sewa: ";
    	cin>>kodekomp;
    	cout<<"berapa jam ingin menyewa: ";
    	cin>>jam;
    	
    	lihatDaftar();
    	
    	ifstream file("text.txt");
    	
    	if (!file.is_open()) {
        cout << "Gagal membuka file data komputer.\n";
        return;
    }
    
    	string baris;
    	while(getline(file,baris)){
    		size_t pos = 0;
            int col = 0;
            string data[4];
		
		 while ((pos = baris.find("|")) != string::npos &&col<3) { 
                data[col] = baris.substr(0, pos);
                baris.erase(0, pos + 1);
                col++;
            }
    	
    	data[3]=baris;
    	
    	if (data[0]==kodekomp){
    		stringstream ss(data[3]);
			ss >> harga; //mengubah string menjadi doublea
    		totalbayar=harga*jam;
    		temukan = true;
                cout<<endl;
                cout<<"Detail sewaan: \n";
                cout<<"Kode komputer = "<<data[0]<<endl;
                cout<<"Kategori  = "<<data[1]<<endl;
                cout<<"Deskripsi = "<<data[2]<<endl;
                cout<<"harga per-jam = "<<harga<<endl;
                cout<<"Durasi sewa = "<<jam<<"Jam\n";
                cout<<"Total bayar = "<<totalbayar<<endl;
		}
	}	
		file.close();
		
		if(!temukan){
			cout<<"Data komputer tidak ada\n";
			
		}
	}
	
    void tambahKomputer(int n) {		
	cout<<endl;					
		cout<<"Ingin Menambahkan Berapa Komputer? = ";cin>>n;
    	daftarMenu *menu = new daftarMenu[n];  
    	cin.ignore(); 							
    	for(int i = 0; i < n; i++){		
			cout<<endl;		
    		cout<<"Masukan Komputer Ke-"<<i+1<<endl;
    		cout << "Masukkan Kode Komputer: ";
    		getline(cin, menu[i].kode);		
    		cout << "Masukkan Kategori Komputer: ";
    		getline(cin, menu[i].kategori);
    		cout << "Masukkan Deskripsi: ";
    		getline(cin, menu[i].deskripsi);
    		cout << "Masukkan Harga per-jam: ";
    		cin>>menu[i].hargaKomputerPerJam;
    		cin.ignore();
    		cout<<"\n|- - - - - - - - - - - - - - - - - - - -|\n";
	}
    										
    ofstream fileku("text.txt", ios::app);	
    if (fileku.is_open()) {					
    	for(int i = 0; i < n; i++){			
        	fileku << menu[i].kode << "|" 	
                   << menu[i].kategori << "|" 
                   << menu[i].deskripsi << "|"
                   << menu[i].hargaKomputerPerJam<<"\n";
   		}
        	fileku.close();						
        	cout << "Tambah komputer berhasil dilakukan!\n";
    	} else {
        	cout << "Gagal menambah komputer.\n";
    	}

	}
	
	void lihatDaftar(){
	ifstream adahku("text.txt");
    string baris;					
    if (adahku.is_open()) {			
	 	
        cout << "\n+" << string(20, '-') << "+" << string(20, '-') << "+"  
             << string(20, '-') << "+" << string(15, '-') << "+\n";
             
        cout << "|" << setw(20) << left << "Kode Komputer" << "|" 
             << setw(20)<<left << "Kategori"<< "|" 
             << setw(20)<<left << "Deskripsi" << "|"
             << setw(15)<<left<<"Harga per-jam"<<"|\n";
             
        cout << "+" << string(20, '-') << "+" << string(20, '-') << "+" 
             << string(20, '-') << "+" << string(15, '-') << "+\n";

       
        while (getline(adahku, baris)) {
            size_t pos = 0;
            int col = 0;
            string tokens[4];
            
            while ((pos = baris.find("|")) != string::npos) { 
                tokens[col] = baris.substr(0, pos);
                baris.erase(0, pos + 1);
                col++;
            }
            tokens[3] = baris; 
            
            cout << "|" << setw(20) << left << tokens[0].substr(0, 19) << "|"
                 << setw(20) << left << tokens[1].substr(0, 19) << "|"
                 << setw(20) << left << tokens[2].substr(0, 19) << "|"
                 << setw(15) << left << tokens[3].substr(0, 14) << "|\n";
        }
        
        cout << "+" << string(20, '-') << "+" << string(20, '-') << "+" 
             << string(20, '-') << "+" << string(15, '-') << "+\n";
        
        adahku.close();			//untuk menutup file
    }
     else {
        cout << "File tidak ditemukan atau tidak dapat dibuka.\n";
    }
        system("START /MIN NOTEPAD text.txt"); // untuk membuka file pada text.txt notepade++
	}

private:
    int roles;        
    int password;
    string username;
    
    struct daftarMenu {			//mendeklarasikan struct
    string kode, kategori, deskripsi;	//member struct
    int hargaKomputerPerJam;
	};
};


ostream &operator<<(ostream &out, Warnet &warnet) {
    warnet.tampilanAwal();
    return out;
}


istream &operator>>(istream &in, Warnet &warnet) {
    warnet.login();
    warnet.cekRole();
    warnet.admin();
    return in;
}

int main() {
	
    Warnet x;
    cout << x;   
    cin >> x;    
    return 0;
}
