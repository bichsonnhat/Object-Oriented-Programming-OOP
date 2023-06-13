#include <bits/stdc++.h>
using namespace std;

class NguonDien{
    protected:
        int HieuSuat;
    public:
        virtual void Nhap(){
            cin >> HieuSuat;
        };
        virtual int TinhCongSuat() = 0;
        virtual int Loai() = 0;
};

class ThuyDien : public NguonDien{
    private:
        int SoToMay;
        bool TichNang;
    public:
        void Nhap(){
            NguonDien::Nhap();
            cin >> SoToMay >> TichNang;
        }
        int TinhCongSuat(){
            return HieuSuat * SoToMay;
        };
        bool getTichNang(){
            return TichNang;
        }

        int Loai(){
            return 1;
        }
};

class NhietDien : public NguonDien{
    private:
        int LuongThan; // (tan / h)
        int TimeAcTive;
    public:
        void Nhap(){
            NguonDien::Nhap();
            cin >> LuongThan;
        }

        int TinhCongSuat(){
            return HieuSuat * LuongThan;
        }

        void setTimeAcTive(int value){
            TimeAcTive = value;
        }

        int Loai(){
            return 2;
        }
};

class DienGio : public NguonDien{
    private:
        int SoTuaBin;
        int MaxTocDoGio;
        int TimeAcTive;
    public:
        void Nhap(){
            NguonDien::Nhap();
            cin >> SoTuaBin >> MaxTocDoGio;
            TimeAcTive = -1;
        }

        int TinhCongSuat(){
            return HieuSuat * SoTuaBin;
        }

        int GetMaxTocDoGio(){
            return MaxTocDoGio;
        }

        int HieuSuatThuc(){
            return 0;
        }

        void setTimeAcTive(int value){
            TimeAcTive = value;
        }

        int getTimeActive(){
            return TimeAcTive;
        }

        int Loai(){
            return 3;
        }
};

class DienMatTroi : public NguonDien{
    private:
        int DienTichPin;
        int TimeAcTive;
    public:
        void Nhap(){
            NguonDien::Nhap();
            cin >> DienTichPin;
            TimeAcTive = -1;
        }

        int TinhCongSuat(){
            return HieuSuat * DienTichPin;
        }

        int getTimeActive(){
            return TimeAcTive;
        }

        void setTimeAcTive(int value){
            TimeAcTive = value;
        }

        int Loai(){
            return 4;
        }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen("TRAINING.INP","r",stdin);
        freopen("TRAINING.OUT","w",stdout);
    #endif
    int n; cin >> n;
    vector <NguonDien*> a(n);
    for (int i = 0; i < n; ++i){
        int type; cin >> type;
        switch (type){
            case 1: 
                a[i] = new ThuyDien;
                break;
            case 2:
                a[i] = new NhietDien;
                break;
            case 3:
                a[i] = new DienGio;
                break;
            case 4:
                a[i] = new DienMatTroi;
                break;
        }
        a[i] -> Nhap();
    }

    int m; cin >> m;
    int DuThua = 0;
    bool can = 0;
    for (int i = 0; i < n; ++i){
        if (a[i] -> Loai() == 1){
            if (((ThuyDien*)a[i]) -> getTichNang() == 1){
                can = 1;
                break;
            }
        }
    }

    long long result = 0;
    for (int i = 0; i < m; ++i){
        int times; cin >> times;
        int TocDoGio; cin >> TocDoGio;
        bool CoMay; cin >> CoMay;
        int TongCS; cin >> TongCS;
        int CS = 0;
        for (int j = 0; j < n; ++j){
            NguonDien* u = a[j];
            int type = u -> Loai();
            if (type == 1){
                    CS += u -> TinhCongSuat();
                    // break;
            }
            if (type == 2){
                    CS += u -> TinhCongSuat();
            }
            if (type == 3){
                    int x = (((DienGio*)a[j]) -> getTimeActive());
                    if (x == -1 || x == times){ 
                        int t = TocDoGio / (((DienGio*)u) -> GetMaxTocDoGio());
                        int curHS = (100 * TocDoGio) / ((((DienGio*)u)) -> GetMaxTocDoGio());
                        int k = (ceil) ((float)(curHS * (u -> TinhCongSuat())) / 100);
                        CS += k;
                    }
            }
            if (type == 4){
                        int x = ((DienMatTroi*)a[j]) -> getTimeActive();
                        if (x == -1 || x == times){
                            int curHS = 0;
                            if (11 <= times && times <= 13){
                                curHS = 100;
                            }
                            if (18 <= times && times <= 23){
                                curHS = 0;
                            }
                            if (0 <= times && times <= 6){
                                curHS = 0;
                            }
                            if (7 <= times && times <= 10){
                                curHS = (times - 7 + 1) * 20;
                            }
                            if (14 <= times && times <= 17){
                                curHS = 100 - (times - 14 + 1) * 20;
                            }
                            CS += ((CoMay == 0) * curHS * (u -> TinhCongSuat()) / 100);
                        }
                }
        }
        if (CS >= TongCS || ((CS < TongCS) && (CS + DuThua >= TongCS))){
                int rem = CS - TongCS;
                if (CS < TongCS){
                    DuThua = (CS + DuThua) - TongCS;
                }
                if (can == 1){
                    DuThua += CS - TongCS;
                }   
                if ((rem * 100 / TongCS) > 20){
                    for (int j = 0; j < n; ++j){
                        if (a[j] -> Loai() == 3) ((DienGio*)a[j]) -> setTimeAcTive(times + 2);
                        if (a[j] -> Loai() == 4) ((DienMatTroi*)a[j]) -> setTimeAcTive(times + 2);
                    }
                }
                result += TongCS * 3000 * 1000; 
                // cout << TongCS * 3000 * 1000 << endl;
            } else {
                // cout << DuThua << endl;
                CS += DuThua;
                int rem = TongCS - CS;
                DuThua = 0;
                if (rem * 100 / TongCS > 20){
                    for (int j = 0; j < n; ++j){
                        if (a[j] -> Loai() == 3) ((DienGio*)a[j]) -> setTimeAcTive(times + 2);
                        if (a[j] -> Loai() == 4) ((DienMatTroi*)a[j]) -> setTimeAcTive(times + 2);
                    }
                }
                int x = 100 * (CS / TongCS);
                int cost = 3000;
                if (x < 80) cost = 2500;
                if (x <= 50) cost = 2000;
                result += CS * 1000 * cost;
            }
    }
    cout << result << endl;

    return 0;
}