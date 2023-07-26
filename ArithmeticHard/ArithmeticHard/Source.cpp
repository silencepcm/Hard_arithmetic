#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;
string int_to_str(int b) {
	int a = b;
	int process;
	string res = {};
	if (a == 0) { res = { "0" }; return res; }
	while (a != 0) {
		process = a % 10;
		switch (process) {
		case 0: res.insert(0, "0"); break;
		case 1: res.insert(0, "1"); break;
		case 2: res.insert(0, "2"); break;
		case 3: res.insert(0, "3"); break;
		case 4: res.insert(0, "4"); break;
		case 5: res.insert(0, "5"); break;
		case 6: res.insert(0, "6"); break;
		case 7: res.insert(0, "7"); break;
		case 8: res.insert(0, "8"); break;
		case 9: res.insert(0, "9"); break;
		}
		a /= 10;
	}
	return res;
}
int char_to_int(char a) {
	int res = 0;
	switch (a) {
	case '0': res = 0; break;
	case '1': res = 1; break;
	case '2': res = 2; break;
	case '3': res = 3; break;
	case '4': res = 4; break;
	case '5': res = 5; break;
	case '6': res = 6; break;
	case '7': res = 7; break;
	case '8': res = 8; break;
	case '9': res = 9; break;
	default: {
		cout << endl << "ERROR CHAR_TO_INT: CHAR \"" << a << "\" IS NOT A DIGIT";
		system("pause");
		break;
	}
	}
	return res;
}
class long_num {
	bool minus = false;
	int index_len = 1;
	vector<long long> num;

	void clear() { num.clear(); minus = false; }
	void resize(int a);
	void new_index_len(int);
	void return_index();
public:
	long_num();
	long_num(string);
	long_num(string, bool);
	long_num(int);
	long_num(long);
	long_num(long long);
	long_num(const long_num&);

	long long& operator [] (long long index) { return num[index]; }
	long long length() { return (long long)num.size(); }
	void push_back(long long a) { num.push_back(a); }
	friend istream& operator>>(istream&, long_num&);
	friend ostream& operator<<(ostream&, long_num);

	long_num& operator = (long long);
	long_num& operator = (const long_num&);

	friend long_num operator + (const long_num&, const long_num&);
	friend long_num operator + (const long_num&, long);
	friend long_num operator - (const long_num&, const long_num&);
	friend long_num operator * (const long_num&, const long_num&);
	friend long_num operator / (const long_num&, const long_num&);
	friend long_num operator % (const long_num&, const long_num&);

	long_num& operator /= (const long_num&);
	long_num& operator %= (const long_num&);
	long_num& operator += (const long_num&);
	long_num& operator -= (const long_num&);
	long_num& operator *= (const long_num&);

	long_num& operator ++() { return *this += 1; }
	long_num& operator --() { return *this -= 1; }
	friend long_num& operator -(long_num&);

	friend bool operator <= (const long_num&, const long_num&);
	friend bool operator < (const long_num&, const long_num&);
	friend bool operator > (const long_num&, const long_num&);
	friend bool operator >= (const long_num&, const long_num&);
	friend bool operator == (const long_num&, const long_num&);

	void insert(int, long long);
	void insert(int, int);
	void erase(long, long);
	void monsterrr_print();
	long_num low_multy(const long_num&);
};

void long_num::resize(int a) {
	if (a < 0) {
		cout << "ERROR SIZE";
		system("pause");
	}
	num.resize(a);
}
void long_num::new_index_len(int b) {
	long_num res;
	res.clear();
	res.minus = minus;
	if (index_len != 1) {
		if (length() > 0)
			for (long long i = length() - 1; i >= 0; --i) {
				long long g = num[i];
				int f = 0;
				while (g > 0) {
					res.insert(0, g % 10);
					g /= 10;
					f++;
				}
				if ((f < index_len) && (i != 0)) for (int j = f; j < index_len; ++j) res.insert(0, 0);
				f = 0;
			}
	}
	if (b != 1) {
		res.index_len = b;
		int p = 1;
		int f = 0;
		long long work = 0;
		for (long long i = length() - 1; i >= 0; --i) {
			work += num[i] * p;
			p *= 10;
			f++;
			if ((f % b == 0) || (i == 0)) {
				res.insert(0, work);
				work = 0;
				p = 1;
			}
		}
	}
	*this = res;
}
void long_num::return_index() {
	long_num res;
	res.clear();
	res.minus = minus;
	for (long long i = length() - 1; i >= 0; --i) {
		long long g = num[i];
		long f = 0;
		while (g > 0) {
			res.insert(0, g % 10);
			g /= 10;
			f++;
		}
		if ((f < index_len) && (i != 0)) for (f; f < index_len; ++f) res.insert(0, 0);
		f = 0;
	}
	*this = res;
}

