#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#define FILE_MAX_ROW 554
#define HAND_ASEMBLE 1
#define REV_ASEMBLE 2
using namespace std;

class Hexa {
public:
	string num; // Change num to string type
	void printstr() {
		cout << num << endl;
	}
};
class Asmstr {
public:
	string num; // Change num to string type
	void printstr() {
		cout << num << endl;
	}
};
class convert {
public:
	vector<string> result_output;
	void print_all()
	{
		cout << "-------------------------------------" << endl;

		for (auto& string : result_output) { // Printing stored values
			cout << string << endl;
		}
		cout << "-------------------------------------" << endl;
	}
};
string findnn(map<string, string>rev, string input, vector<string> revList,bool newline)
{
	static string head;
	string out;
	if (input.empty()) 
	{
		return head="";
	}
	if (newline)
	{
		head="";
	}
	if (input.substr(input.length()-1, 1) == " ")
	{
		input.erase(input.length(), 1);
	}

	head += input.substr(input.length() - 2, 2);
	if(input.length()>=3)input.erase(input.length() - 3, 3);
	if (find(revList.begin(), revList.end(), input) == revList.end())
	{
		if (input.length() <= 2)
		{
			return head = "none→" + input;
		}
		return findnn(rev, input, revList,false);
	}
	if (rev[input].find("nn", 0) != string::npos) 
	{
		return out = rev[input].replace(rev[input].find("nn", 0), 2, head);
	}
	return out = rev[input].replace(rev[input].find("n", 0), 1, head);
}

string convert(map<string, string>rev, string input, vector<string> revList)
{
	findnn(rev_asemble, input, hexaL, true)
}

int main() {
	int switch_num;
	ifstream in{ "アセンブラ命令対応表.txt" };
	string reading_line_buffer;
	vector<Hexa> hexaList; // Using vector instead of array
	vector<Asmstr> asmList;
	vector<string> hexaL;
	vector<string> asmL;
	string hexst;
	map<string, string> asemble;
	map<string, string> rev_asemble;
	for (int i = 1; FILE_MAX_ROW >= i; i++) {
		getline(in, reading_line_buffer);
		cout << reading_line_buffer;
		if (i % 2)//奇数行の場合、16進数コード
		{
			Hexa hexaObj;
			hexaObj.num = reading_line_buffer;
			hexst = hexaObj.num;
			hexaL.push_back(reading_line_buffer);
			hexaList.push_back(hexaObj);
			cout << " → ";
		}
		else//偶数行の場合、アセンブラ命令
		{
			Asmstr asmObj;
			asmObj.num = reading_line_buffer;
			asmL.push_back(reading_line_buffer);
			asmList.push_back(asmObj);
			asemble.insert(make_pair(reading_line_buffer, hexst));
			rev_asemble.insert(make_pair(hexst, reading_line_buffer));
			cout << " |";
			if (!(i % 9))cout << endl << endl;
		}

	}
again:
	cout << endl << endl << endl;
	cout << "ハンドアセンブル:1" << endl << "逆ハンドアセンブル:2" << endl;

	cin >> switch_num;

	while (!(switch_num == HAND_ASEMBLE || switch_num == REV_ASEMBLE))
	{
		cout << "again:" << endl;
		cin >> switch_num;
	};
reagain:
	string input;
	string output_str;
	getline(cin, input);
	convert output;
	do {
		getline(cin, input);
		auto asm_result = find(asmL.begin(), asmL.end(), input);
		auto rev_result = find(hexaL.begin(), hexaL.end(), input);

		if (asm_result == asmL.end() && switch_num == HAND_ASEMBLE ||
			rev_result == hexaL.end() && switch_num == REV_ASEMBLE)
		{
			if (switch_num == REV_ASEMBLE)//逆アセンブル時、
			{

				output.result_output.push_back(convert(rev_asemble, input, hexaL));

			}else if (!(input.empty())) {
				cout << "none→";
				cout << input << endl;
				break;
			}
		}
		else if (!(input.empty()))
		{
			switch (switch_num) {
			case HAND_ASEMBLE:
				output_str = asemble.at(input);
				if (string::npos == input.find("nn", 0) &&
					string::npos == input.find("n", 0))
				{
				}
				else if (string::npos != input.find("nn", 0))
				{
					output_str += " nn";
				}
				else
				{
					output_str += " n";
				}
				output.result_output.push_back(output_str);
				break;
			case REV_ASEMBLE:
				if (rev_asemble[input].find("nn", 0) != string::npos)
				{
					output_str = rev_asemble.at(input);
				}
				output.result_output.push_back(rev_asemble.at(input));
			}
		}
	} while (!(input.empty()));
	output.print_all();
	cout << "again入力で再開、その他で終了" << endl;
	string com;
	getline(cin, com);
	if (com == "again")
	{
		goto again;
	}
	if (com == "ra")
	{
		goto reagain;
	}
	return 0;
}

