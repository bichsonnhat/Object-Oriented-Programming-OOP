#include <iostream>
#include <vector>
using namespace std;

class ChuongNgaiVat{
    protected:
        int length;
        int* a;
    public:
    ~ChuongNgaiVat();
    virtual void Nhap() = 0;
    virtual int Loai() = 0;
};

ChuongNgaiVat::~ChuongNgaiVat(){
    delete[] a;
}
class KhuRungChong : public ChuongNgaiVat{
    private:
        int Tao;
    public:
        void Nhap();
        int Loai();
        bool check(vector <int> u);
        int getTao();
};

void KhuRungChong::Nhap(){
    length = 7;
    a = new int [length];
    for (int i = 0; i < length; ++i){
        cout << "Nhap chieu cao cay chong thu " << i << " : "; 
        cin >> a[i];
    }

    cout << "Nhap chi so qua tao: "; cin >> Tao;
}

int KhuRungChong::Loai(){
    return 1;
}

int KhuRungChong::getTao(){
    return Tao;

}
bool KhuRungChong::check(vector <int> u){
    for (int i = 0; i < 7; ++i){
        if (u[i] + getTao() <= a[i]){
            return false;
        }
    }
    return true;
}

class DuongHamNui : public ChuongNgaiVat{
    private:
    public:
        void Nhap();
        int Loai();
        void setChieuCao(int h);
        bool check(int h);
};

void DuongHamNui::Nhap(){
    cout << "Nhap so luong duong ham: "; 
    cin >> length;

    a = new int [length];
    for (int i = 0; i < length; ++i){
        cout << "Nhap chieu cao duong ham thu " << i << " : ";
        cin >> a[i]; 
    }
}

int DuongHamNui::Loai(){
    return 2;
}

bool DuongHamNui::check(int h){
    int minn = 1e9;
    for (int i = 0; i < 5; ++i){
        minn = min(minn, a[i]);
    }
    return (h <= minn);
}

class QuaiVat : public ChuongNgaiVat{
    private:
    public:
        void Nhap();
        int Loai();
        bool check(vector <int> u);
};

void QuaiVat::Nhap(){
    length = 5;
    a = new int [length];
    for (int i = 0; i < length; ++i){
        cout << "Nhap do manh chieu thu " << i << " cua quai vat: ";
        cin >> a[i];
    }
};

int QuaiVat::Loai(){
    return 3;
}

bool QuaiVat::check(vector <int> u){
    int win = 0, def = 0;
    for (int i = 0; i < 5; ++i){
        if (u[i] > a[i]) win++;
        else def++;
    }
    return (win > def);
}

class NguoiChoi{
    private:
        int* SucNhay;
        int ChieuCao;
        int* SucManh;
    public:
        NguoiChoi(){
            SucNhay = new int [7];
            SucManh = new int [5];
        }

        ~NguoiChoi(){
            delete[] SucNhay;
            delete[] SucManh;
        }

        friend istream& operator >> (istream& input, NguoiChoi &p);
        vector <int> getSucNhay();
        vector <int> getSucManh();
        int getChieuCao();
};


istream& operator >> (istream& input, NguoiChoi &p){
    for (int i = 0; i < 7; ++i){
        cout << "Nhap suc nhay lan thu " << i << " : ";
        cin >> p.SucNhay[i];
    }

    cout << "Nhap chieu cao: "; cin >> p.ChieuCao;

    for (int i = 0; i < 7; ++i){
        cout << "Nhap suc manh lan thu " << i << " : ";
        cin >> p.SucManh[i];
    }
    return input;
}

int NguoiChoi::getChieuCao(){
    return ChieuCao;
}
vector <int> NguoiChoi::getSucNhay(){
    vector <int> result;
    for (int i = 0; i < 7; ++i){
        result.push_back(SucNhay[i]);
    }
    return result;
}

vector <int> NguoiChoi::getSucManh(){
    vector <int> result;
    for (int i = 0; i < 7; ++i){
        result.push_back(SucManh[i]);
    }
    return result;
}

int main(){
    int n;
    cout << "Nhap so luong chuong ngai vat: "; 
    cin >> n;

    vector <ChuongNgaiVat*> a(n);

    for (int i = 0; i < n; ++i){
        int type; 
        cout << "Loai chuong ngai vat: Khu rung chong (1), Duong ham nui (2), Quai vat (3)";
        cin >> type;

        switch (type){
        case 1:
            a[i] = new KhuRungChong;
            break;
        case 2:
            a[i] = new DuongHamNui;
            break;
        case 3:
            a[i] = new QuaiVat;
            break;
        }

        a[i] -> Nhap();
    }

    NguoiChoi p; 
    cin >> p;
    bool passed = true;
    for (int i = 0; i < n; ++i){
        int type = a[i] -> Loai();
        if (type == 1){
            if (((KhuRungChong*)a[i]) -> check(p.getSucNhay()) == 0){
                passed = false;
                break;
            }
        };

        if (type == 2){
            if (((DuongHamNui*)a[i]) -> check(p.getChieuCao()) == 0){
                passed = false;
                break;
            }
        };

        if (type == 3){
            if (((QuaiVat*)a[i]) -> check(p.getSucManh()) == 0){
                passed = false;
                break;
            }
        };
    }

    if (passed == true) cout << "Tim duoc kho bau.";
    else cout << "Khong tim duoc kho bau.";
    
    return 0;
}