long_num::long_num() {
	resize(1);
	num[0] = 0;
	minus = false;
}
long_num::long_num(string q) {
	string a = q;
	if (a[0] == '-') {
		minus = true;
		a.erase(0, 1);
	}
	else minus = false;
	num.resize(a.length());
	for (long long i = 0; i < a.length(); ++i) num[i] = (long long)char_to_int(a[i]);
	while ((num[0] == 0) && (num.size() > 1)) { num.erase(num.begin(), num.begin()); }
	if (a.length() == 0) { num.resize(1); num[0] = 0; minus = false; }
}
long_num::long_num(string a, bool b) {
	long_num res(a);
	*this = res;
	if (num[0] != 0)minus = b;
}
long_num::long_num(int a) {
	num.clear();
	minus = false;
	long long b = a;
	if (a < 0) { minus = true; }
	if (a == 0) {
		num.resize(1);
		num[0] = 0;
	}
	else {
		while (b > 0) {
			num.insert(num.begin(), b % 10);
			b /= 10;
		}
	}
}
long_num::long_num(long a) {
	num.clear();
	minus = false;
	long long b = a;
	if (a < 0) { minus = true; }
	if (a == 0) {
		num.resize(1);
		num[0] = 0;
	}
	else {
		while (b > 0) {
			num.insert(num.begin(), b % 10);
			b /= 10;
		}
	}
}
long_num::long_num(long long a) {
	num.clear();
	minus = false;
	long long b = a;
	if (a < 0) { minus = true; b *= -1; }
	if (a == 0) {
		num.resize(1);
		num[0] = 0;
	}
	else {
		while (b > 0) {
			num.insert(num.begin(), b % 10);
			b /= 10;
		}
	}
}
long_num::long_num(const long_num& t) {
	this->minus = t.minus;
	this->num.resize(t.num.size());
	for (long i = 0; i < this->length(); ++i) {
		this->num[i] = t.num[i];
	}
}
istream& operator>>(istream& in, long_num& a) {
	a.num.clear();
	string b;
	in >> b;
	long_num res(b);
	a = res;
	return in;
}
ostream& operator<<(ostream& out, long_num a) {
	if (a.minus) out << "-";
	long long q = 10;
	long long f = 10;
	for (int i = 1; i < a.index_len; ++i) f *= q;
	for (vector< long long>::iterator it = a.num.begin(); it < a.num.end(); ++it) {
		/*	if (*it == 0) for (int i = 0; i < a.index_len; ++i) out << 0; else {
				while (*it * q < f) { out << 0; q *= 10; }
				q = 10;
				out << *it;
			}*/
		out << *it;
	}
	return out;
}

long_num& long_num::operator = (long long a) {
	long_num res(a);
	num = res.num;
	minus = res.minus;
	return *this;
}
long_num& long_num::operator = (const long_num& a) {
	num = a.num;
	minus = a.minus;
	index_len = a.index_len;
	return *this;
}

