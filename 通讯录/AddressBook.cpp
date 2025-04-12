#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

// 联系人类，包含姓名、性别、电话、城市、邮编信息
class Contact {
private:
    string name;    // 姓名
    string gender;  // 性别
    string tel;     // 电话
    string city;    // 城市
    string zip;     // 邮编

public:
    // 构造函数
    Contact() {}
    Contact(string n, string g, string t, string c, string z) {
        name = n;
        gender = g;
        tel = t;
        city = c;
        zip = z;
    }

    // 获取联系人信息的方法
    string getName() const { return name; }
    string getGender() const { return gender; }
    string getTel() const { return tel; }
    string getCity() const { return city; }
    string getZip() const { return zip; }

    // 设置联系人信息的方法
    void setName(string n) { name = n; }
    void setGender(string g) { gender = g; }
    void setTel(string t) { tel = t; }
    void setCity(string c) { city = c; }
    void setZip(string z) { zip = z; }

    // 显示联系人信息
    void display() const {
        cout << left << setw(15) << name
             << setw(8) << gender
             << setw(15) << tel
             << setw(15) << city
             << setw(10) << zip << endl;
    }
};

// 通讯录类
class AddressBook {
private:
    vector<Contact> contacts;  // 存储联系人的向量
    string filename;          // 通讯录文件名

public:
    // 构造函数
    AddressBook() {
        filename = "contacts.dat";
    }

    // 创建新的通讯录
    void Create() {
        contacts.clear();  // 清空现有联系人
        ofstream file(filename, ios::out | ios::trunc);  // 创建或清空文件
        if (file.is_open()) {
            file.close();
            cout << "通讯录已成功创建！" << endl;
        } else {
            cout << "无法创建通讯录文件！" << endl;
        }
    }

    // 添加新联系人
    void Add() {
        string name, gender, tel, city, zip;
        
        cout << "请输入联系人信息：" << endl;
        cout << "姓名: ";
        cin >> name;
        
        cout << "性别 (男/女): ";
        cin >> gender;
        
        cout << "电话: ";
        cin >> tel;
        
        cout << "城市: ";
        cin >> city;
        
        cout << "邮编: ";
        cin >> zip;
        
        // 创建新联系人并添加到向量中
        Contact newContact(name, gender, tel, city, zip);
        contacts.push_back(newContact);
        
        // 保存到文件
        SaveToFile();
        
        cout << "联系人已成功添加！" << endl;
    }

