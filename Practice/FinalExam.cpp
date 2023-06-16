#include <iostream>
#include <vector>
using namespace std;

struct Date{
    int dd, yy, mm;
};

class cVe{
    protected:
        string MaVe;
        string HoVaTen;
    public:
        virtual void Nhap();
        virtual void Xuat();
        virtual int Loai() = 0;
};

void cVe::Nhap(){
    cout << "Nhap ma ve: ";
    cin >> MaVe;
    cout << "Nhap Ho va ten khach hang: "; 
    cin >> HoVaTen;
};

void cVe::Xuat(){
    cout << "Ma ve: " << MaVe;
    cout << "\nHo va ten khach hang: " << HoVaTen;
};

class cVeThuong : public cVe{
    private:
        int SoKm;
        int GiaVe;
    public:
        void Nhap();
        void Xuat();
        int Loai();
        int getGiaVe();
};

void cVeThuong::Nhap(){
    cVe::Nhap();
    cout << "Nhap so km se di: "; 
    cin >> SoKm;
    if (SoKm <= 5) GiaVe = 10000;
    if (5 < SoKm && SoKm <= 10) GiaVe = 15000;
    if (10 < SoKm && SoKm <= 20) GiaVe = 20000;
    if (20 < SoKm) GiaVe = 25000;   
};

void cVeThuong::Xuat(){
    cVe::Xuat();
    cout << "\nSo km se di: " << SoKm;
    cout << "\nGia ve: " << GiaVe;
};

int cVeThuong::Loai(){
    return 1;
};

int cVeThuong::getGiaVe(){
    return GiaVe;
}

class cVeHSSV : public cVe{
    private:
        string MSSV;
        int SoKm;
        int GiaVe;
    public:
        void Nhap();
        void Xuat();
        int Loai();
        int getGiaVe();
};

void cVeHSSV::Nhap(){
    cVe::Nhap();
    cout << "Nhap ma so sinh vien: ";
    cin >> MSSV;
    cout << "Nhap so km se di: "; 
    cin >> SoKm;
    if (SoKm <= 5) GiaVe = 6000;
    if (5 < SoKm && SoKm <= 10) GiaVe = 10000;
    if (10 < SoKm && SoKm <= 20) GiaVe = 12000;
    if (20 < SoKm) GiaVe = 16000;   
};

void cVeHSSV::Xuat(){
    cVe::Xuat();
    cout << "\nMa so sinh vien: " << MSSV;
    cout << "\nSo km se di: " << SoKm;
    cout << "\nGia ve: " << GiaVe;
};

int cVeHSSV::Loai(){
    return 2;
};

int cVeHSSV::getGiaVe(){
    return GiaVe;
};

class cVeThang : public cVe{
    private:
        Date NgayDangKy;
        Date NgayHetHan;
    public:
        void Nhap();
        void Xuat();
        int Loai();
};

void cVeThang::Nhap(){
    cVe::Nhap();
    cout << "Nhap ngay dang ki dang dd/mm/yy: ";
    cin >> NgayDangKy.dd >> NgayDangKy.mm >> NgayDangKy.yy;
    cout << "Nhap ngay het han dang dd/mm/yy: ";
    cin >> NgayHetHan.dd >> NgayHetHan.mm >> NgayHetHan.yy;
};

void cVeThang::Xuat(){
    cVe::Xuat();
    cout << "\nNgay dang ky: " << NgayDangKy.dd << '/' << NgayDangKy.mm << '/' << NgayDangKy.yy;
    cout << "\nNgay het han: " << NgayHetHan.dd << '/' << NgayHetHan.mm << '/' << NgayHetHan.yy;
};

int cVeThang::Loai(){
    return 3;
};

int main(){
    // Cau 1
    int n;
    cout << "Nhap so luong ve da ban: ";
    cin >> n;
    vector <cVe*> a(n);

    for (int i = 0; i < n; ++i){
        int type;
        cout << "Nhap loai ve da ban: Ve Thuong(1), Ve HSSV (2), Ve Thang (3): ";
        cin >> type;
        switch (type){
        case 1:
            a[i] = new cVeThuong;
            break;
        
        case 2:
            a[i] = new cVeHSSV;
            break;

        case 3:
            a[i] = new cVeThang;
            break;
        }

        a[i] -> Nhap();
    }

    // Cau 2
    int cost_HSSV = 0;
    for (int i = 0; i < n; ++i){
        if (a[i] -> Loai() == 2){
            cost_HSSV += ((cVeHSSV*)(a[i])) -> getGiaVe();
        }
    }

    cout << "\nTong so tien ve da ban la ve danh cho hoc sinh, sinh vien: " << cost_HSSV;

    // Cau 3
    vector <int> d(30000, 0);

    int max_sell = 0, cost_max = 0;
    for (int i = 0; i < n; ++i){
        if (a[i] -> Loai() == 1){
            int cost = ((cVeThuong*)(a[i])) -> getGiaVe();
            d[cost] += 1;
            if (d[cost] > max_sell){
                max_sell = d[cost];
                cost_max = cost;
            }
        }
    }

    cout << "\nTrong loai ve luot thuong da ban, muc gia duoc ban nhieu nhat: " << cost_max;

    // Cau 4
    int max_ticket = 0;
    for (int i = 0; i < n; ++i){
        if (a[i] -> Loai() == 1){
            int cost = ((cVeThuong*)(a[i])) -> getGiaVe();
            max_ticket = max(max_ticket, cost);
        }
    }

    cout << "\nVe thuong da ban co menh gia cao nhat:\n";
    for (int i = 0; i < n; ++i){
        if (a[i] -> Loai() == 1){
            int cost = ((cVeThuong*)(a[i])) -> getGiaVe();
            if (cost == max_ticket){
                a[i] -> Xuat();
                break;
            }
        }
    }
    
    return 0;
}