bool operator > (const long_num& q, const long_num& t) {
	long_num a = q;
	long_num b = t;
	if ((a.minus) && (!b.minus)) return false;
	if ((!a.minus) && (b.minus)) return true;
	if (!a.minus) {
		if (a.length() < b.length()) return false;
		if (a.length() > b.length()) return true;
		for (long i = 0; i < a.length(); ++i) {
			if (a[i] < b[i]) return false;
			if (a[i] > b[i]) return true;
		}
	}
	if (a.minus) {
		if (a.length() < b.length()) return true;
		if (a.length() > b.length()) return false;
		for (long i = 0; i < a.length(); ++i) {
			if (a[i] < b[i]) return true;
			if (a[i] > b[i]) return false;
		}
	}
	return false;
}
bool operator < (const long_num& q, const long_num& t) {
	long_num a = q;
	long_num b = t;
	if ((a.minus) && (!b.minus)) return true;
	if ((!a.minus) && (b.minus)) return false;
	if (!a.minus) {
		if (a.length() < b.length()) return true;
		if (a.length() > b.length()) return false;
		for (long i = 0; i < a.length(); ++i) {
			if (a[i] < b[i]) return true;
			if (a[i] > b[i]) return false;
		}
		return false;
	}
	else {
		if (a.length() < b.length()) return false;
		if (a.length() > b.length()) return true;
		for (long i = 0; i < a.length(); ++i) {
			if (a[i] < b[i]) return false;
			if (a[i] > b[i]) return true;
		}
		return false;
	}
}
bool operator == (const long_num& q, const long_num& t) {
	long_num a = q;
	long_num b = t;
	if (a.length() != b.length()) return false;
	for (long i = 0; i < a.length(); ++i) if (a[i] != b[i]) return false;
	return true;
}
bool operator >= (const long_num& a, const long_num& b) {
	if (a == b || a > b)return true;
	else return false;
}
bool operator <= (const long_num& a, const long_num& b) {
	if (a == b || a < b)return true;
	else return false;
}

long_num low_pow(const long_num& q, long b) {
	long_num a = q;
	long_num res = 1;
	for (long i = 0; i < b; ++i) res = res.low_multy(a);

	return res;
}
long_num pow(const long_num& a, long b0) {
	if (b0 < 0) { cout << "ERROR SECOND PARAMETER < 0, LONG_NUMs ARE INTEGER"; long_num res; return res; }
	if (b0 == 0) { long_num res = 1; return res; }
	long_num t = a;
	long i = 0;
	long b = b0;
	long_num data[400];
	while (b > 0) {
		if (b & 1) data[i++] = t;
		b >>= 1;
		if (!b) break;
		t *= t;
	}
	i--;
	long_num res = 1;
	for (i; i >= 0; i--) {
		res *= data[i];
	}
	if ((a < 0) && (b % 2 == 1)) res *= -1;
	return res;
}
long_num& operator -(long_num& a) {
	if (a.minus) a.minus = false;
	else a.minus = true;
	return a;
}
void swap(long_num& a, long_num& b) {
	long_num res = a;
	a = b;
	b = res;
}

