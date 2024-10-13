#include<iostream>
#include <string>
#include<Windows.h>
#include<chrono>
#include <thread>
using namespace std;

void MySetColor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}

void Clear() {
	this_thread::sleep_for(chrono::seconds(2));
	system("cls");
}

class User {
	string fullname;
	string mail; 
	int age;
	float height;
	int user_id;
public:
	static int static_id;

	User(string fullname, string mail, int age, float height) {
		this->fullname = fullname;
		this->mail = mail;
		this->age = age;
		this->height = height;
		static_id++;
		this->user_id = static_id;
	}

	int GetID() const
	{
		return user_id;
	}

	void SetID(int user_id)
	{
		this->user_id = user_id;
	}

	string GetFullname() const
	{
		return fullname;
	}

	void SetFullname(string fullname)
	{
		if (fullname.length() < 10)
		{
			cout << "Error!!! ";
		}
		else
		{
			this->fullname = fullname;
		}
	}

	string GetMail() const
	{
		return mail;
	}

	void SetMail(string mail)
	{
		if (mail.length() < 20)
		{
			cout << "Error!!! ";
		}
		else
		{
			this->mail = mail;
		}
	}

	int GetAge() const
	{
		return age;
	}

	void SetAge(int age)
	{
		if (age < 15 )
		{
			cout << "Error!!! ";
		}
		else
		{
			this->age = age;
		}
	}

	float GetHeight() const
	{
		return height;
	}

	void SetHeight(float height)
	{
		if (height < 1.30)
		{
			cout << "Error!!! ";
		}
		else
		{
			this->height = height;
		}
	}

};

int User::static_id = 0;

void ShowUser(User& user) {
	cout << "ID: " << user.GetID()<< endl;
	cout << "Fullname: " << user.GetFullname() << endl;
	cout << "Mail: " << user.GetMail() << endl;
	cout << "Age: " << user.GetAge() << endl;
	cout << "Height: " << user.GetHeight() << endl;
}

void SearchUser(User** users_array, int size, int search_id) {
	bool result = false;
	for (size_t i = 0; i < size; i++)
	{
		if (search_id == users_array[i]->GetID()) {
			cout << endl;
			ShowUser(*users_array[i]);
			cout << endl;
			result = true;
			break;
		}
	}
	
	if (!result) {
		MySetColor(3, 0);
		cout << "Not Found" << endl;
		MySetColor(7, 0);
	}
}

void CreateUser(User**& users_array, string new_fullname, string new_mail, int new_age, float new_height, int& size) {
	User* new_user = new User(new_fullname, new_mail, new_age, new_height);
	User** new_users_array = new User * [size + 1];

	for (int i = 0; i < size; i++)
	{
		new_users_array[i] = users_array[i];
	}
	new_users_array[size] = new_user;

	delete[] users_array;
	users_array = new_users_array; 
	size++;
	MySetColor(3, 0);
	cout << "User created" << endl;
	MySetColor(7, 0);

}

void UpdateUser(User**& users_array, int size, int update_id, int choise2) {
	bool result = false;
	for (size_t i = 0; i < size; i++)
	{
		if (update_id == users_array[i]->GetID()) {
			if (choise2 == 1) {
				string new_fullname;
				cout << "Enter new fullname: ";
				cin.ignore();
				getline(cin, new_fullname);
				users_array[i]->SetFullname(new_fullname);
				MySetColor(3, 0);
				cout << "Fullname changed" << endl;
				MySetColor(7, 0);
				result = true;
				break;
			}
			else if (choise2 == 2) {
				string new_mail;
				cout << "Enter new mail: ";
				cin.ignore();
				getline(cin, new_mail);
				users_array[i]->SetMail(new_mail);
				MySetColor(3, 0);
				cout << "Mail changed" << endl;
				MySetColor(7, 0);
				result = true;
				break;
			}
			else if (choise2 == 3) {
				int new_age;
				cout << "Enter new age: ";
				cin >> new_age;
				users_array[i]->SetAge(new_age);
				MySetColor(3, 0);
				cout << "Age changed" << endl;
				MySetColor(7, 0);
				result = true;
				break;
			}
			else if (choise2 == 4) {
				float new_height;
				cout << "Enter new height: ";
				cin >> new_height;
				users_array[i]->SetHeight(new_height);
				MySetColor(3, 0);
				cout << "Height changed" << endl;
				MySetColor(7, 0);
				result = true;
				break;
			}
			else {
				MySetColor(4, 0);
				cout << "Wrong choise" << endl;
				MySetColor(7, 0);
			}
		}
	}

	if (!result) {
		MySetColor(4, 0);
		cout << "Not Found" << endl;
		MySetColor(7, 0);
	}
}

