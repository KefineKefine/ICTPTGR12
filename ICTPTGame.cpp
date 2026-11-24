// PT
// Naidas, Rubio, Addatu, Santos, Humarang - S12G

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void color(int idx = 7) { SetConsoleTextAttribute(h, idx); }

bool active = true;

void print(string text = "", int color_idx = 7) { color(color_idx); cout << text << "\n"; color(); }

void err(string text = "") { print("ERR: " + text, 4); }

void separator(int n = 15, string s = "=") {
	string a; for (int i = 0; i < n; i++) { a += s; }
	cout << "\n" << a << "\n";
}

class Human {
	private:
		const int MAX_HP = 100;
		const int MAX_ST = 50;
		const int MAX_FU = 20;

	public:
		Human& self = *this;
	
		int hp = 100; // health
		int st = 50; // energy
		int fu = 20; // hunger
		int atk = 10;

		string name = "unknown";

		void inc_stat(int& stat, int inc, int max_val) { stat = max(0, min(max_val, stat + inc)); print(); }

		void state_inc(int inc, string positive, string negative, string unit) { bool c = (inc >= 0); print(name + (c ? positive : negative) + to_string(inc) + " " + unit, (c ? 10 : 4) ); }
		
		void bar_view(int val, int max_val, string name) { cout << name << " BAR : |[[ "; for (int i = 0 ; i < max_val ; i++ ) { cout << ((i < val) ? "X" : "_"); } cout << " ]]|\n\n"; }

		void inc_hp(int inc) { inc_stat(hp, inc, MAX_HP); state_inc(inc, " was healed +", " was hurt ", "HP"); bar_view(hp, MAX_HP, "HEALTH"); }
		void inc_st(int inc) { inc_stat(st, inc, MAX_ST); state_inc(inc, " had rested +", " has been tired ", "ST"); bar_view(st, MAX_ST, "STAMINA"); }
		void inc_fu(int inc) { inc_stat(fu, inc, MAX_FU); state_inc(inc, " was fed +", " got hungry ", "FU"); bar_view(fu, MAX_FU, "FULLNESS"); }

		void hurt(Human attacker, bool p = true) {
			if (p) { print(attacker.name + " attacked " + name); }
			inc_hp(-attacker.atk);
		}

		Human(string _name, int ihp = 100, int ist = 50, int ifu = 20, int iatk = 10) {
			name = _name; hp = ihp; st = ist; fu = ifu; atk = iatk;
			
		}
};

class Zombie: public Human {
	public:
		
		void bite(Human human) {
			print("Zombie " + name + " attacked " + human.name);
			human.hurt(self, false);
		}
};

void general_print(string header = "HEADER", string text = "text", int hci = 7, int tci = 7, int sl = 15, string ss = "=") {
	separator(sl, ss); print();
	print("=== " + header + " ===\n", hci);
	print(text, tci);
	separator(sl, ss);
	print();
}

void input_pause() { print("Input '0' to proceed."); int buffer; cin >> buffer; }

void query_print(string header = "decision", string text = "result") { general_print( header, text, 4, 7, 15, "-" ); }

void decision_print(string header = "decision", string text = "result") { general_print( header, text, 8, 7, 10, "-" ); input_pause(); }

int chapter = 0;

void setup() {
	int choice = -1; // inputbuffer n selection
	while (choice == -1 || chapter == 0) {
		print();
		general_print(
			"3 DAYS BEFORE RESCUE",
			"1 - START\n2 - TUTORIAL\n3 - EXIT",
			3,
			7,
			30
		);
		
		cin >> choice;
		switch (choice) {
			case 1:
				chapter = 1;
				break;
			case 2:
			
				separator();

				general_print(
					"OBJECTIVE",
					"Your mission is to survive for three days until the rescue team arrives. Make smart decisions to avoid danger and stay alive.",
					7, 8, 3, "-"
				);

				general_print(
					"PLAYER ATTRIBUTES",
					"You have three survival attributes:\nHEALTH - Represents your physical condition and life. (100 HP)\nSTAMINA - Represents your energy and ability to perform activities. (50 ST)\nHUNGER - Represents your ability to stay nourished. (20 FU)",
					7, 8, 3, "-"
				);

				general_print(
					"DECISION MAKING",
					"Each scene presents a situation with multiple choices. Read the scenario carefully and select the option you think is best. Wrong choices lead to a deduction of points from either Health, Stamina, and/or Hunger.",
					7, 8, 3, "-"
				);

				general_print(
					"GAME OVER CONDITION",
					"If health reaches zero, the player dies. If hunger reaches zero, 5 health points are deducted per-next scenario. If stamina reaches zero, certain strenuous actions cannot be performed which may lead to deduction of health points.",
					7, 8, 3, "-"
				);

				general_print(
					"MULTIPLE ENDINGS",
					"Your decisions determine your fate. Survive until the rescue team arrives to complete your mission. You may also encounter different endings depending on your actions.",
					7, 8, 3, "-"
				);

				separator();

				print("\nGOOD LUCK, SURVIVOR!\nRemember, every decision matters. Choose wisely, manage your points, and stay alive!\n");
				
				input_pause();

				choice = -1;
				break;
			case 3:
				active = false;
				chapter = -2;
				break;
			default:
				err("Enter a valid index.");
				break;
		}
	}

	

}

string choice_formatting(string desc, string c1, string c2, string c3) {
	return (desc + "\n\n1 - " + c1 + "\n2 - " + c2 + "\n3 - " + c3 + "\n\n");
}

int query_buffer() {
	int ib;
	while (true) { cin >> ib; if (ib > 0 && ib < 4) { return ib; } else { err("Enter a valid choice."); } }
}


int main() {

	

	setup();

	general_print(
		"Name your PLAYER",
		"Provide your vessel a name so that it may be referred to that way.",
		2, 8, 30, "-"
	);

	string pname;
	cin >> pname;

	Human player(pname);

	while (active) {
		switch (chapter) {
			case 1:
			
				// the beginning
				
				query_print(
					"October 24, 2026 - 6:30am",
					choice_formatting(
						"You, " + pname + ", wake up to the sound of screaming and alarms. You are one of five participants in an experimental study conducted by a scientist developing a potential cure for the Hantavirus. Unfortunately, the experiment failed for the other four participants. They developed severe neurological complications, became aggressive, and transformed into zombie-like creatures. You were the only successful subject.\n\nOne of the infected escaped containment and attacked the facility's personnel, spreading the outbreak throughout the building. You hear footsteps and screams outside your room. Something is terribly wrong.\n\nWhat will you do?",
						"Peek through the hallway.", "Barricade your room", "Immediately leave your room"
					)
				);

				switch (query_buffer()) {
					case 1:
						player.inc_st(-5);
					
						decision_print(
							"Peek through the hallway.",
							"You crack the door open just enough to see down the corridor. Two infected test subjects are tearing into a security guard at the far end, completely distracted. You slip out quietly into the opposite hallway, avoiding their notice."
						);
						
						

						break;
					//default:
						// theoretically it should never reach here due to query_buffer(), so just never add the default case
						//break;
				}

				break;

			case 2:
				break;
		}

		
		print("end of the line");
	}
	
	return 0;
}


