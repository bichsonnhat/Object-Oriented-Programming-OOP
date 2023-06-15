#include <iostream>
#include <vector>
using namespace std;

class ThuVien{
    protected:
        string MaSach;
        string TenSach;
        string NXB;
        int SoLuong;
        int DonGia;
    public:
        virtual void Nhap();
        virtual void Xuat();
        virtual bool Loai() = 0;
        virtual int ThanhTien() = 0;
};

void ThuVien::Nhap(){
    cout << "Nhap ma sach: "; 
    cin >> MaSach;
    cout << "Nhap ten sach: ";
    cin >> TenSach;
    cout << "Nhap nha xuat ban: ";
    cin >> NXB;
    cout << "Nhap so luong: ";
    cin >> SoLuong;
    cout << "Nhap don gia: ";
    cin >> DonGia;
};

void ThuVien::Xuat(){
    cout << "Ma sach: " << MaSach;
    cout << "\nTen sach: " << TenSach;
    cout << "\nNha xuat ban: " << NXB;
    cout << "\nSo luong: " << SoLuong;
    cout << "\nDon gia: " << DonGia;
};

class SachGiaoKhoa : public ThuVien{
    private:
        bool TinhTrang;
    public:
        void Nhap();
        void Xuat();
        int ThanhTien();
        bool Loai();
        string getNXB();
};

void SachGiaoKhoa::Nhap(){
    ThuVien::Nhap();
    cout << "Nhap tinh trang: Cu (0), Moi (1): "; cin >> TinhTrang;
};

void SachGiaoKhoa::Xuat(){
    ThuVien::Xuat();
    cout << "\nTinh trang: " << (TinhTrang ? "Moi" : "Cu");
}

int SachGiaoKhoa::ThanhTien(){
    return (SoLuong * DonGia * (TinhTrang ? 1 : 0.5));
}

bool SachGiaoKhoa::Loai(){
    return 0;
}

string SachGiaoKhoa::getNXB(){
    return NXB;
}

class SachThamKhao : public ThuVien{
    private:
        int TienThue;
    public:
        void Nhap();
        void Xuat();
        int ThanhTien();
        bool Loai();       
};

void SachThamKhao::Nhap(){
    ThuVien::Nhap();
    cout << "Nhap tien thue: "; 
    cin >> TienThue;
};

void SachThamKhao::Xuat(){
    ThuVien::Xuat();
    cout << "\nTien thue: " << TienThue;
};

int SachThamKhao::ThanhTien(){
    return SoLuong * DonGia + TienThue;
};

bool SachThamKhao::Loai(){
    return 1;
}

int main(){
    // Cau a
    int n; 
    cout << "Nhap so luong sach trong thu vien: ";
    cin >> n;
    vector <ThuVien*> a(n);
    for (int i = 0; i < n; ++i){
        bool type; 
        cout << "Nhap loai: Sach giao khoa (0), Sach Tham Khao (1): "; cin >> type;
        switch (type)
        {
            case 0:
                a[i] = new SachGiaoKhoa;
                break;
            case 1:
                a[i] = new SachThamKhao;
                break;
        }
        a[i] -> Nhap();
    }

    // Cau b
    int minn = 1e9, result = 0;
    for (int i = 0; i < n; ++i){
        int cost = a[i] -> ThanhTien();
        result += cost;
        minn = min(minn, cost);
    }

    cout << "Thanh tien ma thu vien phai tra cho tung loai sach: " << result << endl;
    cout << "Nhung loai sach co thanh tien it tra nhat: \n";

    for (int i = 0; i < n; ++i){
        if (a[i] -> ThanhTien() == minn){
            a[i] -> Xuat();
        }
    }

    // Cau c
    string name; 
    cout << "Nhap ten nha xuat ban: "; cin >> name;
    cout << "Thong tin sach giao khoa co nha xuat ban tuong ung voi " << name << ":\n";
    for (int i = 0; i < n; ++i){
        if (a[i] -> Loai() == 0){
            if (((SachGiaoKhoa*)(a[i])) -> getNXB() == name){
                a[i] -> Xuat();
            }
        }
    }
    return 0;
}