#include <iostream>
#include <string>
#include <vector>
using namespace std;

class cNguoi{
    private:
        string HoVaTen;
        int NamSinh;
        string CMND;
        string DiaChi;
    public:
        void Nhap();
        void Xuat();
};

void cNguoi::Nhap(){
    cout << "\nNhap Ho Va Ten: "; cin >> HoVaTen;
    cout << "\nNhap Nam Sinh: "; cin >> NamSinh;
    cout << "\nNhap CMND: "; cin >> CMND;
    cout << "\nNhap dia chi thuong tru: "; cin >> DiaChi;
};

void cNguoi::Xuat(){
    cout << "Ho Va Ten: " << HoVaTen << endl;
    cout << "\nNam Sinh: " << NamSinh << endl;
    cout << "\nCMND: " << CMND << endl;
    cout << "\nDia chi thuong tru: " << DiaChi << endl;
};

class cGiayChungNhan{
    protected:
        string SoGiay;
        int SoNguoi;
        vector <cNguoi> DanhSachNguoi;
        int SoThuaDat;
        int SoToBanDo;
        string DiaChiThuaDat;
        int DienTich;
        int NgayCap;
        int DonGiaThue;
    public:
        virtual void Nhap();
        virtual void Xuat();
        virtual int TinhThue();
        virtual bool Loai() = 0;
};

void cGiayChungNhan::Nhap(){
    cout << "Nhap so nguoi so huu: "; cin >> SoNguoi;
    DanhSachNguoi.resize(SoNguoi);
    for (int i = 0; i < SoNguoi; ++i){
        DanhSachNguoi[i].Nhap();
    }

    cout << "\nNhap So Giay: "; cin >> SoGiay;
    cout << "\nNhap so thua dat: "; cin >> SoThuaDat;
    cout << "\nNhap so to ban do: "; cin >> SoToBanDo;
    cout << "\nNhap dia chi thua dat: "; cin >> DiaChiThuaDat;
    cout << "\nNhap dien tich thua dat: "; cin >> DienTich;
    cout << "\nNhap ngay cap: "; cin >> NgayCap;
    cout << "\nNhap don gia thue: "; cin >> DonGiaThue;
};

void cGiayChungNhan::Xuat(){
    cout << "So giay chung nhan: " << SoGiay << endl;
    for (int i = 0; i < SoNguoi; ++i){
        DanhSachNguoi[i].Xuat();
    }

    cout << "\nSo giay: " << SoGiay << endl;
    cout << "\nSo thua dat: " << SoThuaDat << endl;
    cout << "\nSo to ban do: " << SoToBanDo << endl;
    cout << "\nDia chi thua dat: " << DiaChiThuaDat << endl;
    cout << "\nDien tich thua dat: " << DienTich << endl;
    cout << "\nNgay cap: " << NgayCap << endl;
    cout << "\nDon gia thue: " << DonGiaThue << endl;
};

int cGiayChungNhan::TinhThue(){
    return DienTich * DonGiaThue;
};

class cDatNongNghiep : public cGiayChungNhan{
    private:
        int ThoiHanSuDung;
    public:
        void Nhap();
        void Xuat();
        bool Loai();
        int ThoiHanSD();
};

void cDatNongNghiep::Nhap(){
    cGiayChungNhan::Nhap();
    cout << "\nNhap thoi han su dung: "; cin >> ThoiHanSuDung;
};

void cDatNongNghiep::Xuat(){
    cGiayChungNhan::Xuat();
    cout << "\nThoi han su dung: " << ThoiHanSuDung;
    cout << "\nTien thue: " << DonGiaThue * DienTich << endl;
};

int cDatNongNghiep::ThoiHanSD(){
    return ThoiHanSuDung;
}

bool cDatNongNghiep::Loai(){
    return 0;
};

class cDatPhiNongNghiep : public cGiayChungNhan{
    public:
        void Xuat();
        bool Loai();
};

void cDatPhiNongNghiep::Xuat(){
    cGiayChungNhan::Xuat();
    cout << "Tien thue: " << DonGiaThue * DienTich << endl;
};

bool cDatPhiNongNghiep::Loai(){
    return 1;
}

int main(){
    cout << "Nhap so luong giay chung nhan: ";
    int n; cin >> n;
    vector <cGiayChungNhan*> list(n);

    // Tao danh sach
    for (int i = 0; i < n; ++i){
        bool type; 
        cout << "\nNhap Giay Nong Nghiep (0) hay Giay Phi Nong Nghiep(1)?";
        cin >> type;
        cGiayChungNhan* x;
        if (type == 0){
            x = new cDatNongNghiep();
        } else {
            x = new cDatPhiNongNghiep();
        }
        x -> Nhap();
        list[i] = x;
    }

    // Tinh tien thue + thua dat co tien thue nhieu nhat?
    int ans = list[0] -> TinhThue();
    int pos = 0;
    for (int i = 1; i < n; ++i){
        if (list[i] -> TinhThue() > ans){
            ans = list[i] -> TinhThue();
            pos = i;
        }
    }

    list[pos] -> Xuat();

    //  Cac thua dat hen han su dung (cur_year < 2023)
    for (int i = 0; i < n; ++i){
        if (!list[i] -> Loai()){
            if (((cDatNongNghiep*)list[i]) -> ThoiHanSD() < 2023){
                list[i] -> Xuat();
            }
        }
    }
    return 0;
}