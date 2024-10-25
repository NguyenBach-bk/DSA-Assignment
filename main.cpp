#include <iostream>

using namespace std;

struct Ngay
{
  int ngay, thang, nam;
};

struct SinhVien
{
  char maSV[8];
  char hoTen[50];
  int gioiTinh; // 0 Nữ 1 Nam
  Ngay ngaySinh;
  char diaChi[100];
  char lop[12];
  char khoa[7];
};

struct Node
{
  SinhVien data;
  Node *link;
};

struct List
{
  Node *first;
  Node *last;
};

// Khởi tạo danh sách rỗng
void
taoList (List &list)
{
  list.first = nullptr;
  list.last = nullptr;
}

// Tạo một sinh viên mới, nhập thông tin sinh viên từ người dùng
SinhVien
taoSinhVien ()
{
  SinhVien sv;
  cout << "Nhap ma sinh vien: ";
  cin >> sv.maSV;
  cout << "Nhap ho ten: ";
  cin.ignore ();
  cin.getline (sv.hoTen, 50);
  cout << "Nhap gioi tinh (0: Nu, 1: Nam): ";
  cin >> sv.gioiTinh;
  cout << "Nhap ngay sinh (ngay thang nam): ";
  cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
  cout << "Nhap dia chi: ";
  cin.ignore ();
  cin.getline (sv.diaChi, 100);
  cout << "Nhap lop: ";
  cin >> sv.lop;
  cout << "Nhap khoa: ";
  cin >> sv.khoa;
  return sv;
}

// Hàm so sánh chuỗi
int
ssChuoi (const char *str1, const char *str2)
{
  while (*str1 && (*str1 == *str2))
    {
      str1++;
      str2++;
    }
  if (*str1 == '\0' && *str2 == '\0')
    return 0;
  else
    return 1;
}
// Trả về 0, hai chuỗi giống nhau. Trả về 1 với trường hợp còn lại

// Thêm sinh viên bằng sắp xếp chèn
void
themSinhVien (List &list, SinhVien sv)
{
  Node *newNode = new Node{ sv, nullptr }; // Tạo nút mới
  if (!list.first || ssChuoi (sv.maSV, list.first->data.maSV) < 0)
    {
      // Sinh viên đầu tiên thêm vào node đầu
      newNode->link = list.first;
      list.first = newNode;
      if (!list.last)
        {
          list.last = newNode;
        }
    }
  else
    {
      Node *current = list.first;
      while (current->link && ssChuoi (current->link->data.maSV, sv.maSV) < 0)
        {
          current = current->link;
        }
      newNode->link = current->link;
      current->link = newNode;
      if (!newNode->link)
        {
          list.last = newNode;
        }
    }
}

// In danh sách sinh viên đã sắp xếp
void
inList (const List &list)
{
  Node *current = list.first;
  while (current)
    {
      cout << "Ma SV: " << current->data.maSV
           << ", Ho ten: " << current->data.hoTen << endl;
      current = current->link;
    }
}

// Tìm và in sinh viên có cùng ngày sinh
void
timgiongngaysinh (const List &list, Ngay ngaySinh)
{
  Node *current = list.first;
  bool found = false;
  while (current)
    {
      if (current->data.ngaySinh.ngay == ngaySinh.ngay
          && current->data.ngaySinh.thang == ngaySinh.thang
          && current->data.ngaySinh.nam == ngaySinh.nam)
        {
          cout << "Ma SV: " << current->data.maSV
               << ", Ho ten: " << current->data.hoTen << endl;
          found = true;
        }
      current = current->link;
    }
  if (!found)
    {
      cout << "Khong tim thay sinh vien cung ngay sinh" << endl;
    }
}

// Loại bỏ sinh viên có cùng ngày sinh
void
xoagiongngaysinh (List &list, Ngay ngaySinh)
{
  Node *current = list.first;
  Node *prev = nullptr;
  while (current)
    {
      if (current->data.ngaySinh.ngay == ngaySinh.ngay
          && current->data.ngaySinh.thang == ngaySinh.thang
          && current->data.ngaySinh.nam == ngaySinh.nam)
        {
          if (prev)
            {
              prev->link = current->link;
            }
          else
            {
              list.first = current->link;
            }
          Node *toDelete = current;
          current = current->link;
          delete toDelete;
        }
      else
        {
          prev = current;
          current = current->link;
        }
    }
}

int
main ()
{
  List list;
  taoList (list);

  int n;
  cout << "Nhap so luong sinh vien: ";
  cin >> n;

  for (int i = 0; i < n; ++i)
    {
      SinhVien sv = taoSinhVien ();
      themSinhVien (list, sv);
    }

  cout << "Danh sach sinh vien:\n";
  inList (list);

  Ngay ngaySinh;
  cout << "Nhap ngay sinh de tim kiem (ngay thang nam): ";
  cin >> ngaySinh.ngay >> ngaySinh.thang >> ngaySinh.nam;

  cout << "Sinh vien co cung ngay sinh:\n";
  timgiongngaysinh (list, ngaySinh);

  cout << "Xoa sinh vien co cung ngay sinh...\n";
  xoagiongngaysinh (list, ngaySinh);

  cout << "Danh sach sinh vien sau khi xoa:\n";
  inList (list);

  return 0;
}