    // 查找联系人
    void Find() {
        if (contacts.empty()) {
            cout << "通讯录为空！" << endl;
            return;
        }
        
        string name;
        cout << "请输入要查找的联系人姓名: ";
        cin >> name;
        
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.getName() == name) {
                cout << "\n找到联系人信息：" << endl;
                cout << left << setw(15) << "姓名"
                     << setw(8) << "性别"
                     << setw(15) << "电话"
                     << setw(15) << "城市"
                     << setw(10) << "邮编" << endl;
                cout << string(60, '-') << endl;
                contact.display();
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "通讯录中没有此人的信息！" << endl;
        }
    }

    // 修改联系人信息
    void Alter() {
        if (contacts.empty()) {
            cout << "通讯录为空！" << endl;
            return;
        }
        
        string name;
        cout << "请输入要修改的联系人姓名: ";
        cin >> name;
        
        bool found = false;
        for (auto& contact : contacts) {
            if (contact.getName() == name) {
                cout << "找到联系人，请输入新的信息：" << endl;
                
                string newName, gender, tel, city, zip;
                
                cout << "姓名 (原: " << contact.getName() << "): ";
                cin >> newName;
                
                cout << "性别 (原: " << contact.getGender() << "): ";
                cin >> gender;
                
                cout << "电话 (原: " << contact.getTel() << "): ";
                cin >> tel;
                
                cout << "城市 (原: " << contact.getCity() << "): ";
                cin >> city;
                
                cout << "邮编 (原: " << contact.getZip() << "): ";
                cin >> zip;
                
                // 更新联系人信息
                contact.setName(newName);
                contact.setGender(gender);
                contact.setTel(tel);
                contact.setCity(city);
                contact.setZip(zip);
                
                // 保存到文件
                SaveToFile();
                
                cout << "联系人信息已成功修改！" << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "通讯录中没有此人的信息！" << endl;
        }
    }

    // 删除联系人
    void Delete() {
        if (contacts.empty()) {
            cout << "通讯录为空！" << endl;
            return;
        }
        
        string name;
        cout << "请输入要删除的联系人姓名: ";
        cin >> name;
        
        bool found = false;
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->getName() == name) {
                contacts.erase(it);
                
                // 保存到文件
                SaveToFile();
                
                cout << "联系人已成功删除！" << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "通讯录中没有此人的信息！" << endl;
        }
    }

    // 显示所有联系人
    void List() {
        if (contacts.empty()) {
            cout << "通讯录为空！" << endl;
            return;
        }
        
        cout << "\n通讯录中的所有联系人：" << endl;
        cout << left << setw(15) << "姓名"
             << setw(8) << "性别"
             << setw(15) << "电话"
             << setw(15) << "城市"
             << setw(10) << "邮编" << endl;
        cout << string(60, '-') << endl;
        
        for (const auto& contact : contacts) {
            contact.display();
        }
    }

    // 从文件加载联系人
    void LoadFromFile() {
        contacts.clear();
        ifstream file(filename, ios::in);
        if (!file.is_open()) {
            return;  // 文件不存在，返回空列表
        }
        
        string name, gender, tel, city, zip;
        while (file >> name >> gender >> tel >> city >> zip) {
            Contact contact(name, gender, tel, city, zip);
            contacts.push_back(contact);
        }
        
        file.close();
    }

    // 保存联系人到文件
    void SaveToFile() {
        ofstream file(filename, ios::out | ios::trunc);
        if (!file.is_open()) {
            cout << "无法打开文件进行保存！" << endl;
            return;
        }
        
        for (const auto& contact : contacts) {
            file << contact.getName() << " "
                 << contact.getGender() << " "
                 << contact.getTel() << " "
                 << contact.getCity() << " "
                 << contact.getZip() << endl;
        }
        
        file.close();
    }
};

// 显示菜单
void Menu() {
    cout << "\n========== 通讯录管理系统 ==========" << endl;
    cout << "1. Create - 创建新的通讯录" << endl;
    cout << "2. Add    - 添加联系人" << endl;
    cout << "3. Find   - 查找联系人" << endl;
    cout << "4. Alter  - 修改联系人" << endl;
    cout << "5. Delete - 删除联系人" << endl;
    cout << "6. List   - 显示所有联系人" << endl;
    cout << "0. Quit   - 退出系统" << endl;
    cout << "==================================" << endl;
    cout << "请输入选项 (0-6): ";
}

// 退出系统
void Quit() {
    cout << "感谢使用通讯录管理系统，再见！" << endl;
    exit(0);
}

// 主函数
int main() {
    AddressBook addressBook;
    addressBook.LoadFromFile();  // 加载现有通讯录
    
    int choice;
    
    while (true) {
        Menu();  // 显示菜单
        
        // 获取用户选择
        if (!(cin >> choice)) {
            cin.clear();  // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略错误输入
            cout << "输入无效，请重新输入数字选项！" << endl;
            continue;
        }
        
        // 处理用户选择
        switch (choice) {
            case 0:  // 退出
                Quit();
                break;
            case 1:  // 创建
                addressBook.Create();
                break;
            case 2:  // 添加
                addressBook.Add();
                break;
            case 3:  // 查找
                addressBook.Find();
                break;
            case 4:  // 修改
                addressBook.Alter();
                break;
            case 5:  // 删除
                addressBook.Delete();
                break;
            case 6:  // 列出
                addressBook.List();
                break;
            default:
                cout << "无效选项，请重新输入！" << endl;
        }
    }
    
    return 0;
}