long_num operator + (const long_num& q, const long_num& t) {
	long_num a = q;
	long_num b = t;
	long_num res;
	res.clear();
	if (a.minus != b.minus) {
		if (a.minus == true) {
			a.minus = false;
			return b - a;
		}
		b.minus = false;
		return a - b;
	}
	long long process = 0;
	long long memory = 0;
	long long j = b.length() - 1;
	for (long long i = a.length() - 1; i >= 0; --i) {
		if (j < 0) {
			for (long long k = i; k >= 0; --k) {
				process = a.num[k] + memory;
				memory = process / 10;
				process %= 10;
				res.insert(0, process);
			}
			break;
		}
		process = a.num[i] + b.num[j] + memory;
		memory = process / 10;
		process %= 10;
		res.insert(0, process);
		j--;
	}
	if (j >= 0) {
		for (long long k = j; k >= 0; --k) {
			process = b.num[k] + memory;
			memory = process / 10;
			process %= 10;
			res.insert(0, process);
		}
	}
	if (memory > 0) res.insert(0, memory);
	return res;
}
long_num operator + (long_num& q, long t) {
	long_num a = q;
	long_num b(t);
	return a + b;
}
long_num operator - (const long_num& q, const long_num& t) {
	long_num a = q;
	long_num b = t;
	long_num res;
	res.clear();
	if ((a.minus) && (!b.minus)) {
		a.minus = false;
		res = a + b;
		res.minus = true;
		return res;
	}
	if ((!a.minus) && (b.minus)) {
		b.minus = false;
		res = a + b;
		return res;
	}
	if (a < b) {
		swap(b, a);
		res.minus = true;
	}
	long long process = 0;
	long long memory = 0;
	long long j = b.length() - 1;
	for (long long i = a.length() - 1; i >= 0; --i) {
		if (j < 0) {
			for (long long k = i; k >= 0; --k) {
				process = a[k] - memory;
				if (process < 0) { memory = 1; process += 10; }
				else memory = 0;
				res.insert(0, process);
				if (k == 0) break;
			}
			break;
		}
		process = a[i] - b[j] - memory;
		if (process < 0) { memory = 1; process += 10; }
		else memory = 0;
		res.insert(0, process);
		j--;
		if (i == 0) break;
	}
	while ((res.length() > 1) && (res[0] == 0)) res.erase(0, 0);

	return res;
}
long_num operator * (const long_num& q, const long_num& t) {
	long_num a = q;
	long_num b = t;
	long_num res;
	res.num = {};
	if (a.minus != b.minus) res.minus = true;
	a.minus = false;
	b.minus = false;
	if (a < b) swap(a, b);
	long long memory = 0;
	long long lena = 0;
	long long lenb = 0;
	long long s = 0;
	long long count_len;
	long long r;
	if ((long long)b.length() * (long long)b.index_len > 9999999999999999) {
		cout << "Multiplication ERROR: numbers are too large. If you continue, the function will return the value 0"
			<< endl;
		system("pause");
		res = 0;
		return res;
	}
	else
		if ((long long)b.length() * b.index_len > 9999999999999999) { count_len = 10; r = 1; }
		else
			if ((long long)b.length() * b.index_len > 99999999999999) { count_len = 100; r = 2; }
			else
				if ((long long)b.length() * b.index_len > 999999999999) { count_len = 1000; r = 3; }
				else
					if ((long long)b.length() * b.index_len > 9999999999) { count_len = 10000; r = 4; }
					else
						if ((long long)b.length() * b.index_len > 99999999) { count_len = 100000; r = 5; }
						else
							if ((long long)b.length() * b.index_len > 999999) { count_len = 1000000; r = 6; }
							else
								if ((long long)b.length() * b.index_len > 9999) { count_len = 10000000; r = 7; }
								else
								{
									count_len = 100000000; r = 8;
								}
	if (r != 1) {
		b.new_index_len(r);
		a.new_index_len(r);
		res.index_len = r;
	}
	for (long long i = 0; i < b.length(); ++i) {
		lena = a.length() - 1 - i;
		lenb = b.length() - 1;
		for (long long j = lena; j < a.length(); ++j) {
			s += b[lenb] * a[j];
			lenb--;
		}
		s += memory;
		memory = s / (count_len);
		res.insert(0, s % (count_len));
		s = 0;
	}

	for (long long i = 1; i <= lena; ++i) {
		lenb = b.length() - 1;
		for (long long j = lena - i; j < lena - i + b.length(); ++j) {
			s += b[lenb] * a[j];
			lenb--;
		}
		s += memory;
		memory = s / (count_len);
		res.insert(0, s % (count_len));
		s = 0;
	}


	for (long long i = 1; i < b.length(); ++i) {
		lenb = b.length() - i - 1;
		long long g = lenb;
		for (long long j = 0; j <= lenb; ++j) {
			s += b[j] * a[g];
			g--;
		}
		lenb--;
		s += memory;
		memory = s / (count_len);
		res.insert(0, s % (count_len));
		s = 0;
	}

	if (memory != 0) res.insert(0, memory);
	res.return_index();
	return res;
}



