#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node
{
	char ch;
	double freq;
	Node* left, * right;
};

Node* getNode(char ch, double freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

// ����� ����� ������
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right)
	{
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int& index, string str)
{
	if (root == nullptr)
	{
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void buildHuffmanTree(string text)
{
	// ��������� ������� � ��������� map
	unordered_map<char, double> freq;
	freq['�'] = 0.067; freq['�'] = 0.019; freq['�'] = 0.039; freq['�'] = 0.012; freq['�'] = 0.027; freq['�'] = 0.063; freq[' '] = 0.154; freq['�'] = 0.008; freq['�'] = 0.012;
	freq['�'] = 0.051; freq['�'] = 0.013; freq['�'] = 0.03; freq['�'] = 0.037; freq['�'] = 0.028; freq['�'] = 0.048; freq['�'] = 0.089; freq['�'] = 0.025; freq['�'] = 0.043;
	freq['�'] = 0.048; freq['�'] = 0.048; freq['�'] = 0.024; freq['�'] = 0.001; freq['�'] = 0.007; freq['�'] = 0.003; freq['�'] = 0.029; freq['�'] = 0.007; freq['�'] = 0.011;
	freq['�'] = 0.001; freq['�'] = 0.016; freq['�'] = 0.002; freq['�'] = 0.016; freq['�'] = 0.022;

	// ������� ������������ ������� ��� �������� �������� ����� ������
	priority_queue<Node*, vector<Node*>, comp> pq;

	// ������� �������� ���� ��� ������� ������� � ��������� � ������������ �������
	for (auto pair : freq)
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// ������ �� ��� ���, ���� � ������� �� ����� ����� ������ ����
	while (pq.size() != 1)
	{
		// ������� ��� ���� � ��������� �����������
		// (����� ������ �������) �� �������
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		// ������� ����� ���������� ���� � ����� ����� ������
		// ��� �������� � � ��������, ������ �����
		// ������ ���� �����. ��������� ����� ����
		// � ������������ �������.
		double sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root ������ ��������� �� ������ ������ ��������
	Node* root = pq.top();

	// �������� �� ������ �������� � ��������� ���� ��������
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "���� �������� :\n" << '\n';
	for (auto pair : huffmanCode)
	{
		cout << pair.first << " " << pair.second << '\n';
	}

	string str = "";
	for (char ch : text)
	{
		str += huffmanCode[ch];
	}

	cout << "\n�������������� ������ ������� �������� :\n" << str << '\n';

	int index = -1;
	cout << "\n�������������� ������ : \n";
	while (index < (int)str.size() - 2)
	{
		decode(root, index, str);
	}
}

void buildShenonTree(string text) 
{
	unordered_map<char, string> ShenonCode;
	ShenonCode['�'] = "1011"; ShenonCode['�'] = "001000"; ShenonCode['�'] = "01100";
	ShenonCode['�'] = "000100"; ShenonCode['�'] = "00111"; ShenonCode['�'] = "1010";
	ShenonCode[' '] = "111"; ShenonCode['�'] = "0000100"; ShenonCode['�'] = "000011";
	ShenonCode['�'] = "1001"; ShenonCode['�'] = "000101"; ShenonCode['�'] = "01010";
	ShenonCode['�'] = "01011"; ShenonCode['�'] = "01000"; ShenonCode['�'] = "10001";
	ShenonCode['�'] = "110"; ShenonCode['�'] = "00110"; ShenonCode['�'] = "01101";
	ShenonCode['�'] = "10000"; ShenonCode['�'] = "0111"; ShenonCode['�'] = "00101";
	ShenonCode['�'] = "0000000001"; ShenonCode['�'] = "000001"; ShenonCode['�'] = "00000001";
	ShenonCode['�'] = "01001"; ShenonCode['�'] = "0000001"; ShenonCode['�'] = "0000101";
	ShenonCode['�'] = "0000000000"; ShenonCode['�'] = "000111"; ShenonCode['�'] = "000000001";
	ShenonCode['�'] = "000110"; ShenonCode['�'] = "001001";

	string str = "";
	for (char ch : text)
	{
		str += ShenonCode[ch];
	}

	cout << "\n�������������� ������ ������� �������-���� :\n" << str << '\n';

	string compare = "", decoded = "";

	cout << "\n�������������� ������ : \n";
	for (char ch : str)
	{
		compare += ch;
		for (auto pair : ShenonCode)
		{
			if (compare == pair.second)
			{
				decoded += pair.first;
				compare = "";
			}
		}
	}
	cout << decoded;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	string text = "������������� � � ������� �� ��������� ���������� ��������  ������ ����� ������� � ����������� �������� ����������� ����� �������� ������ �� ���  ��� ������ �������� ���������� �� ����� ��� ��� �� ����� ���� ���������� ����������  ������ � ����� �� ������ �������� ������� � ��������� ���� ������ ������������� ������  � ��������� �������� �� ��������  �������  ��� ������  ������� ������� �������������� ��������������� � �������� ���� ������ �� �������� �� ��� ������� ������� ���� � � ����  �������� �� ������ ����� ��� ��������� ��� ���������� ����� � ������ ������� �������� ��� �������� ������ ������ �� ������ ��������� ���������� ������� ����� ����� ����� ����� �������� ������  � �  �������������  ���������� ����� ����� ����������� ���� ��� �������� ��� ����������� ����� ����� � ��� � ��� ��������  �������� �� �������  �����������  �� ��������������� �� ��� ����� ��� ����� ����� ��� ������ ���  ����  ���������� ������  �������� ���������� ������� ��� ��� �� �������� ��� ��������� ���������� ����� ������ ��������� ��� ��� ���� � ������� � ���� ��������� ���� � ����� ������� ������ ������� ������� ����������� � ���������� ����� ������ � ����� ������������ ��������� ������ �������� ��� � ������ �������� ������� � �������� ������ � ������ ���� ���� ����� ��������� ���������� ���� �� ���������� ������������� ���������� ������������ �������� ������ ��� ������ ������������ ��� ����� �� ������� ����� ��������� ��������� ��� �����  ��������� � ������� �������� ��� ������� ����� ������ � ��������� �������� ��� �� �� ���� ������ ����� ������� ����� ������ ������ ���� ����� ������ ���� �� ��������� ������� ��������������� ����������� ������� ������ ���� ���������� � ����������� �� ���������� �������  ������ � ��������� ���������� ���� ������ ����� ���� ����� ��� ����� � �� ��������� �� ���������� ������ �� ���� �� �� ���� ������ �������  ���������� ���� ����� �����������  �� ������ ������ ������� �������� �� ���� ��� ������ ���� ����� � ����  ������ � ������ ������ ���� ����� ����������� �� ������������ ����� � �� ������ �����  ������ ���������� � ������� ������� ����� ������ ����� �������� � �������� ������ ���� ������� �������� � �� ����� �� ��� ���� ������ �������  ���������� ���� � �������� ����� ������ ��� ���� ��������� ���� �������� ��� ����� ������� ������� ������� ��� �� ������� ����������� �� ����������� ��� ����������  ������������ �  ����� ������ ����������� ��������� ������� � ��� ����������� ������� �� ��� ������ �������  ������� � ���� �������������� ������ ���� ����� ����� ����������  �������  ������ ������ ����� � ��� ��������� ������� ������� ����� ���� �� ������������ ��� � ������ ��������� ������� �� ����� ���������  ������ ����  �� ����� ������ ������ �������� �� ����� ����� � ��� ������������ ������ ����� �� ���� � ������������ ����������� �� ����� ���� ����� �������� ����� ���� �������������� ���� ����� �� ����������� �� ���� ��� ������  ������ ����� ����� ���� ����� ������ ����� ���������� ������� �������  ������� ������ � ��� ������� �� ���  ��������� ����� �������� ������ ��� � �������������������� ����� ������� ������� ��������� ����� ������� ���������� �� �� ������� ��� ������ ������ ��� ������ ��� ���� �� ����� ��������� �� ����� ������������ ����� ������ ������ � ���� ����������� �������� ������ ������ ������ ������� ����� � ������ ������������� ��� �� ����� �������  �������� ����  �� �� ���������� ����������� � ��� ��� �����  ������ ������ ������ �  � ����� ���� ������������ ��� ��������� �������� ������� � ��� � ���� ����� ��������  ���� ����� ��������  � ��� � �������� �� ����  � ��������� �� ����� ����� ���� ����� ���� ��  ������ ������ � �� ������� �������� ���� �����  ������� ������� ����� ��������� ������������������� � �� ���� ������� ���� �������� �������� ����� ����� �������  ��������� ��������� �� ���  ������� ������� ������ ����� ����� ���� ������� ���������� �  ��������  ������� ������������������� ���� ������� ��� �����  ������������  ����� �� ������� �����������  ����  � ����������� �������� �������� ������������� ���������� � ���������� ���������� � ������������� ���������� ���� �������� ������ ����������� ������ ��� ��� ������� � ���� ���� ������� �� ���� ����� � ����������� ��������� �� �������� �������� �������� ������� ���� �� ��������� �������� ���� �� ��������� ���������� ��� ���� ������� ���� ��� �������� ����� �� ��� � � ���������� ������������ ����� �� ����� �� ������ ����� ��������  ��������� ��������� ���� ������� ������ �����";
	
	buildHuffmanTree(text);

	buildShenonTree(text);
	return 0;
}