void DeleteUser(User**& users_array, int& size, int delete_id) {
	bool result = false;
	int index;
	for (size_t i = 0; i < size; i++)
	{
		if (delete_id == users_array[i]->GetID()) {
			index = i;
			result = true;
			break;
		}
	}

	if (result) {
		delete users_array[index];

		User** new_users_array = new User * [size - 1] {};

		int k = 0;
		for (int i = 0; i < size; i++) 
		{
			if (i != index) {
				new_users_array[k++] = users_array[i];
			}
		}

		delete[] users_array;
		users_array = new_users_array; 
		size--;
		MySetColor(3, 0);
		cout << "User deleted" << endl;
		MySetColor(7, 0);

		for (int i = 0; i < size; i++) 
		{
			users_array[i]->SetID(i + 1);
		}

	}
	else{
		MySetColor(3, 0);
		cout << "Not Found" << endl;
		MySetColor(7, 0);
	}
}

void main() {

	int size = 3;
	User* user1 = new User("Narmin Alishova", "narmin.alishova@hotmail.com", 20, 1.59);
	User* user2 = new User("Aytac Mustafayeva", "aytac.mustafaueva.gmail.com", 25, 1.68);
	User* user3 = new User("Nigar Agayeva", "nigar.agayeva.gmail.com", 17, 1.45);

	User** users_array = new User * [size] {user1, user2, user3};
	
	while (true) {
		Clear();
		int choise;
		cout << "----------------------------" << endl;
		cout << "| 1. Show users            |" << endl;
		cout << "| 2. Shearch user          |" << endl;
		cout << "| 3. Create user           |" << endl;
		cout << "| 4. Update user           |" << endl;
		cout << "| 5. Delete user           |" << endl;
		cout << "| 6. Exit                  |" << endl;
		cout << "----------------------------" << endl;
		cout << "Enter choise:";
		cin >> choise;
		if (choise == 1) {
			for (size_t i = 0; i < size; i++)
			{
				ShowUser(*users_array[i]);
				cout << endl << endl;
			}
		}
		else if (choise == 2) {
			int search_id;
			cout << "Enter ID: ";
			cin >> search_id;
			SearchUser(users_array, size, search_id);
		}
		else if (choise == 3) {
			string new_fullname;
			cout << "Enter new fullname: ";
			cin.ignore();
			getline(cin, new_fullname);

			string new_mail;
			cout << "Enter new mail: ";
			cin.ignore();
			getline(cin, new_mail);

			int new_age;
			cout << "Enter new age: ";
			cin >> new_age;

			float new_height;
			cout << "Enter new height: ";
			cin >> new_height;

			CreateUser(users_array, new_fullname, new_mail, new_age, new_height, size);

		}
		else if (choise == 4) {
			int choise2;
			cout << "1. Fullname" << endl;
			cout << "2. Mail" << endl;
			cout << "3. Age" << endl;
			cout << "4. Height" << endl;
			cout << "Select what you want to change: ";
			cin >> choise2;
			int update_id;
			cout << "Enter ID: ";
			cin >> update_id;
			UpdateUser(users_array, size, update_id, choise2);
		}
		else if (choise == 5) {
			int delete_id;
			cout << "Enter ID: ";
			cin >> delete_id;
			DeleteUser(users_array, size, delete_id);

		}
		else if (choise == 6) {
			break;
		}
		else {
			MySetColor(4, 0);
			cout << "Wrong choise!!!" << endl;
			MySetColor(7, 0);
		}

	}




	for (int i = 0; i < size; i++) {
		delete users_array[i];
	}
	delete[] users_array;
}