long_num operator / (const long_num& q, const long_num& t) {
	long_num a = q;
	long_num b = t;
	long_num res;
	if (((a.minus) && (!b.minus)) || ((!a.minus) && (b.minus))) res.minus = true;
	a.minus = false;
	b.minus = false;
	if (a < b)  return res;
	if (b == 0) { cout << "ERROR OPERATOR/: b = 0"; return res; }
	long_num process;
	long_num work = 0;
	long i = 0;
	while (process < b) {
		process.push_back(a[i]);
		i++;
	}
	process.erase(0, 1);
	while (i <= a.length()) {
		while (b * work <= process) ++work;
		--work;
		res.push_back(work[0]);
		process -= b * work;
		work = 0;
		if (i < a.length()) process.push_back(a[i]); else break;
		while ((process.length() > 1) && (process[0] == 0)) process.erase(0, 1);
		i++;
	}
	while ((res.length() > 1) && (res[0] == 0)) res.erase(0, 1);
	return res;
}
long_num operator % (const long_num& q, const long_num& t) {
	long_num res;
	long_num a = q;
	long_num b = t;
	res = a / b;
	res *= b;
	if (a.minus) {
		a.minus = false;
		res.minus = false;
		res = a - res;
		res.minus = true;
		return res;
	}
	res = a - res;
	return res;
}
long_num& long_num::operator -= (const long_num& f) {
	long_num a = *this;
	long_num b = f;
	*this = a - b;
	return *this;
}
long_num& long_num::operator+=(const long_num& f) {
	long_num a = *this;
	long_num b = f;
	*this = a + b;
	return *this;
}
long_num& long_num::operator*=(const long_num& f) {
	*this = *this * f;
	return *this;
}
long_num& long_num::operator /= (const long_num& f) {
	long_num a = *this;
	long_num b = f;
	*this = a * b;
	return *this;
}
long_num& long_num::operator %= (const long_num& f) {
	long_num a = *this;
	long_num b = f;
	*this = a % b;
	return *this;
}

long_num long_num::low_multy(const long_num& t) {
	long_num a = *this;
	long_num b = t;
	long_num res;
	res.clear();
	long_num work;
	work.clear();
	long long process = 0;
	long long memory = 0;
	for (long long i = b.length() - 1; i >= 0; --i) {
		for (long f = 0; f < b.length() - i - 1; ++f) {
			work.push_back(0);
		}
		for (long long j = a.length() - 1; j >= 0; --j) {
			process = a[j] * b[i] + memory;
			work.insert(0, process % 10);
			memory = process / 10;
		}
		if (memory != 0) {
			work.insert(0, memory);
			memory = 0;
		}
		while ((work.length() > 1) && (work[0] == 0)) work.erase(0, 1);
		res += work;
		work.clear();
	}
	if (memory != 0) res.insert(0, memory);
	if (a.minus != b.minus) res.minus = true;
	if (res[0] == 0) res.minus = false;
	return res;
}

void long_num::insert(int x, int a) {
	if ((x > length()) || (x < 0)) {
		cout << "INSERT OPERATION ERROR: OUT OF RANGE" << endl << x << length();
		system("pause");
	}
	else
		num.insert(num.begin() + x, (long long)a);
}
void long_num::insert(int x, long long a) {
	if ((x > length()) || (x < 0)) {
		cout << "INSERT OPERATION ERROR: OUT OF RANGE" << endl << x << length();
		system("pause");
	}
	else
		num.insert(num.begin() + x, a);
}
void long_num::erase(long q, long t) {
	long x1 = q;
	long x2 = t;
	if ((x1 > length() - 1) || (x1 < 0) || (x2 > length() - 1) || (x2 < 0)) {
		cout << "ERASE OPERATION ERROR: OUT OF RANGE";
		system("pause");
	}
	else {
		if (x1 > x2) swap(x1, x2);
		num.erase(num.begin() + x1, num.begin() + x2 + 1);
	}
}

void long_num::monsterrr_print() {
	long a = 3 - (length() % 3);
	for (long i = 0; i < length(); ++i) {
		cout << num[i];
		a++;
		if ((a % 3 == 0) && (i < length() - 1)) cout << " ";
	}
}
int main() {
	long_num a;
	int b;
	long_num res, c;
	cout << "Enter number and pow:" << endl;
	a = 3;
	b = 2048;
	int y;
	cout << "Enter count of operations:" << endl;
	y = 10;
	auto begin = chrono::steady_clock::now();
	for (int i = 0; i < y; ++i) res = pow(a, b);
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << res;
	cout << endl << "Time: " << elapsed_ms.count() << " ms\n";
	begin = chrono::steady_clock::now();
	for (int i = 0; i < y; ++i) res = low_pow(a, b);
	end = chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << res;
	cout << endl << "Time: " << elapsed_ms.count() << " ms\n";
	system("pause");
	return 0;
}