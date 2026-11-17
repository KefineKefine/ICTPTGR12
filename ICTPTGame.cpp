// PT
// Naidas, Magnus - S12G

#include <iostream>
#include <windows.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void color(int idx = 7) { SetConsoleTextAttribute(h, idx); }

bool active = true;

class Item {
	public:
		string name = "unknown";
		bool lootable = true; // is recieved by the player if owner dies

};

class Human {
	private:
		const int MAX_HP = 100;
		const int MAX_ST = 50;
		const int MAX_FU = 20;

	public:
		int hp = 100; // health
		int st = 50; // energy
		int fu = 20; // hunger

		Item inventory[6] = {  };

		string name = "unknown";

		void inc_stat(int& stat, int inc, int max_val) { stat = max(0, min(max_val, stat + inc)); }

		void inc_hp(int inc) { inc_stat(hp, inc, MAX_HP); }
		void inc_st(int inc) { inc_stat(st, inc, MAX_ST); }
		void inc_fu(int inc) { inc_stat(fu, inc, MAX_FU); }


		Human(string _name) {
			name = _name;
			
		}
};




void setup() {
	
}

void loop() {
	
}

int main() { setup(); while (active) { loop(); } return 0; }


